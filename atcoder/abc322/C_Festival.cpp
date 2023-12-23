#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n+2);
    while(m--){
        int x;
        cin >> x;
        a[x]=x;
    }
    for(int i=n-1;i>=1;i--)if(a[i]==0)a[i]=a[i+1];
    for(int i=1;i<=n;i++)cout << a[i]-i << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}