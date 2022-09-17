# Компилятор
CC := gcc
# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic

# Подпапка для объектных файлов
OBJDIR = out
# Общие объектные файлы
OBJS := $(OBJDIR)/tree_node.o $(OBJDIR)/tree.o $(OBJDIR)/hash_table.o

app.exe : $(OBJS) $(OBJDIR)/main.o
	$(CC) $^ -o $@

vpath %.h inc
vpath %.c src

$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/tree_node.o : tree_node.c tree_node.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/tree.o : tree.c tree_node.h tree.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/hash_table.o : hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/main.o : main.c tree_node.h tree.h hash_table.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :
	rm $(OBJDIR)/*.o *.exe
