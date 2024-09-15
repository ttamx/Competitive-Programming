#include <bits/stdc++.h>

using namespace std;

const int N=10;

queue<int> posa[N],posb[N];

vector<int> ucs(vector<int> a,vector<int> b){
    int n=a.size(),m=b.size();
    set<pair<int,int>> ms;
    for(int i=0;i<n;i++){
        posa[a[i]].emplace(i);
    }
    for(int i=0;i<m;i++){
        posb[b[i]].emplace(i);
    }
    auto insert=[&](int val){
        if(!posa[val].empty()&&!posb[val].empty()){
            ms.emplace(posa[val].front(),val);
        }
    };
    auto erase=[&](int val){
        if(!posa[val].empty()&&!posb[val].empty()){
            ms.erase(make_pair(posa[val].front(),val));
        }
    };
    for(int i=0;i<N;i++){
        insert(i);
    }
    int ai=0,bi=0;
    vector<int> ans;
    for(auto [x,y]:ms){
        cerr << x << " " << y << "\n";
    }
    while(ai<n&&bi<m){
        if(ms.empty())break;
        int val=ms.begin()->second;
        ms.erase(ms.begin());
        int aj=posa[val].front();
        int bj=posb[val].front();
        ans.emplace_back(val);
        cerr << val << " " << bi << " " << bj << "\n";
        set<int> to_upd;
        for(;ai<=aj;ai++){
            int val=a[ai];
            to_upd.emplace(val);
            erase(val);
            posa[val].pop();
        }
        for(;bi<=bj;bi++){
            int val=b[bi];
            to_upd.emplace(val);
            erase(val);
            posb[val].pop();
        }
        for(auto val:to_upd){
            insert(val);
        }
    }
    return ans;
}
