// 动态数组（Vector）C语言库实现

#include "动态数组.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// 创建动态数组，默认容量4
Vector* vectorCreate(void) {
    return vectorCreateWithCapacity(4);
}

// 指定初始容量创建，容量必须大于0
// 失败返回NULL，成功返回Vector指针
Vector* vectorCreateWithCapacity(int initialCapacity) {
    if (initialCapacity <= 0)
        return NULL;
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if (!vec) return NULL;
    vec->data = (Data*)malloc(sizeof(Data) * (size_t)initialCapacity);
    if (!vec->data) {
        free(vec);
        return NULL;
    }
    vec->size = 0;
    vec->capacity = initialCapacity;
    return vec;
}

// 销毁动态数组，允许传NULL
void vectorDestroy(Vector* vec) {
    if (!vec) return;
    free(vec->data);
    vec->data = NULL;
    free(vec);
}

// 容量不足时翻倍扩容
// 返回true表示扩容成功（或本就有空间），false表示失败
static bool vectorGrow(Vector* vec) {
    if (vec->size >= vec->capacity) {
        if (vec->capacity > INT_MAX / 2) return false;  // 防溢出
        int newCapacity = vec->capacity * 2;
        Data* newData = (Data*)realloc(vec->data, sizeof(Data) * (size_t)newCapacity);
        if (!newData) return false;
        vec->data = newData;
        vec->capacity = newCapacity;
    }
    return true;
}

void vectorPush(Vector* vec, Data val) {
    if (!vec || !vectorGrow(vec)) return;
    vec->data[vec->size++] = val;
}

void vectorPop(Vector* vec) {
    if (!vec || vec->size <= 0) return;
    vec->size--;
}

// 越界返回0
Data vectorGet(Vector* vec, int index) {
    if (!vec || index < 0 || index >= vec->size) return 0;
    return vec->data[index];
}

void vectorSet(Vector* vec, int index, Data val) {
    if (!vec || index < 0 || index >= vec->size) return;
    vec->data[index] = val;
}

// 越界返回NULL
Data* vectorAt(Vector* vec, int index) {
    if (!vec || index < 0 || index >= vec->size) return NULL;
    return &vec->data[index];
}

Data vectorFront(Vector* vec) {
    if (!vec || vec->size <= 0) return 0;
    return vec->data[0];
}

Data vectorBack(Vector* vec) {
    if (!vec || vec->size <= 0) return 0;
    return vec->data[vec->size - 1];
}

// 预留容量，只扩容不缩容
void vectorReserve(Vector* vec, int newCapacity) {
    if (!vec || newCapacity <= vec->capacity) return;
    Data* newData = (Data*)realloc(vec->data, sizeof(Data) * (size_t)newCapacity);
    if (!newData) return;
    vec->data = newData;
    vec->capacity = newCapacity;
}

// 调整元素个数；扩容部分用0填充
// newSize必须非负
void vectorResize(Vector* vec, int newSize) {
    if (!vec || newSize < 0) return;
    if (newSize > vec->capacity) {
        vectorReserve(vec, newSize);
        if (vec->capacity < newSize) return;  // 扩容失败，不动size
    }
    if (newSize > vec->size)
        memset(&vec->data[vec->size], 0, sizeof(Data) * (size_t)(newSize - vec->size));
    vec->size = newSize;
}

// 收缩容量到当前size，释放多余内存
// 空数组不处理（避免realloc成空指针）
void vectorShrinkToFit(Vector* vec) {
    if (!vec || vec->capacity == vec->size) return;
    if (vec->size == 0) return;
    Data* newData = (Data*)realloc(vec->data, sizeof(Data) * (size_t)vec->size);
    if (!newData) return;
    vec->data = newData;
    vec->capacity = vec->size;
}

// 清空元素，不释放内存
void vectorClear(Vector* vec) {
    if (!vec) return;
    vec->size = 0;
}

bool vectorIsEmpty(Vector* vec) {
    return !vec || vec->size == 0;
}

int vectorSize(Vector* vec) {
    return vec ? vec->size : 0;
}

int vectorCapacity(Vector* vec) {
    return vec ? vec->capacity : 0;
}

