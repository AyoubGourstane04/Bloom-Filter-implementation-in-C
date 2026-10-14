#include "bloom.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// Hash 1 implementing FNV-1a
static uint64_t hash_1(const char* str){
    uint64_t hash = 14695981039346656037ULL;

    while(*str){
        hash ^= (unsigned char)*str++;
        hash *= 1099511628211ULL;
    }

    return hash;
} 

// Hash 1 implemneting DJB
static uint64_t hash_2(const char* str){
    uint64_t hash = 5831;

    while(*str){
        hash = hash * 33 + (unsigned char)*str++;
    }

    return hash | 1ULL;
} 


// bit shift implementation of DJB
static uint64_t hash_2_bit_shift(const char* str){
    uint64_t hash = 5831;

    while(*str){
        hash =( hash << 5 )+ hash + (unsigned char)*str++;
    }

    return hash | 1ULL;
} 


int bloom_init(BloomFilter* filter, size_t hash_count, size_t bit_count){
    
}




void bloom_add(BloomFilter* filter, const char* item);
int bloom_contains(const BloomFilter* filter, const char* item);
void bloom_free(BloomFilter* filter);
