#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

int n,q;
int a[N],c[N],d[N],mob[N];
vector<int> factor[N];
int l[N],r[N];
ll aux[N];
vector<int> check[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    mob[1]=1;
    for(int i=1;i<N;i++){
        for(int j=i*2;j<N;j+=i){
            mob[j]-=mob[i];
        }
        for(int j=i;j<N;j+=i){
            factor[j].emplace_back(i);
        }
    }
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=q;i++){
        cin >> c[i] >> d[i];
    }
    for(int i=1;i<=n;i++){
        l[i]=1;
        r[i]=q+1;
    }
    while(true){
        bool done=true;
        for(int i=1;i<=n;i++){
            if(l[i]<r[i]){
                done=false;
                check[(l[i]+r[i])/2].emplace_back(i);
            }
        }
        if(done)break;
        ll tot=0;
        for(int i=1;i<=q;i++){
            tot+=d[i];
            for(auto g:factor[c[i]]){
                aux[g]+=d[i];
            }
            for(auto j:check[i]){
                ll res=tot;
                for(auto g:factor[j]){
                    res-=mob[g]*aux[g];
                }
                if(res>=a[j])r[j]=i;
                else l[j]=i+1;
            }
            vector<int>().swap(check[i]);
        }
        for(int i=0;i<N;i++){
            aux[i]=0;
        }
    }
    for(int i=1;i<=n;i++){
        cout << (l[i]<=q?l[i]:-1) << "\n";
    }
}