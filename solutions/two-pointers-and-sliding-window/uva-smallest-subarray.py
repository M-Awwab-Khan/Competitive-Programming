def find_smallest_subsequence_length(N, K, sequence):
    from collections import defaultdict

    # Frequency map to keep track of occurrences of integers in [1, K]
    freq_map = defaultdict(int)

    # Start of sliding window
    left = 0

    # Number of unique integers from [1, K] found in the current window
    unique_count = 0

    # Minimum length of the subsequence
    min_length = float("inf")

    for right in range(N):
        # Add the current number to the frequency map
        num = sequence[right]
        if 1 <= num <= K:
            if freq_map[num] == 0:
                unique_count += 1
            freq_map[num] += 1

        # Check if the current window contains all integers from [1, K]
        while unique_count == K:
            # Update the minimum length
            min_length = min(min_length, right - left + 1)

            # Remove the leftmost element from the window
            left_num = sequence[left]
            if 1 <= left_num <= K:
                freq_map[left_num] -= 1
                if freq_map[left_num] == 0:
                    unique_count -= 1
            left += 1

    return min_length if min_length != float("inf") else -1


def generate_sequence(N, M):
    sequence = [0] * N
    sequence[0], sequence[1], sequence[2] = 1, 2, 3
    for i in range(3, N):
        sequence[i] = (sequence[i - 1] + sequence[i - 2] + sequence[i - 3]) % M + 1
    return sequence


def main():
    T = int(input())
    results = []

    for t in range(1, T + 1):
        N, M, K = map(int, input().split())
        sequence = generate_sequence(N, M)
        min_length = find_smallest_subsequence_length(N, M, K, sequence)

        if min_length == -1:
            results.append(f"Case {t}: sequence nai")
        else:
            results.append(f"Case {t}: {min_length}")

    print("\n".join(results))


if __name__ == "__main__":
    main()
