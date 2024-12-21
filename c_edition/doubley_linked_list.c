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
- Clearing the list
- Destroying the list structure itself
*/ 



struct Node {
    char* data;
    struct Node* prev;
    struct Node* next;
};

struct Node* construct_node(const char* data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node)); // Need to allocate memory and caste location to a node* instead of void*
    node -> data = (char*)malloc(strlen(data)+1); // Need to allocate one more block for the null terminator
    strcpy(node->data, data);
    node -> prev = NULL;
    node -> next = NULL;
    return node;
}



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

// Define the interface
int append_left(struct DoubleLink* list, struct Node* node); // Done
int append_right(struct DoubleLink* list, struct Node* node); // Done
int pop_left(struct DoubleLink* list);
int pop_right(struct DoubleLink* list);
char* get_first(struct DoubleLink* list);
char* get_last(struct DoubleLink* list);
int insert_node(struct DoubleLink* list, struct Node* node);
struct Node* find_node(struct DoubleLink* list, const char* search_string);
int size(struct DoubleLink* list);



int main() {
    FILE* output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    struct DoubleLink* list = construct_double_link();

    // Node construction test
    struct Node* node_1 = construct_node("This is node 1.");
    fprintf(output_file, "%s\n", node_1->data);
    
    
    free(node_1->data);
    free(node_1);
        
    // Close the file
    fclose(output_file);
    return 0;
}


/*Interface Implementation*/ 
// Return 1 if no error raised
// Return -1 if error raised

int append_left(struct DoubleLink* list, struct Node* node){
    if(list == NULL || node == NULL) {
        return -1;
    }
    node->prev = NULL;
    if (list->size==0) {
        list->first = node;
        list->last = node;
    } else{
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }
    list->size++;
    return 1;
}

int append_right(struct DoubleLink* list, struct Node* node){
    if(list == NULL || node == NULL) {
        return -1;
    }
    node->next = NULL;
    if (list->size==0) {
        list->first = node;
        list->last = node;
    } else{
        node->prev = list->last;
        list->last->next = node;
        list->last = node;
    }
    list->size++;
    return 1;
}

int pop_left(struct DoubleLink* list){
    if(list == NULL || list->size == 0){
        return -1;
    }
    free(list->first->data); // free the memory of the first node
    // Case
    // size is one
    // size > 1
    struct Node* temp = list->first; // need the temp so we can detach
    list->first = list->first->next;
    return 0;
}

// int pop_right(struct DoubleLink* list);