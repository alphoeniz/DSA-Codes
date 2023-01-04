#include <iostream>
using namespace std;

const int n = 5;

typedef class node
{
public:
    int *age;
    int size;
    node **children;
    node *parent;
    bool isLeaf;
    int order;
    node(int n)
    {
        order = n;
        size = 0;
        age = new int[n];
        children = new node *[n + 1];
        parent = NULL;
        for (int i = 0; i <= n; i++)
        {
            children[i] = NULL;
        }
    }
    ~node()
    {
        delete[] age;

        for (int i = 0; i <= order; i++)
        {
            delete children[i];
        }

        delete[] children;
    }
} * Node;

// Node Functions starts

bool FindInNode(Node ptr, int age)
{
    for (int i = 0; i < ptr->size; i++)
    {
        if (ptr->age[i] == age)
        {
            return true;
        }
    }

    return false;
}

int FindPosinNode(Node ptr, int age)
{
    for (int i = 0; i < ptr->size; i++)
    {
        if (ptr->age[i] >= age)
        {
            return i;
        }
    }

    return ptr->size;
}

int FindPosinParent(Node ptr)
{
    Node parent = ptr->parent;

    for (int i = 0; i <= parent->size; i++)
    {
        if (parent->children[i] == ptr)
        {
            return i;
        }
    }

    return -1;
}

void InsertinKeyPartition(Node ptr, int pos, Node newPtr)
{
    ptr->children[ptr->size] = newPtr;

    for (int i = ptr->size; i > pos; i--)
    {
        swap(ptr->children[i], ptr->children[i - 1]);
    }
}

void delInKeyPartition(Node ptr, int pos)
{
    delete[] ptr->children[pos]->age;
    delete[] ptr->children[pos]->children;
    operator delete(ptr->children[pos]); // 1  12  8  2  25  6  14  28  17  7  52  16  48  68  3  26  29  53  55  45

    ptr->children[pos] = NULL;

    for (int i = pos; i <= ptr->size; i++)
    {
        swap(ptr->children[i], ptr->children[i + 1]);
    }
}

int delInNode(Node ptr, int age)
{
    int pos = FindPosinNode(ptr, age);

    int deleted = ptr->age[pos];

    ptr->size--;

    for (int i = pos; i < ptr->size; i++)
    {
        ptr->age[i] = ptr->age[i + 1];
    }

    return deleted;
}

void InsertinNode(Node ptr, int age)
{
    ptr->age[ptr->size] = age;
    ptr->size++;
    for (int i = ptr->size - 1; i > 0; i--)
    {
        if (ptr->age[i] < ptr->age[i - 1])
        {
            swap(ptr->age[i], ptr->age[i - 1]);
        }
        else
        {
            break;
        }
    }
}

// Node funstions ends

// BTree function starts

void split(Node ptr, Node &root)
{
    Node newPtr1 = new node(n);

    int i;

    if (ptr->parent == NULL)
    {
        ptr->parent = new node(n);
        root = ptr->parent;
        root->isLeaf = false;
        InsertinKeyPartition(root, 0, ptr);
    }

    InsertinNode(ptr->parent, ptr->age[(n - 1) / 2]);
    newPtr1->parent = ptr->parent;

    newPtr1->isLeaf = ptr->isLeaf;

    for (i = 0; i < (n - 1) / 2; i++)
    {
        InsertinNode(newPtr1, ptr->age[(n + 1) / 2 + i]);
    }

    for (i = 0; i <= (n - 1) / 2; i++)
    {
        delInNode(ptr, ptr->age[(n - 1) / 2 + i]);
    }

    for (i = 0; i <= (n - 1) / 2; i++)
    {
        InsertinKeyPartition(newPtr1, i, ptr->children[(n + 1) / 2 + i]);
        if (!newPtr1->isLeaf)
            newPtr1->children[i]->parent = newPtr1;
        ptr->children[(n + 1) / 2 + i] = NULL;
    }

    InsertinKeyPartition(ptr->parent, FindPosinParent(ptr) + 1, newPtr1);
}

