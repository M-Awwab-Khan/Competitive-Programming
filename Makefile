.DEFAULT_GOAL := help
ifeq ($(OS),Windows_NT)
PYTHON ?= python
else
PYTHON ?= python3
endif
NAME :=
LANG ?= cpp
# LANG is normally a locale inherited from the shell, not a language choice.
ifeq ($(origin LANG),environment)
LANG := cpp
endif
SOURCE :=
PCH ?= 1
RUN_TIMEOUT ?= 5
DEBUG ?= 0
SAMPLE ?=
INPUT ?=
EXPECTED ?=
export CP_DEBUG := $(DEBUG)
export CP_SAMPLE := $(SAMPLE)
export CP_INPUT := $(INPUT)
export CP_EXPECTED := $(EXPECTED)
export CP_NAME := $(NAME)
export CP_LANG := $(LANG)
export CP_SOURCE := $(SOURCE)
export CP_PCH := $(PCH)
export CP_RUN_TIMEOUT := $(RUN_TIMEOUT)
export CP_FILE :=
export CXX
export CPPFLAGS
export CXXFLAGS

# Make treats positional filenames as targets. Consume exactly one filename for
# problem commands, without a catch-all rule that would hide misspelled targets.
problem_actions := $(filter new build run check debug samples sample-add,$(MAKECMDGOALS))
ifneq ($(strip $(problem_actions)),)
ifneq ($(words $(problem_actions)),1)
$(error Use one problem command per invocation: make run problem.cpp)
endif
problem_files := $(filter-out $(problem_actions),$(MAKECMDGOALS))
ifneq ($(strip $(problem_files)),)
ifneq ($(words $(problem_files)),1)
$(error Supply exactly one filename: make new problem.cpp)
endif
ifeq ($(filter %.cpp %.py,$(problem_files)),)
$(error Expected a .cpp or .py filename: make new problem.cpp)
endif
export CP_FILE := $(problem_files)
.PHONY: $(problem_files)
$(problem_files):
	@:
endif
endif

.PHONY: help new build run check debug samples sample-add pch ingest ingest-apply lint companion drill drill-stats drill-weak
companion:
	@$(PYTHON) scripts/companion.py
help:
	@$(PYTHON) scripts/problem.py help
new build run check debug samples sample-add pch:
	@$(PYTHON) scripts/problem.py $@
ingest:
	@$(PYTHON) scripts/ingest.py
ingest-apply:
	@$(PYTHON) scripts/ingest.py --apply
lint:
	@$(PYTHON) scripts/lint_repo.py
# Spaced-repetition review: make drill [NEW=10] [PATTERN=dsu-variants]
NEW ?= 10
PATTERN ?=
drill:
	@$(PYTHON) scripts/drill.py --new $(NEW) $(if $(PATTERN),--pattern $(PATTERN))
drill-stats:
	@$(PYTHON) scripts/drill.py --stats
drill-weak:
	@$(PYTHON) scripts/drill.py --weak
