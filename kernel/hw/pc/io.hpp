template <typename T>
static void out(uint16_t port, T val) {
    if (sizeof(T) == 1)
        asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
    else if (sizeof(T) == 2)
        asm volatile("outw %0, %1" : : "a"(val), "Nd"(port));
    else if (sizeof(T) == 4)
        asm volatile("outl %0, %1" : : "a"(val), "Nd"(port));
}
template <typename T>
static T in(uint16_t port) {
    T val = 0;
    if (sizeof(T) == 1)
        asm volatile("inb %1, %0" : "=a"(val) : "Nd"(port));
    else if (sizeof(T) == 2)
        asm volatile("inw %1, %0" : "=a"(val) : "Nd"(port));
    else if (sizeof(T) == 4)
        asm volatile("inl %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}
static void io_wait() { out<unsigned char>(0x80, 0); }
