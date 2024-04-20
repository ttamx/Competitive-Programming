#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

int n;
int a[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        cout << f.query(a[i]) << " \n"[i==n];
        f.update(a[i],1);
    }
}