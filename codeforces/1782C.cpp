#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> cnt(26);
    for(auto x:s)cnt[x-'a']++;
    int mn=n;
    vector<int> c;
    for(int i=(n+25)/26;i<=n;i++){
        if(n%i)continue;
        vector<pair<int,int>> res(26);
        for(int j=0;j<26;j++)res[j]={max(0,i-cnt[j]),j};
        sort(res.begin(),res.end());
        int tmp=0;
        vector<int> v(26);
        for(int j=0;j<n/i;j++)tmp+=res[j].first,v[res[j].second]=i;
        if(tmp<mn){
            mn=tmp;
            c=v;
        }
    }
    cout << mn << '\n';
    queue<int> q;
    for(int i=0;i<26;i++){
        int x=c[i];
        while(x>cnt[i]){
            x--;
            q.push(i);
        }
    }
    vector<int> cnt2(26);
    for(auto x:s){
        x-='a';
        if(cnt2[x]<c[x]){
            cout << char(x+'a');
            cnt2[x]++;
        }else{
            cout << char(q.front()+'a');
            cnt[q.front()]++;
            q.pop();
        }
    }
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}