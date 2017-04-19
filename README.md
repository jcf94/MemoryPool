# A C++ MemoryPool

Useage

```cpp
MemoryPool mem = MemoryPool(size);

int* a = (int*) mem.mbmalloc(sizeof(int));

*a = 12345;

mem.mbfree(a);
```