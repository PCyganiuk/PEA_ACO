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
    double alpha = 1.0;
    double beta = 3.5;
    double ro = 0.5; //evaporation
    int Cnn = calcInitCnn();
    double initPher = (double) n / (double) Cnn;
    int iterations = 1;
    double pher = 100.0; //ilość feromonów zostawianych przez mrówkę
    vector<vector<double>> pheromones;
    for(int i = 0;i < n;i++){
        vector<double> ph;
        for(int j = 0; j < n; j++)
            ph.push_back(initPher);
        pheromones.push_back(ph);
    }
    vector<vector<double>> pheromones_to_add;
    for(int i = 0; i < n; i++){
        vector<double> ph;
        for(int j = 0; j < n; j++)
            ph.push_back(0.0);
        pheromones_to_add.push_back(ph);
    }
    int i = 0;
    while(i++ < iterations){
        //cout<<"iteracja: " << i <<endl;
        for(int m = 0; m < n; m++){
            int startNode = m;
            vector<int> path;
            path.push_back(startNode);
            vector<int> vertLeft; // wierzchołki możliwe do wybrania
            for(int y = 0; y < n; y++)
                if(y!=startNode)
                    vertLeft.push_back(y);

            for(int x = 0; x < n-1; x++){
                int cn = path.back();
                //cout<< cn << " " << endl;
                double sumFactor = 0.0;
                for(int & it : vertLeft)
                    sumFactor += (pow(pheromones[cn][it],alpha)) * pow((double) 1.0/ (double) graph[cn][it],beta);

                vector<double> prob;

                for(int & ir : vertLeft){
                    double p = ((pow(pheromones[cn][ir],alpha))*(pow((double) 1.0/ (double) graph[cn][ir],beta)))/sumFactor;
                    prob.push_back(p);
                }
                //ruletka
                partial_sum(prob.begin(),prob.end(),prob.begin());

                double p = num(g);
                int k = 0;

                for(vector<double>::iterator ix = prob.begin();ix !=prob.end();ix++){
                    if(p< *ix){
                        int chosen = vertLeft[k];
                        path.push_back(chosen);
                        vertLeft.erase(vertLeft.begin()+k);
                        break;
                    }
                    k++;
                }
            }

            path.push_back(startNode);
            int L = calcCost(path);
            if(L < bestCost || bestCost == INT_MAX){
                bestCost = L;
                sPath = path;
            }
            double ph = pher/ (double) L;

            for(int r = 0; r < path.size()-1;r++)
                pheromones_to_add[path[r]][path[r+1]] +=ph;
        }
        for(i = 0; i < n; i++){
            for(int k = 0;k <n;k++){
                pheromones[i][k] = (pheromones[i][k] * ro) + pheromones_to_add[i][k];
                pheromones_to_add[i][k] = 0.0;
            }
        }

    }
    sPath.pop_back();
    vector<int>::iterator itt = find(sPath.begin(),sPath.end(),0);
    rotate(sPath.begin(),itt,sPath.end());
    sPath.push_back(0);
    
    return bestCost;
}
