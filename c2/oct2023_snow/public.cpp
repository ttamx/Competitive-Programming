#include "snow.cpp"
#include <cassert>
#include <cstdio>
#include <vector>
#include <queue>

namespace public_grader{
    // main variable
    std::vector<int>_U,_V;
    std::vector<int>ans;
    int _N,_M,_X,_Y;
    int road_salt_count;
    bool invalid_call;

    // road salt varible
    std::vector<std::pair<int, int> >_P[100005];
    std::queue<int>_Q;
    bool _vis[100005];
}

bool road_salt(std::vector<bool>road){
    using namespace std;
    using namespace public_grader;

    road_salt_count++;
    if(road.size() != _M){
        printf("invalid size of road_salt vector");
        invalid_call = true;
        return false;
    }

    for(int i = 0; i < _N; i++){
        _vis[i] = false;
    }

    _vis[_X] = true;
    _Q.push(_X);
    while(!_Q.empty()){
        int X = _Q.front();
        _Q.pop();
        if(X == _Y) {
            while(!_Q.empty())_Q.pop();
            return true;
        }

        for(int i = 0; i < _P[X].size(); i++){
            if(!road[_P[X][i].second])continue;
            if(!_vis[_P[X][i].first]){
                _vis[_P[X][i].first] = true;
                _Q.push(_P[X][i].first);
            }
        }
    }

    return false;
}

int _Question(){
    using namespace std;
    using namespace public_grader;

    _U.clear();
    _V.clear();
    road_salt_count = 0;
    invalid_call = false;
    int ret = 0, a, b;

    assert(scanf("%d %d %d %d", &_N, &_M, &_X, &_Y) == 4);
    assert(_X < _N && _X >= 0 && _Y < _N && _Y >= 0);
    for(int i = 0; i < _N; i++)_P[i].clear();
    if(_X > _Y)swap(_X, _Y);
    for(int i = 0; i < _M; i++){
        assert(scanf("%d %d", &a, &b) == 2);
        assert(a < _N && a >= 0 && b < _N && b >= 0);
        _U.push_back(a);
        _V.push_back(b);
        _P[a].push_back({b, i});
        _P[b].push_back({a, i});
    }
    ans = find_pair(_N, _M, _U, _V);
    if(invalid_call){
        return -1;
    }
    if(ans.size() != 2){
        printf("invalid size of return vector!");
        ret = -1;
    }
    else{
        if(ans[0] > ans[1])swap(ans[0], ans[1]);
        if(_X == ans[0] && _Y == ans[1]){
            ret = road_salt_count;
        }
        else{
            ret = -1;
        }
    }
    return ret;
}

int main(){
    using namespace public_grader;
    int ans = 0, T;
    assert(scanf("%d",&T)==1);
    for(int i = 0; i < T; i++){
        ans = _Question();
        if(ans == -1)printf("Wrong Answer\n");
        else printf("Correct Answer, Calling road_salt() for %d times\n",ans);
    }
}
