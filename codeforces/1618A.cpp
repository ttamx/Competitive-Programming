#include<bits/stdc++.h>

using namespace std;

void runcase(){
    vector<int> a(7);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    map<int,int> cnt;
    vector<int> ans;
    for(auto x:a){
        if(cnt[x]==0){
            for(auto y:ans)cnt[x+y]++;
            ans.push_back(x);
            if(ans.size()==3)break;
        }else{
            cnt[x]--;
        }
    }
    for(auto x:ans)cout << x << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}