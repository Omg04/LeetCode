import os
import re
from pathlib import Path
from datetime import datetime
from collections import defaultdict

# ── Config ────────────────────────────────────────────────────────────────────

REPO_ROOT = Path(__file__).resolve().parents[2]

DIFFICULTY_MAP = {
    # Linked List
    "add two numbers": ("Medium", "2"),
    "partition list": ("Medium", "86"),
    "intersection of two linked lists": ("Easy", "160"),
    "intersection_of_two_linked_lists": ("Easy", "160"),
    "middle of the linked list": ("Easy", "876"),
    "middle_of_the_linked_list": ("Easy", "876"),
    "convert binary number in a linked list to integer": ("Easy", "1290"),
    "delete nodes from linked list present in array": ("Medium", "3217"),
}

TOPIC_GOALS = {
    "Linked-List": 50,
    "Arrays": 50,
    "Strings": 40,
    "Trees": 40,
    "Dynamic Programming": 60,
    "Graphs": 40,
    "Stack & Queue": 30,
    "Heap": 25,
    "Binary Search": 30,
    "Backtracking": 25,
}

DIFFICULTY_EMOJI = {"Easy": "🟢", "Medium": "🟡", "Hard": "🔴"}

TOPIC_LINKS = {
    "Linked-List": "./Linked-List/",
}

# ── Scan repo ─────────────────────────────────────────────────────────────────

def scan_problems():
    topics = defaultdict(list)
    skip_dirs = {".git", ".github", "__pycache__"}

    for topic_dir in sorted(REPO_ROOT.iterdir()):
        if not topic_dir.is_dir():
            continue
        if topic_dir.name.startswith(".") or topic_dir.name in skip_dirs:
            continue

        for problem_dir in sorted(topic_dir.iterdir()):
            if not problem_dir.is_dir():
                continue

            # Find a .cpp file
            cpp_files = list(problem_dir.glob("*.cpp"))
            if not cpp_files:
                continue

            problem_name = problem_dir.name
            key = problem_name.lower().replace("_", " ").replace("-", " ").strip()

            diff, num = DIFFICULTY_MAP.get(key, ("Medium", "?"))
            cpp_rel = cpp_files[0].relative_to(REPO_ROOT)

            topics[topic_dir.name].append({
                "num": num,
                "name": problem_name.replace("_", " "),
                "difficulty": diff,
                "topic": topic_dir.name.replace("-", " "),
                "path": str(cpp_rel).replace("\\", "/"),
            })

    return topics

# ── Build README sections ──────────────────────────────────────────────────────

def make_progress_bar(solved, goal, width=28):
    filled = round(width * solved / goal) if goal else 0
    bar = "█" * filled + "░" * (width - filled)
    pct = round(100 * solved / goal) if goal else 0
    return f"`{bar}` {solved}/{goal} ({pct}%)"

def make_shields_url(label, message, color, style="for-the-badge"):
    label_enc = label.replace(" ", "%20")
    message_enc = str(message).replace(" ", "%20")
    return f"https://img.shields.io/badge/{label_enc}-{message_enc}-{color}?style={style}"

def generate_readme(topics):
    total = sum(len(v) for v in topics.values())
    easy = sum(1 for v in topics.values() for p in v if p["difficulty"] == "Easy")
    medium = sum(1 for v in topics.values() for p in v if p["difficulty"] == "Medium")
    hard = sum(1 for v in topics.values() for p in v if p["difficulty"] == "Hard")

    now = datetime.utcnow().strftime("%d %b %Y")

    lines = []

    # Header
    lines += [
        "# ⚡ LeetCode Journey",
        "",
        "> Solving one problem at a time — consistency over perfection.  ",
        f"> Last updated: **{now}**",
        "",
    ]

    # Badges
    lines += [
        f"![Solved]({make_shields_url('Solved', total, '7F77DD')})",
        f"![Easy]({make_shields_url('Easy', easy, '1D9E75')})",
        f"![Medium]({make_shields_url('Medium', medium, 'EF9F27')})",
        f"![Hard]({make_shields_url('Hard', hard, 'E24B4A')})",
        f"![Language]({make_shields_url('Language', 'C++', '00599C')}&logo=cplusplus&logoColor=white)",
        "",
        "---",
        "",
    ]

    # Stats overview
    easy_bar = "█" * easy + "░" * max(0, 10 - easy)
    medium_bar = "█" * medium + "░" * max(0, 10 - medium)
    hard_bar = "█" * hard + "░" * max(0, 10 - hard)

    lines += [
        "## 📈 Stats Overview",
        "",
        "```",
        f"Total Solved  : {total}",
        f"Easy          : {easy}  {easy_bar}",
        f"Medium        : {medium}  {medium_bar}",
        f"Hard          : {hard}  {hard_bar}",
        "```",
        "",
        "---",
        "",
    ]

    # Progress by topic
    lines += [
        "## 📂 Progress by Topic",
        "",
        "| Topic | Solved | Progress |",
        "|-------|--------|----------|",
    ]
    for topic, problems in sorted(topics.items()):
        goal = TOPIC_GOALS.get(topic, 50)
        bar = make_progress_bar(len(problems), goal)
        link = TOPIC_LINKS.get(topic, f"./{topic}/")
        label = topic.replace("-", " ")
        lines.append(f"| [🔗 {label}]({link}) | {len(problems)} | {bar} |")

    lines += ["", "---", ""]

    # Full problem table
    lines += [
        "## 🗂️ All Problems",
        "",
        "| # | Problem | Difficulty | Topic | Solution |",
        "|---|---------|-----------|-------|----------|",
    ]

    all_problems = sorted(
        [p for v in topics.values() for p in v],
        key=lambda x: (x["num"] == "?", int(x["num"]) if x["num"] != "?" else 9999)
    )

    for p in all_problems:
        emoji = DIFFICULTY_EMOJI.get(p["difficulty"], "⬜")
        name_slug = p["name"].replace(" ", "%20").replace("_", "%20")
        lc_url = f"https://leetcode.com/problems/{p['name'].lower().replace(' ', '-').replace('_', '-')}/"
        lines.append(
            f"| {p['num']} | [{p['name']}]({lc_url}) "
            f"| {emoji} {p['difficulty']} "
            f"| {p['topic']} "
            f"| [C++](./{p['path']}) |"
        )

    lines += ["", "---", ""]

    # Footer
    lines += [
        '<div align="center">',
        '  <i>"The secret of getting ahead is getting started." — Mark Twain</i>',
        '</div>',
        "",
    ]

    return "\n".join(lines)

# ── Main ──────────────────────────────────────────────────────────────────────

if __name__ == "__main__":
    topics = scan_problems()
    readme = generate_readme(topics)
    out_path = REPO_ROOT / "README.md"
    out_path.write_text(readme, encoding="utf-8")
    print(f"✅ README updated — {sum(len(v) for v in topics.values())} problems across {len(topics)} topics")
