#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> freq(n);
    vector<int> s(m),d(m),ub(m),ext(m),sz(m);
    vector<map<int,int>> mp(m),cnt(m);
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        x--;
        freq[x]++;
    }
    for(auto &x:s)cin >> x;
    for(auto &x:d)cin >> x;
    int tub=0;
    priority_queue<pair<int,int>> pex,pq;
    for(int i=0;i<m;i++){
        ub[i]=s[i]/d[i];
        sz[i]=ub[i]*d[i];
        ext[i]=s[i]-sz[i];
        tub+=ub[i];
        if(ext[i])pex.emplace(ext[i],i);
        if(sz[i])pq.emplace(sz[i],i);
    }
    vector<int> pos(n);
    iota(pos.begin(),pos.end(),0);
    sort(pos.begin(),pos.end(),[&](int i,int j){
        return freq[i]>freq[j];
    });
    vector<pair<int,int>> left;
    for(auto i:pos){
        vector<pair<int,int>> res;
        while(freq[i]>0&&!pq.empty()){
            auto [_sz,id]=pq.top();
            int used=min({_sz,freq[i],ub[id]});
            pq.pop();
            _sz-=used;
            freq[i]-=used;
            mp[id][i]+=used;
            cnt[id][i]=used;
            if(_sz)res.emplace_back(_sz,id);
        }
        if(freq[i])left.emplace_back(freq[i],i);
        for(auto x:res)pq.emplace(x);
    }
    if(!pq.empty())return void(cout << "-1\n");
    sort(left.rbegin(),left.rend());
    for(auto [f,i]:left){
        vector<pair<int,int>> res;
        while(f>0&&!pex.empty()){
            auto [_ext,id]=pex.top();
            pex.pop();
            int used=min({_ext,f,max(0,ub[id]-cnt[id][i])+1});
            _ext-=used;
            f-=used;
            mp[id][i]+=used;
            if(_ext)res.emplace_back(_ext,id);
        }
        if(f)return void(cout << "-1\n");
        for(auto x:res)pex.emplace(x);
    }
    for(int i=0;i<m;i++){
        vector<pair<int,int>> res;
        for(auto [x,y]:mp[i])res.emplace_back(y,x+1);
        sort(res.rbegin(),res.rend());
        int pos=0,mod=0;
        vector<int> ans(s[i]);
        for(auto &[x,y]:res){
            while(x--){
                ans[pos]=y;
                pos+=d[i];
                if(pos>=s[i])pos=++mod;
            }
        }
        for(auto x:ans)cout << x << " ";
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}