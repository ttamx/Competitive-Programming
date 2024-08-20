#include<bits/stdc++.h>

using namespace std;

const int X=1e5;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    vector<vector<int>> factors(X+1);
    for(int i=1;i<=X;i++){
        for(int j=i*2;j<=X;j+=i){
            factors[j].emplace_back(i);
        }
    }
    vector<int> nimber(X+1);
    for(int i=1;i<=X;i++){
        int s=factors[i].size();
        vector<bool> seen(s+1);
        for(auto j:factors[i]){
            int x=nimber[j];
            if((i/j)%2==0)x=0;
            if(x<=s){
                seen[x]=true;
            }
        }
        int mex=0;
        while(seen[mex])mex++;
        nimber[i]=mex;
    }
    while(t--){
        int n;
        cin >> n;
        int sum=0;
        while(n--){
            int x;
            cin >> x;
            sum^=nimber[x];
        }
        cout << (sum?1:2) << "\n";
    }
}