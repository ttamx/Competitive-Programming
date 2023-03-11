#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    int mx=0;
    for(auto &x:a)cin >> x,mx=max(mx,x);
    const int H=1e5+1;
    vector<int> h(H,0),odd(H,0),even(H,0);
    for(int i=1;i<n;i++)h[min(a[i-1],a[i])+1]++,h[max(a[i-1],a[i])]--;
    int sum=0;
    for(int i=1;i<H;i++){
        sum+=h[i];
        if(i&1)odd[i]+=odd[i-1]+sum,even[i]=even[i-1];
        else odd[i]=odd[i-1],even[i]=even[i-1]+sum;
    }
    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;
        l=max(1,l);
        cout << even[r]-even[l-1] << ' ' << odd[r]-odd[l-1] << '\n';
    }
}