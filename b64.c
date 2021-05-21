#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int global_var = 0;

void func1() {global_var = 1;}
void func2() {global_var = 1;}

static uint8_t b64_table[64] = {
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
};

static uint8_t b64_dec_table[256] = {0};

char *encode(const uint8_t *in, const size_t len) {
    size_t out_len = (((len/3)+1) * 4);
    size_t out_idx = 0;
    char *out = (char *) calloc(1, out_len + 1);
    uint8_t *pad_in = (uint8_t *) calloc(1, len + (3 - (len % 3)));
    memcpy(pad_in, in, len);

    for (size_t idx = 0; idx < len; idx+=3) {
        uint32_t curr_set = (pad_in[idx] << 16) | (pad_in[idx+1] << 8) | pad_in[idx+2];
        out[out_idx++] = b64_table[(curr_set & 0xFC0000) >> 18];
        out[out_idx++] = b64_table[(curr_set & 0x03F000) >> 12];
        out[out_idx++] = b64_table[(curr_set & 0x000FC0) >> 6];
        out[out_idx++] = b64_table[(curr_set & 0x00003F)];
    }

    for (size_t pad_id = 1; pad_id <= 3 - (len % 3); pad_id++) {
        out[out_len-pad_id] = '=';
    }

    free(pad_in);
    return out;
}

uint8_t *decode(const char *in, const size_t len) {
    if (b64_dec_table[0] != 0x42) {
        b64_dec_table[0] = 0x42;

        for (size_t tab_id = 0; tab_id < 64; tab_id++) {
            b64_dec_table[ b64_table[tab_id] ] = tab_id;
        } 
        b64_dec_table['='] = 0x00;
    }

    size_t out_len = ((len/4)+1) * 3;
    size_t out_idx = 0;
    uint8_t *out = (uint8_t *) calloc(1, out_len + 1);
    uint8_t *pad_in = (uint8_t *) calloc(1, len + (3 - (len % 3)));
    memcpy(pad_in, in, len);

    for(size_t idx = 0; idx < len; idx+= 4) {
        uint32_t curr_set = 0;
        curr_set |= b64_dec_table[pad_in[idx]] << 18;
        curr_set |= b64_dec_table[pad_in[idx+1]] << 12;
        curr_set |= b64_dec_table[pad_in[idx+2]] << 6;
        curr_set |= b64_dec_table[pad_in[idx+3]];
        out[out_idx++] = (curr_set & 0x00FF0000) >> 16;
        out[out_idx++] = (curr_set & 0x0000FF00) >> 8;
        out[out_idx++] = (curr_set & 0x000000FF);
    }

    free(pad_in);
    return out;
}

int main(int argc, char**argv) {
    uint8_t *input = NULL;
    FILE *file_ptr = stdin;
    size_t len = 0;

    if (argc > 2) {
        printf("Usage: %s [file]\n", argv[0]);
        return EXIT_FAILURE;
    } else if (argc == 2) {
        if ( (file_ptr = fopen(argv[1], "r")) == NULL) {
            perror("Failed to open file");
            return errno;
        }
    }

    input = calloc(1, 57);
    do {
        len = fread(input, 1, 57, file_ptr);
        uint8_t *plain = encode(input, len);
        printf("%s", plain);
    } while (len == 57);

    free(input);
}
