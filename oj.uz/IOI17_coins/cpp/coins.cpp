#include "coins.h"

using namespace std;

vector<int> coin_flips(vector<int> b,int c){
    int res=0;
    for(int i=0;i<64;i++)if(b[i])res^=i;
    return {res^c};
}

int find_coin(vector<int> b) {
    int res=0;
    for(int i=0;i<64;i++)if(b[i])res^=i;
    return res;
}