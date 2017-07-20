#include <stdint.h>
extern "C" {
void data_abort();
void fast_irq();
void normal_irq();
void prefetch_abort();
void svc_call();
void undefined_op();
extern uintptr_t branch_macro;
}
void initVectors() {
    uintptr_t *vectors = (uintptr_t*)nullptr;
    uintptr_t branch = 0xEA000000;
    vectors[1] = branch + 5;
    vectors[2] = branch + 6;
    vectors[3] = branch + 7;
    vectors[4] = branch + 8;
    vectors[6] = branch + 8;
    vectors[7] = branch + 9;
    vectors[8] = branch_macro;
    vectors[9] = (uintptr_t)&undefined_op;
    vectors[10] = branch_macro;
    vectors[11] = (uintptr_t)&svc_call;
    vectors[12] = branch_macro;
    vectors[13] = (uintptr_t)&prefetch_abort;
    vectors[14] = branch_macro;
    vectors[15] = (uintptr_t)&data_abort;
    vectors[16] = branch_macro;
    vectors[17] = (uintptr_t)&normal_irq;
    vectors[18] = branch_macro;
    vectors[19] = (uintptr_t)&fast_irq;
}
