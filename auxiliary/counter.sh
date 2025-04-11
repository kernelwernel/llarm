find ../charm-emu -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec wc -l {} + | tee /dev/tty | awk '{s+=$1} END {print "Total lines:", s}'
echo ""
find ../charm-asm -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec wc -l {} + | tee /dev/tty | awk '{s+=$1} END {print "Total lines:", s}'