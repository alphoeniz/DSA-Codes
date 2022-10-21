#include <iostream>
using namespace std;

typedef struct t_node {
    string name;
    int age;
    char gender;
    string dept;
    struct t_node *next;
}Node;

class faculty {
    public:
    t_node* head = NULL;
    void Insert(string name, int age, char gender, string dept);
    void Delete(string name);
    void Search(string name);
    void Display();
    };

void faculty::Insert(string name, int age, char gender, string dept){
    Node* temp = new t_node;
    temp->name = name;
    temp->age = age;
    temp->gender = gender;
    temp->dept = dept;
    temp->next = head;
    head = temp;
    return;
    }

void faculty::Delete(string key){
    Node* n = head; 
    if(head == NULL) return;
    if(head->name == key){
        Node* temp = head;
        head = head->next;
        return;
    }
    while(n->next->name != key){
        n = n->next;
        }
    Node* temp = n->next;
    n->next = n->next->next;
    return;
}

void faculty::Search(string key){
    Node* n = head;
    while(n != NULL){
        if(n->name == key){
            cout<<"Name: "<<n->name<<endl;
            cout<<"Age: "<<n->age<<endl;
            cout<<"Gender: "<<n->gender<<endl;
            cout<<"Department: "<<n->dept<<endl;
            return;
    }
    n = n->next;
}
    cout<<"NOT FOUND\n";
}

void faculty::Display()
{
    Node* pointer = head;
    cout<<"(HEAD) -> ";
    while (pointer != NULL)
    {
        cout << pointer->name << " -> ";
        pointer = pointer->next;
    }
    cout<<"(TAIL)"<<endl;
    return;
}

int main(){
    faculty linkedList;
    linkedList.Display();
    cout<<"Inserting first node"<<endl;
    linkedList.Insert("Alpha", 36, 'M', "CSE");
    linkedList.Display();
    cout<<"Inserting second node"<<endl;
    linkedList.Insert("Beta", 32, 'F', "EP");
    linkedList.Display();
    cout<<"Inserting third node"<<endl;
    linkedList.Insert("Gamma", 25, 'M', "BT");
    linkedList.Display();
    cout<<"Searching Beta"<<endl;
    linkedList.Search("Beta");
    cout<<"Deleting Beta"<<endl;
    linkedList.Delete("Beta");
    linkedList.Display();
    return 0;
}
