#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int A=26;

struct SuffixAutomaton{
    struct Node{
        array<int,A> nxt;
        int link,len,val;
        Node(int link,int len):link(link),len(len),val(0){
            for(int i=0;i<A;i++){
                nxt[i]=-1;
            }
        }
    };
    vector<Node> nodes;
    int last;
    SuffixAutomaton():nodes{Node(-1,0)},last(0){}
    int new_node(int link,int len){
        nodes.emplace_back(Node(link,len));
        return (int)nodes.size()-1;
    }
    void extend(char ch){
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
    ll solve(){
        int n=nodes.size();
        vector<int> deg(n);
        for(int i=0;i<n;i++){
            int j=nodes[i].link;
            if(j!=-1){
                deg[j]++;
            }
        }
        queue<int> q;
        for(int i=0;i<n;i++){
            if(deg[i]==0){
                q.emplace(i);
            }
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            int v=nodes[u].link;
            if(v!=-1){
                nodes[v].val+=nodes[u].val;
                if(--deg[v]==0){
                    q.emplace(v);
                }
            }
        }
        ll ans=0;
        for(int i=0;i<n;i++){
            ans=max(ans,1LL*nodes[i].val*nodes[i].len);
        }
        return ans;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    string s,t;
    cin >> s >> t;
    SuffixAutomaton sa;
    for(int i=0;i<n;i++){
        sa.extend(s[i]);
    }
    int u=0;
    for(int i=0;i<n;i++){
        u=sa.nodes[u].nxt[s[i]-'a'];
        assert(u!=-1);
        if(t[i]=='0'){
            sa.nodes[u].val++;
        }
    }
    cout << sa.solve() << "\n";
}