#include<bits/stdc++.h>

using namespace std;

struct SuffixAutomaton{
    struct Node{
        array<int,26> nxt;
        int link,len,dp;
        Node(int link,int len):link(link),len(len){
            nxt.fill(-1);
        }
    };
    vector<Node> nodes;
    int last;
    SuffixAutomaton():nodes{Node(-1,0)},last(0){}
    SuffixAutomaton(const string &s):SuffixAutomaton(){
        for(auto c:s)extend(c-'a');
    }
    int new_node(int link,int len){
        nodes.emplace_back(Node(link,len));
        return (int)nodes.size()-1;
    }
    void extend(int c){
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
};

vector<int> z_algorithm(const string &s){
    int n=(int)s.size();
    vector<int> z(n);
    z[0]=n;
    for(int i=1,l=0,r=1;i<n;i++){
        if(i<r)z[i]=min(r-i,z[i-l]);
        while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
        if(i+z[i]>r)l=i,r=i+z[i];
    }
    return z;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    SuffixAutomaton sa(s);
    int n=sa.nodes.size();
    vector<int> dp(n);
    vector<bool> vis(n);
    for(int u=sa.last;u!=-1;u=sa.nodes[u].link){
        dp[u]=1;
    }
    function<void(int)> dfs=[&](int u){
        if(vis[u])return;
        vis[u]=true;
        for(int c=0;c<26;c++){
            int v=sa.nodes[u].nxt[c];
            if(v!=-1){
                dfs(v);
                dp[u]+=dp[v];
            }
        }
    };
    dfs(0);
    int q;
    cin >> q;
    while(q--){
        string t;
        cin >> t;
        int m=t.size();
        t=t+t;
        auto z=z_algorithm(t);
        for(int i=1;i<=m;i++){
            if(z[i]>=m){
                t.resize(i+m-1);
                break;
            }
        }
        int u=0,len=0,ans=0;
        for(int i=0;i<t.size();i++){
            int c=t[i]-'a';
            while(u!=0&&sa.nodes[u].nxt[c]==-1){
                len--;
                if(len==sa.nodes[sa.nodes[u].link].len){
                    u=sa.nodes[u].link;
                }
            }
            if(sa.nodes[u].nxt[c]!=-1){
                u=sa.nodes[u].nxt[c];
                len++;
            }
            if(i+1>=m&&len>=m){
                ans+=dp[u];
                len--;
                if(len==sa.nodes[sa.nodes[u].link].len){
                    u=sa.nodes[u].link;
                }
            }
        }
        cout << ans << "\n";
    }
}