#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> ans(n);
    for(int i=0;i<n;++i){
        int x;
        cin >> x;
        ans[x-1]=i+2;
        if(ans[x-1]>n)ans[x-1]=1;
    }
    for(auto i:ans)cout << i << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();   
}