import os
from pathlib import Path
from datetime import datetime, timezone
from collections import defaultdict

import urllib.request
import json

def normalize(name: str) -> str:
    """Convert any folder name to a consistent lowercase lookup key."""
    return name.lower().replace("_", " ").replace("-", " ").strip().rstrip(".")
    
def fetch_leetcode_stats(username: str) -> dict:
    """Stats are derived from the repo scan — no external API needed.
    Live stats are handled by the leetcard widget in the README.
    """
    return {"total": 0, "easy": 0, "medium": 0, "hard": 0, "streak": 0}

# ── Config ─────────────────────────────────────────────────────────────

REPO_ROOT = Path(__file__).resolve().parents[2]

LEETCODE_USERNAME = "Treasure12"   # ← your LeetCode username
GITHUB_USERNAME   = "omg04"   # ← your GitHub username

# Add new problems here as you solve them:
# "problem folder name (lowercase)" : ("Difficulty", "LC number")
DIFFICULTY_MAP = {
     # --- EASY ---
    "merge two sorted lists":                         ("Easy", "21"),
    "linked list cycle":                              ("Easy", "141"),
    "remove linked list elements":                    ("Easy", "203"),
    "palindrome linked list":                         ("Easy", "234"),
    "remove duplicates from sorted list":             ("Easy", "83"),
    "intersection of two linked lists.":              ("Easy", "160"),
    "middle of the linked list":                      ("Easy", "876"),
    "convert binary number in a linked list to integer": ("Easy", "1290"),
    "reverse linked list":                            ("Easy", "206"),
    
    # --- MEDIUM ---
    "add two numbers":                                ("Medium", "2"),
    "swap nodes in pairs":                            ("Medium", "24"),
    "reverse linked list ii":                         ("Medium", "92"),
    "remove duplicates from sorted list ii":          ("Medium", "82"),
    "partition list":                                 ("Medium", "86"),
    "rotate list":                                    ("Medium", "61"),
    "remove nth node from end of list":               ("Medium", "19"),
    "reorder list":                                   ("Medium", "143"),
    "swapping nodes in a linked list":                ("Medium", "1721"),
    "delete the middle node of a linked list":        ("Medium", "2095"),
    "maximum twin sum of a linked list":              ("Medium", "2130"),
    "remove nodes from linked list":                  ("Medium", "2487"),
    "delete nodes from linked list present in array": ("Medium", "3217"),
    "insert greatest common divisors in linked list": ("Medium", "2807"),
    "merge nodes in between zeros":                   ("Medium", "2181"),
    "delete node in a linked list":                   ("Medium", "237"),
    "merge in between linked lists":                  ("Medium", "1669"),
    "spiral matrix iv":                               ("Medium", "2326"),
    "Split Linked List in Parts":                     ("Medium", "725"),
    "Find the Minimum and Maximum Number of Nodes Between Critical Points": ("Medium", "2058"),
    "linked list cycle ii":                           ("Medium", "142"),
    "reverse nodes in even length groups":            ("Medium", "2074"),
    "odd even linked list":                           ("Medium", "328"),
    "next greater node in linked list":               ("Medium", "1019"),
}

DIFFICULTY_MAP = {normalize(k): v for k, v in DIFFICULTY_MAP.items()}

# Target problem counts per topic (used for progress bars) 
TOPIC_GOALS = {
    "Linked-List":         66,
    "Arrays":              50,
    "Strings":             40,
    "Trees":               40,
    "Dynamic-Programming": 60,
    "Graphs":              40,
    "Stack-Queue":         30,
    "Heap":                25,
    "Binary-Search":       30,
    "Backtracking":        25,
}

TOPIC_EMOJI = {
    "Linked-List":         "🔗",
    "Arrays":              "📦",
    "Strings":             "🔤",
    "Trees":               "🌲",
    "Dynamic-Programming": "🧮",
    "Graphs":              "📊",
    "Stack-Queue":         "📚",
    "Heap":                "🏔️",
    "Binary-Search":       "🔍",
    "Backtracking":        "🔄",
}

DIFF_EMOJI  = {"Easy": "🟢", "Medium": "🟡", "Hard": "🔴"}
DIFF_BADGE  = {"Easy": "brightgreen", "Medium": "orange", "Hard": "red"}

# DSA roadmap order (add topics here as you start them)
ROADMAP = [
    ("Linked-List",         "✅"),
    ("Arrays",              "🔄"),
    ("Stack-Queue",         "⏳"),
    ("Trees",               "⏳"),
    ("Graphs",              "⏳"),
    ("Dynamic-Programming", "⏳"),
]

# ── Helpers ─────────────────────────────────────────────────────────────

def shields(label, message, color, style="for-the-badge", extra=""):
    l = label.replace(" ", "%20").replace("+", "%2B")
    m = str(message).replace(" ", "%20").replace("+", "%2B")
    return f"https://img.shields.io/badge/{l}-{m}-{color}?style={style}{extra}"

