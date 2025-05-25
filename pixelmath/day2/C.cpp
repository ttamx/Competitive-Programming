#include<bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;

using ll = long long;

const int N=2505;
const int Q=20005;

int n,m,q;
pair<int,int> a[N];
int b[N][N];
set<int> col[N];
int ans[Q];
int base;

bool check(int k){
    for(int i=k;i<=n;i++){
        for(int j=k;j<=m;j++){
            if(b[i][j]-b[i][j-k]-b[i-k][j]+b[i-k][j-k]==0){
                return true;
            }
        }
    }
    return false;
}

bool try_expand(int x,int y){
    deque<pair<int,int>> top,bot;
    for(int i=max(1,y-base);i<=min(m,y+base);i++){
        int new_top=*prev(col[i].upper_bound(x));
        while(!top.empty()&&top.back().first<new_top)top.pop_back();
        top.emplace_back(new_top);
        int new_bot=*prev(col[i].upper_bound(x));
        while(!bot.empty()&&bot.back().first>new_bot)bot.pop_back();
        bot.emplace_back(new_bot);
        if(i>base){
            if(*bot.begin()-*top.rbegin()-1>base)return true;
            top.erase(top.find(*prev(col[i-base].upper_bound(x))));
            bot.erase(bot.find(*col[i-base].lower_bound(x)));
        }
    }
    for(int i=y;i<=min(y+base,m);i++){
    }
    return false;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=m;i++){
        col[i].emplace(0);
        col[i].emplace(n+1);
    }
    for(int i=1;i<=q;i++){
        auto &[x,y]=a[i];
        cin >> x >> y;
        col[y].emplace(x);
        b[x][y]++;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1];
        }
    }
    int l=0,r=min(n,m);
    while(l<r){
        int mid=(l+r+1)/2;
        if(check(mid))l=mid;
        else r=mid-1;
    }
    base=l;
    for(int i=q;i>=1;i--){
        auto [x,y]=a[i];
        col[y].erase(x);
        ans[i]=base;
        while(base<min(n,m)&&try_expand(x,y))base++;
    }
    for(int i=1;i<=q;i++){
        cout << ans[i] << "\n";
    }
}