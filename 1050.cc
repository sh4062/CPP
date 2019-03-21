#include <bits/stdc++.h>
using namespace std;
vector<int> v;
int main()
{

    int N;
    cin >> N;

    for (size_t i = 0; i < N; i++)
    {
        int t = 0;
        cin >> t;
        v.push_back(t);
    }
    sort(v.begin(), v.end(), greater<int>());
    int m = 1, n = 1;
    int min = 10000;
    for (int i = 1; i <= N; i++)
    {
        if ((N % i == 0) && N / i >= i)
        {
            if (N / i - i < min)
            {
                min = N / i - i;
                m = N / i;
                n = i;
            }
        }
    }
    vector<vector<int>> vv(m, vector<int>(n, 0));
    int ii = 0;
    int i = 0;
    int j = 0;
    while (ii < N)
    {
        while (j < n && ii < N)
        {
            if (vv[i][j] != 0)
            {
                break;
            }
            vv[i][j++] = v[ii++];
        }
        j--;
        i++;
        while (i < m && ii < N)
        {
            if (vv[i][j] != 0)
            {
                break;
            }
            vv[i++][j] = v[ii++];
        }
        i--;
        j--;
        while (0 <= j && ii < N)
        {
            if (vv[i][j] != 0)
            {
                break;
            }
            vv[i][j--] = v[ii++];
        }
        j++;
        i--;
        while (0 <= i && ii < N)
        {
            if (vv[i][j] != 0)
            {
                break;
            }
            vv[i--][j] = v[ii++];
        }
        i++;
        j++;
        m -= 1;
        n -= 1;
    }
    for (auto i : vv)
    {
        int c = 0;
        for (auto j : i)
        {
            c++;
            if (c != i.size())
                cout << j << " ";
            else
                cout << j;
        }
        cout << endl;
    }
}