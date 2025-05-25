#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=1<<19;

int n,q;
int a[N];

struct Info{
    
};

struct Segtree{
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;
        int sum=0,base=0;
        priority_queue<int> pq;
        for(int i=l;i<=r;i++){
            int x=a[i];
            base+=x;
            pq.emplace(2*x);
            sum+=2*x;
            if(sum>base){
                sum-=pq.top();
                pq.pop();
            }
        }
        cout << pq.size() << "\n";
    }
}