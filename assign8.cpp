#include <iostream>
using namespace std;

enum colour {red,black};

typedef class node{
    public:
    int age;
    colour color;
    node *left;
    node *right;
    node *parent;
    node(int MyAge){
        age = MyAge;
        left = NULL;
        right = NULL;
        parent = NULL;
        color = red;
    }
}*Node;

Node InsertNColour(Node &root, int age, Node parent){
    Node n;
    if(root == NULL){root = new node(age); root->parent = parent; return root;}
    if(age < root->age){n = InsertNColour(root->left,age, root); return n;}
    else{n = InsertNColour(root->right,age, root); return n;}
}

Node grandfather(Node x){
    return x->parent->parent;
}

Node uncle(Node x){
    if(grandfather(x)->right == x->parent){return grandfather(x)->left;}
    return grandfather(x)->right;
}

void swapColor(Node x){
    x->parent->color = black; grandfather(x)->color = red;
}

void leftRotation(Node &x){
    Node temp = x;
    x = x->right;
    temp->right = x->left;
    x->left = temp;
    x->parent = temp->parent;
    temp->parent = x;
    if (temp->right)
    temp->right->parent = temp;
}

void rightRotation(Node &x){
    Node temp = x;
    x = x->left;
    temp->left = x->right;
    x->right = temp;
    x->parent = temp->parent;
    temp->parent = x;
    if (temp->left)
    temp->left->parent = temp;
}

void Insert(Node &root, int age){
    Node x = InsertNColour(root,age, NULL); 
    x->color = red;

    while (true){
        if(x == root){x->color = black; return;}
        if(x->parent->color == black){return;}
        if(x->parent->color == red){

            if(uncle(x) == NULL || uncle(x)->color == black){
                if(grandfather(x)->left == x->parent){
                    //Case 1: LL rotation
                    if (x->parent->left == x){
                        swapColor(x); 
                        if (!x->parent->parent->parent)
                            rightRotation(root);
                        else if (grandfather(x) == grandfather(x)->parent->left)
                            rightRotation(grandfather(x)->parent->left);
                        else
                            rightRotation(grandfather(x)->parent->right);
                        break;
                    }
                    //Case 2: LR rotation
                    else{
                        leftRotation(x->parent);
                    }

                } else {
                    //Case 3: RR rotation
                    if (x->parent->right == x){
                        swapColor(x);
                        if (!x->parent->parent->parent)
                            leftRotation(root);
                        else if (grandfather(x) == grandfather(x)->parent->left)
                            leftRotation(grandfather(x)->parent->left);
                        else
                            leftRotation(grandfather(x)->parent->right);
                        break;
                    }
                    //Case 4: RL rotation
                    else
                        rightRotation(x->parent);
                }
            }
            else if(uncle(x)->color == red){
                x->parent->color = black; uncle(x)->color = black; grandfather(x)->color = red;
                x = grandfather(x);
            }
        }
    }
}

void Search(Node root, int age){
    if(root == NULL){cout<<"Such node does not exist!!!"<<endl; return;}
    else if(age == root->age){
            cout<<"Age: "<<root->age<<endl;
            return;
    }
    else if(age<root->age) Search(root->left,age);
    else Search(root->right,age);
}

void inorder(Node root){
    if(root == NULL) return;
    inorder(root->left);
    cout<<root->age<<" ";
    inorder(root->right);
}

int main(){
    Node root = NULL;
    Insert(root, 1); 
    Insert(root, 2); 
    Insert(root, 3); 
    Insert(root, 4); 
    Insert(root, 5);  
    Insert(root, 6);
    Insert(root, 23);
    Insert(root, 15);
    Insert(root, 11);
    Search(root,23);
    Search(root,17);
    inorder(root); cout<<endl; return 0;
}
