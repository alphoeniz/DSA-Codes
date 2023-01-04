#include <iostream>
using namespace std;

struct node
{
    int age;
    struct node *left;
    struct node *rightSibling;
    struct node *parent;

    node()
    {
        left = NULL;
        rightSibling = NULL;
        parent = NULL;
    }
};

typedef struct node *Node;

struct binomialTree
{
    Node root;
    int order;

    binomialTree()
    {
        root = NULL;
    }
};

// Binomial Tree functions starts

void _Display(Node ptr)
{
    if (ptr == NULL)
        return;
    cout << ptr->age << " ";
    _Display(ptr->left);
    _Display(ptr->rightSibling);
}

void Display(binomialTree T)
{
    _Display(T.root);
}

Node _Clone(Node ptr, Node newParent)
{
    if (ptr == NULL)
    {
        return NULL;
    }
    else
    {
        Node newNode = new node;
        newNode->parent = newParent;
        newNode->age = ptr->age;
        newNode->left = _Clone(ptr->left, newNode);
        newNode->rightSibling = _Clone(ptr->rightSibling, newParent);

        return newNode;
    }
}

binomialTree CloneTree(binomialTree T)
{
    binomialTree newTree;

    newTree.root = _Clone(T.root, NULL);
    newTree.order = T.order;

    return newTree;
}

binomialTree Merge(binomialTree H1, binomialTree H2)
{
    binomialTree res;
    binomialTree T1 = CloneTree(H1);
    binomialTree T2 = CloneTree(H2);

    if (T1.order == T2.order)
    {
        if (T1.root->age < T2.root->age)
        {
            Node tempLeft = T1.root->left;
            res.root = T1.root;
            res.root->left = T2.root;
            res.root->left->parent = T1.root;
            res.root->left->rightSibling = tempLeft;
        }
        else
        {
            Node tempLeft = T2.root->left;
            res.root = T2.root;
            res.root->left = T1.root;
            res.root->left->parent = T2.root;
            res.root->left->rightSibling = tempLeft;
        }
        res.order = T2.order + 1;
    }
    else
    {
        res.root = NULL;
    }

    return res;
}

// Binomial Tree function ends

struct l_node
{
public:
    binomialTree item;
    l_node *next;

    l_node()
    {
        next = NULL;
    }
};

struct LinkedList
{
    l_node *head;

    LinkedList()
    {
        head = NULL;
    }
};

struct BinomialHeap
{
    LinkedList heap;

    void Sort(LinkedList H)
    {
        l_node *ptr1 = H.head;
        l_node *ptr2 = H.head;

        while (ptr1 != NULL)
        {
            ptr2 = ptr1->next;
            while (ptr2 != NULL)
            {
                if (ptr1->item.order > ptr2->item.order)
                    swap(ptr1->item, ptr2->item);
                ptr2 = ptr2->next;
            }
            ptr1 = ptr1->next;
        }
    }

    // Union operator
    BinomialHeap operator+(BinomialHeap const &H)
    {
        BinomialHeap res;
        l_node *ptr1 = heap.head;
        l_node *ptr2 = H.heap.head;
        l_node *heapPtr = res.heap.head;
        l_node *newNode;
        l_node *ptr;

        while (true)
        {
            if (ptr1 == NULL && ptr2 == NULL)
            {
                break;
            }
            else if (ptr1 == NULL)
            {
                ptr = ptr2;
            }
            else if (ptr2 == NULL)
            {
                ptr = ptr1;
            }
            else
            {
                if (ptr1->item.order < ptr2->item.order)
                {
                    ptr = ptr1;
                }
                else
                {
                    ptr = ptr2;
                }
            }

            l_node *newNode;
            l_node *tempPtr = ptr;

            if (heapPtr == NULL)
            {
                newNode = new l_node;
                newNode->item = ptr->item;
                res.heap.head = newNode;
                heapPtr = res.heap.head;
            }
            else if (heapPtr->item.order == ptr->item.order)
            {
                heapPtr->item = Merge(heapPtr->item, ptr->item);
            }
            else
            {
                newNode = new l_node;
                newNode->item = ptr->item;
                heapPtr->next = newNode;
                heapPtr = heapPtr->next;
            }
            if (tempPtr == ptr2)
                ptr2 = ptr2->next;
            else
                ptr1 = ptr1->next;

            Sort(res.heap);
        }

        return res;
    }
};

