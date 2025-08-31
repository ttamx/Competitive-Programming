#include<bits/stdc++.h>

using namespace std;

using ll = long long;

template<class T>
struct AhoCorasick{
    struct Node{
        array<int,26> ch;
        int fail;
        T val;
        Node(){
            fill(ch.begin(),ch.end(),-1);
            fail=-1;
            val=0;
        }
    };
    vector<Node> nodes;
    AhoCorasick(){new_node();}
    int new_node(){
        nodes.emplace_back(Node());
        return nodes.size()-1;
    }
    void insert(const string &s,const T &val){
        int u=0;
        for(auto x:s){
            int c=x-'a';
            if(nodes[u].ch[c]==-1)nodes[u].ch[c]=new_node();
            u=nodes[u].ch[c];
        }
        nodes[u].val+=val;
    }
    void build(){
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
    }
};

using AC = AhoCorasick<ll>;

const int L=20;

int f[2][L];
AC ac[2][L];
vector<string> a[2][L];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin >> q;
    while(q--){
        int op;
        string s;
        cin >> op >> s;
        if(op==3){
            ll ans=0;
            for(int t=0;t<2;t++){
                for(int i=0;i<L;i++){
                    ll cur=0;
                    auto &b=ac[t][i].nodes;
                    if(b.size()==1)continue;
                    int u=0;
                    for(auto x:s){
                        u=b[u].ch[x-'a'];
                        ans+=b[u].val;
                        cur+=b[u].val;
                    }
                }
                ans=-ans;
            }
            cout << ans << endl;
        }else{
            op--;
            int len=s.size();
            int lg=31-__builtin_clz(len);
            vector<string> cur{s};
            while(f[op][lg]){
                f[op][lg]=0;
                ac[op][lg]=AC();
                for(auto &t:a[op][lg]){
                    cur.emplace_back(t);
                    len+=t.size();
                }
                vector<string>().swap(a[op][lg]);
                lg=31-__builtin_clz(len);
            }
            f[op][lg]=1;
            for(auto t:cur){
                ac[op][lg].insert(t,1);
            }
            ac[op][lg].build();
            a[op][lg]=move(cur);
        }
    }
}