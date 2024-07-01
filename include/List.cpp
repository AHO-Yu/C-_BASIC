#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace list
{
    typedef struct t_List
    {
        int id;
        char str[10];
        struct t_List *next = nullptr;
    } List;

    List *getData(void) // 輸入名字回傳List type
    {
        List *new_list;
        new_list = new List;
        static int id = 0;

        printf("Enter a name: ");
        if (scanf("%9s", new_list->str) == 1)
        {
            new_list->id = id++;
        }

        return new_list;
    };
    List *addToLast(List *head, List *np)
    {
        List *ptr = head;

        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
        }
        ptr->next = np;
        return ptr;
    };

    List *removeFirst(List *head)
    {

        List *new_header = head->next;
        head->next = nullptr;
        delete head;
        return new_header;
    };

    void removeFirst(List **head)
    {

        List *new_header = (*head)->next;
        (*head)->next = nullptr;
        delete *head;
        *head = new_header;
    };

    List *removeLast(List *head)
    {
        List *ptr = head;
        List *previous_ptr;
        while (ptr->next != nullptr)
        {
            previous_ptr = ptr;
            ptr = ptr->next;
        }

        free(ptr);
        previous_ptr->next = nullptr;
        return ptr;
    };

    void showList(List *ptr)
    {
        while (ptr != nullptr)
        {
            printf("id : %d, str : %s\n", ptr->id, ptr->str);
            ptr = ptr->next;
        }
    };
    List *freeList(List *lst)
    {

        while (lst != nullptr)
        {
            lst = removeFirst(lst);
        }
        return nullptr;
    };

    void insert_increase_list(List **hp, int data)
    {
    }

    /*

    Enter a name: amy
    [0:amy,]
    Enter a name: bob
    [0:amy,1:bob,]
    Enter a name: cathy
    [0:amy,1:bob,2:cathy,]
    Enter a name: danny
    [0:amy,1:bob,2:cathy,3:danny,]
    Enter a name: ^Z
    [0:amy,1:bob,2:cathy,3:danny,]
    [1:bob,2:cathy,3:danny,]

    */

    void list_main()
    {

        List *header = getData();
        addToLast(header, getData());
        addToLast(header, getData());
        // header = removeFirst(header);/bas case
        removeFirst(&header); // good case
        showList(header);
        return;
    }
}