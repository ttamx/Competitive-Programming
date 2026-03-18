#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n;
string s;
int ch[N][26];
int buf=1;

int merge(int l,int r){
    if(!l||!r)return l|r;
    for(int i=0;i<26;i++)ch[l][i]=merge(ch[l][i],ch[r][i]);
    return l;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        string t;
        cin >> t;
        int u=1;
        for(auto c:t){
            int x=c-'a';
            if(!ch[u][x])ch[u][x]=++buf;
            u=ch[u][x];
        }
    }
    cin >> s;
    string ans="";
    int root=1,p=0;
    while(p<s.size()){
        int x=s[p]-'a';
        int idx=-1;
        for(int i=0;i<26;i++){
            if(ch[root][i]&&i!=x){
                idx=i;
                break;
            }
        }
        if(idx==-1){
            if(ch[root][x]){
                idx=x;
                p++;
            }else{
                cout << "YES\n";
                cout << ans << "\n";
                exit(0);
            }
        }
        ans.push_back('a'+idx);
        int u=ch[root][idx];
        ch[root][idx]=0;
        root=merge(root,u);
    }
    cout << "NO\n";
}