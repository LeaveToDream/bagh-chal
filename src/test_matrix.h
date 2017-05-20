#ifndef __TEST_MATRIIX_H__
#define __TEST_MATRIIX_H__

#include "test.h"

#define CHECK_MATRIX_SIZE(m, rows, cols, cap, file, line)         \
    if (m == NULL) {                                              \
        printf("%s:%d: Got a NULL matrix.\n", file, line);        \
        test_fail(t);                                             \
    }                                                             \
    if (m->num_rows != rows ||                                    \
        m->num_cols != cols ||                                    \
        (m->capacity != cap && cap != -1)) {                      \
        printf("%s:%d: Matrix sizes don't match.\n", file, line); \
        printf("Expected: {r: %d, c: %d, cap: %d}\n",             \
               rows, cols, cap);                                  \
        printf("Got: {r: %d, c: %d, cap: %d}\n",                  \
               m->num_rows, m->num_cols, m->capacity);            \
        test_fail(t);                                             \
    }

#endif
