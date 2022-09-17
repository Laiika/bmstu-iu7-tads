#ifndef _CREATE_MATRICES_H_
#define _CREATE_MATRICES_H_

#include <string.h>
#include "../inc/read_matrix_cons.h"
#include "../inc/read_matrix_file.h"
#include "../inc/create_rand_matrix.h"
#include "../inc/convert_matrix.h"

int create_matrices(int type, matrix_s *mtr, matrix_s *vector, sparse_matrix_s *sp_mtr, sparse_matrix_s *sp_vector, int *fr);

#endif
