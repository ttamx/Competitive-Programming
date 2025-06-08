#include<bits/stdc++.h>

using namespace std;

const int N=100005;

int n;
int a[N],b[N],l[N],r[N],dp[N];
map<int,int> pos;

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<=n;i+=i&-i)t[i]=max(t[i],v);
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res=max(res,t[i]);
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        pos[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        cin >> b[i];
        if(b[i]<a[i])b[i]=0;
    }
    a[0]=a[n+1]=INT_MAX;
    {
        vector<int> s{0};
        for(int i=1;i<=n;i++){
            while(a[s.back()]<=a[i])s.pop_back();
            l[i]=s.back();
            s.emplace_back(i);
        }
    }
    {
        vector<int> s{n+1};
        for(int i=n;i>=1;i--){
            while(a[s.back()]<=a[i])s.pop_back();
            r[i]=s.back();
            s.emplace_back(i);
        }
    }
    if(n<=5000){
        for(int i=1;i<=n;i++){
            int mx=0;
            for(int j=1;j<=n;j++){
                mx=max(mx,dp[j]);
                if(b[i]==a[j]&&l[j]<i&&i<r[j])dp[j]=mx+1;
            }
        }
        cout << *max_element(dp+1,dp+n+1);
    }else if(pos.size()==n){
        for(int i=1;i<=n;i++){
            int p=pos[b[i]];
            if(p&&l[p]<i&&i<r[p])f.update(p,f.query(p)+1);
        }
        cout << f.query(n);
    }else{
        int v=*max_element(b+1,b+n+1);
        int last=1,ans=0;
        for(int i=1;i<=n;i++){
            if(a[i]!=v)continue;
            for(int j=i;j>=last;j--){
                if(a[j]>v)break;
                if(b[j]==v)ans++;
            }
            for(i++;a[i]<=v;i++){
                if(b[i]==v)ans++;
            }
            last=i;
        }
        cout << ans << "\n";
    }
}