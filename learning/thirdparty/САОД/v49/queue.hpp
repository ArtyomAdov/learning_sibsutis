#ifndef QUEUE_H
#define QUEUE_H

#include "DB.h"
#include "iostream"
#include "iomanip"

using namespace std;

listnode *list_createnode(DB data);
listnode *list_addfront(listnode *l, DB data);

struct queue {
    listnode *head;
    listnode *tail;
    int size;
};

queue *queue_create();
void queue_free(queue *q);
int queue_size(queue *q);
void queue_enqueue(queue *q, DB data);
DB queue_dequeue(queue *q);
void queue_print(queue *q);

#endif
