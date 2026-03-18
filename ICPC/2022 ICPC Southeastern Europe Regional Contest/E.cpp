#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(2*n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> ord(2*n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return a[i]<a[j];
    });
    ll closed=0,opened=1e18;
    for(int i=0;i<2*n;i+=2){
        int u=ord[i],v=ord[i+1];
        if((u^v)==1){
            tie(closed,opened)=make_pair(opened+a[v]+a[u],min(closed-a[u]-a[v],opened+a[u]-a[v]));
        }else{
            tie(closed,opened)=make_pair(min(closed+a[v]-a[u],opened+a[v]+a[u]),min(closed-a[u]-a[v],opened+a[u]-a[v]));
        }
    }
    cout << closed << "\n";
}