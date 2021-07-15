/**
 * Author: FallAngel
 * Date: 15/07/2021
 * 
 * Doubly linked list implemenation in C
 * 
 * Compilation: 
 * $ gcc doubly_linked_list.c
 * $ ./a.out
 * 
 * Supported operations:
 * PUSH   - Add a node to the begining of the list
 * APPEND - Add a node to the end of the list
 * LOOKUP FORWARD - Search in the list for a specific data forwards HEAD (O(n))
 * LOOKUP BACKWARD - Search in the list for a specific data backwards TAIL (O(n))
 * INSERT AFTER - Insert a node after another node
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dlinked_t {
    void *data;
    size_t size;
    struct dlinked_t *prev;
    struct dlinked_t *next;
} dlinked_t;

// Keep the reference to the head and tail
// Useful for push and append operations
dlinked_t *head = NULL, *tail = NULL;

// Allocate and initilialize the node
dlinked_t* create(void *data, size_t size,
                  dlinked_t *prev, dlinked_t *next)
{
    dlinked_t *new = malloc(sizeof(dlinked_t));
    new->data = data;
    new->size = size;
    new->prev = prev;
    new->next = next;
    return new;
}

// Free (forwards) all nodes affter usage
void destroy(void) 
{
    dlinked_t *curr = head;
    int count = 0;
    while (curr) {
        count++;
        free(curr);
        curr = curr->next;
    }
    printf("\nFreed %d nodes\n", count);
}

void push(dlinked_t *node) 
{
    if ((!head && !tail) && node) {
        head = node;
        tail = node;
        return;
    } else {
        node->next = head;
        node->prev = NULL;
        head->prev = node;
        head = node;
    }
}

void append(dlinked_t *node)
{
    if ((!tail && !head) && node) {
        tail = node;
        head = node;
        return;
    } else {
        node->next = NULL;
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
}

void* lookupForward(void *data, size_t size)
{
    dlinked_t *curr = head;
    int count = 0;
    while (curr) {
        count++;
        if (!memcmp(curr->data, data, size)) {
            printf("Data \"%s\" found after search through %d node(s)\n", (char*)curr->data, count);
            return curr->data;
        }
        curr = curr->next;
    }

    printf("Data \"%s\" not found! Looked up %d nodes!\n", (char*)data, count);
    return NULL;
}

void* lookupBackward(void *data, size_t size)
{
    dlinked_t *curr = tail;
    int count = 0;
    while (curr) {
        count++;
        if (!memcmp(curr->data, data, size)) {
            printf("Data \"%s\" found after search through %d node(s)\n", (char*)curr->data, count);
            return curr->data;
        }
        curr = curr->prev;
    }

    printf("Data \"%s\" not found! Looked up %d nodes!\n", (char*)data, count);
    return NULL;
}

// Insert n2 after n1
void insertAfter(dlinked_t* n1, dlinked_t *n2)
{
    if (!n1) {
        printf("the given previous node cannot be NULL");
        return;
    }
 
    n2->next = n1->next;
    n1->next = n2;
    n2->prev = n1;
  
    if (n2->next != NULL)
        n2->next->prev = n2;
}

int main(void)
{
    dlinked_t *node1 = create("ABC", 4, NULL, NULL);
    dlinked_t *node2, *node3, *node4, *node5, *node6;

    node2 = create("DEF", 4, node1, node3);
    node3 = create("GHI", 4, node2, node4);
    node4 = create("JKL", 4, node3, node5);
    node5 = create("XXX", 4, node4, node6);
    node6 = create("ZZZ", 4, node5, NULL);

    push(node1);
    append(node2);
    append(node3);
    append(node4);
    append(node5);

    insertAfter(node4, node6);

    printf("Searching \"XXX\" Forwards ...\n");
    lookupForward("XXX", 4);

    printf("\nSearching \"XXX\" Backwards ...\n");
    lookupBackward("XXX", 4);

    printf("\nSearching \"ABC\" Forwards ...\n");
    lookupForward("ABC", 4);

    printf("\nSearching \"ABC\" Backwards ...\n");
    lookupBackward("ABC", 4);

    printf("\nSearching \"ABC\" Forwards ...\n");
    lookupForward("ZZZ", 4);

    printf("\nSearching \"ABC\" Backwards ...\n");
    lookupBackward("ZZZ", 4);

    destroy();
}