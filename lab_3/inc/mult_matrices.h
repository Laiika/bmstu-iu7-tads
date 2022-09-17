#ifndef _MULT_MATRICES_H_
#define _MULT_MATRICES_H_

#include "mem_matrix.h"

int mult_mtrs(matrix_s *res, matrix_s mtr1, matrix_s mtr2);
int mult_sp_mtrs(sparse_matrix_s *res, sparse_matrix_s mtr1, sparse_matrix_s mtr2);

#endif
