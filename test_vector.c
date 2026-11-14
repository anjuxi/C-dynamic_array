// 动态数组测试：覆盖边界条件、内存安全、异常输入

#include <stdio.h>
#include <stdlib.h>

#include "动态数组.h"

static int total = 0;
static int passed = 0;

#define CHECK(cond, msg) do { \
    total++; \
    if (cond) passed++; \
    else printf("  fail: %s (line %d)\n", msg, __LINE__); \
} while (0)

// 创建与销毁
static void test_create_destroy(void) {
    printf("创建与销毁\n");
    Vector* v = vectorCreate();
    CHECK(v != NULL, "默认创建非空");
    CHECK(vectorSize(v) == 0, "初始size为0");
    CHECK(vectorCapacity(v) == 4, "默认容量4");
    CHECK(vectorIsEmpty(v), "初始为空");
    vectorDestroy(v);

    Vector* v2 = vectorCreateWithCapacity(16);
    CHECK(v2 != NULL, "指定容量创建非空");
    CHECK(vectorCapacity(v2) == 16, "容量16");
    vectorDestroy(v2);

    CHECK(vectorCreateWithCapacity(0) == NULL, "容量0返回NULL");
    CHECK(vectorCreateWithCapacity(-5) == NULL, "负容量返回NULL");
}

// 基本读写
static void test_basic(void) {
    printf("基本读写\n");
    Vector* v = vectorCreate();
    vectorPush(v, 10); vectorPush(v, 20); vectorPush(v, 30);
    CHECK(vectorSize(v) == 3, "push后size=3");
    CHECK(vectorFront(v) == 10, "front=10");
    CHECK(vectorBack(v) == 30, "back=30");
    CHECK(vectorGet(v, 1) == 20, "get(1)=20");
    vectorSet(v, 1, 99);
    CHECK(vectorGet(v, 1) == 99, "set后get(1)=99");
    vectorPop(v);
    CHECK(vectorSize(v) == 2, "pop后size=2");
    CHECK(vectorBack(v) == 99, "pop后back=99");
    vectorDestroy(v);
}

// 越界访问不应崩溃也不应改数据
static void test_bounds(void) {
    printf("越界访问\n");
    Vector* v = vectorCreate();
    vectorPush(v, 1);
    CHECK(vectorGet(v, -1) == 0, "负索引get返回0");
    CHECK(vectorGet(v, 100) == 0, "越界get返回0");
    CHECK(vectorAt(v, -1) == NULL, "负索引at返回NULL");
    CHECK(vectorAt(v, 100) == NULL, "越界at返回NULL");
    vectorSet(v, -1, 5);
    CHECK(vectorSize(v) == 1, "越界set不改size");
    vectorInsert(v, -1, 5);
    CHECK(vectorSize(v) == 1, "负索引insert不改size");
    vectorInsert(v, 5, 5);
    CHECK(vectorSize(v) == 1, "越界insert不改size");
    vectorErase(v, 5);
    CHECK(vectorSize(v) == 1, "越界erase不改size");
    vectorDestroy(v);
}

// NULL指针安全：所有函数传NULL都不应崩溃
static void test_null_safety(void) {
    printf("NULL指针安全\n");
    vectorPush(NULL, 1); vectorPop(NULL); vectorGet(NULL, 0);
    vectorSet(NULL, 0, 1); vectorAt(NULL, 0); vectorFront(NULL);
    vectorBack(NULL); vectorReserve(NULL, 10); vectorResize(NULL, 5);
    vectorShrinkToFit(NULL); vectorClear(NULL); vectorDestroy(NULL);
    vectorInsert(NULL, 0, 1); vectorErase(NULL, 0); vectorRemove(NULL, 1);
    vectorFind(NULL, 1); vectorContains(NULL, 1); vectorCount(NULL, 1);
    vectorPushArray(NULL, NULL, 0); vectorCopy(NULL, NULL);
    vectorSwap(NULL, NULL); vectorReverse(NULL); vectorSort(NULL);
    vectorPrint(NULL);
    CHECK(1, "NULL操作不崩溃");
}

