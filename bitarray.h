#include <stdint.h>

#define WORD_SIZE 64

typedef struct bit_array_t
{
    uint64_t *arr;
    int n;
    int len;
    uint64_t (*get_val)(const struct bit_array_t *, int);
    int (*set_active)(struct bit_array_t *, int);
    int (*set_inactive)(struct bit_array_t *, int);
} BitArray;

// methods
uint64_t get_val_bit_array_t(const struct bit_array_t *, int);
int set_active_bit_array_t(struct bit_array_t *, int);
int set_inactive_bit_array_t(struct bit_array_t *, int);

//associated methods
struct bit_array_t *new_bit_array_t(int, int);
void del_bit_array_t(struct bit_array_t *);
void display_bit_array_t(const struct bit_array_t *);

typedef BitArray *BitArrayptr;

struct bitArrayClass
{
    BitArrayptr (*new)(int, int);
    void (*del)(BitArray *);
    void (*debug_print)(const BitArray *);

} bitArrayClass = {.new = new_bit_array_t, .del = del_bit_array_t, .debug_print = display_bit_array_t};