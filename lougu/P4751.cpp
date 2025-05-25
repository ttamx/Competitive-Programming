#include "template.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"
#include "tree/static-top-tree.hpp"
#include "tree/static-top-tree-dp.hpp"

// dp[u][0] = sum max(dp[v][0],dp[v][1])
// dp[v][1] = sum max(dp[v][0],dp[v][1]) + max(dp[v][0] - max(dp[v][0],dp[v][1]));

struct TreeDP{
    struct Path{
        int dp[2][2];
    };
    struct Point{
        int sum,mx;
    };
    static Path compress(Path l,Path r){
        Path res;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                for(int x=0;x<2;x++){
                    for(int y=0;y<2;y++){
                        res.dp[i][y]=max(res.dp[i][y],res.dp[i][j]+res.dp[x][y]+(i&&x));
                    }
                }
            }
        }
        return res;
    }
    static Point rake(Point l,Point r){
        return Point{l.sum+r.sum,max(l.mx,r.mx)};
    }
    static Point add_edge(Path p){
        Point res;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                res.sum=max(res.sum,p.dp[i][j]);
            }
        }
        res.mx=max(p.dp[0][0],p.dp[0][1])-res.sum;
        return res;
    }
    static Path add_vertex(Point p,int u){
        Path res;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                res.dp[i][j]=p.sum;
            }
        }
        res.dp[1][1]=max(res.dp[1][1],p.sum+p.mx+1);
        return res;
    }
    static Path vertex(int u){
        Path res;
        res.dp[0][0]=0;
        res.dp[0][1]=-INF;
        res.dp[1][0]=-INF;
        res.dp[1][1]=0;
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    auto g=read_tree(n);
}