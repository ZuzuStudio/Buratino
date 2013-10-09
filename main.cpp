#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
using namespace std;

void replacement(string place,short &temp)
{

    if(place=="field")
        temp=0;
    if(place=="malvina")
        temp=1;
    if(place=="home")
        temp=2;
    if(place=="school")
        temp=3;
    if(place=="theater")
        temp=4;
    if(place=="swamp")
        temp=5;
    if(place=="tractoria")
        temp=6;
}

int main()
{
    queue <int> a;
    short size=7, temp,temp1,roads,location1;
    bool marker[size];
    bool home=false,key=false;
    string location,place;
    int matrix[size][size];

    for(int i=0; i<size; ++i)
        for(int j=0; j<size; ++j)
            matrix[i][j]=0;

    ifstream fin("input");
    ofstream fout("output");
    fin>>location>>roads;
    short p;
    while(!fin.eof())
    {
        fin>>place;
        replacement(place,temp);
        fin>>place;
        replacement(place,temp1);
        if(!fin.eof())
        {
            matrix[temp][temp1]=matrix[temp1][temp]=1;
        }
        else break;
    }
    replacement(location,location1);
    if(location1==5)
    {
        marker[5]=true;
    }
    else
    {
        for (int i=0; i<size; ++i)
            marker[i]=false;
        p=location1;
        marker[p]=true;
        for(int i=0; i<size; ++i)
            if(matrix[p][i]==1 && !marker[i])
                a.push(i);
        while(!a.empty() && marker[5]!=true)
        {
            p=a.front();
            a.pop();
            if(marker[p]==true)
                a.pop();
            else
                marker[p]=true;
            for(int i=0; i<size; ++i)
                if(matrix[p][i]==1 && !marker[i])
                    a.push(i);
        }
    }
    if(marker[5])
        key=true;

    if(location1==2)
    {
        marker[2]=true;
    }
    else
    {
        while(!a.empty()) a.pop();
        for (int i=0; i<size; ++i)
            marker[i]=false;
        p=5;
        marker[p]=true;
        for(int i=0; i<size; ++i)
            if(matrix[p][i]==1 && !marker[i])
                a.push(i);
        while(!a.empty() && marker[2]!=true)
        {
            p=a.front();
            a.pop();
            if(marker[p]==true)
                a.pop();
            else
            {
                marker[p]=true;
            }
            for(int i=0; i<size; ++i)
                if(matrix[p][i]==1 && !marker[i])
                    a.push(i);
        }

    }
    if(marker[2])
        home=true;
    int b[size][size];
    int max=10;

    for (int i = 0; i< size; i++)
        for (int j = 0; j < size; j++)
        {
            b[i][j] = (matrix[i][j] == 0)?max: matrix[i][j];
        }
    for (int k = 0; k < size; k++)
        for (int i = 0; i< size; i++)
            for (int j = 0; j < size; j++)
                b[i][j] = min(b[i][j], b[i][k] + b[k][j]);

    int length;
    if(b[location1][5]>=10) fout<<"The golden key is unreachable";
    else if(b[2][5]>=10) fout<<"The home is unreachable";
    else
    {
    if(location1==5)
        b[location1][5]=0;

    length=b[location1][5]+b[2][5];
    fout<<length;
}
    return 0;
}
