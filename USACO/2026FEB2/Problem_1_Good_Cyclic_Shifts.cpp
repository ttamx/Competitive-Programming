#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> t(n+1);
    auto update=[&](int i,int v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    };
    auto query=[&](int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    };
    ll inv=0;
    for(int i=n-1;i>=0;i--){
        inv+=query(a[i]);
        update(a[i],1);
    }
    ll base=0;
    multiset<int> sr;
    multiset<int,greater<int>> sl;
    for(int i=0;i<n;i++){
        int v=i+1-a[i];
        if(v>0)sr.emplace(v);
        else sl.emplace(v);
        base+=abs(v);
    }
    vector<int> ans;
    for(int i=0;i<n;i++){
        if(inv*2<=base)ans.emplace_back((n-i)%n);
        inv-=a[i]-1;
        inv+=n-a[i];
        int v=i+1-a[i];
        if(sr.find(v)!=sr.end()){
            sr.erase(sr.find(v));
        }else if(sl.find(v)!=sl.end()){
            sl.erase(sl.find(v));
        }else{
            assert(false);
        }
        base-=abs(a[i]-1);
        base+=(int)sl.size();
        base-=(int)sr.size();
        while(!sr.empty()&&*sr.begin()==i+1){
            sl.emplace(*sr.begin());
            sr.erase(sr.begin());
        }
        v=n+i+1-a[i];
        if(v>i+1)sr.emplace(v);
        else sl.emplace(v);
        base+=abs(n-a[i]);
    }
    sort(ans.begin(),ans.end());
    cout << ans.size() << "\n";
    for(int i=0;i<ans.size();i++)cout << ans[i] << " \n"[i==ans.size()-1];
    if(ans.empty())cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}