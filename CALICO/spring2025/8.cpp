#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    ll n;
    cin >> n;
    vector<int> ans;
    auto solve=[&](auto &&self,ll s,ll w)->bool {
        if(w<0)return false;
        if(w==0){
            ans.emplace_back(s);
            return true;
        }
        if(s*(s-1)/2<w)return false;
        if(s-1>w)return false;
        for(ll i=s-1;i>0;i--){
            if(i*(s-i)>w)break;
            if(self(self,i,w-i*(s-i))){
                ans.emplace_back(s);
                return true;
            }
        }
        return false;
    };
    for(int i=1;!solve(solve,i,n);i++);
    for(int i=ans.size()-1;i>0;i--)ans[i]-=ans[i-1];
    string s="";
    for(auto x:ans){
        for(int i=0;i<x;i++)s.push_back('u');
        s.push_back('w');
    }
    s.pop_back();
    cout << s << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}