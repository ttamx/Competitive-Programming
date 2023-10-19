#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;

struct node;
typedef node* pnode;
struct node{
    int len,cnt;
    pnode nxt[26],suf;
    node(int _len=1,int _cnt=1){
        len=_len;
        cnt=_cnt;
        for(int i=0;i<26;i++)nxt[i]=nullptr;
        suf=nullptr;
    }
};

int n;
string s;
int a[N];
vector<pnode> v;
pnode cur;
queue<pnode> q;
long long ans=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> s;
    n=s.size();
    a[0]=-1;
    for(int i=1;i<=n;i++)a[i]=s[i-1]-'a';
    v.emplace_back(new node(-1,0));
    v[0]->suf=v[0];
    v.emplace_back(new node(0,0));
    v[1]->suf=v[0];
    cur=v[0];
    for(int i=1;i<=n;i++){
        while(a[i]!=a[i-cur->len-1])cur=cur->suf;
        if(cur->nxt[a[i]]){
            cur=cur->nxt[a[i]];
            cur->cnt++;
            continue;
        }
        pnode tmp=cur->suf;
        cur=cur->nxt[a[i]]=new node(cur->len+2);
        v.emplace_back(cur);
        if(cur->len==1){
            cur->suf=v[1];
            continue;
        }
        while(a[i]!=a[i-tmp->len-1])tmp=tmp->suf;
        cur->suf=tmp->nxt[a[i]];
    }
    reverse(v.begin(),v.end());
    for(auto t:v){
        t->suf->cnt+=t->cnt;
        ans=max(ans,1ll*t->len*t->cnt);
    }
    cout << ans;
}