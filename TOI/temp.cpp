#include "bits/stdc++.h"
#include "magic.h"
//#include "grader.cpp"
#define pb push_back
#define st first
#define nd second
#define INF INT_MAX
#define pii pair<int, int>
#define ll long long
using namespace std;

const int N = 2e5 + 10;

vector<pii> adj[N];
int dis[N][10];
bool vis[N];
priority_queue<pii> pq;

vector<int> magic(int N, int M, int Q, vector<int> U, vector<int> V, vector<vector<int>> q){
    vector<int> W(M, INF);
    for (int i = 0; i < Q; ++i) {
        if (q[i][0] == 0) W[q[i][1]] = i;
    }
    for (int i = 0; i < M; ++i) {
        adj[V[i]].pb({U[i], W[i]});
    }

    dis[0][0] = INF;
    pq.push({INF, 0});
    while (!pq.empty()) {
        int a = pq.top().nd; pq.pop();
        if(vis[a])continue;
        vis[a]=true;
        for (auto [b, t] : adj[a]) {
            if (dis[b][0] < min(dis[a][0], t)) {
                dis[b][0] = min(dis[a][0], t);
                pq.push({dis[b][0], b});
            }
        }
    }

    vector<int> ans;
    for (int i = 0; i < Q; ++i) {
        if (q[i][0] == 0) ans.pb(-1);
        else ans.pb((dis[q[i][1]][0] > i ? 1 : 0));
    }
    return ans;
}