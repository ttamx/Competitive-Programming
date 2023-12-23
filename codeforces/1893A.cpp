#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int rot=0;
    k=min(k,n);
    while(k--){
        int val=a[(n-1+rot)%n];
        if(val<1||val>n)return void(cout << "No\n");
        rot+=n-val;
        rot%=n;
    }
    cout << "Yes\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}