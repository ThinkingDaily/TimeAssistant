/*
reverse_link.c

Reverse a single linked list.

gcc reverse_link.c
./a.out 
valgrind --tool=memcheck ./a.out
*/
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* reverse(struct node* head)
{
    if (NULL == head) return NULL;
    
    struct node* previous = NULL;
    struct node* next = NULL;
    
    for (;;) {
        next = head->next;
        head->next = previous;
        
        if (NULL == next) return head;
        
        previous = head;
        head = next;
    }
}

struct node* new_node(int data)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    //TODO if (NULL == node) ...
    node->data = data;
    node->next = NULL;
    return node;
}

void append(struct node** head, int data)
{
    if (NULL == *head) {
        *head = new_node(data);
        return;
    }
    
    struct node* next = *head;
    for (; next->next; ) {
        next = next->next;
    }
    
    next->next = new_node(data);
}

void print(struct node* head)
{
    struct node* p = head;
    for (; p; p = p->next) {
        printf("%d\t", p->data);
    }
    printf("\n");
}

void delete(struct node* head)
{
    struct node* next = head;
    for (;; ) {
        if (NULL == head) break;
        
        next = head->next;
        free(head);
        head = next;
    }
    
    head = NULL;
}

int main()
{
    struct node* head = NULL;
    int data[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int i;
    
    for (i = 0; i < sizeof(data) / sizeof(int); i++) {
        append(&head, data[i]);
    }
    
    print(head);
    head = reverse(head);
    print(head);
    delete(head);
    
    return 0;
}

