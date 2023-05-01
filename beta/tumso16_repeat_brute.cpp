#include<bits/stdc++.h>

using namespace std;

const int N=5e4+5;

int n,q;
int a[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    int k=1;
    while(q--){
        int x;
        cin >> x;
        if(x>k)swap(x,k);
        set<int> s;
        for(int i=x;i<=k;i++)s.emplace(a[i]);
        int now=s.size();
        k=(now%n)+1;
        cout << now << '\n';
    }
}