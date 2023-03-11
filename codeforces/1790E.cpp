#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long n;
    cin >> n;
    vector<long long> b(35),a(35);
    for(int i=0;i<35;i++)if(n&(1ll<<i))b[i]++,a[i]++;
    for(int i=1;i<35;i++){
        if(n&(1ll<<i)){
            a[i-1]+=2;
            n-=(1<<i);
        }
        if(n<0){
            cout << -1 << '\n';
            return;
        }
    }
    long long x=0,y=0;
    for(int i=0;i<35;i++){
        if(a[i]==2){
            x+=(1ll<<i);
            y+=(1ll<<i);
        }
        if(a[i]==1){
            if(y==0)y+=(1ll<<i);
            else x+=(1ll<<i);
        }
    }
    if(x==0||y==0||(x^y)!=(x+y)/2){
        cout << -1 << '\n';
        return;
    }
    cout << x << ' ' << y << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}