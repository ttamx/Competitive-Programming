#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    if(a[0]!=1)return void(cout << "NO\n");
    vector<bool> c(5001,false);
    c[0]=c[1]=true;
    for(int i=1;i<n;i++){
        int x=a[i];
        if(!c[x])return void(cout << "NO\n");
        for(int j=5000;j>=x;j--)c[j]=c[j]|c[j-x];
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}