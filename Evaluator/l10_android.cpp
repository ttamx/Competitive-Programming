#include<bits/stdc++.h>

using namespace std;

int p,s,m,sum;
int c[1005],l[1005];
set<pair<int,int>> v;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> p >> s >> m;
    for(int i=1;i<=p;++i){
        cin >> c[i];
        l[i]=2e9;
    }
    for(int i=1;i<=s;++i){
        int x;
        cin >> x;
        if(l[x]==2e9){
            sum+=c[x];
            while(sum>m){
                auto it=v.begin();
                sum-=c[it->second];
                l[it->second]=2e9;
                v.erase(it);
            }
        }
        l[x]=i;
        v.clear();
        for(int j=1;j<=p;++j)if(l[j]<2e9)v.insert({l[j],j});
    }
    cout << m-sum;
}
