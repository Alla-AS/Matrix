.PHONY: all clean test objects build_lib rebuild clean_obj gcov_report
CC=gcc
CFLAGS=-Wall -Werror -Wextra -lstdc++

all: test

s21_matrix_oop.a: build_lib clean_obj

build_lib: objects
	@ar rc s21_matrix_oop.a s21_matrix_oop.o
	@ranlib s21_matrix_oop.a

objects:
	@$(CC) $(CFLAGS) -c s21_matrix_oop.cc

test: s21_matrix_oop.a test.cc
	@$(CC) $(CFLAGS) -lgtest test.cc s21_matrix_oop.a -o test
	@./test

check:
	cp ../materials/linters/.clang-format ../
	clang-format -i *.cc
	CK_FORK=no leaks --atExit -- ./test

gcov_report:
	gcc -lstdc++ -lcheck -lgtest --coverage s21_matrix_oop.cc test.cc -o gcov_report
	./gcov_report
	lcov --no-external -t "./gcov_report" -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	open ./report/index.html

clean_obj:
	@rm -rf *.o

clean: clean_obj
	@rm -rf *.a
	@rm -rf ./test
	@rm -rf gcov_report
	@rm -rf report
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info
	@rm -rf ../.clang-format

rebuild: clean all