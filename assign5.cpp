#include <iostream>
using namespace std;

typedef struct t_node {
    string name;
    int age;
    char gender;
    string dept;
    t_node *left;
    t_node *right;
    bool IsThread;
    t_node(string MyName, int MyAge, char MyGender, string MyDept){
        name = MyName;
        age = MyAge;
        gender = MyGender;
        dept = MyDept;
        left = NULL;
        right = NULL;
        IsThread = true;
    }
    ~t_node(){
        delete left;
        delete right;
    }
    bool isChildLess(){
        if (left == NULL && IsThread) return true;
        else return false;
    }
    void cpyData(t_node *Node){
        name = Node->name;
        age = Node->age;
        gender = Node->gender;
        dept = Node->dept;
    }
} *Node;

Node Insert(Node root, string name, int age, char gender, string dept, Node right){
    if(root == NULL){
        Node node = new t_node(name,age,gender,dept);
        node->right = right;
        return node;
    }
    if(name < root->name){
        root->left = Insert(root->left, name, age, gender, dept, root->right);
    }else{
        if (root->IsThread){
            root->right = Insert(NULL, name, age, gender, dept, root->right);
            root->IsThread = false;
        }
        else
            root->right = Insert(root->right, name, age, gender, dept, root->right);
    }
    return root;
}

void Inorder(Node root){
    if(root == NULL) return;
    Inorder(root->left);
    cout<<root->name<<" ";
    if (!root->IsThread)
        Inorder(root->right);
}

void Search(Node root, string name){
    if(root == NULL) return;
    else if(name == root->name){
    	    cout<<"Name: "<<root->name<<endl;
            cout<<"Age: "<<root->age<<endl;
            cout<<"Gender: "<<root->gender<<endl;
            cout<<"Department: "<<root->dept<<endl;
    }
    else if(name < root->name) Search(root->left, name);
    else if (!root->IsThread) 
        Search(root->right, name);
        // Inorder(root->right);
}

Node Delete(Node &root, string name, Node parent){
    if (root == NULL) return NULL;
    else if (name.compare(root->name) == 0) {
        if (root->isChildLess() == true) {
            Node temp_root = root;
            if (parent != NULL){
                if (parent->right == root){
                    parent->right = root->right;
                    parent->IsThread = true;
                }
                else
                    root = NULL;
            }else
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

            if (ptr == parentPtr->right) final = Delete(parentPtr->right, ptr->name, parentPtr);
            else final = Delete(parentPtr->left, ptr->name, parentPtr);

            final->cpyData(temp_root);

            return final;
        }
    }
    else if(name.compare(root->name) < 0) return Delete(root->left, name, root);
    else return Delete(root->right, name, root);
}

int main(){
    Node root = NULL;
    cout<<"Inserting test data into threaded binary tree..."<<endl;
    root = Insert(root,"Alpha", 36, 'M', "CSE",NULL);
    Insert(root, "Beta", 32, 'M', "BT",NULL);
    Insert(root, "Gamma", 25, 'M', "BM",NULL);
    Insert(root, "Delta", 27, 'F', "CE",NULL);
    Insert(root, "Epsilon", 37, 'M', "EE",NULL);
    Insert(root, "Lambda", 48, 'M', "CSE",NULL);
    Insert(root, "Omega", 31, 'M', "CE",NULL);
    Insert(root, "Sigma", 49, 'F', "EP",NULL);
    Inorder(root); cout<<endl;
    cout<<"Searching Sigma..."<<endl;	
    Search(root,"Sigma");
    cout<<"Deleting Sigma..."<<endl;
    delete Delete(root,"Sigma",NULL);
    Inorder(root); cout<<endl;
    cout<<"Deleting Beta..."<<endl;
    delete Delete(root, "Beta",NULL);
    Inorder(root); cout<<endl;
    delete root;
    return 0;
}
