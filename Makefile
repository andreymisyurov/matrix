CC = g++ -std=c++17 #-Wall -Wextra -Werror
OS = $(shell uname)

LEAK_CHECK = leaks --atExit -q -- ./testing.out && rm -rf testing.out
CHECK_FLAGS = -lgtest
OPEN = open ./report/index.html
ifeq ($(OS), Linux)
CHECK_FLAGS += -lpthread -lgtest_main -L/usr/lib
OPEN = open ./report
LEAK_CHECK = valgrind --leak-check=full -s -q -- ./testing.out && rm -rf testing.out
endif

all: gcov

matrix_oop.a: matrix_oop.o
	ar -rvs s21_matrix_oop.a s21_matrix_oop.o
	rm -rf s21_matrix_oop.o

matrix_oop.o:
	$(CC) -c Matrix_oop.cc

leaks: test_build
	$(LEAK_CHECK)

static:
	cp ./linters/CPPLINT.cfg .
	-python3 ./linters/cpplint.py Matrix_oop.cc test.cc
	-cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --std=c++17 Matrix_oop.cc Matrix_oop.h
	rm -rf CPPLINT.cfg

test: test_build
	./testing.out
	rm -rf testing.out

test_build:
	$(CC) test.cc -o testing.out $(CHECK_FLAGS)

debug:
	$(CC) test.cc matrix_oop.cc -g -o testing.out $(CHECK_FLAGS)

gcov:
	$(CC) test.cc matrix_oop.cc -fprofile-arcs -ftest-coverage $(CHECK_FLAGS)
	./a.out
	lcov -t "matrix_oop" -o matrix_oop.info -c -d .
	genhtml -o report matrix_oop.info
	$(OPEN)
	sleep 25
	make clean

clean:
	rm -rf *.o *.a *.info *.gcno *.gcda a.out report *.out

push:
	git add .
	git commit -m"clean"
	git push origin main
