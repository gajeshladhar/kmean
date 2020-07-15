#include<iostream>
#include<cmath>
#include<fstream>
#include "kmean.h"
#include "matrix.h"

using namespace std;
double** read_csv();

int main()
{
    ofstream fout;
    fout.open("result.txt");
   
   double** X=read_csv();
   X=normalization(X,200,2);
   cout<<X[0][0]<<" "<<X[0][1]<<endl;

    KMean* kmean=new KMean(5,2,200);
    kmean->fit(X,30);
    int* C=kmean->get_C();
    for(int i=0;i<200;i++)
    {
    fout<<C[i];
    fout<<"\n";
    }
    fout.close();
    
   
    return 0;
}

































double** read_csv()
{
    ifstream fin;
    fin.open("Mall_Customers.csv");
    string line;
    int count_comma=0;
    string temp;

    double** X=new double*[200];
    for(int i=0;i<200;i++)
    X[i]=new double[2];
    int i=0;


    while(i<201)
    {
        if(i==0)
        {
            i++;
            getline(fin,line);
        continue;
        }
        getline(fin,line);
        count_comma=0;
        temp="";
        for(int j=0;j<line.length();j++)
        {
            if(line[j]!=',')
            temp=temp+line[j];
            else if(line[j]==',' && count_comma<3)
            {
                temp="";
                count_comma++;
            }
            else
            {
                //cout<<temp<<endl;
                X[i-1][count_comma-3]=stoi(temp);
                count_comma++;
                temp="";
            }
            
        }
        
        X[i-1][count_comma-3]=stoi(temp);
    i++;
    }

    return X;

}