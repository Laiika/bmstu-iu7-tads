# Компилятор
CC := gcc
# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic

# Подпапка для объектных файлов
OBJDIR = out
# Общие объектные файлы
OBJS := $(OBJDIR)/stack_array.o $(OBJDIR)/stack_list.o

app.exe : $(OBJS) $(OBJDIR)/main.o
	$(CC) $^ -o $@

vpath %.h inc
vpath %.c src

$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/stack_array.o : stack_array.c stack_array.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/stack_list.o : stack_list.c stack_list.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/main.o : main.c stack_array.h stack_list.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :
	rm $(OBJDIR)/*.o *.exe
