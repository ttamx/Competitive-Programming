#include "rail.h"
#include<bits/stdc++.h>

using namespace std;

void findLocation(int N, int first, int L[], int S[]){
    vector<pair<int,int>> vec;
    for(int i=1;i<N;i++)vec.emplace_back(getDistance(0,i),i);
    sort(vec.begin(),vec.end());
    int p=vec[0].second;
    L[0]=first;
    L[p]=first+vec[0].first;
    S[0]=1;
    S[p]=2;
    int l=0,r=p;
    set<int> C,D;
    C.emplace(L[0]);
    D.emplace(L[r]);
    for(int i=1;i<N-1;i++){
        auto [dist,id]=vec[i];
        int dl=getDistance(l,id),dr=getDistance(r,id);
        int pos=L[l]+dl;
        auto it=C.upper_bound(pos);
        if(it!=C.begin()&&dr==L[r]-*(--it)+pos-*it)L[id]=pos,S[id]=2;
        else{
            pos=L[r]-dr;
            it=D.lower_bound(pos);
            if(it!=D.end()&&dl==*it-L[l]+*it-pos)L[id]=pos,S[id]=1;
            else if(dist==L[p]-first+L[p]-pos)L[id]=pos,S[id]=1;
            else L[id]=L[l]+dl,S[id]=2;
        }
        if(S[id]==1){
            C.emplace(L[id]);
            if(L[id]<L[l])l=id;
        }else{
            D.emplace(L[id]);
            if(L[id]>L[r])r=id;
        }
    }
}