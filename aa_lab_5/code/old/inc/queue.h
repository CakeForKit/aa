#ifndef QUEUE_H__
#define QUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <string.h>

#define MAX_LEN_KEY 10
#define MAX_COUNT_PAIRS 500
#define N 32    // кол-во групп

struct pair_c {
    char key[MAX_LEN_KEY];
    int num;
};
typedef struct pair_c pair_t;

struct group_s
{
    int sum;
    size_t len_pars;
    pair_t *pairs[MAX_COUNT_PAIRS];
};
typedef struct group_s group_t;

typedef struct node_s {
    void *data;
    struct node_s *next;
} node_t;

typedef struct queue_s {
    node_t *head;
    node_t *tail;
} queue_t;

int put(queue_t *q, void *data);

int get(queue_t *q, void **out_data);

void print_queue(queue_t *q, int n);


#endif // QUEUE_H__