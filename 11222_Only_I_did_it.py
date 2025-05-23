import os
import sys
from io import BytesIO, IOBase

sys.setrecursionlimit(300000)

BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


def print(*args, **kwargs):
    sep = kwargs.pop("sep", " ")
    end = kwargs.pop("end", "\n")
    flush = kwargs.pop("flush", False)
    sys.stdout.write(sep.join(map(str, args)) + end)
    if flush:
        sys.stdout.flush()


def solve():
    
    t = int(input())
    for tc in range(1, t + 1):

        st = []
        for i in range(3):
            s = ""
            while len(s) == 0:
                s = input()
            
            st.append([int(i) for i in s.split()][1:])

        a, b, c = st

        a_set = set(a)
        b_set = set(b)
        c_set = set(c)

        # Problems solved uniquely by each contestant
        ass = a_set - (b_set | c_set)
        bs = b_set - (a_set | c_set)
        cs = c_set - (a_set | b_set)

        ans = [sorted(list(ass)), sorted(list(bs)), sorted(list(cs))]

        max_len = max(len(ans[0]), len(ans[1]), len(ans[2]))
        
        print(f"Case #{tc}:")

        for i in range(3):
            if len(ans[i]) == max_len:
                print(i + 1, len(ans[i]), *ans[i])






if __name__ == "__main__":
    solve()