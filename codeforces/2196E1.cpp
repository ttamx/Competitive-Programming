#pragma GCC optmize("O3,unroll-loops")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

struct SuffixAutomaton{
    using T = char;
    struct Node{
        array<int,26> nxt;
        int link,len;
        Node(int link,int len):link(link),len(len){
            for(int i=0;i<26;i++)nxt[i]=-1;
        }
    };
    vector<Node> nodes;
    int last;
    SuffixAutomaton():nodes{Node(-1,0)},last(0){}
    SuffixAutomaton(const string &s):SuffixAutomaton(){
        for(auto c:s)extend(c);
    }
    int new_node(int link,int len){
        nodes.emplace_back(Node(link,len));
        return (int)nodes.size()-1;
    }
    void extend(T ch){
        int c=ch-'a';
        int cur=new_node(0,nodes[last].len+1);
        int p=last;
        while(p!=-1&&nodes[p].nxt[c]==-1){
            nodes[p].nxt[c]=cur;
            p=nodes[p].link;
        }
        if(p!=-1){
            int q=nodes[p].nxt[c];
            if(nodes[p].len+1==nodes[q].len){
                nodes[cur].link=q;
            }else{
                int r=new_node(nodes[q].link,nodes[p].len+1);
                nodes[r].nxt=nodes[q].nxt;
                while(p!=-1&&nodes[p].nxt[c]==q){
                    nodes[p].nxt[c]=r;
                    p=nodes[p].link;
                }
                nodes[q].link=nodes[cur].link=r;
            }
        }
        last=cur;
    }
    ll distinct_substrings(){
        ll res=0;
        for(int i=1;i<(int)nodes.size();i++)res+=nodes[i].len-nodes[nodes[i].link].len;
        return res;
    }
};

void runcase(){
    int n,m;
    cin >> n >> m;
    string s,t;
    cin >> s >> t;
    SuffixAutomaton sa(s);
    int nn=sa.nodes.size();
    int ans=0;
    for(int i=0;i<m;i++){
        ans++;
        vector<int> a{0};
        bool f=false;
        for(;i<m;i++){
            vector<int> na;
            int ch=t[i]-'a';
            for(auto u:a){
                int v=sa.nodes[u].nxt[ch];
                if(v==-1){
                    if(f)break;
                    f=true;
                    for(int c=0;c<26;c++){  
                        int v=sa.nodes[u].nxt[c];
                        if(v==-1)continue;
                        na.emplace_back(v);
                    }
                }else{
                    na.emplace_back(v);
                }
            }
            a=move(na);
            if(a.empty())break;
        }
        i--;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}