#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int n,t;

int ask(int i){
    cout << "Q " << i+1 << endl;
    int res;
    cin >> res;
    return res-1;
}

void answer(int i){
    cout << "A " << i+1 << endl;
    char res;
    cin >> res;
}

void runcase(){
    vector<int> a(n);
    iota(a.begin(),a.end(),0);
    shuffle(a.begin(),a.end(),rng);
    vector<bool> del(n);
    for(auto x:a)if(!del[x]){
        int y=ask(x);
        if(x==y)return answer(x);
        del[x]=del[y]=true;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> t;
    while(t--)runcase();
}