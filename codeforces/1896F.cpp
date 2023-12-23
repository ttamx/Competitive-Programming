#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    if(s.front()!=s.back())return void(cout << "-1\n");
    int sum=0;
    for(auto x:s)sum^=x-'0';
    if(sum)return void(cout << "-1\n");
    if(n==1){
        if(s.front()=='1')cout << "1\n()\n";
        else cout << "0\n";
        return;
    }
    vector<string> ans;
    string s1="(",s2="((";
    for(int i=1;i<2*n-2;i++){
        sum^=s[i]-'0';
        if(i%2==1)s1+=sum?")(":"()";
        else s2+=sum?"()":")(";
    }
    s1+=")",s2+="))";
    ans.emplace_back(s1);
    ans.emplace_back(s2);
    if(s.front()=='1'){
        string tmp="(";
        for(int i=1;i<n;i++)tmp+="()";
        tmp+=")";
        ans.emplace_back(tmp);
    }
    cout << ans.size() << "\n";
    for(auto x:ans)cout << x << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}