#include <iostream>
using namespace std;

typedef struct t_node {
    string name;
    int age;
    char gender;
    string dept;
    t_node *left;
    t_node *right;
    t_node(string MyName, int MyAge, char MyGender, string MyDept){
        name = MyName;
        age = MyAge;
        gender = MyGender;
        dept = MyDept;
        left = NULL;
        right = NULL;
    }
    ~t_node(){
        delete left;
        delete right;
    }
    bool isChildLess(){
        if (left == NULL && right == NULL) return true;
        else return false;
    }
    void cpyData(t_node *Node){
        name = Node->name;
        age = Node->age;
        gender = Node->gender;
        dept = Node->dept;
    }   
}node;

typedef node * Node;

Node Insert(Node root, string name, int age, char gender, string dept){
    if(root == NULL){
        return new node(name,age,gender,dept);
    }
    if(name.compare(root->name)<0){
        root->left = Insert(root->left, name, age, gender, dept);
    }else{
        root->right = Insert(root->right, name, age, gender, dept);     
    }
    return root;
}

void inorder(Node root){
    if(root == NULL) return;
    inorder(root->left);
    cout<<root->name<<" ";
    inorder(root->right);
}

void Search(Node root, string name){
    if(root == NULL) return;
    else if(name.compare(root->name) == 0){
    	    cout<<"Name: "<<root->name<<endl;
            cout<<"Age: "<<root->age<<endl;
            cout<<"Gender: "<<root->gender<<endl;
            cout<<"Department: "<<root->dept<<endl;
    }
    else if(name.compare(root->name) < 0) Search(root->left, name);
    else Search(root->right, name);
}

Node Delete(Node &root, string name){
    if (root == NULL) return NULL;
    else if (name.compare(root->name) == 0) {
        if (root->isChildLess() == true) {
            Node temp_root = root;

            root = NULL;

            return temp_root;
        }
        else {
            Node ptr;
            Node parentPtr = root;
            Node final;
            Node temp_root = root;
            if(root->left == NULL) {
                ptr = parentPtr->right;
                while(ptr->left != NULL) {
                    parentPtr = ptr;
                    ptr = ptr->left;
                }
            }
            else {
                ptr = parentPtr->left;
                while(ptr->right != NULL) {
                    parentPtr = ptr;
                    ptr = ptr->right;
                }
            }
            root->cpyData(ptr);

            if (ptr == parentPtr->right) final = Delete(parentPtr->right, ptr->name);
            else final = Delete(parentPtr->left, ptr->name);

            final->cpyData(temp_root);

            return final;
        }
    }
    else if(name.compare(root->name) < 0) return Delete(root->left, name);
    else return Delete(root->right, name);
}

int main(){
    Node root = NULL;
    cout<<"Inserting test data into binary search tree..."<<endl;
    root = Insert(root,"Alpha", 36, 'M', "CSE");
    Insert(root, "Beta", 32, 'M', "BT");
    Insert(root, "Gamma", 25, 'M', "BM");
    Insert(root, "Delta", 27, 'F', "CE");
    Insert(root, "Epsilon", 37, 'M', "EE");
    Insert(root, "Lambda", 48, 'M', "CSE");
    Insert(root, "Omega", 31, 'M', "CE");
    Insert(root, "Sigma", 49, 'F', "EP");
    inorder(root); cout<<endl;
    cout<<"Searching Sigma..."<<endl;	
    Search(root,"Sigma");
    cout<<"Deleting Sigma..."<<endl;
    delete Delete(root,"Sigma");
    inorder(root); cout<<endl;
    cout<<"Deleting Beta..."<<endl;
    delete Delete(root, "Beta");
    inorder(root); cout<<endl;
    delete root;
    return 0;
}
