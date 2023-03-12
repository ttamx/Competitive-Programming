#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    int mn=0,mx=0;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        s="0"+s+"0";
        string ss=s;
        int cnt=0;
        vector<int> v;
        for(int i=1;i<=m;i++){
            if(s[i]=='0'&&cnt<m/4){
                if(ss[i-1]=='1'){
                    ss[i-1]='0';
                    cnt++;
                    v.push_back(i);
                    v.push_back(i-1);
                }else if(ss[i+1]=='1'){
                    ss[i+1]='0';
                    cnt++;
                    v.push_back(i);
                    v.push_back(i+1);
                }
            }
        }
        for(auto x:v)ss[x]='1';
        cnt=0;
        for(int i=1;i<=m;i++){
            if(ss[i]=='1'&&cnt<m/4){
                if(ss[i-1]=='1'){
                    ss[i-1]='0';
                    ss[i]='0';
                    cnt++;
                }else if(ss[i+1]=='1'){
                    ss[i+1]='0';
                    ss[i]='0';
                    cnt++;
                }
            }
        }
        for(int i=1;i<=m;i++)if(ss[i]=='1')cnt++;
        mx+=cnt;
        cnt=0;
        ss=s;
        for(int i=1;i<=m;i++){
            if(ss[i]=='1'&&cnt<m/4){
                if(ss[i-1]=='1'){
                    ss[i-1]='0';
                    ss[i]='0';
                    cnt++;
                }else if(ss[i+1]=='1'){
                    ss[i+1]='0';
                    ss[i]='0';
                    cnt++;
                }
            }
        }
        for(int i=1;i<=m;i++)if(ss[i]=='1')cnt++;
        mn+=cnt;
    }
    cout << mn << ' ' << mx << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}