#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    string ans=s;
    vector<int> cnt(26);
    int all=0;
    for(auto x:s)if(cnt[x-'a']++==0)all++;
    int l=0,r=s.size()-1;
    stack<int> st;
    for(int i=0;i<26;i++){
        if(cnt[i])all--;
        while(cnt[i]>=2){
            ans[r--]=ans[l++]='a'+i;
            cnt[i]-=2;
        }
        if(cnt[i]){
            if(all==1){
                int idx=i+1;
                while(cnt[idx]==0)idx++;
                for(int j=0;j<(cnt[idx]+1)/2;j++)ans[l++]='a'+idx;
                for(int j=0;j<cnt[idx]/2;j++)ans[r--]='a'+idx;
                ans[l++]='a'+i;
            }else{
                ans[r--]='a'+i;
                for(int j=i+1;j<26;j++)while(cnt[j]--)ans[l++]='a'+j;
            }
            break;
        }
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}