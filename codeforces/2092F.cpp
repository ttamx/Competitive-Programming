#include <bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(n),b(n),ans(n);
    vector<int> pos;
    for(int i=1;i<n;i++){
        a[i]=(s[i]!=s[i-1]);
        if(a[i])pos.emplace_back(i);
    }
    for(int i=1;i<n;i++)b[i]=b[i-1]+a[i];
    auto get_pos=[&](int v){return v>pos.size()?n:pos[v-1];};
    int tot=b[n-1];
    for(int s=1;s<=tot;s++){
        int k=1,cut=0;
        for(int cur=0;cur<n;k++){
            int l=get_pos(b[cur]+s);
            if(l>=n)break;
            int r=get_pos(b[cur]+s+cut+1);
            if(k>1){
                ans[l]++;
                if(r<n)ans[r]--;
            }
            cur=l;
            if(l+1<n&&a[l+1])cur++;
            else cut++;
        }
    }
    for(int i=1;i<n;i++)ans[i]+=ans[i-1];
    for(int i=0;i<n;i++)ans[i]+=i-max(1,b[i])+1;
    for(auto x:ans)cout << x+1 << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}