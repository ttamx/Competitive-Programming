#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n;
int a[N],b[N];
int aa[N],bb[N];
map<int,ll> cnt;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        cin >> b[i];
    }
    for(int i=2;i<=n;i++){
        aa[i]=max(aa[i-1],a[i]);
        bb[i]=max(bb[i-1],b[i]);
    }
    for(int i=1;i<=n;i++){
        cnt[a[i]]++;
        cnt[b[i]]++;
    }
    cnt[a[1]]--;
    for(int i=2;i<=n;i++){
        int j=i;
        while(j<=n&&a[j]<=a[i])j++;
        j--;
        int s1=j-i+1;
        int s2=upper_bound(bb+2,bb+n+1,a[i])-bb-2;
        cnt[a[i]]+=1LL*s1*s2;
        i=j;
    }
    for(int i=2;i<=n;i++){
        int j=i;
        while(j<=n&&b[j]<=b[i])j++;
        j--;
        int s1=j-i+1;
        int s2=lower_bound(aa+2,aa+n+1,b[i])-aa-2;
        cnt[b[i]]+=1LL*s1*s2;
        i=j;
    }
    pair<ll,int> ans(-1,-1);
    for(auto [x,c]:cnt){
        ans=max(ans,make_pair(c,x));
    }
    cout << ans.second << " " << ans.first << "\n";
}