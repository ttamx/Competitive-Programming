#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,ll>;

ll cross(P a,P b,P o){
    a.first-=o.first;
    a.second-=o.second;
    b.first-=o.first;
    b.second-=o.second;
    return a.first*b.second-a.second*b.first;
}

void runcase(int n){
    vector<P> a(n);
    for(auto &[x,y]:a)cin >> x >> y;
    auto check=[&](int i,int j,int k,int l){
        array<int,6> v{i,j,k,l,i,j};
        for(int i=0;i<4;i++){
            if(cross(a[v[i]],a[v[i+2]],a[v[i+1]])>=0){
                return 0;
            }
        }
        return 1;
    };
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                for(int l=0;l<n;l++){
                    ans+=check(i,j,k,l);
                }
            }
        }
    }
    cout << ans/4 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    while(true){
        int n;
        cin >> n;
        if(n==0)break;
        runcase(n);
    }
}