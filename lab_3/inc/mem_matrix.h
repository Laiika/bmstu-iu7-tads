#ifndef _MEM_MATRIX_H_
#define _MEM_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "return_codes.h"

int **allocate_matrix(int n, int m);
int allocate_sparce_matrix(sparse_matrix_s *sp_mtr, int rows, int not_zero);
void free_matrix(int **ptrs, int n);
void free_sparce_matrix(sparse_matrix_s *mtr);

#endif