// Binomial Heap functions starts

void Insert(int age, BinomialHeap &H)
{
    BinomialHeap res;
    BinomialHeap newHeap;
    l_node *temphead = H.heap.head;
    newHeap.heap.head = new l_node;
    newHeap.heap.head->item.order = 0;
    newHeap.heap.head->item.root = new node;
    Node Root = newHeap.heap.head->item.root;
    Root->age = age;

    H = H + newHeap;
}

void Display2(BinomialHeap H)
{
    if (H.heap.head == NULL)
        cout << "No element\n";
    else
    {
        l_node *ptr = H.heap.head;

        while (ptr != NULL)
        {
            Display(ptr->item);
            cout << "\n\n";
            ptr = ptr->next;
        }
    }
}

void DeleteMin(BinomialHeap &H)
{
    if (H.heap.head == NULL)
        cout << "No element\n";
    else
    {
        binomialTree minTree;

        l_node *prevPtr = NULL;
        l_node *ptr = H.heap.head;
        l_node *minPtrPrev = NULL;
        l_node *minPtr = H.heap.head;
        int min = ptr->item.root->age;
        minTree = ptr->item;

        while (ptr != NULL)
        {
            if (ptr->item.root->age < min)
            {
                min = ptr->item.root->age;
                minTree = ptr->item;
                minPtr = ptr;
                minPtrPrev = prevPtr;
            }

            prevPtr = ptr;
            ptr = ptr->next;
        }

        int i;
        BinomialHeap adder;
        Node addPtr = minTree.root->left;
        adder.heap.head = new l_node;
        adder.heap.head->item.root = new node;
        if (minTree.order != 0)
        {
            adder.heap.head->item.root->age = addPtr->age;
            adder.heap.head->item.root->left = addPtr->left;
            adder.heap.head->item.root->parent = NULL;
            adder.heap.head->item.root->rightSibling = NULL;
            adder.heap.head->item.order = minTree.order - 1;
            if (minPtrPrev != NULL)
            {
                minPtrPrev->next = minPtr->next;
            }
            else
            {
                H.heap.head = minPtr->next;
            }
        }

        else
        {
            H.heap.head = minPtr->next;
        }

        for (i = 0; i < minTree.order; i++)
        {
            H = H + adder;
            addPtr = addPtr->rightSibling;
            if (addPtr != NULL)
            {
                adder.heap.head->item = CloneTree(adder.heap.head->item);
                adder.heap.head->item.root->age = addPtr->age;
                adder.heap.head->item.root->left = addPtr->left;
                adder.heap.head->item.order--;
            }
        }

        cout << min << " is deleted\n";
    }
}
// Binomial Heap function ends

int main()
{
    struct BinomialHeap test;
    struct BinomialHeap test2;

    Insert(2,test);
    Insert(46,test);
    Insert(19,test);
    Insert(29,test);
    Insert(3,test);
    Insert(18,test);

    cout << "test:\n";
    Display2(test);

    Insert(180,test2);
    Insert(190,test2);
    Insert(1,test2);
    Insert(21,test2);
    Insert(8,test2);
    Insert(4,test2);
    Insert(5, test2);
    Insert(16,test2);


    cout << "test2:\n";
    Display2(test2);


    // + means Union
    cout << "test + test2:\n"; // Union of test and test2
    Display2(test2 + test);

    DeleteMin(test);
    DeleteMin(test);
    DeleteMin(test);

    cout << "test after deletion: \n";
    Display2(test);

    DeleteMin(test2);
    DeleteMin(test2);
    
    cout << "test2 after deletion:\n";
    Display2(test2);

    return 0;
}