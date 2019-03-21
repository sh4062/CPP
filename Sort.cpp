#include <bits/stdc++.h>
using namespace std;
void bubble(vector<int> &v1)
{

    for (int i = 0; i < v1.size() - 1; i++)
    {
        int flag = 0;

        for (int j = i + 1; j < v1.size(); j++)
        {
            if (v1[i] > v1[j])
            {
                flag = 1;
                swap(v1[i], v1[j]);
            }
        }
        if (flag == 0)
            break;
    }
}
void insert(vector<int> &v1)
{
    int i, j;
    for (i = 1; i < v1.size(); i++)
    {

        if (v1[i] < v1[i - 1])
        {
            int temp = v1[i];
            for (j = i - 1; j >= 0 && v1[j] > temp; j--)
            {
                v1[j + 1] = v1[j];
            }
            v1[j + 1] = temp; //此处就是v1j+1]=temp;
        }
    }
}
void select(vector<int> &v1)
{
    int i, j;
    for (i = 0; i < v1.size() - 1; i++)
    {
        int min = i;
        for (j = i + 1; j < v1.size(); j++)
        {
            if (v1[j] < v1[min])
                min = j;
        }
        if (min != i)
        {
            swap(v1[min], v1[i]);
        }
    }
}
void shell(vector<int> &v1)
{
    int op = 0;
    int i, j, d;
    for (d = v1.size() / 2; d >= 1; d /= 2)
    {
        for (i = d; i < v1.size(); i++)
        {
            int tmp = v1[i];
            for (j = i - d; j >= 0 && v1[j] > tmp; j -= d)
            {
                v1[j + d] = v1[j];
                op++;
            }
            v1[j + d] = tmp;
            op++;
        }
    }
}
int partition(vector<int> &v1, int l, int h)
{
    int p = v1[l];
    while (l < h)
    {
        while (l < h && v1[h] >= p)
            --h;
        v1[l] = v1[h];
        while (l < h && v1[l] <= p)
            ++l;
        v1[h] = v1[l];
    }
    v1[l] = p;
    return l;
}
void qs(vector<int> &v1, int l, int h)
{
    if (l < h)
    {
        int p = partition(v1, l, h);
        //cout<<p;
        qs(v1, l, p - 1);
        qs(v1, p + 1, h);
    }
}
void merge(vector<int> &v1, int l, int m, int h)
{
    vector<int> v2(1024, 0);
    for (int i = l; i <= h; i++)
    {
        v2[i] = v1[i];
    }
    int i = l, j = m + 1, k = i;
    for (; i <= m && j <= h; k++)
    {
        if (v2[i] <= v2[j])
        {
            v1[k] = v2[i];
            i++;
        }
        else
        {
            v1[k] = v2[j];
            j++;
        }
    }
    while (i <= m)
    {
        v1[k++] = v2[i++];
    }
    while (j <= h)
    {
        v1[k++] = v2[j++];
    }
}
void mergeS(vector<int> &v1, int l, int h)
{

    if (l < h)
    {
        int mid = (l + h) / 2;
        //cout<<mid;
        mergeS(v1, l, mid);
        mergeS(v1, mid + 1, h);
        merge(v1, l, mid, h);
    }
}
void heap(vector<int> &v1, int k, int n)
{
    int i = k, j = (i + 1) * 2-1;
    while (j <= n)
    {
        if (j + 1 <= n && v1[j] < v1[j + 1])
            j = j + 1;
        if (v1[i] >= v1[j])
            break;
        swap(v1[i], v1[j]);
        i = j;
        j = (i + 1) * 2-1;
    }
}
void heapS(vector<int> &v1)
{
    for (int i = v1.size() / 2; i >= 0; i--)
    {
        heap(v1, i, v1.size());
    }
    for (int i = v1.size() - 1; i >=1; i--)
    {
        swap(v1[0], v1[i]);
        heap(v1, 0, i - 1);
    }
}
int main()
{
    vector<int> v1 = {5,4,6,8,2,3,4,1,3,4,5};
    //bubble(v1);
    //insert(v1);
    //select(v1);
    //shell(v1);
    //qs(v1, 0, v1.size() - 1);
    //mergeS(v1, 0, v1.size() - 1);
    //heapS(v1);
    for (auto i : v1)
        cout << i << " ";
}