#include "messy_c.h"

void restore_permutation(int n, int w, int r, int* result) {
    add_element("0");
    compile_set();
    check_element("0");
    for (int i = 0; i < n; i++) {
        result[i] = i;
    }
}
