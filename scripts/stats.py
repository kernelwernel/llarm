import os

def count_lines_in_directory(directory):
    total_lines = 0
    total_files = 0
    allowed_extensions = ('.cpp', '.hpp')
    
    for root, _, files in os.walk(directory):
        for file in files:
            if file.lower().endswith(allowed_extensions):
                filepath = os.path.join(root, file)
                try:
                    with open(filepath, 'r', encoding='utf-8') as f:
                        total_lines += sum(1 for _ in f)
                    #print(f"Counted {filepath}")
                    total_files += 1
                except (UnicodeDecodeError, PermissionError) as e:
                    print(f"Skipping {filepath} due to error: {e}")
    
    return total_lines, total_files

if __name__ == "__main__":
    target_directory = "../"
    lines, files = count_lines_in_directory(target_directory)

    print(f"\nTotal lines in .cpp and .hpp files: {lines}")
    print(f"Total files: {files}")