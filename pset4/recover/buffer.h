// In final submission the buffer.h code had to be added to the recover.c file

#include <stdint.h>

typedef int DATA[126];
typedef uint8_t  HEADER[4];

typedef struct {
    HEADER header;
    DATA data;
} BUFFER;