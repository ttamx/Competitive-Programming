#include<bits/stdc++.h>

using namespace std;

const int N=4e5+5;

vector<int> com[N];

void runcase(){
    
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<N;i++)for(int j=i;j<N;j+=i)com[j].emplace_back(i);
    int t(1);
    cin >> t;
    while(t--)runcase();
}