/*
 Harun Çatal
 150130034
 Analysis and Algorithms 1
 Homework 2
 */
#ifndef node_h
#define node_h
#include<string>
#include<vector>

using namespace std;
class node{
public:
    int population;
    string minimumAge;
    string maximumAge;
    string gender;
    string zipCode;
    string geoId;
    void readFile(vector<node>&,int);
    int partition (vector<node>&,int,int);
    void quickSort (vector<node>& ,int,int);
    void writeFile(vector<node>&,int);
    
    node(){
        population=0;
        minimumAge="";
        maximumAge="";
        gender="";
        zipCode="";
        geoId="";
    };

};

#endif /* node_h */
