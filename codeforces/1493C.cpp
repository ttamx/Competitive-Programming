#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    if(n%k!=0)return void(cout << "-1\n");
    int cnt[26]={};
    for(auto x:s)cnt[x-'a']++;
    auto calc=[&](){
        int len=0;
        for(int i=0;i<26;i++)len+=(cnt[i]+k-1)/k*k;
        return len;
    };
    if(calc()==n)return void(cout << s << "\n");
    for(int i=n-1;i>=0;i--){
        int c=s[i]-'a';
        cnt[c]--;
        for(int v=c+1;v<26;v++){
            cnt[v]++;
            int len=calc();
            if(len<=n){
                for(int j=0;j<26;j++){
                    int g=cnt[j]%k;
                    if(g>0){
                        cnt[j]+=k-g;
                    }
                }
                while(len<n){
                    len+=k;
                    cnt[0]+=k;
                }
                string ans="";
                for(int j=0;j<i;j++){
                    ans.push_back(s[j]);
                    cnt[s[j]-'a']--;
                }
                ans.push_back('a'+v);
                cnt[v]--;
                int ch=0;
                for(int j=i+1;j<n;j++){
                    while(!cnt[ch])ch++;
                    ans.push_back('a'+ch);
                    cnt[ch]--;
                }
                cout << ans << "\n";
                return;
            }
            cnt[v]--;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}