#include<bits/stdc++.h>

using namespace std;

//FENWICK TREE
template<class T>
struct fenwick{
    const int n;
    vector<T> t;
    fenwick(int n):n(n+1),t(n+1){}
    void add(int i,T v){
        while(i<n)t[i]+=v,i+=i&-i;
    }
    T read(int i){
        T res=0;
        while(i)res+=t[i],i-=i&-i;
        return res;
    }
};
//--------------------------------------------------------

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    fenwick<int> f(n);
    while(q--){
        int o;
        cin >> o;
        if(o==1){
            int l,r;
            cin >> l >> r;
            f.add(l,1);
            f.add(r+1,-1);
        }else if(o==2){
            int x;
            cin >> x;
            int val=f.read(x);
            f.add(x,-val);
            f.add(x+1,val);
            x--;
            while(val--&&a[x]>9){
                int res=0;
                while(a[x]){
                    res+=a[x]%10;
                    a[x]/=10;
                }
                a[x]=res;
            }
            cout << a[x] << '\n';
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}