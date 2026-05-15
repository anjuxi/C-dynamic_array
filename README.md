# C语言动态数组 (Dynamic Array in C)

[![C](https://img.shields.io/badge/C-99%2F11-blue.svg)](https://en.wikipedia.org/wiki/C99)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

一个用C语言实现的高性能动态数组（Vector）数据结构，类似于C++ STL中的`std::vector`。

## 功能特性

- **动态扩容**：自动扩容机制，容量不足时自动翻倍
- **完整API**：提供创建、销毁、增删改查等完整操作
- **内存安全**：完善的空指针检查和边界检查
- **高效操作**：支持批量操作、排序、反转等常用功能
- **类型可扩展**：通过`typedef`可轻松更改存储的数据类型

## 支持的编译器

- GCC
- Clang
- MSVC
- MinGW

## 快速开始

### 编译

```bash
gcc -o 动态数组 动态数组.cpp
```

### 使用示例

```c
#include <stdio.h>

// 引入动态数组实现
// ... (将代码复制到你的项目中)

int main() {
    // 创建动态数组
    Vector* vec = vectorCreate();
    
    // 添加元素
    vectorPush(vec, 10);
    vectorPush(vec, 20);
    vectorPush(vec, 30);
    
    // 打印数组
    vectorPrint(vec);  // 输出: [10, 20, 30] (size=3, capacity=4)
    
    // 获取元素
    int first = vectorFront(vec);  // 10
    int last = vectorBack(vec);    // 30
    int val = vectorGet(vec, 1);   // 20
    
    // 插入和删除
    vectorInsert(vec, 1, 15);  // 在索引1处插入15
    vectorErase(vec, 2);       // 删除索引2处的元素
    
    // 查找元素
    int index = vectorFind(vec, 20);  // 返回元素20的索引
    bool exists = vectorContains(vec, 15);  // 检查是否包含15
    
    // 排序和反转
    vectorSort(vec);     // 冒泡排序
    vectorReverse(vec);  // 反转数组
    
    // 销毁数组
    vectorDestroy(vec);
    
    return 0;
}
```

## API文档

### 创建与销毁

| 函数                                                    | 说明                        |
| ------------------------------------------------------- | --------------------------- |
| `Vector* vectorCreate(void)`                            | 创建动态数组（默认容量为4） |
| `Vector* vectorCreateWithCapacity(int initialCapacity)` | 指定初始容量创建动态数组    |
| `void vectorDestroy(Vector* vec)`                       | 销毁动态数组，释放内存      |

### 基本操作

| 函数                                               | 说明                   |
| -------------------------------------------------- | ---------------------- |
| `void vectorPush(Vector* vec, Data val)`           | 在尾部添加元素         |
| `void vectorPop(Vector* vec)`                      | 删除尾部元素           |
| `Data vectorGet(Vector* vec, int index)`           | 获取指定位置元素       |
| `void vectorSet(Vector* vec, int index, Data val)` | 设置指定位置元素       |
| `Data* vectorAt(Vector* vec, int index)`           | 获取指定位置元素的指针 |
| `Data vectorFront(Vector* vec)`                    | 获取第一个元素         |
| `Data vectorBack(Vector* vec)`                     | 获取最后一个元素       |

### 容量管理

| 函数                                               | 说明               |
| -------------------------------------------------- | ------------------ |
| `void vectorReserve(Vector* vec, int newCapacity)` | 预留空间           |
| `void vectorResize(Vector* vec, int newSize)`      | 调整数组大小       |
| `void vectorShrinkToFit(Vector* vec)`              | 收缩容量以适应大小 |
| `void vectorClear(Vector* vec)`                    | 清空数组           |
| `bool vectorIsEmpty(Vector* vec)`                  | 判断是否为空       |
| `int vectorSize(Vector* vec)`                      | 获取元素个数       |
| `int vectorCapacity(Vector* vec)`                  | 获取当前容量       |

### 插入与删除

| 函数                                                  | 说明                 |
| ----------------------------------------------------- | -------------------- |
| `void vectorInsert(Vector* vec, int index, Data val)` | 在指定位置插入元素   |
| `void vectorErase(Vector* vec, int index)`            | 删除指定位置元素     |
| `void vectorRemove(Vector* vec, Data val)`            | 删除第一个匹配的元素 |

### 查找操作

| 函数                                         | 说明                         |
| -------------------------------------------- | ---------------------------- |
| `int vectorFind(Vector* vec, Data val)`      | 查找元素位置（返回索引或-1） |
| `bool vectorContains(Vector* vec, Data val)` | 判断是否包含元素             |
| `int vectorCount(Vector* vec, Data val)`     | 统计元素出现次数             |

### 批量操作

| 函数                                                  | 说明                 |
| ----------------------------------------------------- | -------------------- |
| `void vectorPushArray(Vector* vec, Data* arr, int n)` | 批量添加数组元素     |
| `void vectorCopy(Vector* src, Vector* dest)`          | 复制动态数组         |
| `void vectorReverse(Vector* vec)`                     | 反转数组             |
| `void vectorSort(Vector* vec)`                        | 排序数组（冒泡排序） |

### 遍历与输出

| 函数                            | 说明         |
| ------------------------------- | ------------ |
| `void vectorPrint(Vector* vec)` | 打印数组内容 |

## 数据结构

```c
typedef int Data;  // 数据类型，可修改为其他类型

typedef struct {
    Data* data;      // 数据指针
    int size;        // 当前元素个数
    int capacity;    // 当前容量
} Vector;
```

## 自定义数据类型

默认情况下，动态数组存储`int`类型数据。如需存储其他类型，修改以下定义：

```c
// 例如，改为存储 double 类型
typedef double Data;
```

对于复杂类型（如结构体），建议存储指针：

```c
typedef struct {
    char name[32];
    int age;
} Person;

typedef Person* Data;
```

## 时间复杂度

| 操作          | 平均时间复杂度 | 最坏时间复杂度 |
| ------------- | -------------- | -------------- |
| Push          | O(1)           | O(n)           |
| Pop           | O(1)           | O(1)           |
| Get/Set       | O(1)           | O(1)           |
| Insert/Erase  | O(n)           | O(n)           |
| Find/Contains | O(n)           | O(n)           |
| Sort          | O(n²)          | O(n²)          |
| Reverse       | O(n)           | O(n)           |

## 依赖

本项目仅依赖标准C库：

[![stdio.h](https://img.shields.io/badge/stdio.h-Standard%20C%20Library-blue.svg)](https://en.cppreference.com/w/c/io)
[![stdlib.h](https://img.shields.io/badge/stdlib.h-Standard%20C%20Library-blue.svg)](https://en.cppreference.com/w/c/memory)
[![stdbool.h](https://img.shields.io/badge/stdbool.h-Standard%20C%20Library-blue.svg)](https://en.cppreference.com/w/c/types/boolean)
[![string.h](https://img.shields.io/badge/string.h-Standard%20C%20Library-blue.svg)](https://en.cppreference.com/w/c/string/byte)

## 许可证

本项目采用 MIT 许可证 - 详见 [LICENSE](LICENSE) 文件

## 作者信息

**谙弆悕博士（Ailan Anjuxi）**

- 📧 邮箱：[anjuxi.ME@outlook.com](mailto:anjuxi.ME@outlook.com)
- 📞 SIP电话：[sip:anjuxi@sip.linphone.org](sip:anjuxi@sip.linphone.org)

---

*本项目为C语言数据结构学习与实践作品，欢迎交流讨论！*
