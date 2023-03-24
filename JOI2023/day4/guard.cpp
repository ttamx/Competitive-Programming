#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

typedef long long ll;

int n,m,q;
int s[N],cnt[N];
ll sum=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++){
        cin >> s[i];
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
    }
    for(int i=1;i<n;i++){
        if(cnt[i]<s[i]){
            sum+=s[i]-cnt[i];
            cnt[i]=s[i];
        }
        if(cnt[i]<s[i+1]){
            sum+=s[i]-cnt[i];
            cnt[i]=s[i];
        }else{
            cnt[i+1]+=cnt[i]-s[i+1];
        }
    }
    if(cnt[n-1]<=s[n])sum+=s[n]-cnt[n-1];
    cout << sum;
}