#include <stdio.h>
#include <stdlib.h>

struct Student
{
    char name[20];
    int grade;
    int id;
};

struct Node
{
    struct Student std;
    struct Node *pNext;
    struct Node *pPre;
};

struct Node * pHead;
struct Node * pTail;

void FillStd(struct Student *s);
struct Node* CreateNode(struct Student s);
int AddNode(struct Student s);
void PrintStd(struct Node *n);
int PrintMenu();
int InsertNode(struct Student std, int loc);
struct Node * SearchById(int id);
struct Node * SearchByName(char name[]);
int DeleteNode(int loc);

int main()
{
    int choice;
    do
    {
        system("cls");
        choice = PrintMenu();

        if(choice == 1)
        {
            struct Student std, *s;
            s = &std;
            FillStd(s);
            AddNode(std);
        }
        else if(choice == 2)
        {
            struct Node *n;
            if(pHead)
            {
                n = pHead;
                while(n)
                {
                    PrintStd(n);
                    n = n->pNext;
                }
            }
            getch();
        }
        else if(choice == 3)
        {
            int location;
            printf("Enter location to insert into: ");
            scanf("%d", &location);
            struct Student std, *s;
            s = &std;
            FillStd(s);
            InsertNode(std, location);
        }
        else if (choice == 4)
        {
            int id;
            struct Node * node;
            printf("Enter student id: ");
            scanf("%d", &id);
            node = SearchById(id);
            PrintStd(node);
            getch();
        }
        else if(choice == 5)
        {
            struct Node * node;
            char name[20];
            printf("Enter student's name: ");
            scanf("%s", name);
            node = SearchByName(name);
            PrintStd(node);
            getch();
        }
        else if(choice == 6)
        {
            int location;
            printf("Enter location to delete the student: ");
            scanf("%d", &location);
            DeleteNode(location);
        }

    }
    while(choice != 0);

    return 0;
}

int PrintMenu()
{
    int choice;
    printf("1. Add student.\n");
    printf("2. Print student.\n");
    printf("3. Insert Student With location.\n");
    printf("4. Search by student's id.\n");
    printf("5. Search by student's name.\n");
    printf("6. Delete with location.\n");
    printf("0. Exit.\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void FillStd(struct Student *std)
{
    printf("Enter student id: ");
    scanf("%d", &std->id);
    printf("\n");
    printf("Enter student name: ");
    scanf("%s", &std->name);
    printf("\n");
    printf("Enter student grade: ");
    scanf("%d", &std->grade);
    printf("\n");
}

struct Node * CreateNode(struct Student s)
{
    struct Node * ptr;
    ptr = (struct Node *) malloc(sizeof(struct Node));
    if(ptr)
    {
        ptr -> std = s;
        ptr -> pNext = NULL;
        ptr -> pPre = NULL;
    }

    return ptr;
}


int AddNode(struct Student s)
{
    int retVal = 0;
    struct Node * ptr;
    ptr = CreateNode(s);
    if(ptr)
    {
        retVal = 1;
        if(!pHead)
        {
            pHead = pTail = ptr;
        }
        else
        {
            pTail -> pNext = ptr;
            ptr -> pPre = pTail;
            pTail = ptr;
        }
    }

    return retVal;
}

int InsertNode(struct Student std, int loc)
{
    int retVal = 0;
    struct Node *ptr, *temp;
    ptr = CreateNode(std);
    if(ptr)
    {
        retVal = 1;
        if(!pHead)
        {
            pHead = pTail = ptr;
        }
        else
        {
            if(loc == 0)
            {
                pHead->pPre = ptr;
                ptr->pNext = pHead;
                pHead = ptr;
            }
            else
            {
                temp = pHead;
                for(int i=0; i<loc-1&&temp; i++)
                {
                    temp = temp->pNext;
                }
                if(temp == pTail)
                {
                    pTail -> pNext = ptr;
                    ptr->pNext = NULL;
                    ptr->pPre = pTail;
                    pTail = ptr;
                }
                else
                {
                    (temp->pNext)->pPre = ptr;
                    ptr->pNext = temp->pNext;
                    ptr->pPre = temp;
                    temp->pNext = ptr;
                }
            }
        }
    }

    return retVal;
}


struct Node * SearchById(int id)
{
    struct Node *ptr;
    if(pHead)
    {
        ptr = pHead;
        while(ptr->std.id != id && ptr)
        {
            ptr = ptr->pNext;
        }
    }

    return ptr;
}

struct Node * SearchByName(char name[])
{
    struct Node *ptr;
    if(pHead)
    {
        ptr = pHead;
        while(ptr->std.name != name && ptr)
        {
            ptr = ptr->pNext;
        }
    }

    return ptr;
}

int DeleteNode(int loc)
{
    int deleted=0, i;
    struct Node* ptr;
    if(pHead)
    {
        ptr = pHead;
        if(loc == 0)
        {
            if(pHead == pTail)
            {
                pHead = pTail = NULL;
            }
            else
            {
                pHead = pHead ->pNext;
                pHead->pPre = NULL;
            }

            free(ptr);
            deleted = 1;
        }
        else
        {
            for(i=0; i<loc&&ptr; i++)
                ptr = ptr->pNext;

            if(ptr)
            {
                if(ptr == pTail)
                {
                    pTail = pTail->pPre;
                    pTail->pNext = NULL;
                }
                else
                {
                    ptr->pPre->pNext = ptr->pNext;
                    ptr->pNext->pPre = ptr->pPre;
                }

                free(ptr);
                deleted=1;
            }
        }
    }

    return deleted;
}


void PrintStd(struct Node *n)
{
    printf("student Id: %d\n", n->std.id);
    printf("student name: %s\n", n->std.name);
    printf("student grade: %d\n", n->std.grade);
    printf("\n");
}
