#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

struct Node{
    array<int,26> ch;
    int fail;
    ll val;
    Node(){
        fill(ch.begin(),ch.end(),-1);
        fail=-1;
        val=0;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    ll m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<Node> nodes;
    auto new_node=[&](){
        nodes.emplace_back(Node());
        return nodes.size()-1;
    };
    new_node();
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        int u=0;
        for(auto x:s){
            int c=x-'a';
            if(nodes[u].ch[c]==-1)nodes[u].ch[c]=new_node();
            u=nodes[u].ch[c];
        }
        nodes[u].val+=a[i];
    }
    vector<int> q{0};
    for(int i=0;i<q.size();i++){
        int u=q[i];
        int v;
        for(int c=0;c<26;c++){
            if((v=nodes[u].ch[c])!=-1){
                int p=nodes[u].fail;
                while(p!=-1&&nodes[p].ch[c]==-1)p=nodes[p].fail;
                p=p!=-1?nodes[p].ch[c]:0;
                nodes[v].fail=p;
                nodes[v].val+=nodes[p].val;
                q.emplace_back(v);
            }
        }
    }
    for(auto u:q){
        for(int c=0;c<26;c++){
            if(nodes[u].ch[c]==-1){
                int p=nodes[u].fail;
                while(p!=-1&&nodes[p].ch[c]==-1)p=nodes[p].fail;
                nodes[u].ch[c]=p!=-1?nodes[p].ch[c]:0;
            }
        }
    }
    n=nodes.size();
    vector<vector<ll>> base(n,vector<ll>(n,-INF));
    for(int i=0;i<n;i++){
        for(auto j:nodes[i].ch){
            base[i][j]=max(base[i][j],nodes[j].val);
        }
    }
    auto mul=[&](const vector<vector<ll>> &l,const vector<vector<ll>> &r){
        vector<vector<ll>> res(n,vector<ll>(n,-INF));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int k=0;k<n;k++){
                    res[i][j]=max(res[i][j],l[i][k]+r[k][j]);
                }
            }
        }
        return res;
    };
    vector<vector<ll>> ans(n,vector<ll>(n,-INF));
    for(int i=0;i<n;i++)ans[i][i]=0;
    while(m>0){
        if(m&1)ans=mul(ans,base);
        base=mul(base,base);
        m>>=1;
    }
    cout << *max_element(ans[0].begin(),ans[0].end()) << "\n";
}