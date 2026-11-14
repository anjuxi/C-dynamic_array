# 编译器与编译选项
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra

# 库名
LIB_STATIC = libvector.a
LIB_SHARED = libvector.dll
SRC = 动态数组.c
OBJ = 动态数组.o

# 可执行文件
TEST = test_vector

.PHONY: all static shared test clean

all: static shared

# 编译目标文件
$(OBJ): $(SRC) 动态数组.h
	$(CC) $(CFLAGS) -c -o $@ $<

# 静态库
static: $(LIB_STATIC)
$(LIB_STATIC): $(OBJ)
	ar rcs $@ $<

# 动态库（MinGW）
shared: $(LIB_SHARED)
$(LIB_SHARED): $(OBJ)
	$(CC) -shared -o $@ $<

# 编译并链接测试程序（使用静态库）
$(TEST): test_vector.c $(LIB_STATIC)
	$(CC) $(CFLAGS) -o $@ test_vector.c -L. -lvector

# 运行测试
test: $(TEST)
	./$(TEST)

clean:
	rm -f $(OBJ) $(LIB_STATIC) $(LIB_SHARED) $(TEST) *.exe
