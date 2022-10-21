#include <iostream>
using namespace std;

typedef struct t_node {
    string name;
    int age;
    char gender;
    string dept;
    struct t_node *next;
    struct t_node *prev;
}Node;

class faculty {
    public:
    t_node* head = NULL;
    void InsertAtHead(string name, int age, char gender, string dept);
    void InsertAtTail(string name, int age, char gender, string dept);
    void Delete(string name);
    void Search(string name);
    void Display();
    };

void faculty::InsertAtHead(string name, int age, char gender, string dept){
    Node* temp = new t_node;
    temp->name = name;
    temp->age = age;
    temp->gender = gender;
    temp->dept = dept;
    temp->next = head;
    if(head != NULL){
        head->prev = temp;
    }
    head = temp;
    return;
    }

void faculty::InsertAtTail(string name, int age, char gender, string dept){
    Node* temp = new t_node;
    temp->name = name;
    temp->age = age;
    temp->gender = gender;
    temp->dept = dept;
    temp->next = head;
    if(head == NULL){
        InsertAtHead(name, age, gender, dept);
        return;
    }
    Node* n = head;
    while(n->next != NULL){
        n = n->next;
    }
    n->next = temp; temp->prev = n; temp->next = NULL;
    return;
    }

void faculty::Delete(string key){
    if(head == NULL) return;
    if(head->name == key){
        Node* temp = head;
        head = head->next;
        return;
    }
    Node* n = head; 
    while(n->name != key){
        n = n->next;
    }
    Node* temp = n;
    n->prev->next = n->next;
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
    faculty doubleLinkedList;
    doubleLinkedList.Display();
    cout<<"Inserting first node at head"<<endl;
    doubleLinkedList.InsertAtHead("Alpha", 36, 'M', "CSE");
    doubleLinkedList.Display();
    cout<<"Inserting second node at tail"<<endl;
    doubleLinkedList.InsertAtTail("Beta", 32, 'F', "EP");
    doubleLinkedList.Display();
    cout<<"Inserting third node at head"<<endl;
    doubleLinkedList.InsertAtHead("Gamma", 25, 'M', "BT");
    doubleLinkedList.Display();
    cout<<"Searching Beta"<<endl;
    doubleLinkedList.Search("Beta");
    cout<<"Deleting Beta"<<endl;
    doubleLinkedList.Delete("Beta");
    doubleLinkedList.Display();
    return 0;
}
