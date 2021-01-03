#include "queue.hpp"

listnode *list_createnode(DB data) {
    listnode *p;
    p = new listnode; // Âûהוכÿול ןאלÿעü
    if (p != 0) {
        p->data = data;
        p->next = NULL;
        p->prev = NULL;
    }
    return p;
}

listnode *list_addfront(listnode *l, DB data) {
    listnode *newnode;

    newnode = list_createnode(data);

    if (newnode != NULL) {
        newnode->next = l;
        if (l) l->prev = newnode;
        return newnode;
    }

    return l;
}


queue *queue_create() {
    queue *q = new queue;
    if (q != 0) {
        q->size = 0;
        q->head = 0;
        q->tail = 0;
    }
    return q;
}

void queue_free(queue *q) {
    while (q->size > 0)
        queue_dequeue(q);
    delete q;
}

int queue_size(queue *q) {
    return q->size;
}

void queue_enqueue(queue *q, DB data) {
    listnode *oldtail = q->tail;

    /* Create new node */
    q->tail = list_createnode(data);

    if (q->head == 0) {
        /* List is empty */
        q->head = q->tail;
    } else {
        /* Add new node to the end of list */
        oldtail->next = q->tail;
        q->tail->next = NULL;
    }
    q->size++;
}

DB queue_dequeue(queue *q) {
    DB value;
    listnode *p;

    if (q->size == 0) return {0, 0, 0, 0};

    /* Delete first node */
    value = q->head->data;
    p = q->head->next;
    delete (q->head);
    q->head = p;
    q->size--;
    return value;
}

void queue_print(queue *q) {
    listnode *data = q->head;
    while (data) {
        cout << setw(12) << data->data.author << ' '
         << setw(32) << data->data.title << ' '
         << setw(16) << data->data.publisher << ' '
         << setw(4) << data->data.year << ' '
         << setw(4) << data->data.num_of_page << ' '
         << endl;
        data = data->next;
    }
}

