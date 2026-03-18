#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int n,m;
int a[60];

struct DS{
    map<int,ll> dat;
    int lz;
    DS():dat(),lz(0){
        dat[0]=1;
    }
    void add(int x){
        lz=(lz+x)%m;
    }
    void insert(int x,ll v){
        x=(x+m-lz)%m;
        dat[x]+=v;
    }
}l1,l2,r1,r2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    int mid=n/2;
    for(int i=0;i<mid;i++){
        swap(l1,l2);
        l1.add(a[i]);
        for(auto &[x,v]:l2.dat){
            l1.insert((x+l2.lz)%m,v);
        }
    }
    for(int i=n-1;i>mid;i--){
        swap(r1,r2);
        r1.add(a[i]);
        for(auto &[x,v]:r2.dat){
            r1.insert((x+r2.lz)%m,v);
        }
    }
    ll ans=0;
    for(auto &[x,v]:l1.dat){
        int xx=((x+l1.lz)%m+r1.lz)%m;
        int y=(m-xx)%m;
        ans+=r1.dat[y]*v;
    }
    for(auto &[x,v]:l2.dat){
        int xx=(((a[mid]+x)%m+l2.lz)%m+r2.lz)%m;
        int y=(m-xx)%m;
        ans+=r2.dat[y]*v;
    }
    cout << ans << "\n";
}