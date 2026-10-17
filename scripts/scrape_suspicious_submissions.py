import requests
from bs4 import BeautifulSoup
from collections import defaultdict
import re

# List of submission URLs
submission_links = [
    "https://vjudge.net/solution/64906569",
    "https://vjudge.net/solution/64906625",
    "https://vjudge.net/solution/64906666",
    "https://vjudge.net/solution/64906737",
    "https://vjudge.net/solution/64906758",
    "https://vjudge.net/solution/64906785",
    "https://vjudge.net/solution/64906800",
    "https://vjudge.net/solution/64906907",
    "https://vjudge.net/solution/64906965",
    "https://vjudge.net/solution/64906981",
    "https://vjudge.net/solution/64907009",
    "https://vjudge.net/solution/64907052",
    "https://vjudge.net/solution/64907057",
    "https://vjudge.net/solution/64907110",
    "https://vjudge.net/solution/64907111",
    "https://vjudge.net/solution/64907146",
    "https://vjudge.net/solution/64907181",
    "https://vjudge.net/solution/64907250",
    "https://vjudge.net/solution/64907324",
    "https://vjudge.net/solution/64907339",
    "https://vjudge.net/solution/64907345",
    "https://vjudge.net/solution/64907373",
    "https://vjudge.net/solution/64907379",
    "https://vjudge.net/solution/64907402",
    "https://vjudge.net/solution/64907406",
    "https://vjudge.net/solution/64907439",
    "https://vjudge.net/solution/64907441",
    "https://vjudge.net/solution/64907491",
    "https://vjudge.net/solution/64907535",
    "https://vjudge.net/solution/64907548",
    "https://vjudge.net/solution/64907557",
    "https://vjudge.net/solution/64907567",
    "https://vjudge.net/solution/64907578",
    "https://vjudge.net/solution/64907583",
    "https://vjudge.net/solution/64907599",
    "https://vjudge.net/solution/64907612",
    "https://vjudge.net/solution/64907619",
    "https://vjudge.net/solution/64907620",
    "https://vjudge.net/solution/64907648",
    "https://vjudge.net/solution/64907756",
    "https://vjudge.net/solution/64907773",
    "https://vjudge.net/solution/64907828",
]

user_submissions = defaultdict(list)

for url in submission_links:
    try:
        r = requests.get(url, timeout=10)
        r.raise_for_status()
        soup = BeautifulSoup(r.text, "html.parser")

        # Extract <meta property="og:title" content="username's code - Virtual Judge">
        meta_tag = soup.find("meta", {"property": "og:title"})
        if not meta_tag or "content" not in meta_tag.attrs:
            print(f"[!] Username not found on {url}")
            continue

        meta_content = meta_tag["content"]
        match = re.match(r"(.+?)'s code", meta_content)
        if match:
            username = match.group(1).strip()
            user_submissions[username].append(url)
            print(f"[+] {username} -> {url}")
        else:
            print(f"[!] Could not parse username from meta tag on {url}")

    except Exception as e:
        print(f"[Error] {url}: {e}")

# Print results
print("\n\n===== Final Mapping =====")
for user, links in user_submissions.items():
    print(f"{user}:")
    for link in links:
        print(f"  - {link}")
