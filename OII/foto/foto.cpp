#include <vector>

using namespace std;

bool heights(int N, vector<int> Z, vector<int> &H) {
    for(int i=0;i<N;i++)H[i]=-1;
    H[0]=Z[0];
    H[N-1]=Z[N-2];
    for(int i=1;i<N-1;i++){
        if(H[i]!=-1){
            if(H[i]!=Z[i])H[i+1]=Z[i];
        }else if(Z[i]<=Z[i-1]){
            H[i]=Z[i];
        }else if(H[i]){
            H[i]=0;
            H[i+1]=Z[i];
        }
    }
    for(int i=0;i<N-1;i++)if(Z[i]!=max(H[i],H[i+1]))return false;
    return true;
}