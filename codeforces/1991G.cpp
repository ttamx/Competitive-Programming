#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

void runcase(){
    int n,m,k,q;
    cin >> n >> m >> k >> q;
    string s;
    cin >> s;
    vector<vector<int>> a(n,vector<int>(m));
    vector<int> row(n),col(m);
    vector<pair<int,int>> ans;
    auto add=[&](int i,int j,bool h){
        ans.emplace_back(i+1,j+1);
        if(h){
            for(int x=0;x<k;x++){
                assert(a[i][j+x]==0);
                a[i][j+x]=1;
                row[i]++;
                col[j+x]++;
            }
        }else{
            for(int x=0;x<k;x++){
                assert(a[i+x][j]==0);
                a[i+x][j]=1;;
                row[i+x]++;
                col[j]++;
            }
        }
        auto b=a;
        for(int i=0;i<n;i++){
            bool ok=true;
            for(int j=0;j<m;j++){
                if(b[i][j]==0){
                    ok=false;
                    break;
                }
            }
            if(ok){
                for(int j=0;j<m;j++){
                    if(a[i][j]==1){
                        a[i][j]=0;
                        row[i]--;
                        col[j]--;
                    }
                }
            }
        }
        for(int i=0;i<m;i++){
            bool ok=true;
            for(int j=0;j<n;j++){
                if(b[j][i]==0){
                    ok=false;
                    break;
                }
            }
            if(ok){
                for(int j=0;j<n;j++){
                    if(a[j][i]==1){
                        a[j][i]=0;
                        row[j]--;
                        col[i]--;
                    }
                }
            }
        }
    };
    for(auto c:s){
        if(c=='H'){
            bool added=false;
            for(int i=k;i<n;i++){
                if(row[i]==0){
                    add(i,0,true);
                    added=true;
                    break;
                }
            }
            if(added)continue;
            int id=-1;
            for(int i=0;i<k;i++){
                if(a[i][0]==0){
                    if(id==-1||row[i]>row[id]){
                        id=i;
                    }
                }
            }
            assert(id!=-1);
            add(id,0,true);
        }else{
            bool added=false;
            for(int i=k;i<m;i++){
                if(col[i]==0){
                    add(0,i,false);
                    added=true;
                    break;
                }
            }
            if(added)continue;
            int id=-1;
            for(int i=0;i<k;i++){
                if(a[0][i]==0){
                    if(id==-1||col[i]>col[id]){
                        id=i;
                    }
                }
            }
            assert(id!=-1);
            add(0,id,false);
        }
    }
    for(auto [x,y]:ans)cout << x << " " << y << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}