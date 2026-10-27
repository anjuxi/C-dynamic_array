# Dynamic Array in C

[![C](https://img.shields.io/badge/C-99%2F11-blue.svg)](https://en.wikipedia.org/wiki/C99)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

A dynamic array (vector) in C, similar in spirit to C++ `std::vector`.

## Features

- **Dynamic growth** — doubles capacity when full
- **Common operations** — create, destroy, add, remove, get, set
- **Bounds and null checks** — basic memory safety
- **Batch operations** — copy, reverse, sort
- **Configurable element type** — change `Data` with a `typedef`

## Supported Compilers

- GCC
- Clang
- MSVC
- MinGW

## Quick Start

### Build

```bash
gcc -o vector vector.c
```

Use your actual source filename if it differs from `vector.c`.

### Example

```c
#include <stdio.h>

// Include the vector implementation
// ... (copy the code into your project)

int main() {
    // Create a vector
    Vector* vec = vectorCreate();

    // Push elements
    vectorPush(vec, 10);
    vectorPush(vec, 20);
    vectorPush(vec, 30);

    // Print
    vectorPrint(vec);  // [10, 20, 30] (size=3, capacity=4)

    // Access elements
    int first = vectorFront(vec);  // 10
    int last = vectorBack(vec);    // 30
    int val = vectorGet(vec, 1);   // 20

    // Insert and erase
    vectorInsert(vec, 1, 15);  // insert 15 at index 1
    vectorErase(vec, 2);       // erase element at index 2

    // Lookup
    int index = vectorFind(vec, 20);
    bool exists = vectorContains(vec, 15);

    // Sort and reverse
    vectorSort(vec);     // bubble sort
    vectorReverse(vec);

    // Destroy
    vectorDestroy(vec);

    return 0;
}
```

## API

### Create and destroy

| Function | Description |
| ------------------------------------------------------- | ------------------------------- |
| `Vector* vectorCreate(void)` | Create a vector (default capacity 4) |
| `Vector* vectorCreateWithCapacity(int initialCapacity)` | Create a vector with a given capacity |
| `void vectorDestroy(Vector* vec)` | Destroy the vector and free memory |

### Basic operations

| Function | Description |
| -------------------------------------------------- | ---------------------- |
| `void vectorPush(Vector* vec, Data val)` | Append an element |
| `void vectorPop(Vector* vec)` | Remove the last element |
| `Data vectorGet(Vector* vec, int index)` | Get the element at an index |
| `void vectorSet(Vector* vec, int index, Data val)` | Set the element at an index |
| `Data* vectorAt(Vector* vec, int index)` | Get a pointer to an element |
| `Data vectorFront(Vector* vec)` | Get the first element |
| `Data vectorBack(Vector* vec)` | Get the last element |

### Capacity

| Function | Description |
| -------------------------------------------------- | ------------------ |
| `void vectorReserve(Vector* vec, int newCapacity)` | Reserve capacity |
| `void vectorResize(Vector* vec, int newSize)` | Resize the vector |
| `void vectorShrinkToFit(Vector* vec)` | Shrink capacity to the current size |
| `void vectorClear(Vector* vec)` | Clear all elements |
| `bool vectorIsEmpty(Vector* vec)` | Check whether the vector is empty |
| `int vectorSize(Vector* vec)` | Get the element count |
| `int vectorCapacity(Vector* vec)` | Get the current capacity |

### Insert and erase

| Function | Description |
| ----------------------------------------------------- | -------------------- |
| `void vectorInsert(Vector* vec, int index, Data val)` | Insert at an index |
| `void vectorErase(Vector* vec, int index)` | Erase the element at an index |
| `void vectorRemove(Vector* vec, Data val)` | Remove the first matching element |

### Lookup

| Function | Description |
| -------------------------------------------- | ------------------------------ |
| `int vectorFind(Vector* vec, Data val)` | Find an element (index or -1) |
| `bool vectorContains(Vector* vec, Data val)` | Check whether an element exists |
| `int vectorCount(Vector* vec, Data val)` | Count occurrences |

### Batch operations

| Function | Description |
| ----------------------------------------------------- | -------------------- |
| `void vectorPushArray(Vector* vec, Data* arr, int n)` | Push an array of elements |
| `void vectorCopy(Vector* src, Vector* dest)` | Copy a vector |
| `void vectorReverse(Vector* vec)` | Reverse the vector |
| `void vectorSort(Vector* vec)` | Sort (bubble sort) |

### Output

| Function | Description |
| ------------------------------- | ------------ |
| `void vectorPrint(Vector* vec)` | Print the vector |

## Data Structure

```c
typedef int Data;  // element type; change as needed

typedef struct {
    Data* data;      // data pointer
    int size;        // current element count
    int capacity;    // current capacity
} Vector;
```

## Custom Element Types

By default the vector stores `int`. To store another type, change the typedef:

```c
// Example: store double
typedef double Data;
```

For structs, store pointers:

```c
typedef struct {
    char name[32];
    int age;
} Person;

typedef Person* Data;
```

## Complexity

| Operation | Average | Worst case |
| ------------- | -------------- | -------------- |
| Push | O(1) | O(n) |
| Pop | O(1) | O(1) |
| Get/Set | O(1) | O(1) |
| Insert/Erase | O(n) | O(n) |
| Find/Contains | O(n) | O(n) |
| Sort | O(n²) | O(n²) |
| Reverse | O(n) | O(n) |

## Dependencies

Only the C standard library:

[![stdio.h](https://img.shields.io/badge/stdio.h-Standard%20C%20Library-blue.svg)](https://en.cppreference.com/w/c/io)
[![stdlib.h](https://img.shields.io/badge/stdlib.h-Standard%20C%20Library-blue.svg)](https://en.cppreference.com/w/c/memory)
[![stdbool.h](https://img.shields.io/badge/stdbool.h-Standard%20C%20Library-blue.svg)](https://en.cppreference.com/w/c/types/boolean)
[![string.h](https://img.shields.io/badge/string.h-Standard%20C%20Library-blue.svg)](https://en.cppreference.com/w/c/string/byte)

## License

MIT — see [LICENSE](LICENSE).

## Author

**Dr. Ailan Anjuxi (谙弆悕)**

- Email: [anjuxi.ME@outlook.com](mailto:anjuxi.ME@outlook.com)
- SIP: [sip:anjuxi@sip.linphone.org](sip:anjuxi@sip.linphone.org)

---

*A C data-structure exercise. Feedback welcome.*
