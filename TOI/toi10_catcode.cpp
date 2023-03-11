#include<bits/stdc++.h>

using namespace std;

const int N=1e6+3;
const int K=1e5+5;

int k,m,n;
int mp[N],mem[N];
bool vis[K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> k >> m;
    for(int i=1;i<=k;++i){
        string s;
        cin >> s;
        int key=0;
        for(int j=0;j<m;++j)key=(key<<1)+(s[j]=='1');
        int idx=key%N;
        while(mp[idx]!=0)if(++idx==N)idx=0;
        mp[idx]=i;
        mem[idx]=key;
    }
    cin >> n;
    int p=(1<<(m-1))-1;
    while(n--){
        int d,key=0;
        string s;
        cin >> d >> s;
        for(int i=0;i<m-1;++i)key=(key<<1)+(s[i]=='1');
        bool tmp=true;
        for(int i=m-1;i<d;++i){
            key=(key<<1)+(s[i]=='1');
            int idx=key%N;
            while(mp[idx]!=0){
                if(mem[idx]==key){
                    tmp=false;
                    vis[mp[idx]]=true;
                    break;
                }
                if(++idx==N)idx=0;
            }
            key&=p;
        }
        if(tmp)cout << "OK";
        else for(int i=1;i<=k;++i)if(vis[i])cout << i << " ",vis[i]=false;
        cout << '\n';
    }
}
