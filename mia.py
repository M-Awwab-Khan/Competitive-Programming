# while True:
#     s0, s1, r0, r1 = map(int, input().split())
#     if s0 == 0 and s1 == 0 and r0 == 0 and r1 == 0:
#         break


#     if (s0 == 1 and s1 == 2) or (s0 == 2 and s1 == 1):
#         if (r0 == 1 and r1 == 2) or (r0 == 2 and r1 == 1):
#             print("Tie.")
#         else:
#             print("Player 1 wins.")
#     elif (r0 == 1 and r1 == 2) or (r0 == 2 and r1 == 1):
#         print("Player 2 wins.")
#     elif s0 == s1 and r0 == r1:
#         if s0 == r0:
#             print("Tie.")
#         elif s0 > r0:
#             print("Player 1 wins.")
#         else:
#             print("Player 2 wins.")
#     elif s0 == s1:
#         print("Player 1 wins.")
#     elif r0 == r1:
#         print("Player 2 wins.")
#     else:
#         if s0 + s1 > r0 + r1:
#             print("Player 1 wins.")
#         elif s0 + s1 < r0 + r1:
#             print("Player 2 wins.")
#         else:
#             print("Tie.")
def get_score(d1, d2):
    # Special case: Mia (21)
    if (d1 == 2 and d2 == 1) or (d1 == 1 and d2 == 2):
        return 1000

    # Doubles
    if d1 == d2:
        return d1 * 100

    # Regular rolls - make largest number
    return max(d1, d2) * 10 + min(d1, d2)


while True:
    s0, s1, r0, r1 = map(int, input().split())
    if s0 == 0 and s1 == 0 and r0 == 0 and r1 == 0:
        break

    score1 = get_score(s0, s1)
    score2 = get_score(r0, r1)

    if score1 > score2:
        print("Player 1 wins.")
    elif score2 > score1:
        print("Player 2 wins.")
    else:
        print("Tie.")
