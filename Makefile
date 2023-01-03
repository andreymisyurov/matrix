CC = g++ -std=c++17 -Wall -Wextra -Werror
OS = $(shell uname)
SUPPRESS = --suppress=missingIncludeSystem --suppress=unusedFunction --suppress=unmatchedSuppression --suppress=syntaxError

LEAK_CHECK = leaks --atExit -q -- ./testing.out && rm -rf testing.out
CHECK_FLAGS = -lgtest
OPEN = open ./report/index.html
ifeq ($(OS), Linux)
CHECK_FLAGS += -lpthread -lgtest_main -L/usr/lib
OPEN = open ./report
LEAK_CHECK = valgrind --leak-check=full -s -q -- ./testing.out && rm -rf testing.out
endif

all: gcov

leaks: test_build
	$(LEAK_CHECK)

clang-format:
	cp ./linters/.clang-format .
	-clang-format -i *.cc
	-clang-format -i *.h
	-rm .clang-format

clang:
	cp ./linters/.clang-format .
	-clang-format -n *.cc
	-clang-format -n *.h
	-rm .clang-format

static:
	cp ./linters/CPPLINT.cfg .
	-python3 ./linters/cpplint.py my_matrix.h test.cc
	-cppcheck --enable=all $(SUPPRESS) --std=c++17 my_matrix.h
	rm -rf CPPLINT.cfg

test: test_build
	./testing.out
	rm -rf testing.out

test_build:
	$(CC) test.cc -o testing.out $(CHECK_FLAGS)

gcov:
	$(CC) test.cc -fprofile-arcs -ftest-coverage $(CHECK_FLAGS)
	./a.out
	lcov -t "my_matrix" -o my_matrix.info -c -d .
	genhtml -o report my_matrix.info
	$(OPEN)

clean:
	rm -rf *.o *.a *.info *.gcno *.gcda a.out report *.out
