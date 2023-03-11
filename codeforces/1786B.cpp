#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,w,h;
    cin >> n >> w >> h;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    int d=(a[0]-w)-(b[0]-h);
    int mn=2e9;
    for(int i=0;i<n;i++){
        int al=a[i]-w;
        int bl=b[i]-h+d;
        if(bl<al){
            d+=al-bl;
            mn-=al-bl;
        }
        int ar=a[i]+w;
        int br=b[i]+h+d;
        mn=min(mn,ar-br);
    }
    if(mn<0)cout << "NO\n";
    else cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}