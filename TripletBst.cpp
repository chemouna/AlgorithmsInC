//
// Created by Mouna Cheikhna on 07/04/2017.
//
#include<stdio.h>

/**
 * Given a Balanced Binary Search Tree (BST), write a function isTripletPresent() that returns true if there
 * is a triplet in given BST with sum equals to 0, otherwise returns false.
 */

struct node {
    int key;
    struct node *left;
    struct node *right;
};

void convertBSTtoDll(node *root, node **head, node **tail) {
    if (root == NULL) {
        return;
    }

    if (root->left) {
        convertBSTtoDll(root->left, head, tail);
    }

    // Change left of current root as last node of left subtree
    root->left = *tail;

    // If tail is not NULL, then set right of tail as root, else current
    // node is head
    if (*tail)
        (*tail)->right = root;
    else
        *head = root;

    // Update tail
    *tail = root;

    // Finally, convert right subtree
    if (root->right) {
        convertBSTtoDll(root->right, head, tail);
    }

}




