/**
 * Author: FallAngel
 * Date: 15/07/2021
 * 
 * Single linked list implemenation in C
 * 
 * Compilation: 
 * $ gcc single_linked_list.c
 * $ ./a.out
 * 
 * Supported operations:
 * PUSH   - Add a node to the begining of the list
 * APPEND - Add a node to the end of the list
 * LOOKUP - Search in the list for a specific data (O(n))
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct slinked_t {
    void *data;
    size_t size;
    struct slinked_t *next;
} slinked_t;

// Keep the reference to the head and tail
// Useful for push and append operations
slinked_t *head = NULL, *tail = NULL;

// Allocate a single linked list structure and return
slinked_t* create(void *data, size_t size, slinked_t *next) 
{
    slinked_t *new = malloc(sizeof(slinked_t));
    new->data = data;
    new->size = size;
    new->next = next;
    return new;
}

// Will free all the nodes
void destroy(void) 
{
    int count = 0;
    slinked_t *curr = head, *next;
    while (curr) {
        count++;
        next = curr->next;
        free(curr);
        curr = next;
    }
    printf("Freed %d nodes\n", count);
}

void push(slinked_t *node)
{
    if (!head && node) {
        head = node;
        return;
    }
    else {
        node->next = head;
        head = node;
    }
}

void append(slinked_t *node)
{
    if (!tail && node) {
        tail = node;
        return;
    } else {
       tail->next = node;
       node->next = NULL;
       tail = node;
    }
}

void* lookup(void *data, size_t size)
{
    int count = 0;
    slinked_t *curr = head;
    while (curr) {
        count++;
        if (!memcmp(curr->data, data, size)) {
            printf("Data \"%s\" found after search through %d node(s)\n", (char*)curr->data, count);
            return curr->data;
        }
        curr = curr->next;
    }
    printf("Data \"%s\" not found! Looked up %d nodes!\n", (char*)curr->data, count);
    
    return NULL;
}

int main(void) 
{
    slinked_t *node1 = create("ABC", 4, NULL);
    slinked_t *node2 = create("DEF", 4, node1);
    slinked_t *node3 = create("GHI", 4, node2);
    slinked_t *node4 = create("JKL", 4, node3);
    slinked_t *node5 = create("XXX", 4, node4);

    push(node5);
    push(node1);
    append(node4);
    append(node3);
    append(node2);

    lookup("ABC", 4);
    lookup("DEF", 4);
    lookup("GHI", 4);
    lookup("JKL", 4);
    lookup("XXX", 4);

    destroy();

    return 0;
}