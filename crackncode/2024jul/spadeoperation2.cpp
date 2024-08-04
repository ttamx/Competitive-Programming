#include<bits/stdc++.h>

using namespace std;

const int N=20005;
const int MOD=1e9+7;

int n;
int a[N],b[N];
int ans;

int norm(int x){
    return x<0?x+MOD:x>=MOD?x-MOD:x;
}

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        b[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        int x=b[i];
        int l=x-1-f.query(x),r=n-x-(i-1-f.query(x));
        ans+=min(l,r);
        f.update(x,1);
    }
    vector<int> dp(ans+1);
    dp[0]=1;
    for(int i=n;i>=1;i--){
        vector<int> add(ans+1),ndp(ans+1);
        int x=(i-1)/2;
        for(int j=0;j<=ans;j++){
            if(j>0)add[j]=norm(add[j]+add[j-1]);
            add[j]=norm(add[j]+norm(dp[j]*2));
            if(i%2){
                if(j+x+1<=ans)add[j+x+1]=norm(add[j+x+1]-dp[j]);
                if(j+x<=ans)add[j+x]=norm(add[j+x]-dp[j]);
            }else{
                if(j+x+1<=ans)add[j+x+1]=norm(add[j+x+1]-norm(dp[j]*2));
            }
            ndp[j]=add[j];
        }
        swap(dp,ndp);
    }
    cout << ans << "\n";
    cout << dp[ans] << "\n";
}