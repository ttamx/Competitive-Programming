#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    cin >> k;
    vector<pair<int,int>> suf(n);
    for(int i=0;i<n;i++)suf[i]={a[i],-i};
    for(int i=n-2;i>=0;i--)suf[i]=min(suf[i],suf[i+1]);
    vector<int> ans(n);
    int pos=0;
    int add=0;
    int t=1e9;
    while(pos<n&&k>0){
        auto [v,id]=suf[pos];
        id=-id;  
        v-=add;
        t=min(k/v,t);
        if(t==0)break;
        k-=v*t;
        add+=v;
        while(pos<=id)ans[pos++]+=t;
    }
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}