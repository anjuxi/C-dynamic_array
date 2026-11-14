// 动态数组（Vector）C语言库头文件
// 用法类似C++的std::vector，支持动态扩容、随机访问、插入删除、查找排序

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdbool.h>

// 元素类型，按需修改（如 double、自定义结构体指针等）
typedef int Data;

// 动态数组
typedef struct {
    Data* data;         // 数据存储区
    int size;           // 当前元素个数
    int capacity;       // 已分配容量
} Vector;

// 创建与销毁
Vector* vectorCreate(void);
Vector* vectorCreateWithCapacity(int initialCapacity);
void vectorDestroy(Vector* vec);

// 基本读写
void vectorPush(Vector* vec, Data val);
void vectorPop(Vector* vec);
Data vectorGet(Vector* vec, int index);
void vectorSet(Vector* vec, int index, Data val);
Data* vectorAt(Vector* vec, int index);
Data vectorFront(Vector* vec);
Data vectorBack(Vector* vec);

// 容量管理
void vectorReserve(Vector* vec, int newCapacity);
void vectorResize(Vector* vec, int newSize);
void vectorShrinkToFit(Vector* vec);
void vectorClear(Vector* vec);
bool vectorIsEmpty(Vector* vec);
int vectorSize(Vector* vec);
int vectorCapacity(Vector* vec);
Data* vectorData(Vector* vec);

// 插入删除
void vectorInsert(Vector* vec, int index, Data val);
void vectorErase(Vector* vec, int index);
void vectorRemove(Vector* vec, Data val);

// 查找
int vectorFind(Vector* vec, Data val);
bool vectorContains(Vector* vec, Data val);
int vectorCount(Vector* vec, Data val);

// 批量操作
void vectorPushArray(Vector* vec, Data* arr, int n);
void vectorCopy(Vector* src, Vector* dest);
void vectorSwap(Vector* a, Vector* b);
void vectorReverse(Vector* vec);
void vectorSort(Vector* vec);

// 输出
void vectorPrint(Vector* vec);

#endif
