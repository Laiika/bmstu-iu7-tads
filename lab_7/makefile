# Компилятор
CC := gcc
# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic

# Подпапка для объектных файлов
OBJDIR = out
# Общие объектные файлы
OBJS := $(OBJDIR)/node.o $(OBJDIR)/digraph.o

app.exe : $(OBJS) $(OBJDIR)/main.o
	$(CC) $^ -o $@

vpath %.h inc
vpath %.c src

$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/node.o : node.c node.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/digraph.o : digraph.c digraph.h node.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/main.o : main.c digraph.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :
	rm $(OBJDIR)/*.o *.exe
