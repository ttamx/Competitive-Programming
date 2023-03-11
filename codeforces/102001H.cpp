#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,k;
int f[N],d[N];
bool vis[N];
set<int> s;
vector<tuple<int,int,int>> v;

void add(int x,int v){
    for(int i=x;i<N;i+=i&-i)f[i]+=v;
}

int read(int x){
    int ret=0;
    for(int i=x;i>0;i-=i&-i)ret+=f[i];
    return ret;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;++i){
        int x;
        cin >> x;
        if(x){
            add(i,x);
            d[i]=x;
        }else{
            s.insert(i);
            add(i,-1);
            d[i]=-1;
        }
    }
    for(int i=0;i<k;++i){
        int a,b,c;
        cin >> a >> b >> c;
        v.emplace_back(b,a,c);
    }
    sort(v.begin(),v.end());
    for(auto [b,a,c]:v){
        int sum=read(b)-read(a-1);
        while(sum<c){
            auto it=s.upper_bound(b);
            if(it==s.begin()||*(--it)<a){
                cout << "Impossible";
                return 0;
            }
            add(*it,2);
            d[*it]=1;
            sum+=2;
            s.erase(it);
        }
    }
    for(int i=1;i<=n;++i){
        cout << d[i] << " ";
    }
}
