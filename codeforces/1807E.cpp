#include<bits/stdc++.h>

using namespace std;

int ask(int l,int r){
    cout << "? " << r-l+1;
    for(int i=l;i<=r;i++)cout << " " << i;
    cout << endl;
    int res;
    cin >> res;
    return res;
}

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+1),qs(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        qs[i]=qs[i-1]+a[i];
    }
    int l=1,r=n;
    while(l<r){
        int m=(l+r)/2;
        if(ask(l,m)!=qs[m]-qs[l-1])r=m;
        else l=m+1;
    }
    cout << "! " << l << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}