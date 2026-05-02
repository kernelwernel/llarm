import os

ALLOWED_EXTENSIONS = ('.cpp', '.hpp', '.c', '.h')
EXCLUDED_DIRS = {'build', '_deps', 'archive', 'scripts', 'cmake'}


def count_lines_in_directory(directory):
    counts = {ext: {'lines': 0, 'files': 0} for ext in ALLOWED_EXTENSIONS}

    for root, dirs, files in os.walk(directory):
        dirs[:] = [d for d in dirs if d not in EXCLUDED_DIRS]

        for file in files:
            ext = os.path.splitext(file.lower())[1]
            if ext in ALLOWED_EXTENSIONS:
                filepath = os.path.join(root, file)
                try:
                    with open(filepath, 'r', encoding='utf-8') as f:
                        lines = sum(1 for _ in f)
                    counts[ext]['lines'] += lines
                    counts[ext]['files'] += 1
                except (UnicodeDecodeError, PermissionError) as e:
                    print(f"Skipping {filepath} due to error: {e}")

    return counts


def find_subprojects(root):
    subprojects = []
    for entry in sorted(os.listdir(root)):
        path = os.path.join(root, entry)
        if os.path.isdir(path) and os.path.isfile(os.path.join(path, 'CMakeLists.txt')):
            subprojects.append((entry, path))
    return subprojects


def totals(counts):
    return sum(d['lines'] for d in counts.values()), sum(d['files'] for d in counts.values())


def print_counts(counts, indent='  '):
    for ext, data in counts.items():
        if data['files'] > 0:
            print(f"{indent}{ext:5}  {data['lines']:>6} lines  {data['files']:>4} files")


if __name__ == "__main__":
    root = os.path.normpath(os.path.join(os.path.dirname(__file__), '..'))
    subprojects = find_subprojects(root)

    grand_lines = 0
    grand_files = 0

    for name, path in subprojects:
        counts = count_lines_in_directory(path)
        lines, files = totals(counts)
        if files == 0:
            continue
        print(f"{name}  ({lines} lines, {files} files)")
        print_counts(counts)
        print()
        grand_lines += lines
        grand_files += files

    print(f"Total  {grand_lines:>6} lines  {grand_files:>4} files")
