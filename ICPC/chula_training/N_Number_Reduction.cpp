#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    int k;
    cin >> s >> k;
    int n=s.size();
    vector<vector<int>> nxt(10,vector<int>(n));
    for(int d=0;d<10;d++){
        int last=1e9;
        for(int i=n-1;i>=0;i--){
            if(s[i]-'0'==d)last=i;
            nxt[d][i]=last;
        }
    }
    string t="";
    int m=n-k,cur=0;
    for(int i=0;i<m;i++){
        for(int d=0;d<10;d++){
            if(i==0&&d==0)continue;
            int need=nxt[d][cur]-cur;
            if(need>k)continue;
            t.push_back('0'+d);
            cur+=need+1;
            k-=need;
            break;
        }
    }
    cout << t << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}