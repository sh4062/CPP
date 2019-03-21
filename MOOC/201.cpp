#include <iostream>
#include <map>
using namespace std;
int main()
{
    int cases;cin>>cases;
    while(cases--)
    {
        map<int,int,::greater<int>> poly;
        int coef,pow;
        while(cin>>coef>>pow)
        {
            if(pow<0) break;
            if(poly.find(pow)!=poly.end()) poly[pow]+=coef;
            else poly.insert(make_pair(pow,coef));
        }
        while(cin>>coef>>pow)
        {
            if(pow<0) break;
            if(poly.find(pow)!=poly.end()) poly[pow]+=coef;
            else poly.insert(make_pair(pow,coef));
        }
        for(map<int,int>::iterator it=poly.begin();it!=poly.end();++it)
            if(it->second!=0)
                cout<<"[ "<<it->second<<" "<<it->first<<" ] ";
        cout<<endl;
    }
}