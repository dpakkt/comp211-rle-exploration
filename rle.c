#include <stddef.h>
#include <stdlib.h>

unsigned char *rle_encode(const unsigned char *in, size_t n, size_t *out_len) {
    if (out_len == NULL) {
        return NULL;
    }

    *out_len = 0;

    if (in == NULL && n > 0) {
        return NULL;
    }

    if (n == 0) {
        unsigned char *out = malloc(1);
        if (out == NULL) {
            return NULL;
        }
        return out;
    }

    if (n > (size_t)-1 / 2) {
        return NULL;
    }

    unsigned char *out = malloc(2 * n);

    if (out == NULL) {
        return NULL;
    }

    size_t i = 1;
    size_t j = 0;

    unsigned char current = in[0];
    unsigned int count = 1;

    for (; i < n; i++) {
        if (in[i] == current && count < 255) {
            count++;
        } else {
            out[j] = (unsigned char)count;
            out[j + 1] = current;
            j += 2;

            current = in[i];
            count = 1;
        }
    }

    out[j] = (unsigned char)count;
    out[j + 1] = current;
    j += 2;

    *out_len = j;

    return out;
}

unsigned char *rle_decode(const unsigned char *in, size_t n, size_t *out_len) {
    if (out_len == NULL) {
        return NULL;
    }

    *out_len = 0;

    if (in == NULL && n > 0) {
        return NULL;
    }

    if (n % 2 != 0) {
        return NULL;
    }

    size_t total = 0;
    for (size_t i = 0; i < n; i += 2) {
        unsigned char count = in[i];

        if (count == 0) {
            return NULL;
        }
        if (total > (size_t)-1 - count) {
            return NULL;
        }

        total += count;
    }
    unsigned char *out = malloc(total == 0 ? 1 : total);

    if (out == NULL) {
        return NULL;
    }
    size_t j = 0;

    for (size_t i = 0; i < n; i += 2) {
        unsigned char count = in[i];
        unsigned char value = in[i + 1];

        for (size_t k = 0; k < count; k++) {
            out[j] = value;
            j++;
        }
    }

    *out_len = j;

    return out;
}
