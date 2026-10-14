#include "bloom.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//
//  Helper functions
//

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

static void set_bit(BloomFilter* filter, size_t index){
    size_t byte_index = index / 8;
    size_t bit_offset = index % 8;

    filter->bits[byte_index] |= (uint8_t)(1u << bit_offset);
}

static int get_bit(const BloomFilter* filter, size_t index){
    size_t byte_index = index / 8;
    size_t bit_offset = index % 8;

    return (filter->bits[byte_index] >> bit_offset) & 1u;
}



int bloom_init(BloomFilter* filter, size_t hash_count, size_t bit_count){
    if(filter == NULL || hash_count == 0 || bit_count == 0){
        fprintf(stderr, "Error Intialising the filter");
        return 0;
    }

    filter->bits = NULL;
    filter->bit_count = 0;
    filter->hash_count = 0;

    size_t byte_count = bit_count / 8 + (bit_count % 8 != 0);

    filter->bits = calloc(byte_count, sizeof(uint8_t));

    if(filter->bits == NULL){
        fprintf(stderr, "Error Intialising the filter");
        return 0;
    }

    filter->bit_count = bit_count;
    filter->hash_count = hash_count;

    return 1;
}


void bloom_add(BloomFilter* filter, const char* item){
    if(filter == NULL || filter->bits == NULL || item == NULL){
        fprintf(stderr, "Error Adding the item");
        return;
    }

    uint64_t hash1 = hash_1(item);
    uint64_t hash2 = hash_2(item);

    for(size_t i=0; i<filter->bit_count; i++){
        size_t index = (size_t)((hash1 + (uint64_t) i * hash2) % filter->bit_count);
        set_bit(filter, index);
    }
}

int bloom_contains(const BloomFilter* filter, const char* item){
    if(filter == NULL || filter->bits == NULL || item == NULL){
        fprintf(stderr, "Error Checking existence");
        return 0;
    }

    uint64_t hash1 = hash_1(item);
    uint64_t hash2 = hash_2(item);

    for(size_t i=0; i<filter->bit_count; i++){
        size_t index = (size_t)((hash1 + (uint64_t) i * hash2) % filter->bit_count);
       
        if(!get_bit(filter, index)){
            return 0;
        }
    }  

    return 1; 
}


void bloom_free(BloomFilter* filter){
    if(filter == NULL) return;

    free(filter->bits);
    filter->bits = NULL;
    filter->bit_count = 0;
    filter->hash_count = 0;

    free(filter);
}
