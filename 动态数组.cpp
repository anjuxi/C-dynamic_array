#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 动态数组结构体
typedef int Data;

typedef struct {
    Data* data;         // 数据指针
    int size;           // 当前元素个数
    int capacity;       // 当前容量
} Vector;

// 函数声明
Vector* vectorCreate(void);
Vector* vectorCreateWithCapacity(int initialCapacity);
void vectorDestroy(Vector* vec);

// 基本操作
void vectorPush(Vector* vec, Data val); // 压栈
void vectorPop(Vector* vec); // 出栈
Data vectorGet(Vector* vec, int index); // 获取元素
void vectorSet(Vector* vec, int index, Data val); // 设置元素
Data* vectorAt(Vector* vec, int index); // 获取元素指针
Data vectorFront(Vector* vec); // 获取第一个元素
Data vectorBack(Vector* vec); // 获取最后一个元素

// 容量管理
void vectorReserve(Vector* vec, int newCapacity);
void vectorResize(Vector* vec, int newSize);
void vectorShrinkToFit(Vector* vec);
void vectorClear(Vector* vec);
bool vectorIsEmpty(Vector* vec);
int vectorSize(Vector* vec);
int vectorCapacity(Vector* vec);

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
void vectorReverse(Vector* vec);
void vectorSort(Vector* vec);

// 遍历
void vectorPrint(Vector* vec);

// ========== 函数实现 ==========

// 创建动态数组（默认容量为4）
Vector* vectorCreate(void) {
    return vectorCreateWithCapacity(4);
}

// 指定初始容量创建动态数组
Vector* vectorCreateWithCapacity(int initialCapacity) {
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if (!vec) return NULL;
    
    vec->data = (Data*)malloc(sizeof(Data) * initialCapacity);
    if (!vec->data) {
        free(vec);
        return NULL;
    }
    
    vec->size = 0;
    vec->capacity = initialCapacity;
    return vec;
}

// 销毁动态数组
void vectorDestroy(Vector* vec) {
    if (!vec) return;
    free(vec->data);
    free(vec);
}

// 扩容检查
static void vectorGrow(Vector* vec) {
    if (vec->size >= vec->capacity) {
        int newCapacity = vec->capacity * 2;
        Data* newData = (Data*)realloc(vec->data, sizeof(Data) * newCapacity);
        if (!newData) return;
        vec->data = newData;
        vec->capacity = newCapacity;
    }
}

// 尾部添加元素
void vectorPush(Vector* vec, Data val) {
    if (!vec) return;
    vectorGrow(vec);
    vec->data[vec->size++] = val;
}

// 尾部删除元素
void vectorPop(Vector* vec) {
    if (!vec || vec->size <= 0) return;
    vec->size--;
}

// 获取指定位置元素
Data vectorGet(Vector* vec, int index) {
    if (!vec || index < 0 || index >= vec->size) return 0;
    return vec->data[index];
}

// 设置指定位置元素
void vectorSet(Vector* vec, int index, Data val) {
    if (!vec || index < 0 || index >= vec->size) return;
    vec->data[index] = val;
}

// 获取指定位置元素的指针
Data* vectorAt(Vector* vec, int index) {
    if (!vec || index < 0 || index >= vec->size) return NULL;
    return &vec->data[index];
}

// 获取首元素
Data vectorFront(Vector* vec) {
    if (!vec || vec->size <= 0) return 0;
    return vec->data[0];
}

// 获取尾元素
Data vectorBack(Vector* vec) {
    if (!vec || vec->size <= 0) return 0;
    return vec->data[vec->size - 1];
}

// 预留空间
void vectorReserve(Vector* vec, int newCapacity) {
    if (!vec || newCapacity <= vec->capacity) return;
    Data* newData = (Data*)realloc(vec->data, sizeof(Data) * newCapacity);
    if (!newData) return;
    vec->data = newData;
    vec->capacity = newCapacity;
}

// 调整大小
void vectorResize(Vector* vec, int newSize) {
    if (!vec) return;
    if (newSize > vec->capacity) {
        vectorReserve(vec, newSize);
    }
    if (newSize > vec->size) {
        memset(&vec->data[vec->size], 0, sizeof(Data) * (newSize - vec->size));
    }
    vec->size = newSize;
}

// 收缩到合适大小
void vectorShrinkToFit(Vector* vec) {
    if (!vec || vec->capacity == vec->size) return;
    Data* newData = (Data*)realloc(vec->data, sizeof(Data) * vec->size);
    if (!newData) return;
    vec->data = newData;
    vec->capacity = vec->size;
}

// 清空数组
void vectorClear(Vector* vec) {
    if (!vec) return;
    vec->size = 0;
}

// 判断是否为空
bool vectorIsEmpty(Vector* vec) {
    return !vec || vec->size == 0;
}

// 获取元素个数
int vectorSize(Vector* vec) {
    return vec ? vec->size : 0;
}

// 获取容量
int vectorCapacity(Vector* vec) {
    return vec ? vec->capacity : 0;
}

