#include<bits/stdc++.h>

using namespace std;

const int N=505;

int n,w;
int a[N][N],b[N][N];
int p[N];

int fp(int u){
    return p[u]=u==p[u]?u:fp(p[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> w;
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            cin >> a[j][i];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            cin >> b[j][i];
        }
    }
    vector<tuple<int,int,int>> ans;
    iota(p,p+n,0);
    if(w!=1){
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(a[j][i]+b[j][i]<w){
                    cout << "NO\n";
                    exit(0);
                }
            }
        }
        for(int i=0;i+1<n;i++){
            ans.emplace_back(i,i+1,b[0][1]);
        }
        map<int,vector<pair<int,int>>> event;
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                event[-a[j][i]].emplace_back(j,i);
            }
        }
        for(auto &[val,edges]:event){
            for(auto [u,v]:edges){
                if(fp(u)==fp(v)){
                    cout << "NO\n";
                    exit(0);
                }
            }
            for(auto [u,v]:edges){
                if(fp(u)!=fp(v)){
                    ans.emplace_back(u,v,w+val);
                    p[fp(u)]=v;
                }
            }
        }
    }else{
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(a[j][i]&&b[j][i]){
                    if(fp(i)!=fp(j)){
                        ans.emplace_back(i,j,0);
                        ans.emplace_back(i,j,1);
                        p[fp(i)]=fp(j);
                    }
                }
            }
        }
        // for(int i=0;i<n;i++){
        //     for(int j=0;j<i;j++){
        //         if(a[j][i]^b[j][i]){
        //             if(fp(i)==fp(j)){
        //                 cout << "NO\n";
        //                 exit(0);
        //             }
        //         }
        //     }
        // }
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(a[j][i]^b[j][i]){
                    if(fp(i)!=fp(j)){
                        ans.emplace_back(i,j,b[j][i]);
                        p[fp(i)]=fp(j);
                    }
                }
            }
        }
        // for(int i=0;i<n;i++){
        //     for(int j=0;j<i;j++){
        //         if(a[j][i]+b[j][i]==0){
        //             if(fp(i)==fp(j)){
        //                 cout << "NO\n";
        //                 exit(0);
        //             }
        //         }
        //     }
        // }
    }
    cout << ans.size() << "\n";
    for(auto [u,v,w]:ans){
        cout << u << " " << v << " " << w << "\n";
    }
}