#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int S=19;
const int N=1<<S;
const int K=2<<S;

int n,q,k;
int a[N];

struct Info{
    ll sz,sum,ans;
    friend Info operator+(const Info &l,const Info &r){
        return Info{l.sz+r.sz,l.sum+r.sum,l.ans+r.ans+r.sum*l.sz};
    }
};

struct Info2{
    ll sz,sum,ans;
    array<ll,S> a;
    friend Info2 operator+(const Info2 &l,const Info2 &r){
        Info2 res;
        res.sz=l.sz+r.sz;
        res.sum=l.sum+r.sum;
        res.ans=l.ans+r.ans+l.sz*r.sum;
        for(int i=0;i<S;i++){
            res.a[i]=l.a[i]+r.a[i];
        }
        return res;
    }
    Info get(int x){
        ll res=ans;
        for(int i=0;i<S;i++){
            if(x>>i&1){
                res+=a[i];
            }
        }
        return Info{sz,sum,res};
    }
};

struct Segtree{
    Info2 t[K];
    void build(int l,int r,int i,int d){
        if(l==r){
            t[i].sz=1;
            t[i].sum=t[i].ans=a[l];
            for(int j=0;j<S;j++){
                t[i].a[j]=0;
            }
            return;
        }
        d--;
        int m=(l+r)/2;
        build(l,m,i*2,d);
        build(m+1,r,i*2+1,d);
        Info2 L=t[i*2],R=t[i*2+1];
        t[i]=L+R;
        t[i].a[d]=L.sum*R.sz-R.sum*L.sz;
    }
    Info query(int d,int i,int l,int r,int x){
        if(l==0&&r==(1<<d)-1){
            return t[i].get(x);
        }
        d--;
        if((l>>d&1)==(r>>d&1)){
            l^=(1<<d)&x;
            r^=(1<<d)&x;
            if(l>>d&1)return query(d,i*2+1,l^(1<<d),r^(1<<d),x);
            else return query(d,i*2,l,r,x);
        }
        if(x>>d&1){
            return query(d,i*2+1,l,(1<<d)-1,x)+query(d,i*2,0,r^(1<<d),x);
        }else{
            return query(d,i*2,l,(1<<d)-1,x)+query(d,i*2+1,0,r^(1<<d),x);
        }
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    while((1<<k)<n)k++;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    seg.build(0,n-1,1,k);
    int x=0;
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int v;
            cin >> v;
            x^=v;
        }else{
            int l,r;
            cin >> l >> r;
            auto res=seg.query(k,1,l,r,x);
            if(op==2){
                cout << res.sum << "\n";
            }else{
                cout << res.ans << "\n";
            }
        }
    }
}