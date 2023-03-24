#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> v;
    for(int i=1;i<=n;i++){
        if(k==0){
            v.push_back(-1000);
            continue;
        }
        if(i<=k){
            v.push_back(2);
            k-=i;
            continue;
        }
        v.push_back(-2*(i-k)+1);
        k=0;
    }
    for(auto x:v)cout << x << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}