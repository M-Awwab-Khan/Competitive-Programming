t = int(input())
while t:
    t -= 1
    name, study, birth, courses = input().split()
    study = int(study[:4])
    birth = int(birth[:4])
    courses = int(courses)
    if study >= 2010 or birth >= 1991:
        print(f"{name} eligible")
    elif courses > 40:
        print(f"{name} ineligible")
    else:
        print(f"{name} coach petitions")
