#ifndef _READ_MATRIX_FILE_H_
#define _READ_MATRIX_FILE_H_

#include <stdio.h>
#include "mem_matrix.h"

int read_from_file(FILE *file, matrix_s *mtr, matrix_s *vector, int rows, int cols, int nz_m, int nz_v);

#endif
