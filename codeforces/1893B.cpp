#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n),b(m);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    sort(b.begin(),b.end());
    for(auto x:a){
        while(!b.empty()&&b.back()>=x){
            cout << b.back() << " ";
            b.pop_back();
        }
        cout << x << " ";
    }
    while(!b.empty()){
        cout << b.back() << " ";
        b.pop_back();
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}