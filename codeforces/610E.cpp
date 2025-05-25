#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q,k;
    cin >> n >> q >> k;
    string s;
    cin >> s;
    map<int,pair<int,int>> mp;
    for(int i=0;i<n;i++)mp[i]={i,s[i]-'a'};
    vector<vector<int>> cnt(k,vector<int>(k));
    for(int i=0;i+1<n;i++)cnt[s[i]-'a'][s[i+1]-'a']++;
    auto update=[&](map<int,pair<int,int>>::iterator it,int v){
        if(next(it)==mp.end())return;
        cnt[it->second.second][next(it)->second.second]+=v;
    };
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int l,r;
            char c;
            cin >> l >> r >> c;
            l--,r--;
            auto it=mp.lower_bound(l);
            assert(it!=mp.end());
            {
                int &pl=it->second.first;
                if(pl<l){
                    mp[l-1]=it->second;
                    pl=l;
                }
            }
            if(it!=mp.begin())update(prev(it),-1);
            for(;it!=mp.end()&&it->first<=r;it=mp.erase(it)){
                int pr=it->first;
                auto [pl,pc]=it->second;
                cnt[pc][pc]-=pr-pl;
                update(it,-1);
            }
            if(it!=mp.end()){
                int pr=it->first;
                auto &[pl,pc]=it->second;
                if(pl<=r){
                    cnt[pc][pc]-=r-pl+1;
                    pl=r+1;
                }
            }
            mp[r]={l,c-'a'};
            it--;
            if(it!=mp.begin())update(prev(it),+1);
            update(it,+1);
            cnt[c-'a'][c-'a']+=r-l;
        }else{
            string p;
            cin >> p;
            vector<int> ord(k);
            for(int i=0;i<k;i++)ord[p[i]-'a']=i;
            int res=1;
            for(int i=0;i<k;i++)for(int j=0;j<k;j++)if(ord[i]>=ord[j])res+=cnt[i][j];
            cout << res << "\n";
        }
    }
}