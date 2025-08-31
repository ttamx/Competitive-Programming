#include<bits/stdc++.h>

using namespace std;

const int N=2e6+5;

int buf=0;
int e[N];
int nxt[N],front[N],back[N];

void push(int i,int v){
    e[++buf]=v;
    nxt[back[i]]=buf;
    back[i]=buf;
    if(!front[i])front[i]=buf;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    int n=s.size();
    int bal=n;
    int ans1=0,ans2=1;
    push(n,0);
    for(int i=1;i<=n;i++){
        bal+=(s[i-1]=='('?1:-1);
        front[bal+1]=back[bal+1]=0;
        push(bal,i);
        int j=e[front[bal]];
        if(i-j>ans1){
            ans1=i-j;
            ans2=1;
        }else if(i-j==ans1&&ans1>0){
            ans2++;
        }
    }
    cout << ans1 << " " << ans2 << "\n";
}