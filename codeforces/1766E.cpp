#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    long long ans=0;
    map<vector<int>,int> mp;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        mp[{}]++;
        if(x){
            map<vector<int>,int> mp2;
            for(auto [v,cnt]:mp){
                bool add=true;
                auto v2=v;
                for(auto &a:v2){
                    if(a&x){
                        add=false;
                        a=x;
                        break;
                    }
                }
                if(add)v2.push_back(x);
                mp2[v2]+=cnt;
            }
            mp=mp2;
        }else{
            ans+=1ll*(i+1)*(n-i);
        }
        for(auto [v,cnt]:mp){
            ans+=1ll*v.size()*cnt;
        }
    }
    cout << ans;
}