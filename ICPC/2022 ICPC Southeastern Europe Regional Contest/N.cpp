#include<bits/stdc++.h>

using namespace std;

const int N=1e5;
int a[N];
set<pair<int,int>> s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    for (int i=0;i<n;i++) cin >> a[i];
    for (int i=0;i<n;i++){
        s.emplace(a[i],i);
    }
    while (!s.empty()){
        auto it =s.end();
        it--;
        auto [nv,i]=*it;
        s.erase(it);
        if (i>0 && nv-a[i-1]>m){
            s.erase(make_pair(a[i-1],i-1));
            a[i-1]=nv-m;
            s.emplace(a[i-1],i-1);
        }
        if (i<n-1 && nv-a[i+1]>m){
            s.erase(make_pair(a[i+1],i+1));
            a[i+1]=nv-m;
            s.emplace(a[i+1],i+1);
        }
    }
    for (int i=0;i<n;i++) cout << a[i] << ' ';
}