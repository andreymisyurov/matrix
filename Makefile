CC = g++ -std=c++17 -Wall -Wextra -Werror
OS = $(shell uname)
SUPPRESS = --suppress=missingIncludeSystem --suppress=unusedFunction --suppress=unmatchedSuppression --suppress=syntaxError

LEAK_CHECK = leaks --atExit -q -- ./testing.out
CHECK_FLAGS = -lgtest
OPEN = open ./report/index.html
ifeq ($(OS), Linux)
CHECK_FLAGS += -lpthread -lgtest_main -L/usr/lib
OPEN = open ./report
LEAK_CHECK = valgrind --leak-check=full -s -q -- ./testing.out
endif

all: leaks static-test clean

leaks: test_build
	$(LEAK_CHECK)

clang-format:
	cp ./linters/.clang-format .
	-clang-format --sort-includes --style=Google -i *.cc
	-clang-format --sort-includes --style=Google -i *.h
	-rm .clang-format

clang:
	cp ./linters/.clang-format .
	-clang-format -n *.cc
	-clang-format -n *.h
	-rm .clang-format

static-test:
	-cp ./linters/CPPLINT.cfg .
	-python3 ./linters/cpplint.py my_matrix.h test.cc
	-cppcheck --enable=all $(SUPPRESS) --std=c++17 my_matrix.h
	rm -rf CPPLINT.cfg

test: test_build
	./testing.out

test_build:
	$(CC) test.cc -o testing.out $(CHECK_FLAGS)

gcov-report:
	$(CC) test.cc -fprofile-arcs -ftest-coverage $(CHECK_FLAGS)
	./a.out
	lcov -t "my_matrix" -o my_matrix.info -c -d .
	genhtml -o report my_matrix.info
	$(OPEN)

clean:
	rm -rf *.o *.a *.info *.gcno *.gcda a.out report *.out .clang-format *.dSYM

docker-run:
	docker build -t matrix-test . && docker run -it --rm --name tests matrix-test

docker-rm:
	docker rmi matrix-test
