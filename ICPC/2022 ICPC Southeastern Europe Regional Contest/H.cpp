#include<bits/stdc++.h>

using namespace std;

const int N=1e5;
const bool DBG=0;
const bool AUTO=0;

deque<int> dq[5];
vector<pair<int,int>> ans;

mt19937 rng(0);

void solve(){
    ans.clear();
    int n;
    if(AUTO){
        n=rng()%1000;
    }else{
        cin >> n;
    }
    vector<vector<int>> h(3);
    if(AUTO){
        vector<int> a(n);
        iota(a.begin(),a.end(),1);
        shuffle(a.begin(),a.end(),rng);
        for(auto x:a){
            dq[1].emplace_back(x);
            h[0].emplace_back(x);
        }
    }else{
        for (int i=0;i<n;i++){
            int a;
            cin >> a;
            dq[1].emplace_back(a);
            h[0].emplace_back(a);
        }
    }
    int nr=3,xr=2;
    while (!dq[1].empty()){
        while (!dq[1].empty() && (dq[nr].empty() || dq[nr].back()>dq[1].back())){
            // cout << "1 " << nr << "\n";
            ans.emplace_back(1,nr);
            dq[nr].emplace_back(dq[1].back());
            dq[1].pop_back();
        }
        if (!dq[1].empty() && dq[1].back()>dq[nr].back()){
            // cout << "1 " << xr << '\n';
            ans.emplace_back(1,xr);
            dq[xr].emplace_back(dq[1].back());
            dq[1].pop_back();
            while(!dq[nr].empty() && dq[nr].back()<dq[xr].back()){
                // cout << nr << " 1\n";
                ans.emplace_back(nr,1);
                dq[1].emplace_back(dq[nr].back());
                dq[nr].pop_back();
            }
            ans.emplace_back(xr,nr);
            dq[nr].emplace_back(dq[xr].back());
            dq[xr].pop_back();
            while (!dq[1].empty() && dq[1].back()<dq[nr].back()){
                // cout << "1 "<< nr << '\n';
                ans.emplace_back(1,nr);
                dq[nr].emplace_back(dq[1].back());
                dq[1].pop_back();
            }
        }
    }
    for (auto [f,s]:ans) {
        assert(f!=s);
        f--,s--;
        if(DBG){
            cerr  << "OP : " << f+1 << " " << s+1 << "\n";
            for(auto &v:h){
                for(auto x:v)cerr << x << " ";
                cerr << "\n";
            }
            cerr << "-----\n";
        }
        assert(!h[f].empty());
        int sz=h[f].back();
        h[f].pop_back();
        if(s!=0){
            assert(h[s].empty() || h[s].back()>sz);
        }
        h[s].emplace_back(sz);
    }
    if(DBG){
        for(auto &v:h){
            for(auto x:v)cerr << x << " ";
            cerr << "\n";
        }
        cerr << "-----\n";
    }
    if(!AUTO){
        cout << ans.size() <<'\n';
        for (auto [f,s]:ans){
            cout << f << " " << s << "\n";
        }
    }
    dq[3].clear();
    if(AUTO){
        cerr << n << " " << ans.size() << "\n";
    }
    assert(ans.size()<=2*n*n);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    if(AUTO){
        while(true){
            solve();
        }
    }else{
        solve();
    }
}