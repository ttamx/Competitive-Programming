#include<bits/stdc++.h>

using namespace std;

int t;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> t;
    while(t--){
        vector<int> v[30],ans;
        string s;
        cin >> s;
        int i=1;
        for(auto c:s)v[c-'a'].emplace_back(i++);
        int l=s[0]-'a',r=s[s.size()-1]-'a';
        if(l<r)for(int i=l;i<=r;++i)for(auto j:v[i])ans.emplace_back(j);
        else for(int i=l;i>=r;--i)for(auto j:v[i])ans.emplace_back(j);
        cout << abs(l-r) << ' ' << ans.size() << '\n';
        for(auto i:ans)cout << i << ' ';
        cout << '\n';
    }
}
