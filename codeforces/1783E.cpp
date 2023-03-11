#include<bits/stdc++.h>
 
using namespace std;
 
const int N=1000;
 
bool notp[N];
vector<int> p;
 
void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    vector<int> cnt(n+1);
    for(int i=0;i<n;i++){
        if(a[i]<=b[i])continue;
        cnt[b[i]]++;
        cnt[a[i]]--;
    }
    vector<int> ans;
    for(int i=1;i<=n;i++)cnt[i]+=cnt[i-1];
    for(int i=1;i<=n;i++){
        bool ok=true;
        for(int j=i;j<=n;j+=i)if(cnt[j])ok=false;
        if(ok)ans.push_back(i);
    }
    cout << ans.size() << '\n';
    for(auto x:ans)cout << x << ' ';
    cout << '\n';
}
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(notp[i])continue;
        p.push_back(i);
        for(int j=i;j<N;j+=i)notp[i]=true;
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}