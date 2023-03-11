#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=3e5;

bool notprime[N];
vector<int> prime;

void runcase(){
    
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    notprime[0]=notprime[1]=true;
    for(int i=2;i<N;i++){
        if(notprime[i])continue;
        prime.push_back(i);
        for(int j=i+i;j<N;j+=i)notprime[j]=true;
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}