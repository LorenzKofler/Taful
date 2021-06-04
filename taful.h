#ifndef TAFUL_H
#define TAFUL_H

/* INCLUDES */
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* INCLUDES */

/* TYPEDEFS */
typedef enum {
    TAFUL_ERROR = EKEYREJECTED,
    TAFUL_OK = EXIT_SUCCESS,
    TAFUL_INVALID_PARAMS = EINVAL,
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
