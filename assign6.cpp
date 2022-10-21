#include <iostream>
using namespace std;

#define hL 100
#define N 1e5

class Heap{
    public:
    int size = 0;
    int heap[hL];
    void Insert(int age);
    void deleteMin();
    int findMin();
    int parent(int i);
    void swap(int i, int j);
    void Initialize();
};

int Heap::parent(int i){
return ((i-1)/2);
}

void Heap::Initialize(){
    for(int i=0; i<hL; i++){
    	heap[i] = N;
    }
}

void Heap::swap(int i, int j){
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void Heap::Insert(int age){
    if(size == 0){heap[size]=age; size++;}
    else{heap[size] = age; int i = size; size++;
    while(heap[parent(i)]>age){
    swap(parent(i), i);
    i=parent(i);
    }    	
}}

void Heap::deleteMin(){
    if(size == 0){return;}
    int i = 0; swap(0,size); heap[size] = N; size--;
    while(heap[i]>heap[2*i+1] || heap[i]>heap[2*i+2]){
    	int temp = heap[i]; int index;
    	int m = min(heap[2*i+1], heap[2*i+2]);
    	if(m == heap[2*i+1]){index = 2*i+1;}
    	else{index = 2*i+2;}
    	swap(i, index);
    	i = index;
    }
}

int Heap::findMin(){
    if(size == 0){return -1;}
    return heap[0];
}

int main(){
    class Heap hp;
    hp.Initialize();
    hp.Insert(32); hp.Insert(36); hp.Insert(12); hp.Insert(17); hp.Insert(22);
    cout<<hp.findMin()<<endl;
    hp.deleteMin();
    cout<<hp.findMin()<<endl;
    hp.deleteMin();
    cout<<hp.findMin()<<endl;
    hp.deleteMin();
    cout<<hp.findMin()<<endl;
    hp.deleteMin();
    cout<<hp.findMin()<<endl;
    hp.deleteMin();
    cout<<hp.findMin()<<endl; // -1 symbolizes heap is empty.
    hp.deleteMin();
    cout<<hp.findMin()<<endl; // -1 symbolizes heap is empty.
    hp.deleteMin();
    return 0;
}
