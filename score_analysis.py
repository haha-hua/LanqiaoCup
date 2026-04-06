import argparse
import re
from collections import defaultdict
from statistics import mean, median, pstdev

import matplotlib.pyplot as plt
from matplotlib import font_manager


def configure_chinese_font():
    candidates = ["Microsoft YaHei", "SimHei", "Noto Sans CJK SC", "PingFang SC"]
    available_fonts = {font.name for font in font_manager.fontManager.ttflist}
    for font_name in candidates:
        if font_name in available_fonts:
            plt.rcParams["font.sans-serif"] = [font_name]
            break
    else:
        plt.rcParams["font.sans-serif"] = candidates
    plt.rcParams["axes.unicode_minus"] = False


configure_chinese_font()


DATA = """
16届B组70分
16届A组51分
16届研究生组103分
16界C组127分
15届A组61分
15届B组78分
15届C组109分
14届A组74分
14届B组107分
13届B组108分
"""

PATTERN = re.compile(r"^(?P<year>\d{2})(?:届|界)(?P<group>.+?)组(?P<score>\d+)分$")


def parse_records(text: str):
    records = []
    for raw_line in text.splitlines():
        line = raw_line.strip()
        if not line:
            continue
        match = PATTERN.match(line)
        if not match:
            raise ValueError(f"Cannot parse line: {line}")
        year = int(match.group("year"))
        group = match.group("group")
        score = int(match.group("score"))
        records.append({"year": year, "group": group, "score": score})
    return records


def fmt_percent(score: float, full_score: int) -> str:
    return f"{score / full_score * 100:.1f}%"


def linear_trend(xs, ys):
    n = len(xs)
    if n < 2:
        return 0.0, ys[0] if ys else 0.0

    x_mean = mean(xs)
    y_mean = mean(ys)
    numerator = sum((x - x_mean) * (y - y_mean) for x, y in zip(xs, ys))
    denominator = sum((x - x_mean) ** 2 for x in xs)
    slope = numerator / denominator if denominator else 0.0
    intercept = y_mean - slope * x_mean
    return slope, intercept


def analyze(records, full_score):
    scores = [item["score"] for item in records]
    years = defaultdict(list)
    groups = defaultdict(list)

    for item in records:
        years[item["year"]].append(item["score"])
        groups[item["group"]].append(item["score"])

    year_order = sorted(years, reverse=True)
    year_stats = []
    for year in year_order:
        values = years[year]
        year_stats.append((year, len(values), mean(values), max(values), min(values)))

    group_stats = []
    for group in sorted(groups, key=lambda g: (g != "研究生", g)):
        values = groups[group]
        group_stats.append((group, len(values), mean(values), max(values), min(values)))

    ranked_records = sorted(records, key=lambda x: (-x["score"], x["year"], x["group"]))

    year_x = [item[0] for item in year_stats]
    year_y = [item[2] for item in year_stats]
    x_positions = list(range(len(year_stats)))
    slope, intercept = linear_trend(x_positions, year_y)

    fig, axes = plt.subplots(2, 2, figsize=(15, 10))
    fig.suptitle("成绩分析图表", fontsize=18, fontweight="bold")

    ax = axes[0, 0]
    labels = [f"{item['year']}届{item['group']}组" for item in ranked_records]
    values = [item["score"] for item in ranked_records]
    ax.barh(labels, values, color="#4C78A8")
    ax.invert_yaxis()
    ax.set_title("成绩排行")
    ax.set_xlabel("分数")
    ax.set_xlim(0, full_score)
    for index, value in enumerate(values):
        ax.text(value + 1, index, f"{value} ({fmt_percent(value, full_score)})", va="center", fontsize=9)

    ax = axes[0, 1]
    ax.plot(x_positions, year_y, marker="o", linewidth=2.5, color="#F58518")
    trend_y = [slope * x + intercept for x in x_positions]
    ax.plot(x_positions, trend_y, linestyle="--", color="#54A24B", label="线性趋势")
    for x, y in zip(x_positions, year_y):
        ax.text(x, y + 1.5, f"{y:.1f}", ha="center", fontsize=9)
    ax.set_title("按年份的平均分趋势")
    ax.set_xlabel("届数")
    ax.set_ylabel("平均分")
    ax.set_xticks(x_positions)
    ax.set_xticklabels([f"{year}届" for year in year_x])
    ax.set_ylim(0, full_score)
    ax.grid(alpha=0.25)
    ax.legend(loc="best")
    ax.text(
        0.02,
        0.95,
        f"趋势解读: 16->15 下降, 15->14 回升, 14->13 大幅回升\n斜率: {slope:.2f} 分/步",
        transform=ax.transAxes,
        va="top",
        fontsize=10,
        bbox=dict(boxstyle="round", facecolor="white", alpha=0.85),
    )

    ax = axes[1, 0]
    group_labels = [f"{item[0]}组" for item in group_stats]
    group_values = [item[2] for item in group_stats]
    ax.bar(group_labels, group_values, color="#72B7B2")
    ax.set_title("按组别的平均分")
    ax.set_ylabel("平均分")
    ax.set_ylim(0, full_score)
    for index, value in enumerate(group_values):
        ax.text(index, value + 1.5, f"{value:.1f}", ha="center", fontsize=9)
    ax.grid(axis="y", alpha=0.25)

    ax = axes[1, 1]
    ax.hist(scores, bins=[50, 60, 70, 80, 90, 100, 110, 120, 130], color="#E45756", edgecolor="white")
    ax.set_title("分数分布")
    ax.set_xlabel("分数区间")
    ax.set_ylabel("人数")
    ax.grid(axis="y", alpha=0.25)
    ax.text(
        0.02,
        0.95,
        f"均分: {mean(scores):.2f}\n中位数: {median(scores):.2f}\n标准差: {pstdev(scores):.2f}",
        transform=ax.transAxes,
        va="top",
        fontsize=10,
        bbox=dict(boxstyle="round", facecolor="white", alpha=0.85),
    )

    fig.tight_layout(rect=[0, 0, 1, 0.96])
    output_path = "score_analysis.png"
    fig.savefig(output_path, dpi=200, bbox_inches="tight")
    plt.show()


def main():
    parser = argparse.ArgumentParser(description="Analyze score records.")
    parser.add_argument("--full-score", type=int, default=150, help="Full score for normalization.")
    parser.add_argument("--file", type=str, help="Optional text file containing one record per line.")
    args = parser.parse_args()

    text = DATA
    if args.file:
        with open(args.file, "r", encoding="utf-8") as f:
            text = f.read()

    records = parse_records(text)
    analyze(records, args.full_score)


if __name__ == "__main__":
    main()