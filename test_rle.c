#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

unsigned char *rle_encode(const unsigned char *in, size_t n, size_t *out_len);
unsigned char *rle_decode(const unsigned char *in, size_t n, size_t *out_len);

void test_round_trip(const char *name, const unsigned char *in, size_t n) {
    size_t elen = 0;
    size_t dlen = 0;

    unsigned char *e = rle_encode(in, n, &elen);

    if (e == NULL) {
        printf("FAIL: %s - encoder returned NULL\n", name);
        return;
    }

    unsigned char *d = rle_decode(e, elen, &dlen);

    if (d == NULL) {
        printf("FAIL: %s - decoder returned NULL\n", name);
        free(e);
        return;
    }

    if (dlen != n) {
        printf("FAIL: %s - decoded length was incorrect\n", name);
    } else if (n > 0 && memcmp(d, in, n) != 0) {
        printf("FAIL: %s - decoded data did not match\n", name);
    } else {
        printf("PASS: %s\n", name);
    }

    free(e);
    free(d);
}

void test_invalid_input(const char *name, const unsigned char *in, size_t n) {
    size_t out_len = 999;

    unsigned char *out = rle_decode(in, n, &out_len);

    if (out == NULL && out_len == 0) {
        printf("PASS: %s\n", name);
    } else {
        printf("FAIL: %s - invalid input was not rejected\n", name);
    }

    free(out);
}

void test_encoder_null_input(void) {
    size_t out_len = 999;

    unsigned char *out = rle_encode(NULL, 5, &out_len);

    if (out == NULL && out_len == 0) {
        printf("PASS: encoder rejects NULL input\n");
    } else {
        printf("FAIL: encoder NULL input test\n");
    }

    free(out);
}

void test_null_out_len(void) {
    unsigned char input[] = {'A'};

    unsigned char *out = rle_encode(input, 1, NULL);

    if (out == NULL) {
        printf("PASS: encoder rejects NULL out_len\n");
    } else {
        printf("FAIL: encoder NULL out_len test\n");
    }

    free(out);
}

void test_decoder_null_out_len(void) {
    unsigned char input[] = {1, 'A'};

    unsigned char *out = rle_decode(input, 2, NULL);

    if (out == NULL) {
        printf("PASS: decoder rejects NULL out_len\n");
    } else {
        printf("FAIL: decoder NULL out_len test\n");
    }

    free(out);
}


// Checks the exact encoded output for a single run.
void test_255_limit(void) {
    unsigned char input[255];

    memset(input, 'A', sizeof(input));

    size_t out_len = 0;
    unsigned char *out = rle_encode(input, sizeof(input), &out_len);

    if (out != NULL &&
        out_len == 2 &&
        out[0] == 255 &&
        out[1] == 'A') {
        printf("PASS: exactly 255 repeated bytes\n");
    } else {
        printf("FAIL: exactly 255 repeated bytes\n");
    }

    free(out);
}

void test_256_limit(void) {
    unsigned char input[256];

    memset(input, 'A', sizeof(input));

    size_t out_len = 0;
    unsigned char *out = rle_encode(input, sizeof(input), &out_len);

    if (out != NULL &&
        out_len == 4 &&
        out[0] == 255 &&
        out[1] == 'A' &&
        out[2] == 1 &&
        out[3] == 'A') {
        printf("PASS: 256 repeated bytes\n");
    } else {
        printf("FAIL: 256 repeated bytes\n");
    }

    free(out);
}


int main(void) {
    unsigned char basic[] = {'A', 'A', 'A', 'A', 'B', 'B', 'C', 'C'};

    unsigned char one[] = {'A'};

    unsigned char unique[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    unsigned char binary[] = {0x00, 0x00, 0x00, 0x41};

    unsigned char *empty = NULL;

    unsigned char long_run[300];
    memset(long_run, 'A', sizeof(long_run));

    printf("Round-trip tests:\n");

    test_round_trip("empty input", empty, 0);
    test_round_trip("single character", one, sizeof(one));
    test_round_trip("multiple runs", basic, sizeof(basic));
    test_round_trip("unique characters", unique, sizeof(unique));
    test_round_trip("binary data containing zero bytes", binary, sizeof(binary));
    test_round_trip("255 repeated bytes", long_run, 255);
    test_round_trip("256 repeated bytes", long_run, 256);
    test_round_trip("300 repeated bytes", long_run, 300);

    printf("\nEncoder boundary tests:\n");

    test_255_limit();
    test_256_limit();

    printf("\nInvalid input tests:\n");

    unsigned char odd_length[] = {2, 'A', 1};
    unsigned char zero_count[] = {0, 'A'};

    test_invalid_input("rejects odd-length input", odd_length, sizeof(odd_length));
    test_invalid_input("rejects zero count", zero_count, sizeof(zero_count));
    test_invalid_input("rejects NULL input with nonzero length", NULL, 2);

    printf("\nAdditional API tests:\n");

    test_encoder_null_input();
    test_null_out_len();
    test_decoder_null_out_len();

    return 0;
}
