CC := clang
CFLAGS1=-Wall -Wextra -Werror -std=c11
CFLAGS=-Wall -Wextra -Werror -std=c11 -I/opt/homebrew/Cellar/check/0.15.2/include/ -D_THREAD_SAFE
LDFLAGS=-L/opt/homebrew/Cellar/check/0.15.2/lib
TEST_FLAGS=-lcheck -lm -pthread
GREP = main.c s21_funcs/s21_atoi.c s21_funcs/s21_binary.c s21_funcs/s21_case.c s21_funcs/s21_sprintf.c s21_funcs/s21_strlen.c
QUEST1 = s21_sprintf
LM = -lm

SRC_DIR=s21_funcs
TEST_DIR=tests

SRC_FILES=$(shell find $(SRC_DIR) -name "*.c")
TEST_FILES=$(shell find $(TEST_DIR) -name "*.c")

OBJ=$(SRC_FILES:.c=.o)
TOBJ=$(TEST_FILES:.c=.o)

LIB_NAME=s21_string.a
TARGET=s21_tests

UNAME=$(shell uname -s)

ifeq ($(UNAME), Linux)
    LIBS = -lcheck -lm -lrt -lpthread -lsubunit
else
    LIBS = -lcheck
endif

all: clean $(LIB_NAME)

clean:
	rm -rf $(OBJ) $(TOBJ) $(TARGET) $(TARGET)_gcov $(LIB_NAME) report coverage.info *.gcda *.gcno *.info log.txt

.PHONY: all clean test gcov_report check_style fix_style

test: $(TARGET)
	./$(TARGET)

s21_sprintf: $(GREP)
	$(CC) $(CFLAGS1) $^ -o $(QUEST1) $(LM)

$(LIB_NAME): $(OBJ)
	ar rcs $@ $^
	ranlib $@

$(TARGET): $(LIB_NAME) $(TOBJ)
	$(CC) $(CFLAGS) $(TOBJ) $(LIB_NAME) $(LDFLAGS) -o $@ $(TEST_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n --style=file $(SRC_DIR)/*.c $(SRC_DIR)/*.h $(TEST_DIR)/*.c
	clang-format -i --style=file $(SRC_DIR)/*.c $(SRC_DIR)/*.h $(TEST_DIR)/*.c
	rm ./.clang-format

gcov_report:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -I$(SRC_DIR) $(SRC_FILES) $(TEST_FILES) -o $(TARGET)_gcov -L/opt/homebrew/Cellar/check/0.15.2/lib -lcheck -lm -pthread
	./$(TARGET)_gcov
	lcov -t "$(TARGET)" -o $(TARGET).info -c -d .
	genhtml -o report $(TARGET).info
	xdg-open report/index.html || open report/index.html
