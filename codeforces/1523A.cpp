#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;
        string s;
        cin >> s;
        vector<int> l(n),r(n);
        for(int tt=0;tt<2;tt++){
            int last=-INT_MAX/2;
            for(int i=0;i<n;i++){
                if(s[i]=='1'){
                    last=i;
                }
                l[i]=i-last;
            }
            swap(l,r);
            reverse(s.begin(),s.end());
        }
        reverse(r.begin(),r.end());
        for(int i=0;i<n;i++){
            if(s[i]=='0'){
                if(min(l[i],r[i])<=m&&l[i]!=r[i]){
                    s[i]='1';
                }
            }
        }
        cout << s << "\n";
    }
}