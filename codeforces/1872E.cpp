#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=(1<<18)+5;

int n;
int a[N];
string s;

struct segtree{
    int t[K],sum[K];
    bool lz[K];
    void pushlz(int l,int r,int i){
        if(!lz[i])return;
        lz[i]=false;
        t[i]^=sum[i];
        if(l<r){
            lz[i*2]^=true;
            lz[i*2+1]^=true;
        }
    }
    void build(int l,int r,int i){
        lz[i]=false;
        if(l==r)return t[i]=(s[l]=='1'?a[l]:0),sum[i]=a[l],void();
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]^t[i*2+1];
        sum[i]=sum[i*2]^sum[i*2+1];
    }
    void update(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=true,pushlz(l,r,i),void();
        int m=(l+r)/2;
        update(l,m,i*2,x,y);
        update(m+1,r,i*2+1,x,y);
        t[i]=t[i*2]^t[i*2+1];
    }
}st;

void runcase(){
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    cin >> s;
    s=" "+s;
    st.build(1,n,1);
    int q;
    cin >> q;
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int l,r;
            cin >> l >> r;
            st.update(1,n,1,l,r);
        }else{
            int x;
            cin >> x;
            if(x==1){
                cout << st.t[1] << " ";
            }else{
                cout << (st.t[1]^st.sum[1]) << " ";
            }
        }
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}