#include<bits/stdc++.h>

using namespace std;

const int N=20005;
const int Q=2e5+5;

int n,q;
int a[N],ans[Q];
vector<int> vec;
vector<tuple<int,int,int>> add[N],del[N];

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
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        vec.emplace_back(a[i]);
    }
    sort(vec.begin(),vec.end());
    for(int i=1;i<=q;i++){
        int a,b,s,e;
        cin >> a >> b >> s >> e;
        s=lower_bound(vec.begin(),vec.end(),s)-vec.begin()+1;
        e=upper_bound(vec.begin(),vec.end(),e)-vec.begin();
        del[a].emplace_back(i,s,e);
        add[b].emplace_back(i,s,e);
    }
    for(int i=1;i<=n;i++){
        for(auto [j,s,e]:del[i])ans[j]-=f.read(e)-f.read(s-1);
        f.add(lower_bound(vec.begin(),vec.end(),a[i])-vec.begin()+1,1);
        for(auto [j,s,e]:add[i])ans[j]+=f.read(e)-f.read(s-1);
    }
    for(int i=1;i<=q;i++)cout << ans[i] << ' ';
}