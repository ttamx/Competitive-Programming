#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

struct fenwick{
    int t[N];
    void add(int i,int v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f1,f2;

int n;
int a[N],l[N],r[N];
int mx=-1;
vector<int> ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++){
        l[i]=f1.read(a[i]);
        f1.add(a[i],1);
    }
    for(int i=n;i>=1;i--){
        r[i]=f2.read(a[i]);
        f2.add(a[i],1);
    }
    for(int i=1;i<=n;i++){
        int res=min(l[i],r[i]);
        if(res>mx){
            mx=res;
            ans.clear();
            ans.emplace_back(i);
        }else if(res==mx){
            ans.emplace_back(i);
        }
    }
    cout << mx << "\n";
    for(auto x:ans)cout << x << " ";
}