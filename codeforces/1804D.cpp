#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    int mn=0,mx=0;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(auto x:s){
            mn+=x-'0';
            mx+=x-'0';
        }
        int cnt=0;
        for(int j=1;j<m;j++){
            if(cnt==m/4)break;
            if(s[j]=='1'&&s[j-1]=='1'){
                cnt++;
                j++;
            }
        }
        mn-=cnt;
        cnt=m/4;
        for(int j=1;j<m;j++){
            if(cnt==0)break;
            if(s[j]=='0'||s[j-1]=='0'){
                cnt--;
                j++;
            }
        }
        mx-=cnt;
    }
    cout << mn << " " << mx << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}