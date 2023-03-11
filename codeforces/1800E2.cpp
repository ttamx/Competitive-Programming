#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    string a,b;
    cin >> a >> b;
    if(a==b)return void(cout << "YES\n");
    vector<int> cnt(26);
    for(auto x:a)cnt[x-'a']++;
    for(auto x:b)cnt[x-'a']--;
    for(int i=0;i<26;i++)if(cnt[i]!=0)return void(cout << "NO\n");
    if(n>=k*2)return void(cout << "YES\n");
    if(n<=k)return void(cout << "NO\n");
    vector<int> p(n);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){
        if(p[u]==u)return u;
        return p[u]=fp(p[u]);
    };
    auto merge=[&](int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return;
        p[u]=v;
    };
    vector<string> va(n),vb(n); 
    for(int i=0;i<n;i++){
        if(i-k>=0)merge(i,i-k);
        if(i+k<n)merge(i,i+k);
        if(i-k-1>=0)merge(i,i-k-1);
        if(i+k+1<n)merge(i,i+k+1);
    }
    for(int i=0;i<n;i++)va[fp(i)].push_back(a[i]);
    for(int i=0;i<n;i++)vb[fp(i)].push_back(b[i]);
    for(int i=0;i<n;i++)if(p[i]==i)sort(va[i].begin(),va[i].end());
    for(int i=0;i<n;i++)if(p[i]==i)sort(vb[i].begin(),vb[i].end());
    for(int i=0;i<n;i++)if(p[i]==i)if(va[i]!=vb[i])return void(cout << "NO\n");
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}