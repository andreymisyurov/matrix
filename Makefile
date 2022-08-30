CC = g++ -std=c++17 -Wall -Wextra -Werror
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
	$(CC) -c Matrix_oop.cpp

leaks: test_build
	$(LEAK_CHECK)

static:
	cp ./linters/CPPLINT.cfg .
	-python3 ./linters/cpplint.py Matrix_oop.cpp test.cpp
	-cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --std=c++17 Matrix_oop.cpp Matrix_oop.hpp
	rm -rf CPPLINT.cfg

test: test_build
	./testing.out
	rm -rf testing.out

test_build:
	$(CC) test.cpp matrix_oop.cpp -o testing.out $(CHECK_FLAGS)

gcov:
	$(CC) test.cpp matrix_oop.cpp -fprofile-arcs -ftest-coverage $(CHECK_FLAGS)
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
	git reset .DS_Store
	git commit -m"commit_from_makefile"
	git push origin main