#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    multiset<int> ms;
    for(auto x:a){
        auto it=ms.lower_bound(x-1);
        if(it!=ms.end()&&*it==x-1)ms.erase(it);
        ms.insert(x);
    }
    cout << ms.size() << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}