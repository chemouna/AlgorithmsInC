//
// Created by Mouna Cheikhna on 18/04/2017.
//

#include <vector>
#include <assert.h>

using namespace std;

struct node {
    int data;
    struct node *next;
};

void push(struct node **head_ref, int new_data) {
    struct node *new_node =
            (struct node *) malloc(sizeof(struct node));

    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct node *node) {
    while (node != NULL) {
        printf("%d ", node->data);
        printf("%u \n", node);
        node = node->next;
    }
}

void MoveNode(struct node **destRef, struct node **sourceRef) {
    struct node *newNode = *sourceRef; // the front source node
    assert(newNode != NULL);
    *sourceRef = newNode->next; // Advance the source pointer
    newNode->next = *destRef; // Link the old dest off the new node
    *destRef = newNode; // Move dest to point to the new node
}

void AlternatingSplit(struct node *source,
                      struct node **aRef, struct node **bRef) {
    struct node *a = NULL; // Split the nodes to these 'a' and 'b' lists
    struct node *b = NULL;
    struct node *current = source;
    while (current != NULL) {
        MoveNode(&a, &current); // Move a node to the first split
        if (current != NULL) {
            MoveNode(&b, &current); // Move a node to the second split
        }
    }
    *aRef = a;
    *bRef = b;
}


int main() {
    struct node *head = NULL;
    struct node *a = NULL;
    struct node *b = NULL;

    /* 0->1->2->3->4->5 */
    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);
    push(&head, 0);

    printf("\nOriginal linked List: \n ");
    printList(head);

    AlternatingSplit(head, &a, &b);

    printf("\nAlternating split first part with 'a' : \n");
    printList(a);

    printf("\n Alternating split second part with 'b' : \n");
    printList(b);

    getchar();
    return 0;
}




