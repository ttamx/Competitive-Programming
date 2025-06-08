#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int SIGMA = 26;

struct SuffixAutomaton{
    struct Node{
        array<int,SIGMA> nxt;
        int link,len,last;
        Node(int link,int len):link(link),len(len),last(-1){
            nxt.fill(-1);
        }
    };
    vector<Node> nodes;
    int last;
    SuffixAutomaton():nodes{Node(-1,0)},last(0){}
    SuffixAutomaton(const string &s):SuffixAutomaton(){
        for(int i=0;i<s.size();i++)extend(s[i]-'a',i);
    }
    int new_node(int link,int len){
        nodes.emplace_back(Node(link,len));
        return (int)nodes.size()-1;
    }
    void extend(int c,int i){
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
        while(cur!=-1){
            nodes[cur].last=i;
            cur=nodes[cur].link;
        }
    }
};

int main(){
    freopen("name.in","r",stdin);
    freopen("name.out","w",stdout);
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    int n=s.size();
    int q;
    cin >> q;
    vector<vector<tuple<string,int,int>>> qr(n);
    for(int i=0;i<q;i++){
        string t;
        int l,r;
        cin >> t >> l >> r;
        l--,r--;
        qr[r].emplace_back(t,l,i);
    }
    SuffixAutomaton sa;
    vector<ll> ans(q);
    for(int r=0;r<n;r++){
        sa.extend(s[r]-'a',r);
        int u=sa.last;
        for(auto &[t,l,id]:qr[r]){
            int m=t.size();
            u=0;
            int len=0;
            auto valid=[&](int c){
                return sa.nodes[u].nxt[c]!=-1&&sa.nodes[sa.nodes[u].nxt[c]].last-l+1>=len+1;
            };
            vector<int> a(m);
            for(int i=0;i<m;i++){
                int c=t[i]-'a';
                while(u&&!valid(c)){
                    len--;
                    if(len==sa.nodes[sa.nodes[u].link].len){
                        u=sa.nodes[u].link;
                    }
                }
                if(valid(c)){
                    u=sa.nodes[u].nxt[c];
                    len++;
                }
                a[i]=len;
            }
            SuffixAutomaton sa2(t);
            for(int u=1;u<sa2.nodes.size();u++){
                int len_u=sa2.nodes[u].len;
                int len_p=sa2.nodes[sa2.nodes[u].link].len;
                ans[id]+=len_u-len_p;
                ans[id]-=max(0,min(len_u,a[sa2.nodes[u].last])-len_p);
            }
        }
    }
    for(auto x:ans)cout << x << "\n";
}