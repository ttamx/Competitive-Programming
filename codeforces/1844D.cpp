#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<vector<bool>> a(n,vector<bool>(26,true));
    vector<int> d;
    for(int i=1;i<n;i++)if(n%i==0)d.emplace_back(i);
    string ans="";
    for(int i=0;i<n;i++){
        int res=0;
        while(!a[i][res])res++;
        ans.push_back(char('a'+res));
        for(auto x:d){
            if(i+x>=n)break;
            a[i+x][res]=false;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}