import os
import sys
from io import BytesIO, IOBase

sys.setrecursionlimit(300000)
sys.set_int_max_str_digits(1000001)

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

MOD = 998244353

def build_max_number(n, s):
    digits = []
    for _ in range(n):
        take = min(9, s)
        digits.append(str(take))
        s -= take
    return int("".join(digits))

def solve():
    n, s = map(int, input().split())
    if  (s < 2 and n == 1):
        print(0)
        return
    
    if ((s < 2) or (s > 18 * n)):
        print(-1)
        return
    
    s1 = s // 2
    s2 = s - s1
    
    x = build_max_number(n, s1)
    y = build_max_number(n, s2)
    
    print((x % MOD) * (y % MOD) % MOD)


if __name__ == "__main__":
    t = int(input())
    while t:
        t -= 1
        solve()