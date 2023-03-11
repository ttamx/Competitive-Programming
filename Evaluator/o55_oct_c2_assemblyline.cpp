#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

int k,n;
int pos[30];
char c[30];
p2 adj[30][30];
long long dp[205][205][30];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    while(true){
        cin >> k;
        if(k==0)break;
        for(int i=0;i<k;++i)cin >> c[i],c[i]-='a',pos[c[i]]=i;
        for(int i=0;i<k;++i){
            for(int j=0;j<k;++j){
                string s;
                cin >> s;
                int len=s.size();
                int x=0;
                for(int i=0;i<len-2;++i)x*=10,x+=s[i]-'0';
                adj[i][j]={x,pos[s[len-1]-'a']};
            }
        }
        cin >> n;
        while(n--){
            string s;
            cin >> s;
            for(auto &x:s)x=pos[x-'a'];
            int len=s.size();
            for(int i=0;i<len;++i)for(int j=0;j<len;++j)for(int l=0;l<k;++l)dp[i][j][l]=2e9;
            for(int i=0;i<len;++i)dp[i][i][s[i]]=0;
            for(int sz=2;sz<=len;++sz){
                for(int l=0;l+sz-1<len;++l){
                    int r=l+sz-1;
                    for(int m=l;m<r;++m){
                        for(int ll=0;ll<k;++ll){
                            for(int rr=0;rr<k;++rr){
                                dp[l][r][adj[ll][rr].second]=min(dp[l][r][adj[ll][rr].second],dp[l][m][ll]+dp[m+1][r][rr]+adj[ll][rr].first);
                            }
                        }
                    }                    
                }
            }
            pair<long long,char> ans={2e9,c[0]+'a'};
            for(int i=0;i<k;++i){
                if(dp[0][len-1][i]<ans.first){
                    ans={dp[0][len-1][i],c[i]+'a'};
                }
            }
            cout << ans.first << '-' << ans.second << '\n';
        }
        cout << '\n';
    }
    return 0;
}