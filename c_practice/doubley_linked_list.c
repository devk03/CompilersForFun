#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
Goals: implement a doubly linked list - open practice problem from crafting interpreters! requirements we all self made
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
    struct Node* prev;
    struct Node* next;
};

struct Node* construct_node(const char* data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node -> data = (char*)malloc(strlen(data)+1);
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
int pop_left(struct DoubleLink* list); // Done
int pop_right(struct DoubleLink* list); // Done
char* get_first(struct DoubleLink* list); // Done
char* get_last(struct DoubleLink* list); // Done
int insert_before(struct DoubleLink* list, struct Node* node, int index); // Done
struct Node* find_node(struct DoubleLink* list, const char* search_string);
int size(struct DoubleLink* list); // Done



int main() {
    FILE* output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    struct DoubleLink* list = construct_double_link();
    fprintf(output_file, "Initial size: %d\n", size(list));

    // Test node construction and append operations
    struct Node* node_1 = construct_node("First Node");
    struct Node* node_2 = construct_node("Second Node");
    struct Node* node_3 = construct_node("Third Node");
    
    append_right(list, node_1);
    fprintf(output_file, "After append_right: First=%s, Size=%d\n", get_first(list), size(list));
    
    append_left(list, node_2);
    fprintf(output_file, "After append_left: First=%s, Last=%s, Size=%d\n", 
            get_first(list), get_last(list), size(list));

    // Test insert operation
    struct Node* insert_node = construct_node("Inserted Node");
    insert_before(list, insert_node, 1);
    fprintf(output_file, "After insert: First=%s, Last=%s, Size=%d\n", 
            get_first(list), get_last(list), size(list));

    // Test find operation
    struct Node* found = find_node(list, "First Node");
    fprintf(output_file, "Find 'First Node': %s\n", 
            found ? "Found" : "Not Found");

    // Test pop operations
    pop_left(list);
    fprintf(output_file, "After pop_left: First=%s, Size=%d\n", 
            get_first(list), size(list));

    pop_right(list);
    fprintf(output_file, "After pop_right: Last=%s, Size=%d\n", 
            get_last(list), size(list));

    // Cleanup
    while (size(list) > 0) {
        pop_left(list);
    }
    free(list);
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
    struct Node* temp = list->first;
    if (list->size==1){
        list->first = NULL;
        list->last = NULL;
    } else {
        list->first = list->first->next;
        list->first->prev = NULL;
    }
    free(temp->data);
    free(temp);
    list->size--;
    return 0;
}

int pop_right(struct DoubleLink* list){
    if(list == NULL || list->size == 0){
        return -1;
    }
    struct Node* temp = list->last;
    if (list->size==1){
        list->first = NULL;
        list->last = NULL;
    } else {
        list->last = list->last->prev;
        list->last->next = NULL;
    }
    free(temp->data);
    free(temp);
    list->size--;
    return 0;
}

char* get_first(struct DoubleLink* list){
    if (list == NULL || list->first == NULL){
        return NULL;
    }
    return list->first->data;
}

char* get_last(struct DoubleLink* list){
    if (list == NULL){
        return NULL;
    }
    return list->last->data;
}

int insert_before(struct DoubleLink* list, struct Node* node, int index) {
    if(list == NULL || node == NULL || index < 0 || index > list->size) {
        return -1;
    }

    if (index == 0) {
        return append_left(list, node);
    } else if (index == list->size) {
        return append_right(list, node);
    }
    struct Node* temp = list->first;
    int curr_index = 0;
    while (curr_index < index) {
        temp = temp->next;
        curr_index++;
    }
    node->next = temp;
    node->prev = temp->prev;
    temp->prev->next=node;
    temp->prev=node;

    list->size++;
    return 1;
}

struct Node* find_node(struct DoubleLink* list, const char* search_string){
    if (list == NULL || search_string==NULL){
        return NULL;
    }
    struct Node* current = list->first;
    while(current != NULL){
        if(strcmp(current->data,search_string)==0){
            return current;
        } else {
            current = current->next;
        }
    }
    return NULL;
}

int size(struct DoubleLink* list){
    if (list == NULL){
        return -1;
    } else {
        return list->size;
    }
}