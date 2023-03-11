#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long n,c;
    cin >> n >> c;
    vector<long long> a(n+1),mn(n+1);
    vector<pair<long long,int>> v,s;
    vector<bool> b(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        mn[i]=min(a[i]+i,a[i]+n+1-i);
        v.push_back({mn[i],i});
    }
    sort(v.begin(),v.end());
    int ans=0;
    long long sum=0;
    int sz=0;
    for(auto [x,i]:v){
        if(sum+x>c)break;
        sum+=x;
        s.push_back({x,i});
        b[i]=true;
        sz++;
    }
    reverse(s.begin(),s.end());
    for(int i=1;i<=n;i++){
        int res=sz+1;
        int tmp=sum+a[i]+i;
        if(b[i])tmp-=mn[i],res--;
        for(auto [x,j]:s){
            if(tmp<=c||res<=ans)break;
            if(i==j)continue;
            tmp-=x;
            res--;
        }
        if(tmp>c)continue;
        ans=max(ans,res);
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}