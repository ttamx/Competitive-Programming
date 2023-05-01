//unfinished
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
int pos[N],cnt[N];

struct fenwick{
    int t[N];
    void add(int i,int v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        pos[x]=i;
        cnt[x]=i-f.read(x)-1;
        f.add(i,1);
    }
    while(q--){
        int k,x;
        cin >> k >> x;
        cout << pos[x]-min(k,cnt[x]) << '\n';
    }
}