#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    reverse(s.begin(),s.end());
    int c=0;
    vector<int> ans;
    int id=-1;
    int cnt=0;
    for(auto x:s){
        int n=x-'0'+c;
        if(n<10&&n>=5)n=10,id=cnt;
        c=n/10;
        n%=10;
        ans.push_back(n);
        cnt++;
    }
    if(c)ans.push_back(c);
    for(int i=ans.size()-1;i>=0;i--){
        if(i<=id)cout << 0;
        else cout << ans[i];
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}