#include<bits/stdc++.h>
using namespace std;
    int d(int m, int n){
    if(m<0)return 0;
    if(m==0||n==1)return 1;
    return d(m,n-1)+d(m-n,n);

}
int main(){
    int t;
    cin>>t;
    while(t--){
        int M,N;
        cin>>M>>N;
        cout<<d(M,N);
    }
}