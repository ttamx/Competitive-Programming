#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m,q;
int posx[N],posy[N],szx[N],szy[N];
map<int,int> px,py;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++)cin >> posx[i];
    for(int i=1;i<=n;i++)cin >> szx[i],szx[i]+=szx[i-1];
    for(int i=1;i<=n;i++)px[posx[i]]=szx[i];
    for(int i=1;i<=m;i++)cin >> posy[i];
    for(int i=1;i<=m;i++)cin >> szy[i],szy[i]+=szy[i-1];
    for(int i=1;i<=m;i++)py[posy[i]]=szy[i];
    px[-2e9]=py[-2e9]=0;
    while(q--){
        int a,b,k;
        cin >> a >> b >> k;
        int l=-1e6,r=1e8+1e6;
        while(l<r){
            int mid=floor((l+r)/2.0);
            if(prev(py.upper_bound((mid-b)/a))->second+prev(px.upper_bound(mid))->second>=k)r=mid;
            else l=mid+1;
        }
        cout << l << "\n";
    }
}