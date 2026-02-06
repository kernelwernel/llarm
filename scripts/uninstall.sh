#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}=== LLARM Cleanup Script ===${NC}\n"

# Define search locations
SEARCH_PATHS=(
    "/usr/local/lib"
    "/usr/local/include"
    "/usr/local/bin"
    "/usr/lib"
    "/usr/include"
    "/usr/bin"
)

# Find all llarm-related files
echo -e "${YELLOW}Searching for llarm-related files...${NC}\n"

FOUND_FILES=()
for path in "${SEARCH_PATHS[@]}"; do
    if [ -d "$path" ]; then
        while IFS= read -r file; do
            FOUND_FILES+=("$file")
        done < <(find "$path" -name "*llarm*" 2>/dev/null)
    fi
done

# If nothing found, exit
if [ ${#FOUND_FILES[@]} -eq 0 ]; then
    echo -e "${GREEN}No llarm-related files found.${NC}"
    exit 0
fi

# Display what was found
echo -e "${RED}Found ${#FOUND_FILES[@]} llarm-related files:${NC}\n"
for file in "${FOUND_FILES[@]}"; do
    echo "  $file"
done

# Ask for confirmation
echo
read -p "$(echo -e ${YELLOW}Do you want to delete all these files? [y/N]:${NC} )" -n 1 -r
echo

if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo -e "${GREEN}Aborted. No files were deleted.${NC}"
    exit 0
fi

# Delete files
echo -e "\n${YELLOW}Deleting files...${NC}\n"
DELETED=0
FAILED=0

for file in "${FOUND_FILES[@]}"; do
    if sudo rm -rf "$file" 2>/dev/null; then
        echo -e "${GREEN}✓${NC} Deleted: $file"
        ((DELETED++))
    else
        echo -e "${RED}✗${NC} Failed to delete: $file"
        ((FAILED++))
    fi
done

# Update ldconfig cache
echo -e "\n${YELLOW}Updating library cache...${NC}"
sudo ldconfig

# Summary
echo -e "\n${YELLOW}=== Summary ===${NC}"
echo -e "${GREEN}Deleted: $DELETED files${NC}"
if [ $FAILED -gt 0 ]; then
    echo -e "${RED}Failed: $FAILED files${NC}"
fi

echo -e "\n${GREEN}Cleanup complete!${NC}"