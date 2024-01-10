//
// Created by pcyga on 06.12.2023.
//

#ifndef PEA_SA_TSP_H
#define PEA_SA_TSP_H


#include<vector>
#include<iostream>
#include<list>
#include<stack>
#include<string>
#include<fstream>
#include<bitset>
#include<climits>
#include<algorithm>
#include<random>

using namespace std;

class TSP {
private:
    int n;
    vector<vector<int>> graph;
public:
    vector<int> sPath;
    TSP();
    ~TSP();
    void readFromFile(const string& filename);
    int calcInitCnn();
    int aco();
    static void shuffleSol(int begin,int end, vector<int> & tab);
    int calcCost(vector<int> path );
    void displayMatrix();
};


#endif //PEA_SA_TSP_H
