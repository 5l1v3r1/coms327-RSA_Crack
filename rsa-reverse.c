#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    unsigned int start = atoi(argv[1]);
    unsigned int end = atoi(argv[2]);
    unsigned int target_seed = atoi(argv[3]);

    unsigned int microseconds = 0;
    unsigned int seed = 0;

    // Between some starting and ending value, some combination has to give you
    // the time the RNG was seeded. Simple brute force approach to find it.
    // Seeds are unique within a (small) time period, so quit once found.
    //
    // 1 million (max microseconds) ~= 20 bits
    for (; start <= end; start++) {
        for (microseconds = 0; microseconds < 1000000; microseconds++) {
            seed = (microseconds ^ (start << 20)) & 0xffffffff;
            if (seed == target_seed) {
                printf("s: %u, m: %u\n", start, microseconds);
                return 0;
            }
        }
    }
    printf("Didn't find seed in range.\n");
    return 1;
}
