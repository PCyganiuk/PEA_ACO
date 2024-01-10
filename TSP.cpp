//
// Created by pcyga on 06.12.2023.
//

#include "TSP.h"

TSP::TSP() {
    n = 0;
}
TSP::~TSP() = default;

void TSP::readFromFile(const string& filename) {
    fstream p;
    int a;
    p.open(filename,ios::in);
    if(p.good()){
        p>>n;
        graph.clear();
        graph.resize(n,vector<int>(n,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                p>>a;
                graph[i][j]=a;
            }
        }
        p.close();
    }
    else
        cout<<"blad";
}

void TSP::displayMatrix() {
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<graph[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void TSP::shuffleSol(int begin, int end,vector<int>& sol) {
    random_device rd;
    mt19937 g(rd());
    shuffle(sol.begin()+begin,sol.end()-end-1,g);
}

int TSP::calcCost(vector<int> path) {
    int cost = 0;
    for (int i = 0; i < path.size()-1; i++) {
        cost += graph[path[i]][path[i+1]];
    }
    return cost;
}

int TSP::calcInitCnn() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> d(1, n-1);

    vector<int> path;
    for(int i=0;i<n;i++)
        path.push_back(i);
    path.push_back(0);

    int sum = 0;
    int N = 10000;
    for(int i = 0; i < N;i++){
        shuffle(path.begin()+1, path.end()-1, g);
        sum += calcCost(path);
    }
    sum = (double) sum / (double) N;
    return sum;
}

int TSP::aco() {
    int bestCost = INT_MAX;
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<double> num(0.0, 1.0);
    std::uniform_int_distribution<int> node(0, n-1);
    vector<int> bestPath;
    double alpha = 1.0;
    double beta = 3.5;
    double ro = 0.5;
    int m = n;
    int Cnn = calcInitCnn();
    double initPher = (double) n / (double) Cnn;
    int iterations = 1;
    double pher = 100.0; //ilość feromonów zostawianych przez mrówkę
    
    return bestCost;
}
