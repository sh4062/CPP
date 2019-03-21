#include <bits/stdc++.h>
using namespace std;
int partition(vector<int> &L, int low, int high)
{
    int i,j=low;
    for(i = low+1;i<=high;i++){
        if(L[i]>L[low]){
            j++;
            swap(L[i],L[j]);
            
        }

    }
    swap(L[low],L[j]);
    return j;
}
int med(vector<int> L, int low, int high)
{
    int mid = (low + high) / 2;
    while (1)
    {
        int pos = partition(L, low, high);
        if (pos > mid)
        {
            high = pos-1;
        }
        else if (pos < mid)
        {
            low = pos+1;
        }
        else
        {
            break;
        }
    }
    cout << L[mid];
}
int main()
{
    vector<int> v1 = {1, 2, 3, 4, 5, 6, 7};
    vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8};
    med(v1,0,v1.size()-1);
    med(v2,0,v2.size()-1);
    int a;
    cin>>a;
    cout<<a;
}