#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H
#include <QMainWindow>
#include<bits/stdc++.h>
using namespace std;


string QStringToString(const QString& src)
{
    return src.toStdString();

}

QString StringToQString(const string& src)
{
    return QString::fromStdString(src);
}
int StringToInt(string s)
{
    int res=0;

    for(int i=0;i<s.size();++i)
    {
        res*=10;
        res+=(s[i]-'0');
    }
    return res;
}
string IntToString(int a)
{
    string s;
    while(a!=0)
    {
        s=char((a%10)+'0')+s;
        a/=10;
    }
    return s;
}
#endif // MYFUNCTIONS_H
