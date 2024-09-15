#include<bits/stdc++.h>

using namespace std;

struct Fenwick{
    int n,lg;
    vector<int> t;
    Fenwick(int _n):n(_n),lg(31-__builtin_clz(n)),t(n+1){}
    void update(int i,int v){
        for(;i<=n;i+=i&-i){
            t[i]+=v;
        }
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i){
            res+=t[i];
        }
        return res;
    }
    int lower_bound(int v){
        int x=0;
        for(int d=1<<lg;d>0;d>>=1){
            if(x+d<=n&&t[x+d]<v){
                v-=t[x+d];
                x+=d;
            }
        }
        return x+1;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    Fenwick f(2*n),f1(n),f2(n);
    for(int i=1;i<=n;i++){
        f.update(i*2-1,1);
    }
    while(q--){
        char op;
        cin >> op;
        if(op=='g'){
            int x;
            cin >> x;
            int i=f.lower_bound(x+1);
            if(i%2==1)i++;
            f.update(i,1);
            f2.update(i/2,1);
        }else if(op=='d'){
            int x;
            cin >> x;
            int i=f.lower_bound(x+1);
            f.update(i,-1);
            if(i%2==1){
                f1.update((i+1)/2,1);
            }else{
                f2.update(i/2,-1);
            }
        }else if(op=='i'){
            int l,r;
            cin >> l >> r;
            int ans=0;
            ans+=f1.query(r)-f1.query(l-1);
            ans+=f2.query(r-1)-f2.query(l-1);
            cout << ans << "\n";
        }else{
            assert(false);
        }
    }
}