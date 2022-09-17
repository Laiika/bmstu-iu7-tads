#!/bin/bash

cd "/proc/$PPID/cwd"

gcc -std=c99 -Wall -Wextra -Wpedantic -Werror -c read_number.c
gcc -std=c99 -Wall -Wextra -Wpedantic -Werror -c normalize_number.c
gcc -std=c99 -Wall -Wextra -Wpedantic -Werror -c mult_numbers.c
gcc -std=c99 -Wall -Wextra -Wpedantic -Werror -c calc_exp.c
gcc -std=c99 -Wall -Wextra -Wpedantic -Werror -c round_mantissa.c
gcc -std=c99 -Wall -Wextra -Wpedantic -Werror -c print_number.c
gcc -std=c99 -Wall -Wextra -Wpedantic -Werror -c main.c
gcc -o app.exe main.o read_number.o normalize_number.o mult_numbers.o calc_exp.o round_mantissa.o print_number.o

echo "Compile"
