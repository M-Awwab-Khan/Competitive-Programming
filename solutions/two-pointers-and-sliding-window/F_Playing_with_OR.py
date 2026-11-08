import sys

input = sys.stdin.read


def count_odd_or_subarrays(n, k, array):
    odd_count = 0
    # Count the number of odds in the first window
    current_odd = sum(1 for i in range(k) if array[i] % 2 == 1)
    if current_odd > 0:
        odd_count += 1

    # Sliding window over the array
    for i in range(k, n):
        # Slide the window: Remove the first element and add the next element
        if array[i - k] % 2 == 1:
            current_odd -= 1
        if array[i] % 2 == 1:
            current_odd += 1
        # If there is at least one odd in the current window, increase the count
        if current_odd > 0:
            odd_count += 1

    return odd_count


def main():
    # Reading all input at once for efficiency
    data = input().split()
    T = int(data[0])
    index = 1
    result = []

    for _ in range(T):
        n = int(data[index])
        k = int(data[index + 1])
        index += 2
        array = list(map(int, data[index : index + n]))
        index += n
        result.append(str(count_odd_or_subarrays(n, k, array)))

    # Print all results at once
    sys.stdout.write("\n".join(result) + "\n")


if __name__ == "__main__":
    main()
