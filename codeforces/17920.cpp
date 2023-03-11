#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    int cnt=0;
    for(auto &x:a){
        cin >> x;
        if(x==1)cnt++;
    }
    cnt/=2;
    cout << n-cnt << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}