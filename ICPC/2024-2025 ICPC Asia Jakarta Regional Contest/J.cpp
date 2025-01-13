#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int B=30;

struct Node{
    int cnt;
    array<int,2> ch;
    Node():cnt(0),ch{-1,-1}{}
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    map<int,int> cnt;
    ll ans=0;
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        ans+=cnt[x]++;
    }
    sort(a.begin(),a.end());
    int mn=1<<B;
    for(int i=1;i<n;i++){
        mn=min(mn,a[i]^a[i-1]);
    }
    if(mn==0){
        cout << ans;
        exit(0);
    }
    vector<bool> good(B);
    vector<Node> node;
    auto new_node=[&]()->int{
        node.emplace_back(Node());
        return node.size()-1;
    };
    int root=new_node();
    auto update=[&](int x,int k)->void{
        int u=root;
        node[u].cnt+=k;
        for(int i=B-1;i>=0;i--){
            int c=x>>i&1;
            if(node[u].ch[c]==-1)node[u].ch[c]=new_node();
            u=node[u].ch[c];
            node[u].cnt+=k;
        }
    };
    auto query=[&](int x)->int{
        int u=root;
        int res=0;
        for(int i=B-1;i>=0;i--){
            int c=x>>i&1;
            if(mn>>i&1){
                if(node[u].ch[c]!=-1)res+=node[node[u].ch[c]].cnt;
                c^=1;
            }
            if(node[u].ch[c]==-1)return res;
            u=node[u].ch[c];
        }
        res+=node[u].cnt;
        return res;
    };
    for(auto [x,c]:cnt){
        ans+=1LL*query(x)*c;
        update(x,c);
    }
    cout << ans;
}