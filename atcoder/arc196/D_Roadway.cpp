#include<bits/stdc++.h>

using namespace std;

const int N=4e5+5;
const int M=2e5+5;
const int Q=2e5+5;

int n,m,q;
int s[M],t[M];
vector<pair<int,int>> qr[M];
bool ans[Q];
int pe[N][2],ps[N][2],pt[N][2];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=m;i++)cin >> s[i] >> t[i];
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        qr[r].emplace_back(l,i);
    }
    int last=0;
    for(int i=1;i<=m;i++){
        if(s[i]<t[i]){
            last=max(last,pe[s[i]][1]);
            last=max(last,pe[t[i]-1][0]);
            pe[s[i]][0]=pe[t[i]-1][1]=i;
            last=max(last,ps[s[i]][0]);
            last=max(last,pt[t[i]][0]);
            ps[s[i]][0]=pt[t[i]][0]=i;
        }else{
            last=max(last,pe[s[i]-1][1]);
            last=max(last,pe[t[i]][0]);
            pe[s[i]-1][0]=pe[t[i]][1]=i;
            last=max(last,ps[s[i]][1]);
            last=max(last,pt[t[i]][1]);
            ps[s[i]][1]=pt[t[i]][1]=i;
        }
        for(auto [l,j]:qr[i])ans[j]=(l>last);
    }
    for(int i=1;i<=q;i++)cout << (ans[i]?"Yes":"No") << "\n";
}