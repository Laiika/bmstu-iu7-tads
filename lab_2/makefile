OBJS := read_perf.o read_perfs.o add_delete_perf.o print_perfs_table.o search_music_perfs.o sort_perfs.o get_keys_array.o print_keys_table.o sort_keys.o

app.exe : $(OBJS) main.o
	gcc $^ -o $@


read_perf.o : read_perf.c perf.h errors.h
	gcc -std=c99 -Wall -Werror -pedantic -c read_perf.c

read_perfs.o : read_perfs.c perf.h perfs.h errors.h key.h
	gcc -std=c99 -Wall -Werror -pedantic -c read_perfs.c

add_delete_perf.o : add_delete_perf.c perf.h perfs.h errors.h key.h
	gcc -std=c99 -Wall -Werror -pedantic -c add_delete_perf.c

print_perfs_table.o : print_perfs_table.c perf.h perfs.h errors.h key.h
	gcc -std=c99 -Wall -Werror -pedantic -c print_perfs_table.c

search_music_perfs.o : search_music_perfs.c perf.h perfs.h errors.h key.h
	gcc -std=c99 -Wall -Werror -pedantic -c search_music_perfs.c

sort_perfs.o : sort_perfs.c perf.h perfs.h errors.h key.h
	gcc -std=c99 -Wall -Werror -pedantic -c sort_perfs.c


print_keys_table.o : print_keys_table.c errors.h key.h
	gcc -std=c99 -Wall -Werror -pedantic -c print_keys_table.c

get_keys_array.o : get_keys_array.c perf.h key.h errors.h
	gcc -std=c99 -Wall -Werror -pedantic -c get_keys_array.c

sort_keys.o : sort_keys.c key.h errors.h
	gcc -std=c99 -Wall -Werror -pedantic -c sort_keys.c


main.o : main.c perf.h perfs.h errors.h key.h
	gcc -std=c99 -Wall -Werror -pedantic -c main.c

clean :
	rm *.o *.exe
