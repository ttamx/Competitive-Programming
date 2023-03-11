#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    string a,b;
    cin >> a >> b;
    set<int> s;
    map<char,int> mp;
    vector<vector<int>> v(11);
    int idx=0;
    for(int i=0;i<n;i++){
        if(a[i]==b[i]){
            s.insert(i);
        }else{
            if(mp.find(a[i])==mp.end())mp[a[i]]=idx++;
            v[mp[a[i]]].push_back(i);
        }
    }
    k=min(k,idx);
    if(k==idx){
        cout << 1ll*n*(n+1)/2 << '\n';
        return;
    }
    auto calc=[&](set<int> s){
        long long res=0,tmp=0;
        int prev=-2e9;
        for(auto x:s){
            if(x==prev+1){
                tmp++;
            }else{
                res+=tmp*(tmp+1)/2;
                tmp=1;
            }
            prev=x;
        }
        res+=tmp*(tmp+1)/2;
        return res;
    };
    function<long long(set<int>,int,int)> sol=[&](set<int> s,int i,int cnt){
        if(idx-i+cnt<k)return 0ll;
        long long res=calc(s);
        if(cnt>=k||i>=idx)return res;
        res=max(res,sol(s,i+1,cnt));
        for(auto x:v[i])s.insert(x);
        res=max(res,sol(s,i+1,cnt+1));
        return res;
    };
    cout << sol(s,0,0) << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}