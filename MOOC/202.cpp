#include <bits/stdc++.h>
using namespace std;

int main()
{
    string a, b;
    while(cin >> a >> b){
    int maxIndex = 0;    //最大的字符所在位置
    char maxChar = a[0]; //最大字符
    for (int i = 1; i < a.size(); i++)
    { //查找最大的字符
        if (a[i] > maxChar)
        {
            maxChar = a[i];
            maxIndex = i;
        }
    }
    for (int i = 0; i <= maxIndex; i++)
    {

        cout << a[i];
    }
    cout << b;
    for (int i = maxIndex + 1; i < a.size(); i++)
    {

        cout << a[i];
    }
    cout<<endl;
    }

}

// #include<stdio.h>
// #include<string.h>

// int main(){
// 	char str[15],substr[4];
// 	int i,l,max,j,t=0;
// 	char ch=0;
// 	while(scanf("%s",str)!=EOF&&scanf("%s",substr)!=EOF){
// 	l=strlen(str);
// 	for(i=0;i<l;i++){
// 		if(str[i]>ch){
// 			ch=str[i];
// 			max=i;
// 			}
// 	}   //小心，！！！这里的i已经没用了，下面要用max！
// 	for(i=0;i<=max;i++){
// 		printf("%c",str[i]);
// 	}
// 	printf("%.3s",substr);
// 	for(i=max+1;i<l;i++){     //i<l一开始变成了i<=max+3 
// 		printf("%c",str[i]);}
// 	printf("\n");  //不要把换行加到上面循环中，那样会输出多个换行 
// 	ch=0;
	
// }
// return 0;
// }