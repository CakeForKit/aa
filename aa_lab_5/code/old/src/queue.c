#include "queue.h"

void print_queue(queue_t *q, int n) {
    if (n == 2) {
        // node_t *node = q->head;
        // printf("head: %p\n", node);
        // pair_t *pair = node->data;
        // printf("\tdata: (%s : %d)\n", pair->key, pair->num);
        // if (node->next != NULL) {
        //     printf("node: %p\n", node->next);
        //     pair = node->next->data;
        //     printf("\tdata: (%s : %d)\n", pair->key, pair->num);
        //     if (node->next->next != NULL) {
        //         printf("node: %p\n", node->next->next);
        //         pair = node->next->next->data;
        //     printf("\tdata: (%s : %d)\n", pair->key, pair->num);
        //     }    
        // }
            
        node_t *node = q->head;
        printf("queue1:");
        while (node != NULL) {
            pair_t *pair = node->data;
            printf("\tnode: (%s : %d)\n", pair->key, pair->num);
            assert(node != node->next);
            node = node->next;
        }
        printf("\n");
    }
}

int put(queue_t *q, void *data) {
    assert(q != NULL && data != NULL);
    node_t *n = malloc(sizeof(node_t));
    if (n == NULL)
        return -1;
    n->data = data;
    n->next = NULL;

    if (q->head == NULL) {
        printf("change_head\n");
        q->head = n;
        q->tail = n;
    } else {
        assert(q->head->data != data);
        (q->tail)->next = n;
        q->tail = (q->tail)->next;
    }
    assert(q->tail->next == NULL);
    // print_queue(q, 2);
    
    return 0;
}

int get(queue_t *q, void **out_data) {
    assert(q != NULL);
    node_t *n = q->head;
    if (n == NULL)
        return -1;
    else if (n == q->tail)
        q->tail = NULL;
    q->head = n->next;
    *out_data = n->data;
    free(n);
    return 0;
}