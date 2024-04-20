#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <assert.h>
#include "mapping.cpp"
using namespace std;

mt19937_64 rngg(time(nullptr));

static int NN,S,cntt,rnk[1005];
static long long dista[1005][1005];
static vector<pair<int,long long>> adja[1005];

void dfs(int x, int par, long long d, int st) {
    dista[st][x]=d;
    for (auto s : adja[x]) {
        if (s.first==par) continue;
        dfs(s.first,x,d+s.second,st);
    }
}

bool send_signal(int x, int a, int b) {
    // cerr << x << " " << a << " " << b << "\n";
    assert(1<=x && x<=NN); assert(1<=a && a<=NN); assert(1<=b && b<=NN);
    assert(dista[x][a]!=dista[x][b]);
    ++cntt;
    if (S==-1) {
        if (dista[x][a]<dista[x][b]) return true;
        else return false;
    } else {
        if (abs(rnk[a]-rnk[b])<=1) {
            if (dista[x][a]<dista[x][b]) return false;
            else return true;
        } else {
            if (dista[x][a]<dista[x][b]) return true;
            else return false;
        }
    }
}

int main() {

    assert(scanf("%d%d",&NN,&S)==2);

    vector<pair<int,int>> input;

    for (int i=0; i<NN-1; ++i) {
        int a,b;
        long long w;
        a=rngg()%(i+1)+1;
        b=i+2;
        // w=rngg()%(1'000'000'000'000'000LL)+1;
        assert(scanf("%d%d%lld",&a,&b,&w)==3);
        adja[a].push_back(make_pair(b,w));
        adja[b].push_back(make_pair(a,w));
        input.push_back(make_pair(min(a,b),max(a,b)));
    }
    sort(input.begin(),input.end());

    for (int i=1; i<=NN; ++i) dfs(i,0,0,i);

    if (S!=-1) {
        vector<pair<long long,int>> temp;
        for (int i=1; i<=NN; ++i) temp.push_back(make_pair(dista[S][i],i));
        sort(temp.begin(),temp.end());
        for (int i=0; i<NN; ++i) rnk[temp[i].second]=i+1;
    }

    vector<pair<int,int>> res=mapping(NN,S);
    vector<pair<int,int>> v;

    for (auto s : res) v.push_back(make_pair(min(s.first,s.second),max(s.first,s.second)));
    sort(v.begin(),v.end());

    if (v.size()!=NN-1) printf("The size is incorrect.");
    else {
        int w=0;
        for (int i=0; i<NN-1; ++i){
            // cerr << v[i].first << " " << v[i].second << " - " << input[i].first << " " << input[i].second << "\n";
            if (v[i].first!=input[i].first || v[i].second!=input[i].second) w=1;
        }
        if (w==0) {
            printf("The answer is correct.\n");
            printf("The count of send_signal : %d",cntt);
        } else {
            printf("The answer is incorrect.");
        }
    }
}