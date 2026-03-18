#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

struct Node{
    int dp,cnt;
    array<int,2> ch;
    Node():dp(-1),cnt(0),ch{0,0}{};
}t[120*N];

void runcase(){
    int n,q,k;
    cin >> n >> q >> k;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    t[0]=t[1]=Node();
    int buf=2;
    auto new_node=[&](){
        t[buf]=Node();
        return buf++;
    };
    auto update=[&](ll x,int v){
        int u=1;
        t[u].cnt+=v;
        vector<int> s;
        for(int i=0;i<k;i++){
            s.emplace_back(u);
            int c=x>>i&1;
            if(!t[u].ch[c])t[u].ch[c]=new_node();
            u=t[u].ch[c];
            t[u].cnt+=v;
        }
        for(int i=k-1;i>=0;i--){
            int u=s[i];
            int l=t[u].ch[0];
            int r=t[u].ch[1];
            t[u].dp=-1;
            if(t[l].dp!=-1||t[l].cnt==0){
                t[u].dp=max(t[u].dp,t[r].cnt*i+max(t[l].dp,0));
            }
            if(t[r].dp!=-1||t[r].cnt==0){
                t[u].dp=max(t[u].dp,t[l].cnt*i+max(t[r].dp,0));
            }
        }
    };
    for(auto x:a)update(x,+1);
    cout << max(t[1].dp,0) << "\n";
    while(q--){
        int i;
        ll x;
        cin >> i >> x;
        i--;
        update(a[i],-1);
        update(a[i]=x,+1);
        cout << max(t[1].dp,0) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}