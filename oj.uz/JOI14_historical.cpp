#include<bits/stdc++.h>

using namespace std;

const int N=100005;
const int Q=100005;
const int K=1<<18;

int n,q;
int a[N];

vector<int> t[K];



int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=q;i++){
        cin >> ql[i] >> qr[i];
    }
}