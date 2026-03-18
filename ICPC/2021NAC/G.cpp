#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

int n,s;
int a[N],pos[N];

struct Node;
using Ptr = Node*;
struct Node{
    int len,val,dep;
    Node(int len):len()
};

void build()

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> s;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        pos[a[i]]=i;
    }
}