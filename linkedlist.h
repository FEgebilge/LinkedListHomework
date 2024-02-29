#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"

typedef struct LINKED_LIST_NODE_s *LINKED_LIST_NODE;
typedef struct LINKED_LIST_NODE_s
{
    LINKED_LIST_NODE next;
    void *data;
} LINKED_LIST_NODE_t[1];

typedef struct LINKED_LIST_s *LINKED_LIST;
typedef struct LINKED_LIST_s
{
    LINKED_LIST_NODE head; 
} LINKED_LIST_t[1];

LINKED_LIST linked_list_init()
{
    LINKED_LIST list = (LINKED_LIST)malloc(sizeof(LINKED_LIST_t));
    LINKED_LIST_NODE head = (LINKED_LIST_NODE)malloc(sizeof(LINKED_LIST_NODE_t));
    head->data = NULL;
    head->next = NULL;
    list->head = head;
    return list;
}
void linked_list_print_integers(LINKED_LIST list)
{
    LINKED_LIST_NODE currentNode = list->head;
    while (currentNode->next != NULL)
    {
        currentNode = currentNode->next;
        printf("%d  ", *(int *)currentNode->data);
    }
    printf("\n");
}
void linked_list_prepend(LINKED_LIST list, void *data)
{

    LINKED_LIST_NODE prependNode = (LINKED_LIST_NODE)malloc(sizeof(LINKED_LIST_NODE));
    prependNode->data = data;
    prependNode->next = list->head->next;
    list->head->next = prependNode;
}

void linked_list_append(LINKED_LIST list, void *data)
{

    LINKED_LIST_NODE newNode = (LINKED_LIST_NODE)malloc(sizeof(LINKED_LIST_NODE));
    newNode->data = data;
    newNode->next = NULL;
    LINKED_LIST_NODE currentNode = list->head;

    while (currentNode->next != NULL)
    {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;
}

int sizeOfList(LINKED_LIST list)
{
    LINKED_LIST_NODE currentNode = list->head;
    int sizeOfList = 0;
    while (currentNode->next != NULL)
    {
        sizeOfList++;
        currentNode = currentNode->next;
    }
    return sizeOfList;
}

void linked_list_insert(LINKED_LIST list, void *data, int idx)
{

    LINKED_LIST_NODE newNode = (LINKED_LIST_NODE)malloc(sizeof(LINKED_LIST_NODE));
    newNode->data = data;
    LINKED_LIST_NODE currentNode = list->head->next;

    for (int i = 0; i < idx - 1; i++)
    {
        currentNode = currentNode->next;
    }
    newNode->next = currentNode->next;
    currentNode->next = newNode;
}

void linked_list_set(LINKED_LIST list, void *data, int idx)
{

    LINKED_LIST_NODE currentNode = list->head->next;
    for (int i = 0; i < idx; i++)
    {
        currentNode = currentNode->next;
    }
    currentNode->data = data;
}

void *linked_list_get(LINKED_LIST list, int idx)
{

    LINKED_LIST_NODE currentNode = list->head->next;
    for (int i = 0; i < idx; i++)
    {
        currentNode = currentNode->next;
    }
    return currentNode->data;
}

void *linked_list_remove(LINKED_LIST list, int idx)
{
    LINKED_LIST_NODE currentNode = list->head;
    if (currentNode == NULL)
        return 0;

    int i = 0;
    while (i < idx)
    {
        currentNode = currentNode->next;
        i++;
    }
    void *data = currentNode->next->data;
    LINKED_LIST_NODE temp = currentNode;

    currentNode->next = currentNode->next->next;
    free(temp);
    return data;
}

void linked_list_removeall(LINKED_LIST list)
{
    if (list->head == NULL)
        return;


    LINKED_LIST_NODE currentNode = list->head->next;
    while (currentNode->next != NULL)
    {
        currentNode = currentNode->next;
        linked_list_remove(list, 0);
    }
}
void linked_list_free(LINKED_LIST list)
{

    linked_list_removeall(list);
    free(list);
}

void linked_list_concatenate(LINKED_LIST list, LINKED_LIST list2)
{
    LINKED_LIST_NODE currentL1 = list->head;
    LINKED_LIST_NODE currentL2 = list2->head->next;
    while (currentL1->next != NULL)
    {
        currentL1 = currentL1->next;
    }
    currentL1->next = currentL2;
}

LINKED_LIST linked_list_slice(LINKED_LIST list, int start, int end)
{
    int i = 0;
    LINKED_LIST_NODE current1 = list->head;
    LINKED_LIST newList = linked_list_init();
    while (i < start)
    {
        current1 = current1->next;
        i++;
    }
    LINKED_LIST_NODE current2 = current1->next;
    while (i <=end)
    {
        void * a= linked_list_remove(list,i);
        linked_list_append(newList,a );
        end=end-1;
    }
    return newList;
}

void linked_list_insert_piece(LINKED_LIST list, LINKED_LIST piece, int index)
{
    LINKED_LIST_NODE currentL1 = list->head;
    LINKED_LIST_NODE currentL2 = piece->head->next;
    for (int i = 0; i < index; i++)
    {
        currentL1 = currentL1->next;
    }
    LINKED_LIST_NODE temp = currentL1->next;
    currentL1->next = currentL2;
    while (currentL2->next != NULL)
    {
        currentL2 = currentL2->next;
    }
    currentL2->next = temp;
}
void linked_list_cut_left(LINKED_LIST pS, int left) {
    while (left>0)
    {
        linked_list_remove(pS,0);
        left--;
    }
}

void linked_list_cut_right(LINKED_LIST pS,int index) {
    int loop= sizeOfList(pS)-index;
    int i=0;
    while (i<loop)
    {
        linked_list_remove(pS,index);
        i++;
    }
}

void linked_list_trim(LINKED_LIST list, int left , int right)
{
    linked_list_cut_left(list, left);
    int size= sizeOfList(list);
    LINKED_LIST_NODE currentNode=list->head;
    int i=0;
    while (i<size-right)
    {
        currentNode=currentNode->next;
        i++;
    }
    linked_list_cut_right(list,i);
}
void fill_linked_list(LINKED_LIST list, int firstNum, int LastNum, int interval)
{
    if (LastNum > firstNum)
    {
        for (int i = firstNum; i <= LastNum; i = i + interval)
        {
            int *value = (int *)malloc(sizeof(int));
            *value = i;
            linked_list_append(list, value);
        }
    }
    if (LastNum < firstNum)
    {
        for (int i = firstNum; i >= LastNum; i = i - interval)
        {
            int *value = (int *)malloc(sizeof(int));
            *value = i;
            linked_list_append(list, value);
        }
    }
}
