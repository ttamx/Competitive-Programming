#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    if(a[n-1]<b[n-1])swap(a[n-1],b[n-1]);
    for(int i=0;i<n;i++){
        if(a[i]<b[i])swap(a[i],b[i]);
        if(a[i]>a[n-1])return void(cout << "No\n");
    }
    for(int i=0;i<n;i++){
        if(b[i]>b[n-1])return void(cout << "No\n");
    }
    cout << "Yes\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}