void Insert(Node &root, int age, Node ptr)
{
    if (root == NULL)
    {
        root = new node(n);
        root->age[0] = age;
        root->size++;
        root->isLeaf = true;
    }
    else if (ptr->isLeaf)
    {
        InsertinNode(ptr, age);
        if (ptr->size == n)
        {
            split(ptr, root);
        }
    }
    else
    {
        Insert(root, age, ptr->children[FindPosinNode(ptr, age)]);
        if (ptr->size == n)
        {
            split(ptr, root);
        }
    }
    return;
}

void Merge(int idx, Node parent)
{
    Node child = parent->children[idx];
    Node sibling = parent->children[idx + 1];
    int t = child->size;

    child->age[t] = parent->age[idx];

    for (int i = 0; i < sibling->size; ++i)
    {
        child->age[i + t + 1] = sibling->age[i];
    }

    if (!child->isLeaf)
    {
        for (int i = 0; i <= sibling->size; ++i)
        {
            child->children[i + t + 1] = sibling->children[i];
            child->children[i+ t + 1]->parent = child;
        }
    }

    for (int i = idx + 1; i < parent->size; ++i)
    {
        parent->age[i - 1] = parent->age[i];
    }

    for (int i = idx + 2; i <= parent->size; ++i)
    {
        parent->children[i - 1] = parent->children[i];
    }

    child->size += sibling->size + 1;
    parent->size--;

    delete[] sibling->age;
    delete[] sibling->children;
    operator delete(sibling);
    // int i;
    // Node sibling;
    // int posOfsibling;
    // int PosOfPtrInParent = FindPosinParent(ptr);
    // int k;
    // int c;

    // if (PosOfPtrInParent + 1 <= ptr->parent->size)
    // {
    //     sibling = ptr->parent->children[PosOfPtrInParent + 1];
    //     posOfsibling = PosOfPtrInParent + 1;
    //     k = PosOfPtrInParent;
    //     c = (n + 1) / 2;
    // }
    // else
    // {
    //     sibling = ptr->parent->children[PosOfPtrInParent - 1];
    //     posOfsibling = PosOfPtrInParent - 1;
    //     k = PosOfPtrInParent-1;
    //     c = 0;
    // }

    // InsertinNode(ptr, ptr->parent->age[k]);

    // for (i = 0; i < (n - 1) / 2; i++)
    // {
    //     InsertinNode(ptr, sibling->age[i]);
    // }
    // for (i = 0; i <= (n - 1) / 2; i++)
    // {
    //     InsertinKeyPartition(ptr, c + i, sibling->children[i]);
    // }

    // delInNode(ptr->parent, ptr->parent->age[k]);
    // delInKeyPartition(ptr->parent, posOfsibling);
}

bool Borrow(Node ptr)
{
    Node sibling;
    int posOfPtr = FindPosinParent(ptr);

    if (posOfPtr + 1 <= ptr->parent->size && ptr->parent->children[posOfPtr + 1]->size > (n - 1) / 2)
    {
        sibling = ptr->parent->children[posOfPtr + 1];

        InsertinNode(ptr, ptr->parent->age[posOfPtr]);
        swap(ptr->parent->age[posOfPtr], sibling->age[0]);
        delInNode(sibling,sibling->age[0]);

        return true;
    }
    else if (posOfPtr - 1 >= 0 && ptr->parent->children[posOfPtr - 1]->size > (n - 1) / 2)
    {
        sibling = ptr->parent->children[posOfPtr - 1];

        InsertinNode(ptr, ptr->parent->age[posOfPtr - 1]);
        swap(ptr->parent->age[posOfPtr - 1], sibling->age[sibling->size-1]);
        delInNode(sibling,sibling->age[sibling->size - 1]);

        return true;
    }
    else
    {
        return false;
    }
}

