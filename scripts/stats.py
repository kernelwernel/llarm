import os

def count_lines_in_directory(directory):
    allowed_extensions = ('.cpp', '.hpp', '.c', '.h')
    counts = {ext: {'lines': 0, 'files': 0} for ext in allowed_extensions}

    excluded_dirs = {'build', '_deps', 'archive'}

    for root, dirs, files in os.walk(directory):
        dirs[:] = [d for d in dirs if d not in excluded_dirs]

        for file in files:
            ext = os.path.splitext(file.lower())[1]
            if ext in allowed_extensions:
                filepath = os.path.join(root, file)
                try:
                    with open(filepath, 'r', encoding='utf-8') as f:
                        lines = sum(1 for _ in f)
                    counts[ext]['lines'] += lines
                    counts[ext]['files'] += 1
                except (UnicodeDecodeError, PermissionError) as e:
                    print(f"Skipping {filepath} due to error: {e}")

    return counts

if __name__ == "__main__":
    target_directory = "../"
    counts = count_lines_in_directory(target_directory)

    total_lines = 0
    total_files = 0

    for ext, data in counts.items():
        print(f"{ext:5}  {data['lines']:>6} lines  {data['files']:>4} files")
        total_lines += data['lines']
        total_files += data['files']

    print(f"\nTotal  {total_lines:>6} lines  {total_files:>4} files")
