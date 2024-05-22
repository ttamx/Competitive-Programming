#pragma GCC optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
#define ll int
#define pb push_back
ll B;
string s;
ll n;
bool app[200005];
ll ans[200005];
ll kmp(ll k){
    if(app[k])return ans[k];
    ll m=k;
    string pat=s.substr(0,k);
    ll lps[m+5];
   //By def, lps[0]=0;
   lps[0]=0;
   for(int i=1;i<m;i++){
       ll j=lps[i-1];
       while(j>0&&pat[i]!=pat[j]){
           j=lps[j-1];
       }
       if(pat[i]==pat[j]){
           j++;
       }
       lps[i]=j;
   }
   ll i=0,j=0;
    ll prev=-1e9,cnt=0;
   while(i<n){
       if(s[i]==pat[j]){
           i++;j++;
       }
       if(j==m){
           if(i-m-prev>=k){
               prev=i-m;
               cnt++;
           }
           j=lps[j-1];
       }
       else if(j<m&&s[i]!=pat[j]){
           if(j!=0){
               j=lps[j-1];
           }
           else{
               i++;
           }
       }
   }
//    cout<<'\n';
app[k]=1,ans[k]=cnt;
   return cnt; 

}
void solve(){
   ll l,r;
   cin>>n>>l>>r;
   cin>>s;
   if(n==1){
       ll lb=0,rb=1;
       while(lb<=rb){
       if(lb==rb)break;
       else if(lb==rb-1){if(kmp(rb)>=l){lb=rb;}else{rb=lb;}}
       else{
           ll mid=(lb+rb)>>1;
           if(kmp(mid)>=l){
               lb=mid;
           }
           else{
               rb=mid;
           }
       }
   }
   cout<<lb<<' ';
   cout<<'\n';
   for(int i=0;i<=n;i++){
       app[i]=0;
   }
   return;
   }
   double bruh=sqrt((double)n*log2(n));
   B=(int)bruh;
//    cout<<B<<'\n';
   vector<pair<ll,ll> >store;
   for(int i=1;i<=B;i++){
       store.push_back({kmp(i),i});
   }
   for(int i=l;i<=r;i++){
       if(i<=n/B){
            ll lb=0,rb=n;
   while(lb<=rb){
       if(lb==rb)break;
       else if(lb==rb-1){if(kmp(rb)>=i){lb=rb;}else{rb=lb;}}
       else{
           ll mid=(lb+rb)>>1;
           if(kmp(mid)>=i){
               lb=mid;
           }
           else{
               rb=mid;
           }
       }
   }
   cout<<lb<<' ';
       }
       else{
           ll lb=0,rb=B-1;
           while(lb<=rb){
               if(lb==rb)break;
               else if(lb==rb-1){if(store[rb].first>=i){lb=rb;}else{rb=lb;}}
               else{
                   ll mid=(lb+rb)>>1;
                   if(store[mid].first>=i){
                       lb=mid;
                   }
                   else{
                       rb=mid;
                   }
               }
           }
           if(store[lb].first<i){
               cout<<0<<' ';
           }
           else{
           cout<<store[lb].second<<' ';
           }
       }
   }
   cout<<'\n';
   for(int i=0;i<=n;i++){
       app[i]=0;
   }
}
int main(){
    auto start = chrono::high_resolution_clock::now();
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    ll t=1;
    cin>>t;
    while(t--){
        solve();
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cerr << "Time: " << duration.count() << " ms" << endl;
}