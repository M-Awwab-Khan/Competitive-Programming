def maximize_bananas(t, test_cases):
    results = []
    for a, b, c in test_cases:
        for _ in range(5):
            max_product = a * b * c
            ai = (a + 1) * b * c
            bi = a * (b + 1) * c
            ci = a * b * (c + 1)
            if (bi <= ai >= ci):
                a += 1
                max_product = ai
            elif (ai <= bi >= ci):
                b += 1
                max_product = bi

            elif (ai <= ci >= bi):
                c += 1
                max_product = ci
        results.append(max_product)

    return results

t = int(input())
test_cases = [tuple(map(int, input().split())) for _ in range(t)]

results = maximize_bananas(t, test_cases)
print('\n'.join(map(str, results)))