void swap(Node ptr, int posOfAge, int &pos)
{
    Node swapPtr;

    if (posOfAge + 1 <= ptr->size)
    {
        swapPtr = ptr->children[posOfAge + 1];
        pos = posOfAge + 1;
        while (!swapPtr->isLeaf)
        {
            swapPtr = swapPtr->children[0];
        }
        swap(ptr->age[posOfAge], swapPtr->age[0]);
    }
    else
    {
        swapPtr = ptr->children[posOfAge];
        pos = posOfAge;
        while (!swapPtr->isLeaf)
        {
            swapPtr = swapPtr->children[swapPtr->size];
        }
        swap(ptr->age[posOfAge], swapPtr->age[swapPtr->size - 1]);
    }
}

void fixer(Node ptr, Node &root)
{
    if (ptr->parent != NULL)
    {
        if (ptr->size < (n - 1) / 2)
        {
            if (!Borrow(ptr))
            {
                int pos = FindPosinParent(ptr);
                if (pos + 1 <= ptr->parent->size)
                {
                    Merge(pos, ptr->parent);
                }
                else
                {
                    Merge(pos - 1, ptr->parent);
                }
            }
        }
    }

    else
    {
        if (root->size == 0)
        {
            Node tempRoot = root;

            root = root->children[0];
            root->parent = NULL;

            delete[] tempRoot->age;
            delete[] tempRoot->children;
            operator delete(tempRoot);
        }
    }
}

void Delete(Node ptr, int age, Node &root)
{
    if (FindInNode(ptr, age))
    {
        if (ptr->isLeaf)
        {
            delInNode(ptr, age);

            fixer(ptr, root);
        }

        else
        {
            int posOfAge = FindPosinNode(ptr, age);
            int pos;
            swap(ptr, posOfAge, pos);
            Delete(ptr->children[pos], age, root);

            fixer(ptr, root);
        }
    }

    else
    {
        int pos = FindPosinNode(ptr, age);
        Delete(ptr->children[pos], age, root);

        fixer(ptr, root);
    }
}

void Search(Node ptr, int age)
{
    if (FindInNode(ptr, age))
    {
        cout << age << " is found\n";
    }
    else if (ptr->isLeaf)
    {
        cout << "Not found\n";
    }
    else
    {
        Search(ptr->children[FindPosinNode(ptr, age)], age);
    }
}

void traverse(Node root)
{
    cout << "[";
    for (int i = 0; i < root->size; i++)
    {
        cout << root->age[i] << " ";
    }
    if (root->isLeaf)
        cout << "L]\n";
    else
        cout << "]\n";
    if (!root->isLeaf)
    {
        for (int i = 0; i <= root->size; i++)
        {
            traverse(root->children[i]);
        }
    }
}

// BTree function ends

int main()
{
    Node root = NULL;
    Insert(root, 3, root);
    Insert(root, 7, root);
    Insert(root, 9, root);
    Insert(root, 23, root);
    Insert(root, 45, root);
    Insert(root, 1, root);
    Insert(root, 5, root);
    Insert(root, 14, root);
    Insert(root, 25, root);
    Insert(root, 24, root);
    Insert(root, 13, root);
    Insert(root, 11, root);
    Insert(root, 8, root);
    Insert(root, 19, root);
    Insert(root, 4, root);
    Insert(root, 31, root);
    Insert(root, 35, root);
    Insert(root, 56, root);
    Insert(root, 2, root);
    Insert(root, 6, root);
    Insert(root, 12, root);

    // 3, 7, 9, 23, 45, 1, 5, 14, 25, 24, 13, 11, 8, 19, 4, 31, 35, 56

    traverse(root);

    Search(root, 3);

    // 4, 5, 7, 3, 14

    Delete(root,4,root);
    Delete(root,5,root);

    cout << endl;
    traverse(root); 

    Delete(root,7,root);
    cout << endl;
    traverse(root); 
    Delete(root,3,root);
    Delete(root,14,root);

    cout << endl;
    traverse(root);

    Delete(root,56,root);

    cout << endl;
    traverse(root);

    delete root;
    return 0;
}
