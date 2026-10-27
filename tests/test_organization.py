"""Integration checks for source preservation and organizer decisions in isolated repos."""
import copy
import hashlib
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

REPO = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(REPO / 'scripts'))
import organization
from ingest import plan
from lint_repo import lint


class OrganizationTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='cp-organizer-test-')
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for folder in ['scripts','catalog','notes/patterns','practice/inbox']:
            (self.root / folder).mkdir(parents=True)
        for source in (REPO / 'scripts').glob('*.py'):
            (self.root / 'scripts' / source.name).write_bytes(source.read_bytes())
        for source in (REPO / 'notes/patterns').glob('*.md'):
            (self.root / 'notes/patterns' / source.name).write_bytes(source.read_bytes())
        # Keep the linked reference self-contained instead of copying archive examples.
        guide_dir = self.root / 'notes/contest-prep'
        guide_dir.mkdir()
        (guide_dir / 'div3-speed-programming.md').write_text(
            '# Contest reference\n\n<!-- snippet:fixture -->\n```cpp\n'
            'inline int fixture() { return 1; }\n```\n')
        from build_sp_reference import render as render_reference
        header = self.root / 'templates/cpp/sp-reference.hpp'
        header.parent.mkdir(parents=True)
        header.write_text(render_reference(self.root)[0])
        original = organization.read_catalog()
        self.write_catalog(dict(schema_version=2, categories=original['categories'], problems=[]))
        (self.root / 'catalog/patterns.json').write_bytes((REPO / 'catalog/patterns.json').read_bytes())
        event = dict(id='initial',time='2026-10-17T00:00:00+00:00',operation='SETUP',changes=[])
        (self.root / 'catalog/events.jsonl').write_text(json.dumps(event)+'\n')
        (self.root / '.gitignore').write_text('__pycache__/\n*.organize-tmp\ncatalog/.organize.lock\n')
        (self.root / 'README.md').write_text('# Test repository\n')
        self.tool('build_catalog.py')

    def tool(self, name, *args, success=True):
        result = subprocess.run([sys.executable, 'scripts/' + name, *args], cwd=self.root, text=True, capture_output=True)
        if success:
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        else:
            self.assertNotEqual(result.returncode, 0, result.stdout + result.stderr)
        return result

    def source(self, name='work.py', text='print(1)\n'):
        path = self.root / 'practice/inbox' / name
        path.write_text(text)
        return path

    def catalog(self):
        return organization.read_catalog(self.root)

    def write_catalog(self, catalog):
        (self.root / 'catalog/problems.json').write_text(organization.json_text(catalog))

    def filed(self, name='work.py', category='math/arithmetic', text='print(1)\n'):
        source = self.source(name, text)
        self.tool('add_solution.py', str(source), '--category', category)
        return next(p for p in self.catalog()['problems'] if Path(p['path']).name == name)

    def test_preview_is_nonmutating_and_repeated_ingestion_is_idempotent(self):
        source = self.source()
        before = (self.root / 'catalog/problems.json').read_bytes()
        events = (self.root / 'catalog/events.jsonl').read_bytes()
        self.tool('ingest.py')
        self.assertTrue(source.exists())
        self.assertEqual(before, (self.root / 'catalog/problems.json').read_bytes())
        self.assertEqual(events, (self.root / 'catalog/events.jsonl').read_bytes())
        self.tool('ingest.py', '--apply')
        self.assertFalse(source.exists())
        record = self.catalog()['problems'][0]
        self.assertEqual((self.root / record['path']).read_text(), 'print(1)\n')
        once = (self.root / 'catalog/events.jsonl').read_bytes()
        result = self.tool('ingest.py', '--apply')
        self.assertIn('0 change(s)', result.stdout)
        self.assertEqual(once, (self.root / 'catalog/events.jsonl').read_bytes())

    def test_filename_collision_preserves_both_attempts(self):
        self.source(text='print(1)\n'); self.tool('ingest.py', '--apply')
        self.source(text='print(2)\n'); self.tool('ingest.py', '--apply')
        records = self.catalog()['problems']
        self.assertEqual(len(records), 2)
        self.assertEqual(len({p['path'] for p in records}), 2)
        self.assertEqual({(self.root / p['path']).read_text() for p in records}, {'print(1)\n','print(2)\n'})

    def test_changed_reviewed_source_keeps_decision_and_stays_in_review_queue(self):
        original = self.filed()
        path = self.root / original['path']; path.write_text('print(2)\n')
        self.tool('ingest.py', '--apply')
        current = self.catalog()['problems'][0]
        for field in ['path','category','tags','classification_status','classification_evidence','classification_sha256']:
            self.assertEqual(current[field],original[field])
        self.assertTrue(current['review_required'])
        self.assertNotEqual(current['observed_sha256'],current['classification_sha256'])
        self.assertIn('Source changed', (self.root / 'catalog/REVIEW.md').read_text())
        self.assertIn('stale-classification', [e['code'] for e in lint(self.root)['warnings']])
        self.assertIn('0 change(s)',self.tool('ingest.py','--apply').stdout)

    def test_explicit_review_moves_source_and_locks_new_decision(self):
        previous = self.filed()
        data = (self.root / previous['path']).read_bytes()
        self.tool('review_solution.py','work.py','--category','simulation','--evidence','Direct output simulation','--apply')
        current = self.catalog()['problems'][0]
        self.assertTrue(current['classification_locked'])
        self.assertEqual(current['path'],'solutions/simulation/work.py')
        self.assertEqual((self.root / current['path']).read_bytes(),data)
        self.assertEqual(current['original_sha256'],previous['original_sha256'])
        self.assertEqual(current['original_path'],previous['original_path'])
        self.assertEqual(json.loads((self.root/'catalog/events.jsonl').read_text().splitlines()[-1])['operation'],'REVIEW')

    def test_automatic_changed_source_can_be_reclassified(self):
        self.source();self.tool('ingest.py','--apply')
        p=self.catalog()['problems'][0]
        (self.root/p['path']).write_text('dp = [0] * 3\nfor i in range(1, 3):\n    dp[i] = dp[i-1] + 1\n')
        self.tool('ingest.py','--apply')
        p=self.catalog()['problems'][0]
        self.assertEqual(p['category'],'dynamic-programming/general')
        self.assertEqual(p['classification_status'],'suggested')
        self.assertEqual(p['classification_sha256'],p['observed_sha256'])

    def test_historical_basename_does_not_grant_reviewed_status(self):
        self.source('B_Fence.cpp','int main(){ int dp[3]; dp[0]=0; dp[1]=dp[0]+1; }\n')
        self.tool('ingest.py','--apply')
        p=self.catalog()['problems'][0]
        self.assertEqual(p['classification_status'],'suggested')
        self.assertFalse(p['classification_locked'])
        self.assertEqual(p['category'],'dynamic-programming/general')

    def test_bad_tags_and_patterns_leave_source_and_catalog_unchanged(self):
        source=self.source()
        baseline=(self.root/'catalog/problems.json').read_bytes()
        self.tool('add_solution.py',str(source),'--category','math/arithmetic','--tags','invalid',success=False)
        self.tool('add_solution.py',str(source),'--category','math/arithmetic','--pattern','invalid',success=False)
        self.assertTrue(source.exists())
        self.assertEqual(baseline,(self.root/'catalog/problems.json').read_bytes())

    def test_failure_after_move_rolls_back_metadata_and_source(self):
        source=self.source()
        catalog,changes,_=plan(self.catalog(),self.root)
        baseline=(self.root/'catalog/problems.json').read_bytes()
        events=(self.root/'catalog/events.jsonl').read_bytes()
        with patch('build_catalog.render',side_effect=ValueError('render failure')):
            with self.assertRaisesRegex(ValueError,'render failure'):
                with organization.lock(self.root):
                    organization.apply(catalog,changes,'INGEST',self.root)
        self.assertEqual(source.read_text(),'print(1)\n')
        self.assertEqual(baseline,(self.root/'catalog/problems.json').read_bytes())
        self.assertEqual(events,(self.root/'catalog/events.jsonl').read_bytes())
        self.assertFalse((self.root/'catalog/.organize-journal.json').exists())

    def test_existing_journal_blocks_apply_and_is_preserved(self):
        source=self.source()
        journal=self.root/'catalog/.organize-journal.json';journal.write_text('{}\n')
        self.tool('ingest.py','--apply',success=False)
        self.assertEqual(journal.read_text(),'{}\n')
        self.assertTrue(source.exists())

    def test_cph_samples_survive_source_move(self):
        source=self.source()
        record=source.parent/'.cph/local.prob';record.parent.mkdir()
        tests=[dict(input='8\n',output='YES\n',id=1)]
        record.write_text(json.dumps(dict(srcPath=str(source),url=str(source),tests=tests)))
        self.tool('ingest.py','--apply')
        filed=self.root/self.catalog()['problems'][0]['path']
        records=list((filed.parent/'.cph').glob('*.prob'))
        self.assertEqual(len(records),1)
        current=json.loads(records[0].read_text())
        self.assertEqual(current['srcPath'],str(filed))
        self.assertEqual(current['tests'],tests)
        self.assertFalse(record.exists())

    def test_lint_detects_coverage_schema_links_and_stale_navigation(self):
        self.filed()
        p=self.root/'solutions/math/arithmetic/unindexed.py';p.write_text('print(2)\n')
        self.assertIn('uncataloged-sources',[e['code'] for e in lint(self.root)['errors']]);p.unlink()
        data=self.catalog();data['problems'][0]['tags'].append('unknown');self.write_catalog(data)
        self.assertIn('record-schema',[e['code'] for e in lint(self.root)['errors']])
        data['problems'][0]['tags'].remove('unknown');self.write_catalog(data)
        (self.root/'README.md').write_text('[Broken](missing.md)\n')
        self.assertIn('broken-link',[e['code'] for e in lint(self.root)['errors']])
        (self.root/'README.md').write_text('# Test repository\n')
        (self.root/'catalog/INDEX.md').write_text('stale\n')
        self.assertIn('stale-navigation',[e['code'] for e in lint(self.root)['errors']])

    def test_companion_metadata_ingestion_and_explicit_overrides(self):
        workspace = self.root / 'practice/inbox/Number_of_Ways'
        workspace.mkdir()
        source = workspace / 'Number_of_Ways.cpp'
        source.write_text('int main() {return 0;}\n')
        payload = dict(name='Y. Number of Ways', group='Codeforces - Sheet 7',
                       url='https://codeforces.com/group/example/contest/223339/problem/Y',
                       timeLimit=1000, memoryLimit=256, interactive=False, tests=[])
        (workspace / 'problem.json').write_text(json.dumps(payload))
        self.tool('ingest.py', str(source), '--apply')
        record = self.catalog()['problems'][0]
        self.assertEqual(record['title'], 'Number of Ways')
        self.assertEqual((record['platform'], record['problem_id']), ('codeforces', '223339Y'))
        self.assertEqual(record['urls'], [payload['url']])
        self.assertEqual(record['collections'], ['Codeforces - Sheet 7'])
        self.assertEqual(record['time_limit_ms'], 1000)
        self.assertEqual(record['memory_limit_mb'], 256)
        self.assertFalse(record['interactive'])
        self.assertEqual(record['implementation_status'], 'not-verified')
        self.assertEqual((workspace / 'problem.json').read_text(), json.dumps(payload))
        source = workspace / 'another.cpp'
        source.write_text('int main() {}\n')
        self.tool('add_solution.py', str(source), '--category', 'simulation',
                  '--title', 'Explicit title', '--platform', 'custom', '--id', 'explicit')
        record = self.catalog()['problems'][1]
        self.assertEqual(record['title'], 'Explicit title')
        self.assertEqual((record['platform'], record['problem_id']), ('custom', 'explicit'))

    def test_companion_vjudge_unknown_identity_and_bad_metadata(self):
        workspace = self.root / 'practice/inbox/divisor'
        workspace.mkdir()
        source = workspace / 'divisor.py'
        source.write_text('print(1)\n')
        metadata = workspace / 'problem.json'
        metadata.write_text(json.dumps(dict(name='k-th divisor',
                                            url='https://vjudge.net/problem/CodeForces-762A')))
        self.tool('ingest.py', str(source), '--apply')
        record = self.catalog()['problems'][0]
        self.assertEqual((record['platform'], record['problem_id']), ('vjudge', 'CodeForces-762A'))
        source = workspace / 'unknown.py'
        source.write_text('print(2)\n')
        metadata.write_text(json.dumps(dict(name='Unknown', url='https://example.org/task/12')))
        self.tool('ingest.py', str(source), '--apply')
        record = self.catalog()['problems'][1]
        self.assertIsNone(record['platform'])
        self.assertIsNone(record['problem_id'])
        source = workspace / 'bad.py'
        source.write_text('print(3)\n')
        before = (self.root / 'catalog/problems.json').read_bytes()
        metadata.write_text('{broken')
        self.tool('ingest.py', str(source), '--apply', success=False)
        self.assertTrue(source.is_file())
        self.assertEqual(before, (self.root / 'catalog/problems.json').read_bytes())

    def test_shared_problem_ids_are_information_and_not_deleted(self):
        for name in ['a.py','b.py']:
            source=self.source(name,'print('+str(len(name))+')\n')
            self.tool('add_solution.py',str(source),'--category','math/arithmetic','--platform','codeforces','--id','1A')
        report=lint(self.root)
        self.assertFalse(report['errors'])
        self.assertIn('shared-problem-id',[e['code'] for e in report['information']])
        self.assertEqual(len(self.catalog()['problems']),2)

    def test_pattern_examples_refresh_without_overwriting_authored_notes(self):
        source=self.source()
        self.tool('add_solution.py',str(source),'--category','math/arithmetic','--pattern','prefix-sum-frequency-map')
        note=self.root/'notes/patterns/prefix-sum-frequency-map.md'
        self.assertIn('work',note.read_text())
        note.write_text(note.read_text().replace('## Recognition clues','A personal observation.\n\n## Recognition clues'))
        self.tool('build_catalog.py')
        self.assertIn('A personal observation.',note.read_text())
        found=json.loads(self.tool('search.py','--pattern','prefix-sum-frequency-map','--json').stdout)
        self.assertEqual(len(found),1)

    def test_malformed_record_and_event_are_reported_without_crashing(self):
        self.filed()
        original=self.catalog()
        broken=copy.deepcopy(original);broken['problems'].append(None);self.write_catalog(broken)
        self.assertIn('record-schema',[e['code'] for e in lint(self.root)['errors']])
        self.write_catalog(original)
        with (self.root/'catalog/events.jsonl').open('a') as handle:
            handle.write('null\n')
        self.assertIn('event-log',[e['code'] for e in lint(self.root)['errors']])

    def test_json_apply_outputs_one_machine_readable_result(self):
        self.source()
        result=json.loads(self.tool('ingest.py','--json','--apply').stdout)
        self.assertTrue(result['applied'])
        self.assertEqual(len(result['changes']),1)

    def test_staged_lint_checks_index_instead_of_worktree(self):
        p=self.filed()
        subprocess.run(['git','init','-q'],cwd=self.root,check=True)
        subprocess.run(['git','add','-A'],cwd=self.root,check=True)
        self.tool('lint_repo.py','--staged')
        (self.root/p['path']).write_text('print(99)\n')
        self.tool('lint_repo.py','--staged')
        self.tool('review_solution.py','work.py','--category','simulation','--evidence','Changed process','--apply')
        subprocess.run(['git','add','solutions'],cwd=self.root,check=True)
        self.tool('lint_repo.py','--staged',success=False)


if __name__ == '__main__':
    unittest.main()
