// random.c - Generador pseudoaleatorio de 16 bits

unsigned long seed = 0x12345678;

void srand(unsigned long new_seed) {
    seed = new_seed;
}

unsigned short rand(void) {
    seed = seed * 1103515245 + 12345;
    return (unsigned short)(seed >> 16);
}