#include<bits/stdc++.h>

using namespace std;

const int N=1<<20;

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int find(int k){
        int i=0;
        for(int b=(1<<19);b>0;b>>=1)if(t[i+b]<k)k-=t[i+=b];
        return i+1;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        f.update(x,+1);
    }
    int bal=n;
    while(q--){
        int x;
        cin >> x;
        if(x>0){
            bal++;
            f.update(x,+1);
        }else{
            bal--;
            int i=f.find(-x);
            f.update(i,-1);
        }
    }
    cout << (bal?f.find(1):0) << "\n";
}