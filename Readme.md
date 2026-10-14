
# Bloom Filter in C

A simple implementation of a **Bloom Filter** in C, a space-efficient probabilistic data structure used to test whether an element belongs to a set

## How It Works

* **Definitely absent:** The element was not inserted.
* **Possibly present:** The element may have been inserted, but false positives are possible.

## Build

Compile using GCC:

```bash
gcc test.c bloom.c -o test
```
