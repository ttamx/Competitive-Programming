#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m;
int a[N],val[N];

struct wavelet{
    int lo,hi;
    wavelet *l,*r;
    vector<int> v;
    wavelet(int *st,int *ed,int x,int y){
        lo=x,hi=y;
        if(st>=ed||lo==hi)return;
        int mid=(lo+hi)/2;
        auto f=[&](int x){
            return x<=mid;
        };
        v.emplace_back(0);
        for(auto it=st;it!=ed;it++){
            v.emplace_back(v.back()+f(*it));
        }
        auto pivot=stable_partition(st,ed,f);
        l=new wavelet(st,pivot,lo,mid);
        r=new wavelet(pivot,ed,mid+1,hi);
    }
    int query(int l,int r,int k){
        if(l>r)return 0;
        if(lo==hi)return lo;
        int inleft=v[r]-v[l-1];
        int cntl=v[l-1];
        int cntr=v[r];
        if(k<=inleft)return this->l->query(cntl+1,cntr,k);
        return this->r->query(l-cntl,r-cntr,k-inleft);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> a[i],val[i]=a[i];
    sort(val+1,val+n+1);
    for(int i=1;i<=n;i++)a[i]=lower_bound(val+1,val+n+1,a[i])-val;
    wavelet t(a+1,a+n+1,1,n);
    while(m--){
        int l,r,k;
        cin >> l >> r >> k;
        cout << val[t.query(l,r,k)] << "\n";
    }
}