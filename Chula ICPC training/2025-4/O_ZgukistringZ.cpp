#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s,a,b;
    cin >> s >> a >> b;
    int cnt[26]={},ca[26]={},cb[26]={};
    for(auto x:s)cnt[x-'a']++;
    for(auto x:a)ca[x-'a']++;
    for(auto x:b)cb[x-'a']++;
    int mn=INT_MAX;
    for(int i=0;i<26;i++)if(cb[i])mn=min(mn,cnt[i]/cb[i]);
    int ans=mn;
    int opt=0;
    for(int t=1;;t++){
        bool bad=false;
        for(int i=0;i<26;i++){
            cnt[i]-=ca[i];
            if(cnt[i]<0)bad=true;
        }
        if(bad)break;
        for(int i=0;i<26;i++)if(cb[i])mn=min(mn,cnt[i]/cb[i]);
        if(t+mn>ans){
            ans=t+mn;
            opt=t;
        }
    }
    for(int i=0;i<26;i++){
        cnt[i]=-ca[i]*opt-cb[i]*(ans-opt);
    }
    for(auto x:s)cnt[x-'a']++;
    for(int i=0;i<opt;i++)cout << a;
    for(int i=0;i<ans-opt;i++)cout << b;
    for(int i=0;i<26;i++)cout << string(cnt[i],'a'+i);
    cout << "\n";
}