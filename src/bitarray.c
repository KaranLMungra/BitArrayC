#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include"bitarray.h"


struct bit_array_t *new_bit_array_t(int n, int val)
{
    if(n < 0) return NULL;
    uint64_t v = val != 0 ? ~(0): 0;
    int len = n / WORD_SIZE + 1;
    struct bit_array_t *ba = (struct bit_array_t *)malloc(sizeof *ba);
    ba->arr = (uint64_t *)malloc(sizeof(uint64_t) * len);
    ba->len = len;
    ba->n = n;
    for (int i = 0; i < len; ++i) ba->arr[i] = v;
    ba->get_val = get_val_bit_array_t;
    ba->set_active = set_active_bit_array_t;
    ba->set_inactive = set_inactive_bit_array_t;
    return ba;
}

uint64_t get_val_bit_array_t(const struct bit_array_t *ba, int i)
{
    if(ba == NULL) return 3;
    if (i >= ba->n && ba->n < 0) return 2;
    int l = i / 64;
    uint64_t mask = 1 << i - (WORD_SIZE * l);
    return (ba->arr[l] & mask) == mask;
}

int set_active_bit_array_t(struct bit_array_t *ba, int i)
{
    if(ba == NULL)
        return 3;
    if (i >= ba->n && ba->n < 0)
        return 2;
    int l = i / WORD_SIZE;
    uint64_t mask = 1 << i - (WORD_SIZE * l);
    ba->arr[l] |= mask;
}

int set_inactive_bit_array_t(struct bit_array_t *ba, int i)
{
    if(ba == NULL)
        return 3;
    if (i >= ba->n && ba->n < 0)
        return 2;
    int l = i / WORD_SIZE;
    uint64_t mask = ~(1 << i - (WORD_SIZE * l));
    ba->arr[l] &= mask;
}

void display_bit_array_t(const struct bit_array_t *ba)
{  
    if(ba == NULL) {
        printf("BitArray{NULL}\n");
        return;
    }
    printf("BitArray{%d}", ba->n);
    for (int i = 0; i < ba->n; ++i)
    {
        if (i == 0)
            printf("[%d", ba->get_val(ba, i));
        else
            printf(", %d", ba->get_val(ba, i));
    }
    printf("]\n");
}

void del_bit_array_t(struct bit_array_t *ba)
{
    if(ba == NULL)
        return;
    free(ba->arr);
    free(ba);
    return;
}
