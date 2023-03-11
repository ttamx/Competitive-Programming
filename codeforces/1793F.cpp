#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;
const int K=1<<20;

int n,q;
int a[N],l[N],r[N];
vector<tuple<int,int,int>> qr;
multiset<pair<int,int>> sl,sr;
multiset<int> mn;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=q;i++){
        cin >> l[i] >> r[i];
        qr.emplace_back(l[i],r[i],i);
    }
    sort(qr.begin(),qr.end());
    int cl=0,cr=0;
    for(auto )
}