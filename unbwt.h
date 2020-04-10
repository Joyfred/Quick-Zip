
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
//linked list for storing characters from bwt_arr[]

struct node 
{
    int data;
    struct node* next;
};
 
//compare function to sort alphabetically

int cmprfunc(const void* a, const void* b)
{
    const char* ia = (const char*)a;
    const char* ib = (const char*)b;
    return strcmp(ia, ib);
}
 
//new node creator for linked list

struct node* getNode(int i)
{
    struct node* nn = 
        (struct node*)malloc(sizeof(struct node));
    nn->data = i;
    nn->next = NULL;
    return nn;
}
 
//function to add elements at the last

void addAtLast(struct node** head,struct node* nn)
{
    if (*head == NULL) {
        *head = nn;
        return;
    }
    struct node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = nn;
}
 
// Computes transfomation matrix

void* computeLShift(struct node** head,int index,int* l_shift)
{
    l_shift[index] = (*head)->data;
    (*head) = (*head)->next;
}
 
void invert(char bwt_arr[],int major_index)
{
    int i,len_bwt=strlen(bwt_arr);
    char* sorted_bwt = (char*)malloc(len_bwt * sizeof(char));
    strcpy(sorted_bwt, bwt_arr);
    int* l_shift = (int*)malloc(len_bwt * sizeof(int));
 
    // index at which original string appears in the sorted rotations list
    int x = major_index;
 
    // sorts the characters of bwt_arr[] alphabetically to get the the first column of sorted rotation of strings
    qsort(sorted_bwt, len_bwt, sizeof(char), cmprfunc);
 
    //array of pointers that act as head nodes to linked lists created to compute transformation matrix
    struct node* arr[128] = { NULL };
 
    // takes each distinct character of bwt_arr[] as head of a linked list and appends to it the new node
    for (i = 0; i < len_bwt; i++) {
        struct node* nn = getNode(i);
        addAtLast(&arr[bwt_arr[i]], nn);
    }
 
    // takes each distinct character of sorted_arr[] as head of a linked list and finds transformation matrix
    for (i = 0; i < len_bwt; i++)
        computeLShift(&arr[sorted_bwt[i]], i, l_shift);
 
    printf("Burrows - Wheeler Transform: %s\n", bwt_arr);
    printf("Inverse of Burrows - Wheeler Transform: ");
    // Decodes the bwt
    for (i = 0; i < len_bwt; i++) {
        x = l_shift[x];
        printf("%c", bwt_arr[x]);
    }
}
 
