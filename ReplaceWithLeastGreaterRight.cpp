//
// Created by Mouna Cheikhna on 07/04/2017.
//

/**
 * Given an array of integers, replace every element with the least greater element on its right side in the array.
 * If there are no greater element on right side, replace it with -1.
 * Input: [8, 58, 71, 18, 31, 32, 63, 92, 43, 3, 91, 93, 25, 80, 28]
 * Output: [18, 63, 80, 25, 32, 43, 80, 93, 80, 25, 93, -1, 28, -1, -1]
 *
 */
#include "iostream"

using namespace std;

struct Node {
    int data;
    Node *left, *right;
};

Node *newNode(int item) {
    Node *n = new Node;
    n->data = item;
    n->left = n->right = NULL;
    return n;
}

void insert(Node *&node, int data, Node *&succ) {
    if (node == NULL) { //tree empty
        node = newNode(data);
        return;
    }

    if (data < node->data) {
        succ = node;
        insert(node->left, data, succ);
    } else {
        insert(node->right, data, succ);
    }
}

void replace(int arr[], int n) {
    Node *root = NULL;
    for (int i = n - 1; i >= 0; i--) {
        Node *succ = NULL;
        insert(root, arr[i], succ);
        arr[i] = succ ? succ->data : -1;
    }
}

int main() {
    int arr[] = {8, 58, 71, 18, 31, 32, 63, 92, 43, 3, 91, 93, 25, 80, 28};
    int n = sizeof(arr) / sizeof(arr[0]);
    replace(arr, n);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    return 0;
}


