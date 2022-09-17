# Компилятор
CC := gcc
# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic

# Подпапка для объектных файлов
OBJDIR = out
# Общие объектные файлы
OBJS := $(OBJDIR)/queue_array.o $(OBJDIR)/queue_list.o

app.exe : $(OBJS) $(OBJDIR)/main.o
	$(CC) $^ -o $@

vpath %.h inc
vpath %.c src

$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/queue_array.o : queue_array.c queue_array.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/queue_list.o : queue_list.c queue_list.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/main.o : main.c queue_array.h queue_list.h return_codes.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :
	rm $(OBJDIR)/*.o *.exe
