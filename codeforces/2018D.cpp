#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    if(n==1){
        cout << a[0]*2+1 << "\n";
        return;
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){return a[i]>a[j];});
    ll ans=a[ord.back()]*2+1;
    vector<bool> alive(n);
    DSU dsu(n);
    vector<array<ll,2>> mx(n,{0,0});
    multiset<ll> diff;
    auto get_diff=[&](int x){
        x=dsu.find(x);
        int s=dsu.size(x);
        ll val1=mx[x][0];
        ll val2=mx[x][1]-(s%2);
        return max(val1,val2);
    };
    ll cur=0;
    auto uni=[&](int u,int v){
        u=dsu.find(u),v=dsu.find(v);
        cur-=(dsu.size(u)+1)/2;
        cur-=(dsu.size(v)+1)/2;
        diff.erase(diff.find(get_diff(u)));
        diff.erase(diff.find(get_diff(v)));
        if(dsu.size(u)%2==0){
            mx[u][0]=max(mx[u][0],mx[v][0]);
            mx[u][1]=max(mx[u][1],mx[v][1]);
        }else{
            mx[u][0]=max(mx[u][0],mx[v][1]);
            mx[u][1]=max(mx[u][1],mx[v][0]);
        }
        dsu.merge(u,v);
        cur+=(dsu.size(u)+1)/2;
        diff.emplace(get_diff(u));
    };
    for(auto i:ord){
        alive[i]=true;
        mx[i][0]=a[i];
        cur++;
        diff.emplace(get_diff(i));
        if(i>0&&alive[i-1]){
            uni(i-1,i);
        }
        if(i+1<n&&alive[i+1]){
            uni(i,i+1);
        }
        ans=max(ans,cur+*diff.rbegin()+a[i]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}