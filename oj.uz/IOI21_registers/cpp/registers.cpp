#include "registers.h"
#include "bits/stdc++.h"

using namespace std;

const int B=2000;
const int ONE=99;
const int ALT=98;
const int FILL=97;

void construct_instructions(int s, int n, int k, int q) {
	vector<bool> b1(B),b2(B),b3(B);
	for(int i=0;i<B;i+=2*k)b1[i]=1;
	append_store(ONE,b1);
	for(int i=0;i<B;i+=2*k)for(int j=0;j<k;j++)b2[i+j]=1;
	append_store(ALT,b2);
	for(int i=n*k;i<B;i++)b3[i]=1;
	append_store(FILL,b3);
	append_or(0,0,FILL);
	if(s==0){
		int cnt=k;
		while(n>1){
			append_right(1,0,cnt);
			append_and(0,0,ALT); // A
			append_and(1,1,ALT); // B
			append_not(2,1); // - B - 1
			append_add(2,0,2); // A - B - 1
			append_right(2,2,k);
			append_and(2,2,ONE);
			append_add(2,2,ALT);
			append_and(1,1,2);
			append_not(2,2);
			append_and(0,0,2);
			append_or(0,0,1);
			n=(n+1)/2;
			cnt<<=1;
		}
	}else{
		for(int i=0;i<n;i++){
			if(i&1)append_left(1,0,k);
			else append_right(1,0,k);
			append_and(0,0,ALT);
			append_and(1,1,ALT);
			append_not(2,1);
			append_add(2,0,2);
			append_right(2,2,k);
			append_and(2,2,ONE);
			append_add(2,2,ALT);
			append_not(3,2);
			append_and(5,1,2);
			append_and(6,0,3);
			append_or(6,5,6);
			append_and(7,1,3);
			append_and(8,0,2);
			append_or(8,7,8);
			if(i&1)append_right(6,6,k);
			else append_left(8,8,k);
			append_or(0,6,8);
		}
		append_not(FILL,FILL);
		append_and(0,0,FILL);
	}
}