#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k,x;
    cin >> n >> k >> x;
    vector<bool> used(n+2);
    int res=0,cnt=0;
    for(int i=1;i<=n;i++)res^=i;
    if(res!=(k&1)*x){
        cout << "NO\n";
        return;
    }
    if(k==1){
        cout << "YES\n";
        cout << n << ' ';
        for(int i=1;i<=n;i++)cout << i << ' ';
        cout << '\n';
        return;
    }
    vector<vector<int>> ans;
    if(x<=n){
        ans.push_back({x});
        used[x]=true;
        cnt++;
        k--;
    }
    for(int i=1;i<=n;i++){
        if(k==1)break;
        if(used[i])continue;
        if((i^x)>n||used[i^x])continue;
        ans.push_back({i,i^x});
        used[i]=used[i^x]=true;
        cnt+=2;
        k--;
    }
    if(k!=1||cnt==n){
        cout << "NO\n";
        return;
    }
    vector<int> tmp;
    for(int i=1;i<=n;i++)if(!used[i])tmp.push_back(i);
    ans.push_back(tmp);
    cout << "YES" << '\n';
    for(auto v:ans){
        cout << v.size() << ' ';
        for(auto x:v)cout << x << ' ';
        cout << '\n';
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}