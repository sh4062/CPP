#include <bits/stdc++.h>
using namespace std;
int main()
{
    int N;
    cin >> N;
    vector<int> v(1001, 0);
    while (N--)
    {
        int t;
        cin >> t;
        int flag = 1;
        vector<vector<int>> dp(3, vector<int>(2*(t + 1), 0));
        for (int i = 1; i < t + 1; i++)
        {
            int tt;
            cin >> tt;
            v[i] = tt;
            if (dp[0][v[i]] || dp[1][v[i] - i + t] || dp[2][v[i] + i])
                flag = 0;
            dp[0][v[i]] = 1;
            dp[1][v[i] - i + t] = 1;
            dp[2][v[i] + i] = 1;
        }

        if (flag)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}