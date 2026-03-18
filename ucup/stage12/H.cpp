#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int B=30;

bool solve(){
    int n;
    cin >> n;
    int cnt[B]={};
    vector<int> a(2*n);
    int sum=0;
    for(auto &x:a){
        cin >> x;
        sum^=x;
        for(int i=0;i<B;i++)cnt[i]+=x>>i&1;
    }
    int c=0;
    for(int i=0;i<B;i++){
        if(cnt[i]%4==2){
            return false;
        }
        if(cnt[i]%4==1||cnt[i]%4==3){
            c++;
        }
    }
    return c%4!=2;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        cout << (solve()?"Menji":"Bot") << "\n";
    }
}