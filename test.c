#include "bloom.h"
#include<stdio.h>

int main(){

    BloomFilter filter;

    if(!bloom_init(&filter, 1000, 7)){
        fprintf(stderr, "Failed to initialize bloom filter");
        return 1;
    }

    bloom_add(&filter, "Gojira");
    bloom_add(&filter, "Radiohead");
    bloom_add(&filter, "Muse");
    bloom_add(&filter, "Oasis");
    bloom_add(&filter, "Tool");

    printf("Gojira : %s\n", bloom_contains(&filter, "Gojira") ? "Possibly present" : "definitely absent");
    printf("Radiohead : %s\n", bloom_contains(&filter, "Radiohead") ? "Possibly present" : "definitely absent");
    printf("Muse : %s\n", bloom_contains(&filter, "Muse") ? "Possibly present" : "definitely absent");
    printf("Oasis : %s\n", bloom_contains(&filter, "Oasis") ? "Possibly present" : "definitely absent");
    printf("Tool : %s\n", bloom_contains(&filter, "Tool") ? "Possibly present" : "definitely absent");
    printf("Bjork : %s\n", bloom_contains(&filter, "Bjork") ? "Possibly present" : "definitely absent");
    printf("The Strokes : %s\n", bloom_contains(&filter, "The Strokes") ? "Possibly present" : "definitely absent");

    bloom_free(&filter);

    return 0;
}