#include <bits/stdc++.h>
using namespace std;
int N, M;
vector<int> v;
int count_bit(int t)
{
    int cnt = 0;
    int b = t;
    for (int i = 0; i < N; i++)
    {
        
            //cout<<v[i]<<" "<<(1<<b)<<endl;
            if((v[i]&(1<<(b)))!=0)
            cnt++;
        
    }
    return cnt;
}
int main()
{
    cin >> N >> M;
    v.resize(N + 1);
    for (int i = 0; i < N; i++)
    {
        int t;
        cin >> t;
        v[i] = t;
    }
    while (M--)
    {
        char q;
        int t;
        cin >> q >> t;
        if (q == 'Q')
        {
            cout<<count_bit(t)<<endl;
        }
        else
        {
            for (int i = 0; i < N; i++)
            {

                v[i] = (v[i] + t) % 65536;
                
            }
        }
    }
}