def progress_bar(solved, goal, width=24):
    filled = round(width * solved / goal) if goal else 0
    pct    = round(100 * solved / goal)   if goal else 0
    return f"`{'█' * filled}{'░' * (width - filled)}` **{solved}/{goal}** ({pct}%)"

def ascii_bar(n, total=10):
    filled = min(round(n / total * 10), 10)
    return "█" * filled + "░" * (10 - filled)

def lc_slug(name):
    return name.lower().replace(" ", "-").replace("_", "-")

# ── Scan repo ────────────────────────────────────────────────────────────

def scan_problems():
    topics = defaultdict(list)
    skip   = {".git", ".github", "__pycache__", "node_modules"}

    for topic_dir in sorted(REPO_ROOT.iterdir()):
        if not topic_dir.is_dir(): continue
        if topic_dir.name.startswith(".") or topic_dir.name in skip: continue

        for prob_dir in sorted(topic_dir.iterdir()):
            if not prob_dir.is_dir(): continue
            cpp_files = list(prob_dir.glob("*.cpp"))
            if not cpp_files: continue

            name = prob_dir.name
            key  = normalize(name)
            diff, num = DIFFICULTY_MAP.get(key, ("Medium", "?"))
            rel  = str(cpp_files[0].relative_to(REPO_ROOT)).replace("\\", "/")

            topics[topic_dir.name].append({
                "num":   num,
                "name":  name.replace("_", " ").rstrip("."),
                "diff":  diff,
                "topic": topic_dir.name,
                "path":  rel,
            })

    return topics

# ── README builder ──────────────────────────────────────────────────────────

