#include<bits/stdc++.h>

using namespace std;

const int inf=2e9;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    if(n==1)return void(cout << "0\n");
    int t=n;
    while(t>1&&a[t-1]<=a[t])t--;
    vector<int> suf(n+2);
    suf[n+1]=inf;
    for(int i=n;i>=1;i--)suf[i]=min(suf[i+1],a[i]);
    for(int i=1;i<t;i++){
        suf[i]=0;
        int l=i,r=n;
        while(l<r){
            int m=(l+r+1)/2;
            if(suf[m]<a[i])l=m;
            else r=m-1;
        }
        if(l==i)return void(cout << -1 << "\n");
    }
    cout << t-1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}