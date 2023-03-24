#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    if(a[0]!=1)return void(cout << "NO\n");
    long long sum=1;
    for(int i=1;i<n;i++){
        int x=a[i];
        if(x>sum)return void(cout << "NO\n");
        sum+=x;
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}