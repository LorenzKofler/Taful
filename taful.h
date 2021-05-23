#ifndef TAFUL_H
#define TAFUL_H

/* INCLUDES */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/blowfish.h>
/* INCLUDES */

/* TYPEDEFS */
typedef enum {
    TAFUL_ERROR = 0,
    TAFUL_OK = 42,
    TAFUL_INVALID_PARAMS = 3,
} eTafulStatus;

typedef void (*taful_ptr)();
/* TYPEDEFS */


/*
|- Validates a given null-terminated license key
|-- @param input: license key (max. 32 bytes)
|-- @returns: TAFUL_OK on Success, else an error code
*/
eTafulStatus validate(char *input);

#endif
