# Компилятор
CC := gcc
# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic

# Подпапка для объектных файлов
OBJDIR = out
# Общие объектные файлы
OBJS := $(OBJDIR)/cmp_mult_results.o $(OBJDIR)/convert_matrix.o $(OBJDIR)/create_matrices.o $(OBJDIR)/create_rand_matrix.o $(OBJDIR)/mem_matrix.o $(OBJDIR)/mult_matrices.o $(OBJDIR)/print_matrix.o $(OBJDIR)/read_matrix_cons.o $(OBJDIR)/read_matrix_file.o

app.exe : $(OBJS) $(OBJDIR)/main.o
	$(CC) $^ -o $@

vpath %.h inc
vpath %.c src

$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/cmp_mult_results.o : cmp_mult_results.c cmp_mult_results.h create_rand_matrix.h convert_matrix.h mult_matrices.h mem_matrix.h matrix.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/convert_matrix.o : convert_matrix.c convert_matrix.h mem_matrix.h matrix.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/create_matrices.o : create_matrices.c read_matrix_cons.h read_matrix_file.h create_rand_matrix.h convert_matrix.h mem_matrix.h matrix.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/create_rand_matrix.o : create_rand_matrix.c mem_matrix.h matrix.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/mem_matrix.o : mem_matrix.c mem_matrix.h matrix.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/mult_matrices.o : mult_matrices.c mult_matrices.h mem_matrix.h matrix.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/print_matrix.o : print_matrix.c matrix.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/read_matrix_cons.o : read_matrix_cons.c read_matrix_cons.h mem_matrix.h matrix.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/read_matrix_file.o : read_matrix_file.c read_matrix_file.h mem_matrix.h matrix.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/main.o : main.c cmp_mult_results.h convert_matrix.h create_matrices.h create_rand_matrix.h matrix.h mem_matrix.h mult_matrices.h print_matrix.h read_matrix_cons.h read_matrix_file.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :
	rm $(OBJDIR)/*.o *.exe
