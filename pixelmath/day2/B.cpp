#include<bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;

using ll = long long;

const int N=1005;
const int M=11;

int n,m,q;
int id[256];
int nxt[N][M];
char ans[N][M];
int disc[N][M];
bool mark[N][M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=0;i<m;i++){
        char c;
        cin >> c;
        id[c]=i;
    }
    for(int i=0;i<n*m;i++){
        int u,v;
        char cu,cv;
        cin >> u >> cu >> v >> cv;
        nxt[u][id[cu]]=v;
        ans[u][id[cu]]=cv;
    }
    string s;
    cin >> s;
    int k=s.size();
    int step=0,cur=0;
    while(!mark[cur][step%k]){
        mark[cur][step%k]=true;
        disc[cur][step%k]=step;
        cur=nxt[cur][id[s[step%k]]];
        step++;
    }
    int loop=step-disc[cur][step%k];
    int treshold=step-loop;
    for(int qq=1;qq<=q;qq++){
        int l,r;
        cin >> l >> r;
        l--;
        string res="";
        int step2=0,cur2=0;
        if(l>=treshold){
            step2=treshold+(l-treshold)/loop*loop;
            cur2=cur;
        }
        while(step2<l){
            cur2=nxt[cur2][id[s[step2%k]]];
            step2++;
        }
        while(step2<r){
            res.push_back(ans[cur2][id[s[step2%k]]]);
            cur2=nxt[cur2][id[s[step2%k]]];
            step2++;
        }
        cout << res << "\n";
    }
}