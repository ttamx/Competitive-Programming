#include<bits/stdc++.h>

using namespace std;

int n,q;
map<int,vector<int>> pos;

int lowerBound(int idx,int c){
    int left=0,right=pos[c].size();
    while(left<right){
        int mid=(left+right)/2;
        if(pos[c][mid]>=idx){
            right=mid;
        }else{
            left=mid+1;
        }
    }
    return left;
}

int upperBound(int idx,int c){
    int left=0,right=pos[c].size();
    while(left<right){
        int mid=(left+right)/2;
        if(pos[c][mid]>idx){
            right=mid;
        }else{
            left=mid+1;
        }
    }
    return left;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int val;
        cin >> val;
        pos[val].push_back(i);
    }
    while(q--){
        int l,r,c;
        cin >> l >> r >> c;
        cout << upperBound(r,c)-lowerBound(l,c) << "\n";
    }
}