// 插入删除
static void test_insert_erase(void) {
    printf("插入删除\n");
    Vector* v = vectorCreate();
    vectorPushArray(v, (Data[]){1,2,3,4,5}, 5);
    vectorInsert(v, 2, 99);
    CHECK(vectorGet(v, 2) == 99, "插入后索引2为99");
    CHECK(vectorSize(v) == 6, "插入后size=6");
    CHECK(vectorGet(v, 3) == 3, "原索引2元素后移");
    vectorErase(v, 2);
    CHECK(vectorGet(v, 2) == 3, "删除后索引2恢复3");
    CHECK(vectorSize(v) == 5, "删除后size=5");
    vectorInsert(v, 0, 100);
    CHECK(vectorFront(v) == 100, "头部插入");
    vectorInsert(v, vectorSize(v), 200);
    CHECK(vectorBack(v) == 200, "尾部插入");
    vectorDestroy(v);
}

// 查找与计数
static void test_find_count(void) {
    printf("查找与计数\n");
    Vector* v = vectorCreate();
    vectorPushArray(v, (Data[]){1,2,3,2,4,2,5}, 7);
    CHECK(vectorFind(v, 2) == 1, "第一个2在索引1");
    CHECK(vectorFind(v, 99) == -1, "不存在返回-1");
    CHECK(vectorContains(v, 3), "包含3");
    CHECK(!vectorContains(v, 99), "不包含99");
    CHECK(vectorCount(v, 2) == 3, "2出现3次");
    CHECK(vectorCount(v, 99) == 0, "99出现0次");
    vectorDestroy(v);
}

// 容量管理
static void test_capacity(void) {
    printf("容量管理\n");
    Vector* v = vectorCreateWithCapacity(2);
    CHECK(vectorCapacity(v) == 2, "初始容量2");
    vectorPush(v, 1); vectorPush(v, 2);
    CHECK(vectorCapacity(v) == 2, "满时未扩容");
    vectorPush(v, 3);
    CHECK(vectorCapacity(v) == 4, "触发扩容到4");
    vectorReserve(v, 100);
    CHECK(vectorCapacity(v) == 100, "reserve到100");
    vectorReserve(v, 50);
    CHECK(vectorCapacity(v) == 100, "reserve小值不缩容");
    vectorResize(v, 10);
    CHECK(vectorSize(v) == 10, "resize到10");
    CHECK(vectorGet(v, 5) == 0, "扩容区为0");
    vectorShrinkToFit(v);
    CHECK(vectorCapacity(v) == 10, "shrink到size");
    vectorClear(v);
    CHECK(vectorSize(v) == 0, "clear后size=0");
    CHECK(vectorCapacity(v) == 10, "clear容量不变");
    vectorDestroy(v);
}

// 批量操作：排序、反转、复制、交换
static void test_batch(void) {
    printf("批量操作\n");
    Vector* v = vectorCreate();
    vectorPushArray(v, (Data[]){5,4,3,2,1}, 5);
    vectorSort(v);
    CHECK(vectorGet(v, 0) == 1, "排序后首元素1");
    CHECK(vectorGet(v, 4) == 5, "排序后尾元素5");
    vectorReverse(v);
    CHECK(vectorGet(v, 0) == 5, "反转后首5");
    CHECK(vectorGet(v, 4) == 1, "反转后尾1");

    Vector* c = vectorCreate();
    vectorCopy(v, c);
    CHECK(vectorSize(c) == vectorSize(v), "复制size相等");
    CHECK(vectorGet(c, 0) == vectorGet(v, 0), "复制首元素相等");
    vectorPush(v, 999);
    CHECK(vectorSize(c) == 5, "改原数组不影响副本");

    int fa = vectorFront(v), fb = vectorFront(c);
    vectorSwap(v, c);
    CHECK(vectorFront(v) == fb, "swap后v首为原c首");
    CHECK(vectorFront(c) == fa, "swap后c首为原v首");
    vectorDestroy(v); vectorDestroy(c);
}

// remove + 原始指针
static void test_remove_data(void) {
    printf("remove与原始指针\n");
    Vector* v = vectorCreate();
    vectorPushArray(v, (Data[]){10,20,30,20,40}, 5);
    vectorRemove(v, 20);
    CHECK(vectorFind(v, 20) == 2, "删第一个20后剩余在索引2");
    Data* raw = vectorData(v);
    CHECK(raw != NULL, "data非空");
    CHECK(raw[0] == 10, "原始首元素10");
    raw[0] = 99;
    CHECK(vectorGet(v, 0) == 99, "指针修改反映到数组");
    vectorDestroy(v);
}

int main(void) {
    printf("动态数组测试\n\n");
    test_create_destroy();
    test_basic();
    test_bounds();
    test_null_safety();
    test_insert_erase();
    test_find_count();
    test_capacity();
    test_batch();
    test_remove_data();
    printf("\n结果: %d/%d 通过\n", passed, total);
    return passed == total ? 0 : 1;
}
