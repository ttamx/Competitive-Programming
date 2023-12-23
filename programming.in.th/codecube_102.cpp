#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n,p;

struct fenwick{
    int t[N];
    void add(int i,int v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> p;
    while(p--){
        int a,k,d,q;
        cin >> a >> k >> d >> q;
        f.add(max(1,a-k),d);
        f.add(a+k+1,-d);
        if(a-k<1)f.add(a-k+n,d);
        if(a+k>n){
            f.add(1,d);
            f.add(a+k-n+1,-d);
        }
        while(q--){
            int x;
            cin >> x;
            cout << max(0,10000-f.read(x)) << ' ';
        }
        cout << '\n';
    }
}