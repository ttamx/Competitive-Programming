#include<bits/stdc++.h>

using namespace std;

using pi = pair<int,int>;

const int N=2e6+5;

int n;
int t[N];
string s;
stack<int> st;
vector<int> adj[N];

struct Info{
    int l,m,r;
    Info():l(0),m(1),r(0){}
    int sz(){
        return l+m+r;
    }
}dp[N];

void dfs(int u){
    if(t[u]==0)return;
    for(auto v:adj[u])dfs(v);
    Info dl=dp[adj[u][0]],dr=dp[adj[u][1]];
    int tot=dl.sz()+dr.sz();
    if(t[u]==-1){
        dp[u].l=min(dl.l,dr.l);
        dp[u].m=dl.l+dl.m+dr.l+dr.m-1-dp[u].l;
        dp[u].r=tot-dp[u].l-dp[u].m;
    }else{
        dp[u].r=min(dl.r,dr.r);
        dp[u].m=dl.r+dl.m+dr.r+dr.m-1-dp[u].r;
        dp[u].l=tot-dp[u].r-dp[u].m;
    }
}

void pop(){
    int u=st.top();
    st.pop();
    int p=st.top();
    adj[p].emplace_back(u);
    if(adj[p].size()==2)pop();
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> s;
    st.emplace(0);
    for(int i=0;i<s.size();i++){
        if(s[i]==','||s[i]=='('||s[i]==')')continue;
        st.emplace(++n);
        if(s[i]=='?'){
            t[n]=0;
            pop();
        }else if(s.substr(i,3)=="min"){
            t[n]=-1;
            i+=2;
        }else{
            t[n]=1;
            i+=2;
        }
    }
    dfs(1);
    cout << dp[1].m;
}