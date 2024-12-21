#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Goals: implement a doubly linked list
- insert
- delete
- append_left
- append_right
- pop_left
- pop_right
- find
*/ 


struct Node {
    char* data;
    struct Node* left;
    struct Node* right;
};


struct DoubleLink {
    struct Node* first;
    struct Node* last;
    int size;
};


struct DoubleLink* construct_double_link(){
    struct DoubleLink* list = (struct DoubleLink*)malloc(sizeof(struct DoubleLink));
    list -> first = NULL;
    list -> last = NULL;
    list -> size = 0;
    return list;
}

int main() {
    // Essentially construct a list witht the necessary amount of memory (casted to a DoubleLink Ptr)
    struct DoubleLink* list = construct_double_link();
    return 0;
}