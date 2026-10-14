#ifndef BLOOM_H
#define BLOOM_H

#include<stdint.h>
#include<stddef.h>



typedef struct{
    uint8_t* bits;
    size_t hash_count;
    size_t bit_count;
}BloomFilter;


int bloom_init(BloomFilter* filter, size_t hash_count, size_t bit_count);
void bloom_add(BloomFilter* filter, const char* item);
int bloom_contains(const BloomFilter* filter, const char* item);
void bloom_free(BloomFilter* filter);










#endif