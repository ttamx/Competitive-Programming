#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    int res=0;
    for(int i=0;i<3;i++){
        vector<int> a(n);
        for(auto &x:a)cin >> x;
        for(auto x:a){
            if((x&k)!=x)break;
            res|=x;
        }
    }
    cout << (res==k?"Yes":"No") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}