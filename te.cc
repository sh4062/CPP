#include <bits/stdc++.h>
using namespace std;
unordered_map<string,int> m;
int main(){
    string a;
    while(cin>>a&&a!="QUIT"){
        cout<<m[a]<<endl;
        m[a]++;

    }
}