#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

// this is the maximum range of the shifter operand's operation space. It resides between bits 0 and 11,
// so this macro represents the range for which it goes out of bounds.
#define operand_range (1 << 12) - 1


// basically llarm::util::rotr
static inline uint32_t ror(uint32_t x, unsigned n) {
    n &= 31;
    return (x >> n) | (x << (32 - n));
}

int main() {
    uint64_t minimum = 0;
    uint64_t maximum = 0;

    FILE *f = fopen("out.txt", "w");
    if (!f) return 1;

    for (uint16_t num = 0; num <= operand_range; num++) {
        const uint8_t rotate_imm = (num >> 8) & 0xF;
        const uint8_t immed_8 = (num & 0xF);

        const uint32_t value = ror(immed_8, rotate_imm * 2);

        if (value > maximum) {
            maximum = value;
        }

        fprintf(f, "%" PRIu32 "\n", value);
    }

    printf("\n\nmaximum: %" PRIu64 "\n", maximum);
    fclose(f);

    return 0;
}