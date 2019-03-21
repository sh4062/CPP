#include <bits/stdc++.h>
using namespace std;
void Han(int n, char a, char tmp, char t)
{
    if (n == 1){cout<<a<<"->"<<t<<endl;}
        else
        {

            Han(n - 1, a, t, tmp);
            cout << a << "->" << t  << endl;
            Han(n - 1, tmp, a, t);
        }
}

void per(vector<int> &v,int k,int n){
    if(k==n-1){
        for(auto i:v){
            cout<<i<<" ";
        }
        cout<<endl;
    }else{
        for(int i = k;i<n;i++){
            swap(v[i],v[k]);
            per(v,k+1,n);
            swap(v[i],v[k]);
        }
    }
}

void rev(vector<int> &v){
    int mid = (0+v.size()-1)/2;
    for(int i = 0;i<=mid;i++){
        swap(v[i],v[v.size()-1-i]);
    }

}

int main()
{
    //Han(2, 'x', 'y', 'z'); 
    vector<int> v={1,2,3,4,5};
    //per(v,0,4);
    rev(v);
    for(auto i:v){
            cout<<i<<" ";
        }
        cout<<endl;
}