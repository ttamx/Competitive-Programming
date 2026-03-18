#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int S=450;
const int X=1e6+5;

int n,q;
int a[N];
vector<tuple<int,int,int>> qr[S];

ll cur=0;
ll freq[X];
ll ans[N];

void upd(ll i,ll v){
    i=a[i];
    cur-=freq[i]*freq[i]*i;
    freq[i]+=v;
    cur+=freq[i]*freq[i]*i;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for(int i=0;i<q;i++){
        int l,r;
        cin >> l >> r;
        l--,r--;
        qr[l/S].emplace_back(r,l,i);
    }
    int st=0,ed=-1;
    for(int b=0;b<S;b++){
        sort(qr[b].begin(),qr[b].end());
        for(auto [r,l,i]:qr[b]){
            while(ed<r)upd(++ed,+1);
            while(st>l)upd(--st,+1);
            while(ed>r)upd(ed--,-1);
            while(st<l)upd(st++,-1);
            ans[i]=cur;
        }
    }
    for(int i=0;i<q;i++){
        cout << ans[i] << "\n";
    }
}