#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    auto ask=[&](array<int,3> a){
        cout << a[0] << " " << a[1] << " " << a[2] << endl;
        int res;
        cin >> res;
        return res;
    };
    auto answer=[&](vector<int> a){
        for(auto x:a)cout << x << " ";
        cout << endl;
        exit(0);
    };
    vector<array<int,3>> eq;
    eq.push_back({1,0,0});
    eq.push_back({0,1,0});
    eq.push_back({0,0,1});
    eq.push_back({1,1,1});
    eq.push_back({1,2,3});
    vector<int> ans(5);
    for(int i=0;i<5;i++){
        ans[i]=ask(eq[i]);
    }
    auto solve=[&](vector<array<double,3>> eq,vector<double> ans){
        for(int i=0;i<3;i++){
            for(int j=i;j<3;j++){
                if(eq[j][i]!=0){
                    swap(eq[i],eq[j]);
                    swap(ans[i],ans[j]);
                    break;
                }
            }
            double rat=eq[i][i];
            for(auto &x:eq[i])x/=rat;
            ans[i]/=rat;
            for(int j=0;j<3;j++)if(i!=j){
                double mul=eq[j][i];
                for(int k=i;k<3;k++){
                    eq[j][k]-=mul*eq[i][k];
                }
                ans[j]-=mul*ans[i];
            }
        }
        return ans;
    };
    for(int i=0;i<5;i++){
        set<vector<int>> s;
        for(int j=0;j<5;j++)if(i!=j){
            vector<array<double,3>> eq2;
            vector<double> ans2;
            for(int k=0;k<5;k++)if(i!=k&&j!=k){
                array<double,3> a;
                for(int i=0;i<3;i++)a[i]=eq[k][i];
                eq2.emplace_back(a);
                ans2.emplace_back(ans[k]);
            }
            auto res=solve(eq2,ans2);
            vector<int> res2;
            for(auto x:res){
                int y=x+.5;
                if(abs(x-y)>1e-9){
                    res2={-1,-1,-1};
                    break;
                }
                res2.emplace_back(y);
            }
            s.emplace(res2);
        }
        if(s.size()==1){
            answer(*s.begin());
        }
    }
    assert(false);
}