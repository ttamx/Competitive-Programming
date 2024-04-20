#include<iostream>
#include<string>
#pragma GCC optimize("Ofast")

using namespace std;

const int N=1000007;
const int K=100005;

int k,m,n;
int mp[N],mem[N];
bool vis[K];
string s;
int key,idx,d;
bool tmp;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> k >> m;
    for(int i=1;i<=k;++i){
        cin >> s;
        key=0;
        for(int j=0;j<m;++j)key=(key<<1)+(s[j]=='1');
        idx=key%N;
        while(mp[idx]!=0)if(++idx==N)idx=0;
        mp[idx]=i;
        mem[idx]=key;
    }
    cin >> n;
    int p=(1<<(m-1))-1;
    while(n--){
        key=0;
        cin >> d >> s;
        for(int i=0;i<m-1;++i)key=(key<<1)+(s[i]=='1');
        tmp=true;
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