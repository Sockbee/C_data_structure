#include <stdio.h>

int main() {
    unsigned int word = 0xABCDEF01;
    unsigned char memory[4];

    // i. Little-endian
    printf("Little-endian 저장:\n");
    for(int i=0; i<4; i++) {
        memory[i] = (word >> (8*i)) & 0xFF;
        printf("주소 %d: 0x%02X\n", i, memory[i]);
    }

    printf("\n");

    // ii. Big-endian
    printf("Big-endian 저장:\n");
    for(int i=0; i<4; i++) {
        memory[i] = (word >> (8*(3-i))) & 0xFF;
        printf("주소 %d: 0x%02X\n", i, memory[i]);
    }

    return 0;
}
