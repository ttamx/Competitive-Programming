#include "conveyor.h"
#include<bits/stdc++.h>
#include "grader.cpp"

using namespace std;

void Solve(int n, vector<int> A, vector<int> B) {
	vector<int> ans(n - 1, 0);
    vector<bool> done(n-1);
	vector<pair<int,int>> edge(n-1);
	vector<vector<int>> adj(n);
	for(int i=0;i<n-1;i++){
		auto &[u,v]=edge[i];
		u=A[i];
		v=B[i];
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
    {
        vector<int> x(n-1),y(n);
        for(int i=1;i+1<n;i+=3){
            y[i]=1;
        }
        auto res=Query(x,y);
        for(int i=1;i+1<n;i+=3){
            if(res[i]==0){
                done[i-1]=true;
                done[i]=true;
                ans[i-1]=0;
                ans[i]=1;
            }else{
                if(res[i-1]==1){
                    done[i-1]=true;
                    ans[i-1]=1;
                }else{
                    done[i]=true;
                    ans[i]=0;
                }
            }
        }
    }
    {
        vector<int> x(n-1),y(n);
        for(int i=1;i+1<n;i+=3){
            y[i]=1;
        }
        auto res=Query(x,y);
        for(int i=1;i+1<n;i+=3){
            if(res[i]==0){
                done[i-1]=true;
                done[i]=true;
                ans[i-1]=0;
                ans[i]=1;
            }else{
                if(res[i-1]==1){
                    done[i-1]=true;
                    ans[i-1]=1;
                }else{
                    done[i]=true;
                    ans[i]=0;
                }
            }
        }
    }
	Answer(ans);
}