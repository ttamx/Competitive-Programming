#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> vec[35];
    for(int i=0;i<n;i++){
        cin >> a[i];
        int b=31-__builtin_clz(a[i]&-a[i]);
        vec[b].emplace_back(i);
    }
    while(q--){
        int x;
        cin >> x;
        for(int j=30;j>=x;j--){
            for(auto i:vec[j]){
                a[i]+=1<<(x-1);
                vec[x-1].emplace_back(i);
            }
            vec[j].clear();
        }
    }
    for(auto x:a)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}