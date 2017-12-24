//
// Created by Mouna Cheikhna on 24/12/2017.
//

#include <cstdio>
#include <cstdlib>

using namespace std;

#define MAX_DEGREE 5
#define MAX_NUM_VERTICES 20

struct vertices_s {
    int index;
    int low_link;
    int in_stack;
    int deg;
    int adj[MAX_DEGREE];
};
vertices_s vertices[] = {
        {-1, -1, 0, 3, {2,  -3,  4}},
        {-1, -1, 0, 2, {-1, 3}},
        {-1, -1, 0, 3, {1,  -2,  7}},
        {-1, -1, 0, 3, {-1, -5,  6}},
        {-1, -1, 0, 2, {4,  -7}},
        {-1, -1, 0, 3, {-4, 7,   -8}},
        {-1, -1, 0, 4, {-3, 5,   -6, -12}},
        {-1, -1, 0, 3, {6,  -9,  11}},
        {-1, -1, 0, 2, {8,  -10}},
        {-1, -1, 0, 3, {9,  -11, -12}},
        {-1, -1, 0, 3, {-8, 10,  12}},
        {-1, -1, 0, 3, {7,  10,  -11}}
};

int num_vertices = sizeof(vertices) / sizeof(vertices[0]);

struct stack_s {
    int top;
    int items[MAX_NUM_VERTICES];
};

stack_s stack = {-1, {}};

void stack_push(int v) {
    stack.top++;
    if (stack.top < MAX_NUM_VERTICES) {
        stack.items[stack.top] = v;
    } else {
        printf("Stack is full.");
        exit(1);
    }
}

int stack_pop() {
    return stack.top < 0 ? -1 : stack.items[stack.top--];
}


#define vertex(X) (vertices[(X)])
#define v_index(X) (vertex((X)).index)
#define v_lowlink(X) (vertex((X)).low_link)
#define v_instack(X) (vertex((X)).in_stack)
#define v_deg(X) (vertex((X)).deg)
#define v_adj(X) (vertex((X)).adj)

int curr_index = 0;

void reset_vertices() {
    for (int i = 0; i < num_vertices; i++) {
        v_index(i) = -1;
        v_lowlink(i) = -1;
        v_instack(i) = 0;
    }
}

int min(int u, int v) {
    return u < v ? u : v;
}

void scc(int v) {
    v_index(v) = curr_index;
    v_lowlink(v) = curr_index;
    curr_index++;

    stack_push(v);
    v_instack(v) = 1;

    int i, c, n;
    for (i = 0, c = v_deg(v); i < c; i++) {
        if (v_adj(v)[i] > 0) {
            n = v_adj(v)[i] - 1;
            if (v_index(n) == -1) { // not visited yet
                scc(n);
                v_lowlink(v) = min(v_lowlink(n), v_lowlink(v));
            } else if (v_instack(n)) {
                v_lowlink(v) = min(v_lowlink(v), v_index(n));
            }
        }
    }

    if(v_index(v) == v_lowlink(v)) { //root of scc
        printf("scc: ");
        while((n = stack_pop()) != -1) {
            v_instack(n) = 0;
            printf(" %d", n + 1);
            if(n == v) {
                printf("\n"); // a new line after finishing displaying scc
                break;
            }
        }
    }
}

int main() {
    reset_vertices();
    for(int i = 0; i < num_vertices; i++) {
        if(v_index(i) == -1) { //not visited yet
            scc(i);
        }
    }
    return 0;
}