// 在指定位置插入元素
void vectorInsert(Vector* vec, int index, Data val) {
    if (!vec || index < 0 || index > vec->size) return;
    vectorGrow(vec);
    for (int i = vec->size; i > index; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[index] = val;
    vec->size++;
}

// 删除指定位置元素
void vectorErase(Vector* vec, int index) {
    if (!vec || index < 0 || index >= vec->size) return;
    for (int i = index; i < vec->size - 1; i++) {
        vec->data[i] = vec->data[i + 1];
    }
    vec->size--;
}

// 删除第一个匹配的元素
void vectorRemove(Vector* vec, Data val) {
    if (!vec) return;
    int index = vectorFind(vec, val);
    if (index != -1) {
        vectorErase(vec, index);
    }
}

// 查找元素位置
int vectorFind(Vector* vec, Data val) {
    if (!vec) return -1;
    for (int i = 0; i < vec->size; i++) {
        if (vec->data[i] == val) return i;
    }
    return -1;
}

// 判断是否包含元素
bool vectorContains(Vector* vec, Data val) {
    return vectorFind(vec, val) != -1;
}

// 统计元素出现次数
int vectorCount(Vector* vec, Data val) {
    if (!vec) return 0;
    int count = 0;
    for (int i = 0; i < vec->size; i++) {
        if (vec->data[i] == val) count++;
    }
    return count;
}

// 批量添加数组元素
void vectorPushArray(Vector* vec, Data* arr, int n) {
    if (!vec || !arr || n <= 0) return;
    for (int i = 0; i < n; i++) {
        vectorPush(vec, arr[i]);
    }
}

// 复制动态数组
void vectorCopy(Vector* src, Vector* dest) {
    if (!src || !dest) return;
    vectorClear(dest);
    vectorReserve(dest, src->size);
    memcpy(dest->data, src->data, sizeof(Data) * src->size);
    dest->size = src->size;
}

// 反转数组
void vectorReverse(Vector* vec) {
    if (!vec || vec->size <= 1) return;
    int left = 0, right = vec->size - 1;
    while (left < right) {
        Data temp = vec->data[left];
        vec->data[left] = vec->data[right];
        vec->data[right] = temp;
        left++;
        right--;
    }
}

// 排序（冒泡排序）
void vectorSort(Vector* vec) {
    if (!vec || vec->size <= 1) return;
    for (int i = 0; i < vec->size - 1; i++) {
        for (int j = 0; j < vec->size - i - 1; j++) {
            if (vec->data[j] > vec->data[j + 1]) {
                Data temp = vec->data[j];
                vec->data[j] = vec->data[j + 1];
                vec->data[j + 1] = temp;
            }
        }
    }
}

// 打印数组
void vectorPrint(Vector* vec) {
    if (!vec) {
        printf("NULL\n");
        return;
    }
    printf("[");
    for (int i = 0; i < vec->size; i++) {
        printf("%d", vec->data[i]);
        if (i < vec->size - 1) printf(", ");
    }
    printf("] (size=%d, capacity=%d)\n", vec->size, vec->capacity);
}

// ========== 测试代码 ==========

int main() {
    printf("=== 动态数组测试 ===\n\n");
    
    // 创建动态数组
    Vector* vec = vectorCreate();
    printf("创建动态数组:\n");
    vectorPrint(vec);
    
    // 添加元素
    printf("\n添加元素 1, 2, 3, 4, 5:\n");
    vectorPush(vec, 1);
    vectorPush(vec, 2);
    vectorPush(vec, 3);
    vectorPush(vec, 4);
    vectorPush(vec, 5);
    vectorPrint(vec);
    
    // 在指定位置插入
    printf("\n在索引2处插入99:\n");
    vectorInsert(vec, 2, 99);
    vectorPrint(vec);
    
    // 删除元素
    printf("\n删除索引3处的元素:\n");
    vectorErase(vec, 3);
    vectorPrint(vec);
    
    // 获取元素
    printf("\n获取索引0处的元素: %d\n", vectorGet(vec, 0));
    printf("首元素: %d, 尾元素: %d\n", vectorFront(vec), vectorBack(vec));
    
    // 查找元素
    printf("\n查找元素99的位置: %d\n", vectorFind(vec, 99));
    printf("是否包含元素3: %s\n", vectorContains(vec, 3) ? "是" : "否");
    
    // 批量添加
    printf("\n批量添加数组 [10, 20, 30]:\n");
    Data arr[] = {10, 20, 30};
    vectorPushArray(vec, arr, 3);
    vectorPrint(vec);
    
    // 反转
    printf("\n反转数组:\n");
    vectorReverse(vec);
    vectorPrint(vec);
    
    // 排序
    printf("\n排序数组:\n");
    vectorSort(vec);
    vectorPrint(vec);
    
    // 预留空间
    printf("\n预留空间到20:\n");
    vectorReserve(vec, 20);
    vectorPrint(vec);
    
    // 收缩空间
    printf("\n收缩到合适大小:\n");
    vectorShrinkToFit(vec);
    vectorPrint(vec);
    
    // 复制数组
    printf("\n复制数组到vec2:\n");
    Vector* vec2 = vectorCreate();
    vectorCopy(vec, vec2);
    printf("vec2: ");
    vectorPrint(vec2);
    
    // 清空
    printf("\n清空vec:\n");
    vectorClear(vec);
    vectorPrint(vec);
    
    // 销毁
    vectorDestroy(vec);
    vectorDestroy(vec2);
    printf("\n数组已销毁\n");
    
    return 0;
}
