/*
 Harun Çatal
 150130034
 Analysis and Algorithms 1
 Homework 2
 */
//PLEASE COMPILE ONLY MAIN FILE 

#include "node.h"
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string>
#include<vector>
#include<stdio.h>
using namespace std;

void node::readFile(vector<node>& myVector,int size)
{
    ifstream file;//file reading
    file.open("population_by_zip_2010.csv");
    node temp;
    string tmp;//to get population as string
    if(file.is_open())
    {
        int i=0;
        getline(file,tmp,'\n');//first line
        while(i<=size)
        {
            getline(file,tmp,',');//until comma
            temp.population=stoi(tmp);
            getline(file,temp.minimumAge,',');
            getline(file,temp.maximumAge,',');
            getline(file,temp.gender,',');
            getline(file,temp.zipCode,',');
            getline(file,temp.geoId,'\n');
            myVector.push_back(temp);//push vector
            i++;
        }
        
        file.close();
    }
    else
        cout<<"Dosya acilamadi"<<endl;
}
int node::partition (vector<node>& myVector, int p, int r)
{
    node pivot = myVector[r]; //pivot
    int i = p - 1;  //smaller index
    
    for (int j = p; j <= r- 1; j++)//When smaller or equal to pivot
    {
        
        if ((myVector[j].population) < (pivot.population))//when population smaller than pivot
        {
            i++;
            swap(myVector[i], myVector[j]);//swapping
        }
        else if((myVector[j].population) == (pivot.population))//when population numbers are equal
        {
            if((myVector[j].geoId)<= (pivot.geoId))//comparing geoId's
            {
                i++;
                swap(myVector[i], myVector[j]);
            }
        }
    }
    swap(myVector[i + 1], myVector[r]);//pivot placed
    return i+1;
}
void node::quickSort(vector<node>& myVector, int p, int r)
{
    if (p < r)
    {

        int p_index = partition(myVector, p, r);//p_index->partitioning index
        
        
        // Sorting elements before and after partition
        quickSort(myVector, p, p_index - 1);
        quickSort(myVector, p_index + 1, r);
    }
}
void node::writeFile(vector<node>& myVector,int size)

{
    ofstream wfile;//writing operation
    
    wfile.open("output.csv");
    wfile<<"population,minimum_age,maximum_age,gender,zipcode,geo_id"<<endl;
    int i=0;
    while(i<=size)
    {
        wfile<<myVector[i].population<<","<<myVector[i].minimumAge<<","<<myVector[i].maximumAge<<","<<myVector[i].gender<<","<<myVector[i].zipCode<<","<<myVector[i].geoId<<endl;
        i++;
    }
    
    wfile.close();
}
