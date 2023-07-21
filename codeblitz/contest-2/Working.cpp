#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n,q;
ll a[N],sum;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i],sum+=a[i];
    while(q--){
        int m;
        ll w;
        cin >> m >> w;
        w+=sum;
        while(m--){
            int x;
            cin >> x;
            w-=a[x];
        }
        cout << w << "\n";
    }
}