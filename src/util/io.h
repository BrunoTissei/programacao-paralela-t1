#ifndef _IO_H
#define _IO_H

#include <stdio.h>
#include <sys/time.h>

#include "core/dataset.h"

void print_usage(void);

set_t *read_input_data(char *filename);

double timestamp(void);

#endif
