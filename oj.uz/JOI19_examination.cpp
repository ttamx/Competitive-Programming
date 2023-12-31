#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,q;
int ans[N];
vector<int> v;

struct point{
    int x,y,z,i;
    bool operator<(const point &o)const{
        if(x!=o.x)return x>o.x;
        if(y!=o.y)return y>o.y;
        return i<o.i;
    }
}a[N],b[N];

struct fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<=n+q;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

void CDQ(int l,int r){
    if(l==r)return;
    int m=(l+r)/2;
    CDQ(l,m);
    CDQ(m+1,r);
    for(int i=l,j=m+1,p=l;p<=r;){
        if(j>r||(i<=m&&a[i].y>=a[j].y)){
            b[p++]=a[i];
            if(a[i].i==0)f.update(a[i].z,1);
            i++;
        }else{
            b[p++]=a[j];
            if(a[j].i)ans[a[j].i]+=f.query(n+q)-f.query(a[j].z-1);
            j++;
        }
    }
    for(int i=l;i<=m;i++)if(a[i].i==0)f.update(a[i].z,-1);
    for(int i=l;i<=r;i++)a[i]=b[i];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i].x >> a[i].y;
        a[i].z=a[i].x+a[i].y;
        v.emplace_back(a[i].z);
    }
    for(int i=n+1;i<=n+q;i++){
        cin >> a[i].x >> a[i].y >> a[i].z;
        v.emplace_back(a[i].z);
        a[i].i=i-n;
    }
    sort(v.begin(),v.end());
    for(int i=1;i<=n+q;i++)a[i].z=lower_bound(v.begin(),v.end(),a[i].z)-v.begin()+1;
    sort(a+1,a+n+q+1);
    CDQ(1,n+q);
    for(int i=1;i<=q;i++)cout << ans[i] << "\n";
}