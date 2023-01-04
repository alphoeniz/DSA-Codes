#include <iostream>
using namespace std;

const int N = 1e5+7;
int par[N];

int find(int v){
    if(v == par[v]) return v;
    return par[v] = find(par[v]);
}

int min_index(int n, int* arr){
    int res = 0, m = N;
    for(int i=0; i<n; i++){
        if(arr[i]<m){res = i; m = arr[i];}
    }
    return res;
}

int main(){
    int n,m; int s = 0;
    cin>>n>>m;
    pair<int,int> nodes[m]; int edgewts[m];
    for(int i=0; i<m; i++){
        int u,v,wt;
        cin>>u>>v>>wt;
        nodes[i] = {u,v}; edgewts[i] = wt;
    }
    cout<<"These are the edges in the minimum spanning tree with corresponding edge weights."<<endl;
    for(int i=0; i<m-1; i++){
        int res = min_index(m,edgewts);
        int wt = edgewts[res]; int u = nodes[res].first; int v = nodes[res].second;
        if(par[u] == 0){par[u] = u;} if(par[v] == 0){par[v] = v;}
        int u1 = find(u), v1 = find(v);
        if(u1 != v1){par[v] = u; s+=wt; cout<<u<<" "<<v<<" "<<wt<<endl;}
        edgewts[res] = N;
    }
    cout<<"The total edge weight of the minimum spanning tree is "<<s<<"."<<endl;
    return 0;
}