// 返回原始数据指针，可直接读写底层数组
Data* vectorData(Vector* vec) {
    return vec ? vec->data : NULL;
}

// 在index处插入元素，后面的元素后移
// index范围：0 <= index <= size
void vectorInsert(Vector* vec, int index, Data val) {
    if (!vec || index < 0 || index > vec->size) return;
    if (!vectorGrow(vec)) return;
    if (index < vec->size)
        memmove(&vec->data[index + 1], &vec->data[index],
                sizeof(Data) * (size_t)(vec->size - index));
    vec->data[index] = val;
    vec->size++;
}

// 删除index处元素，后面的元素前移
void vectorErase(Vector* vec, int index) {
    if (!vec || index < 0 || index >= vec->size) return;
    if (index < vec->size - 1)
        memmove(&vec->data[index], &vec->data[index + 1],
                sizeof(Data) * (size_t)(vec->size - index - 1));
    vec->size--;
}

// 删除第一个等于val的元素
void vectorRemove(Vector* vec, Data val) {
    if (!vec) return;
    int idx = vectorFind(vec, val);
    if (idx != -1) vectorErase(vec, idx);
}

// 返回第一个匹配val的索引，没找到返回-1
int vectorFind(Vector* vec, Data val) {
    if (!vec) return -1;
    for (int i = 0; i < vec->size; i++)
        if (vec->data[i] == val) return i;
    return -1;
}

bool vectorContains(Vector* vec, Data val) {
    return vectorFind(vec, val) != -1;
}

// 统计val出现次数
int vectorCount(Vector* vec, Data val) {
    if (!vec) return 0;
    int count = 0;
    for (int i = 0; i < vec->size; i++)
        if (vec->data[i] == val) count++;
    return count;
}

// 批量追加n个元素，一次扩容后memcpy
void vectorPushArray(Vector* vec, Data* arr, int n) {
    if (!vec || !arr || n <= 0) return;
    int needed = vec->size + n;
    if (needed > vec->capacity) {
        // 按翻倍策略算到能装下为止
        int target = vec->capacity;
        while (target < needed) {
            if (target > INT_MAX / 2) { target = needed; break; }
            target *= 2;
        }
        vectorReserve(vec, target);
        if (vec->capacity < needed) return;
    }
    memcpy(&vec->data[vec->size], arr, sizeof(Data) * (size_t)n);
    vec->size = needed;
}

// 把src复制到dest，dest原有内容被清空
void vectorCopy(Vector* src, Vector* dest) {
    if (!src || !dest) return;
    vectorClear(dest);
    if (src->size == 0) return;
    vectorReserve(dest, src->size);
    if (dest->capacity < src->size) return;
    memcpy(dest->data, src->data, sizeof(Data) * (size_t)src->size);
    dest->size = src->size;
}

// 交换两个数组的内容，只换指针和元数据，O(1)
void vectorSwap(Vector* a, Vector* b) {
    if (!a || !b) return;
    Data* td = a->data;
    int ts = a->size, tc = a->capacity;
    a->data = b->data; a->size = b->size; a->capacity = b->capacity;
    b->data = td; b->size = ts; b->capacity = tc;
}

void vectorReverse(Vector* vec) {
    if (!vec || vec->size <= 1) return;
    int left = 0, right = vec->size - 1;
    while (left < right) {
        Data tmp = vec->data[left];
        vec->data[left] = vec->data[right];
        vec->data[right] = tmp;
        left++; right--;
    }
}

// qsort比较函数，升序
static int vectorCompare(const void* a, const void* b) {
    Data x = *(const Data*)a, y = *(const Data*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

// 排序，用标准库qsort，平均O(n log n)
void vectorSort(Vector* vec) {
    if (!vec || vec->size <= 1) return;
    qsort(vec->data, (size_t)vec->size, sizeof(Data), vectorCompare);
}

// 打印数组内容及size/capacity
void vectorPrint(Vector* vec) {
    if (!vec) { printf("NULL\n"); return; }
    printf("[");
    for (int i = 0; i < vec->size; i++) {
        printf("%d", vec->data[i]);
        if (i < vec->size - 1) printf(", ");
    }
    printf("] (size=%d, capacity=%d)\n", vec->size, vec->capacity);
}
