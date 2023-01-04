#include <iostream>
#include <cstdlib>
using namespace std;

#define P_INF "__+INF__"
#define N_INF "__-INF__"

typedef enum
{
    male,
    female
} gender;

string gender_to_string(gender G)
{
    string res;
    if (G == male)
        res = "male";
    else
        res = "female";

    return res;
}

typedef struct node
{
    string name;
    int age;
    gender gend;
    string dept;
    node *left;
    node *right;
    node *up;
    node *down;

    node(string _name = "", int _age = 0, gender _gend = male, string _dept = "")
    {
        name = _name;
        age = _age;
        gend = _gend;
        dept = _dept;
        left = NULL;
        right = NULL;
        up = NULL;
        down = NULL;
    }
    ~node()
    {
        delete right;
    }
} * Node;

// Node functions starts

void attach(Node ptr, Node up, Node down, Node left, Node right)
{
    ptr->up = up;
    ptr->down = down;
    ptr->left = left;
    ptr->right = right;

    if (up != NULL)
        up->down = ptr;
    if (down != NULL)
        down->up = ptr;
    if (right != NULL)
        right->left = ptr;
    if (left != NULL)
        left->right = ptr;
}

void detach(Node ptr)
{
    if (ptr->left != NULL) ptr->left->right = ptr->right;
    if (ptr->right != NULL) ptr->right->left = ptr->left;
    if (ptr->up != NULL) ptr->up->down = ptr->down;
    if (ptr->down != NULL) ptr->down->up = ptr->up;

    ptr->left = NULL;
    ptr->right = NULL;
    ptr->up = NULL;
    ptr->down = NULL;
}

// Node functions ends

typedef struct skipList
{
    Node head;
    int h; // Number of list

    skipList()
    {
        head = new node(N_INF);

        Node newNode = new node(P_INF);

        attach(newNode, NULL, NULL, head, NULL);

        h = 1;
    }
    ~skipList()
    {
        Node ptr = head;
        Node next = head->down;

        while (ptr != NULL)
        {
            delete ptr;
            ptr = next;
            if (next != NULL)
                next = next->down;
        }
    }
} * SkipList;

// SkipList function starts

void Display(SkipList list)
{
    Node listPtr = list->head;
    Node ptr = listPtr;

    while (ptr != NULL)
    {
        if (ptr->name == N_INF || ptr->name == P_INF)
        {
            ptr = ptr->right;
        }
        else
        {
            cout << ptr->name << ", ";
        }
    }
    cout << "\n";

    while (listPtr != NULL)
    {
        ptr = listPtr;
        while (ptr != NULL)
        {
            if (ptr->name == N_INF || ptr->name == P_INF)
            {
                ptr = ptr->right;
            }
            else
            {
                cout << ptr->name << ", ";
                ptr = ptr->right;
            }
        }
        cout << "\n";

        listPtr = listPtr->down;
    }
}

void Insert(SkipList list, string name, int age, gender gend, string dept)
{
    Node newNode = new node(name, age, gend, dept);

    int i = 0;
    int j;

    while (rand() % 2 != 0)
    {
        i++;
    }

    int h = list->h;

    if (i + 2 > h)
    {
        Node tempHead;
        for (j = 0; j < i - h + 2; j++)
        {
            tempHead = list->head;
            list->head = new node(N_INF);

            Node plus_inf = new node(P_INF);

            Node endTempHead = tempHead;

            while (endTempHead->right != NULL)
            {
                endTempHead = endTempHead->right;
            }

            attach(plus_inf, NULL, endTempHead, list->head, NULL);
            attach(list->head, NULL, tempHead, NULL, plus_inf);

            list->h = list->h + 1;
        }
    }

    Node bottom_list = list->head;

    while (bottom_list->down != NULL)
    {
        bottom_list = bottom_list->down;
    }

    Node Appropiate_pos = bottom_list;

    while (Appropiate_pos->right->name != P_INF && Appropiate_pos->right->name < name)
    {
        Appropiate_pos = Appropiate_pos->right;
    }

    attach(newNode, NULL, NULL, Appropiate_pos, Appropiate_pos->right);

    Node newPrev;
    Node newNext;
    Node newDown;

    for (j = 0; j < i; j++)
    {
        newPrev = newNode->left;
        while (newPrev->left != NULL && newPrev->up == NULL)
        {
            newPrev = newPrev->left;
        }
        newPrev = newPrev->up;
        newNext = newNode->right;
        while (newNext->right != NULL && newNext->up == NULL)
        {
            newNext = newNext->right;
        }
        newNext = newNext->up;
        newDown = newNode;
        newNode = new node(name, age, gend, dept);

        attach(newNode, NULL, newDown, newPrev, newNext);
    }
}

void Search(SkipList list,string name)
{
    Node ptr = list->head;

    while (ptr != NULL)
    {
        if (ptr->right->name == name)
        {
            cout << "Name: " << ptr->right->name << ", Age: " << ptr->right->age << ", Gender: " << gender_to_string(ptr->right->gend) << ", Department: " << ptr->right->dept << endl;
            return;
        }
        else if (ptr->right->name == P_INF || ptr->right->name > name)
        {
            ptr = ptr->down;
        }
        else
        {
            ptr = ptr->right;
        }
    }
    
    cout << "Not found\n";
    return;
}

void Delete(SkipList list,string name)
{
    Node ptr = list->head;
    Node listPtr = list->head;

    while (ptr != NULL)
    {
        if (ptr->right->name == name)
        {
            ptr = ptr->right;
            break;
        }
        else if (ptr->right->name == P_INF || ptr->right->name > name)
        {
            ptr = ptr->down;
            listPtr = listPtr->down;
        }
        else
        {
            ptr = ptr->right;
        }
    }
    
    if (ptr == NULL)
    {
        cout << "Not deleted\n";
        return;
    }

    Node deleteNode;
    Node deleteList;

    while (ptr != NULL)
    {
        deleteNode = ptr;
        ptr = ptr->down;

        detach(deleteNode);

        if (listPtr->right->name == P_INF)
        {
            deleteList = listPtr->right;
            detach(deleteList);
            delete deleteList;
            deleteList = listPtr;
            listPtr = listPtr->down;
            detach(deleteList);
            delete deleteList;
            list->h = list->h - 1;
        }
        else listPtr = listPtr->down;

        delete deleteNode;
    }

    cout << name << " is deleted\n";    
}

// SkipList function ends

int main()
{
    srand(time(0));

    SkipList L1 = new skipList;

    Insert(L1,"Prasham Walvekar",19,male,"CSE");
    Insert(L1,"Varun Gupta",20,male,"CSE");
    Insert(L1,"Sakshi Takale",25,female,"EP");
    Insert(L1,"Rishit Gupta",19,male,"CSE");
    Insert(L1,"Donald",20,male,"Civil");
    Insert(L1,"Anshul Sangrame",25,male,"CSE");
    Insert(L1,"Harsh Khandelwal",19,male,"Civil");
    Insert(L1,"Varshini",20,female,"CSE");

    Display(L1);
    cout << "\n";

    Search(L1,"Donal");
    Search(L1,"Donald");
    cout << "\n";

    Delete(L1,"Sakshi Takale");
    Delete(L1,"Prasham Walvekar");
    Delete(L1,"Varshini");
    cout << "\n";

    Display(L1);
    cout << "\n";

    Insert(L1,"SatyaPeri",40,male,"CSE");
    Insert(L1,"Pranav",19,male,"Electrical");

    Display(L1);

    delete L1;

    return 0;
}