def build(topics):
    lc     = fetch_leetcode_stats(LEETCODE_USERNAME)
    total  = lc["total"]  or sum(len(v) for v in topics.values())
    easy   = lc["easy"]   or sum(1 for v in topics.values() for p in v if p["diff"] == "Easy")
    medium = lc["medium"] or sum(1 for v in topics.values() for p in v if p["diff"] == "Medium")
    hard   = lc["hard"]   or sum(1 for v in topics.values() for p in v if p["diff"] == "Hard")
    streak = lc["streak"]
    now    = datetime.now(timezone.utc).strftime("%d %b %Y — %H:%M UTC")

    L = []   # lines

    # ── Hero banner ──────────────────────────────────────────────────────────
    typing_url = (
        "https://readme-typing-svg.demolab.com"
        "?font=Fira+Code&size=16&pause=1000&color=1D9E75&width=600&lines="
        "Solving+problems+one+commit+at+a+time...;"
        "Language%3A+C%2B%2B+%7C+Focus%3A+DSA;"
        "Next+target%3A+Arrays+%26+Hashing+%F0%9F%93%A6;"
        "Consistency+is+the+key+%F0%9F%94%91"
    )

    L += [
        "# ⚡ LeetCode Journey — omg04",
        "",
        f"[![Typing SVG]({typing_url})](https://github.com/{GITHUB_USERNAME})",
        "",
        "> Solving one problem at a time — consistency over perfection.",
        f"> 🕐 Last auto-updated: **{now}**",
        "",
    ]

    # ── Shields badges ────────────────────────────────────────────────────────
    L += [
        f"![Solved]({shields('Total Solved', total, '7F77DD')})"
        f"![Easy]({shields('Easy', easy, '1D9E75')})"
        f"![Medium]({shields('Medium', medium, 'EF9F27')})"
        f"![Hard]({shields('Hard', hard, 'E24B4A')})"
        f"![Streak]({shields('Streak', f'{streak} days', 'FF6B35')})"
        f"![Language]({shields('Language', 'C++', '00599C', extra='&logo=cplusplus&logoColor=white')})"
        f"![Status]({shields('Status', 'Active', '1D9E75')})",
        "",
        "---",
        "",
    ]

    # ── Live LeetCode stats card ──────────────────────────────────────────────
    card_light = (
        f"https://leetcard.jacoblin.cool/{LEETCODE_USERNAME}"
        "?theme=light&font=Fira%20Code&ext=heatmap"
    )
    card_dark = (
        f"https://leetcard.jacoblin.cool/{LEETCODE_USERNAME}"
        "?theme=dark&font=Fira%20Code&ext=heatmap"
    )
    L += [
        "## 📊 Live Stats",
        "",
        "<!-- leetcard auto-updates from your LeetCode profile -->",
        f'<picture>',
        f'  <source media="(prefers-color-scheme: dark)"  srcset="{card_dark}">',
        f'  <source media="(prefers-color-scheme: light)" srcset="{card_light}">',
        f'  <img src="{card_light}" alt="LeetCode Stats Card" width="480">',
        f'</picture>',
        "",
        "---",
        "",
    ]

    # ── Quick stats table ─────────────────────────────────────────────────────
    L += [
        "## 🔢 Overview",
        "",
        "```",
        f"  Total Solved : {total:>4}",
        f"  Easy         : {easy:>4}   {ascii_bar(easy,  max(easy,medium,hard,1))}",
        f"  Medium       : {medium:>4}   {ascii_bar(medium,max(easy,medium,hard,1))}",
        f"  Hard         : {hard:>4}   {ascii_bar(hard,  max(easy,medium,hard,1))}",
        f"  Topics       : {len(topics):>4}",
        "```",
        "",
        "---",
        "",
    ]

    # ── Progress by topic ─────────────────────────────────────────────────────
    L += [
        "## 📂 Progress by Topic",
        "",
        "| | Topic | Solved | Progress |",
        "|--|-------|--------|----------|",
    ]
    for topic, problems in sorted(topics.items()):
        goal  = TOPIC_GOALS.get(topic, 50)
        emoji = TOPIC_EMOJI.get(topic, "📁")
        bar   = progress_bar(len(problems), goal)
        label = topic.replace("-", " ")
        L.append(f"| {emoji} | [{label}](./{topic}/) | {len(problems)} | {bar} |")

    # Add placeholder rows for topics not yet started
    for topic, goal in TOPIC_GOALS.items():
        if topic not in topics:
            emoji = TOPIC_EMOJI.get(topic, "📁")
            label = topic.replace("-", " ")
            bar   = progress_bar(0, goal)
            L.append(f"| {emoji} | {label} | 0 | {bar} |")

    L += ["", "---", ""]

    # ── DSA Roadmap ──────────────────────────────────────────────────────────
    L += ["## 🗺️ DSA Roadmap", ""]
    rm_cols = " | ".join(
        f"{icon} {t.replace('-', ' ')}"
        for t, icon in ROADMAP
    )
    L += [f"| {rm_cols} |"]
    L += ["|" + "|".join(["---"] * len(ROADMAP)) + "|"]
    L += ["", "---", ""]

    # ── Collapsible topic folders ─────────────────────────────────────────────
    L += ["## 🗂️ Problems Solved", ""]

    all_problems_flat = sorted(
        [p for v in topics.values() for p in v],
        key=lambda x: (x["num"] == "?", int(x["num"]) if x["num"] != "?" else 9999)
    )

    for topic, problems in sorted(topics.items()):
        emoji    = TOPIC_EMOJI.get(topic, "📁")
        label    = topic.replace("-", " ")
        goal     = TOPIC_GOALS.get(topic, 50)
        solved   = len(problems)
        pct      = round(100 * solved / goal) if goal else 0
        e_count  = sum(1 for p in problems if p["diff"] == "Easy")
        m_count  = sum(1 for p in problems if p["diff"] == "Medium")
        h_count  = sum(1 for p in problems if p["diff"] == "Hard")
        bar      = f"{'█' * round(20*pct/100)}{'░' * (20 - round(20*pct/100))} {pct}%"

        diff_summary = " · ".join(filter(None, [
            f"🟢 {e_count} Easy"   if e_count  else "",
            f"🟡 {m_count} Medium" if m_count  else "",
            f"🔴 {h_count} Hard"   if h_count  else "",
        ])) or "No problems yet"

        L += [
            f"<details>",
            f"<summary><b>{emoji} {label}</b> &nbsp;—&nbsp; {solved}/{goal} solved &nbsp;|&nbsp; {diff_summary}</summary>",
            "",
            f"```",
            f"Progress: [{bar}]",
            f"```",
            "",
        ]

        if problems:
            L += [
                "| # | Problem | Difficulty | Solution |",
                "|---|---------|-----------|----------|",
            ]
            for p in sorted(problems, key=lambda x: (x["num"]=="?", int(x["num"]) if x["num"]!="?" else 9999)):
                de   = DIFF_EMOJI.get(p["diff"], "⬜")
                slug = lc_slug(p["name"])
                L.append(
                    f"| `{p['num']}` "
                    f"| [{p['name']}](https://leetcode.com/problems/{slug}/) "
                    f"| {de} {p['diff']} "
                    f"| [C++](./{p['path']}) |"
                )
        else:
            L += ["> 🚧 No problems yet — coming soon!"]

        L += ["", "</details>", ""]

    L += ["---", ""]

    # ── Footer ────────────────────────────────────────────────────────────
    L += [
        '<div align="center">',
        "",
        f'  <img src="https://img.shields.io/badge/Keep%20Going-💪-1D9E75?style=flat-square" alt="Keep Going">',
        "",
        '  <br><br>',
        '  <i>"The secret of getting ahead is getting started." — Mark Twain</i>',
        "",
        f'  <br><br>',
        f'  <sub>⚡ Auto-generated by GitHub Actions on every push · <a href="./.github/scripts/generate_readme.py">view script</a></sub>',
        "",
        "</div>",
        "",
    ]

    return "\n".join(L)

# ── Main ──────────────────────────────────────────────────────────────

if __name__ == "__main__":
    topics = scan_problems()
    readme = build(topics)
    out    = REPO_ROOT / "README.md"
    out.write_text(readme, encoding="utf-8")

    total = sum(len(v) for v in topics.values())
    print(f"✅ README updated — {total} problems across {len(topics)} topics")
    for t, ps in sorted(topics.items()):
        print(f"   {TOPIC_EMOJI.get(t,'📁')} {t}: {len(ps)} problems")
