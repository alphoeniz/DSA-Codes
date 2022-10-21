#include <iostream>
using namespace std;

const int N = 100;
int queue[N];
int s=0, e=0;

void Insert(int age){
    if(s != 0 && e == s-1 || s == 0 && e == N-1){
        cout<<"Overflow\n"; return;
    }
    queue[e] = age;
    e++;
    e %= N;
}

void Delete(){
    if(s == e){
        cout<<"Queue is Empty\n"; return;
    }
    queue[s] = 0;
    s++;
    s %= N;
}

void Display(){
    int i = s;
    while(i != e){
        cout<<queue[i]<<" ";
        i++; i %= N;
    }
    cout<<endl;
}

int main(){
    Insert(32); Insert(36); Insert(12); Insert(17); Insert(22);
    Display(); Delete(); Display();
    Delete(); Delete(); Delete(); Display(); Delete(); Delete();
    return 0;
}
