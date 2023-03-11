#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

struct fenwick{
  long long f[N];
  void clear(){
    for(int i=0;i<N;++i)f[i]=0;
  }
  void add(int i,long long v){
    while(i<N)f[i]+=v,i+=i&-i;
  }
  long long read(int i){
    long long ret=0;
    while(i)ret+=f[i],i-=i&-i;
    return ret;
  }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> v=a;
    sort(v.begin(),v.end());
    long long ans=0;
    for(auto x:a){
        int idx=lower_bound(v.begin(),v.end(),x)-v.begin()+1;
        ans+=f.read(n)-f.read(idx);
        f.add(idx,1);
    }
    cout << ans;
}