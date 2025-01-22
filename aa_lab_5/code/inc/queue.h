#ifndef QUEUE_H__
#define QUEUE_H__

#include <iostream>
#include <queue>
#include <vector>
#include <assert.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

#define PARALLEL 1
#define DEBUG 0

#define MAX_LEN_KEY 20
#define COUNT_PAIRS 500
#define N 8    // кол-во групп

struct pair_t {
    char key[MAX_LEN_KEY];
    int num;
};

struct group_t
{
    int sum;
    std::vector<pair_t> pairs;
};


#endif // QUEUE_H__