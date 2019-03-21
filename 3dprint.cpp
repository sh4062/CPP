#include <bits/stdc++.h>
using namespace std;
int main()
{
    int x, y, z;
    cin >> x >> y >> z;
    int xx = 2 * x + 1 + 2 * y;
    int yy = 2 * y + 1 + 2 * z;
    int a = 2 * y, b = 2 * y;
    for (int i = 0; i < yy; i++)
    {

        if (a > 0)
        {
            int ii = 0;
            for (; ii < a; ii++)
            {
                cout << '.';
            }

            if (i % 2 == 0)
            {
                for (; ii < a + 2 * x; ii += 2)
                {
                    cout << "+-";
                }
                ii--;
                if (i == 0)
                {
                    cout << '+' << endl;
                }
                else
                {
                    while (ii < xx - 2)
                    {
                        cout << "+.";
                        ii += 2;
                    }
                    cout << '+' << endl;
                }
            }
            else
            {
                for (; ii < a + 2 * x; ii += 2)
                {
                    cout << "/.";
                }
                ii--;
                // cout<<ii<<endl;
                while (ii < xx - 2)
                {
                    cout << "/|";
                    ii += 2;
                }
                cout << endl;
            }

            a--;
            continue;
        }
        if (i >= 2 * y && i < yy - 2 * y)
        {
            int ii = 0;
            if (i % 2 == 0)
            {
                for (; ii < 2 * x; ii += 2)
                {
                    cout << "+-";
                }
                while (ii < xx - 2)
                {
                    cout << "+.";
                    ii += 2;
                }
                cout << '+' << endl;
                ii++;
            }
            else
            {
                for (; ii < 2 * x; ii += 2)
                {
                    cout << "|.";
                }
                //ii--;
                // cout<<ii<<endl;
                while (ii < xx -2)
                {
                    cout << "|/";
                    ii += 2;
                }
                cout << '|' << endl;
                ii++;
            }
            continue;
        }
        if (b > 0)
        {
            int ii = 0;
            if (i % 2 == 0)
            {
                for (; ii < 2 * x; ii += 2)
                {
                    cout << "+-";
                }
                //ii--;
                if (i == yy - 1)
                {
                    cout << '+' ;
                }
                else
                {
                    while (ii < xx - (2 * y - b) - 2)
                    {
                        cout << "+.";
                        ii += 2;
                    }
                    cout << '+';
                }
                ii++;
                for (; ii < xx; ii++)
                {
                    cout << '.';
                }
                cout << endl;
            }
            else
            {
                for (; ii < 2 * x; ii += 2)
                {
                    cout << "|.";
                }
                //ii--;
                // cout<<ii<<endl;
                while (ii < xx - (2 * y - b) - 2)
                {
                    cout << "|/";
                    ii += 2;
                }
                //ii--;
                //cout<<ii<<endl;
                for (; ii < xx; ii++)
                {
                    cout << '.';
                }
                cout << endl;
            }

            b--;
        }
    }
}