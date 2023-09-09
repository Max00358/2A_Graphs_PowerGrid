#include <iostream>
#include <fstream>
#include <vector>

#include "graph.hpp"
#include "graphFunction.cpp"
using namespace std;

int main(){
    string input;
    Graph* myGraph = new Graph();
    int textInput;
    int cost = 0;

    while(cin>>input){
        if(input == "END"){
            break;
        }
        if(input == "LOAD"){
            cin >> input;
            ifstream text(input);

            int count = 0;
            int verticesNum = 0;
            text >> verticesNum;
            vector<int> set;

            while(text >> textInput){
                set.push_back(textInput);
                count++;
                if(count == 3){
                    myGraph->load(verticesNum, set);
                    count = 0;
                    set.clear();
                }
            }
            cout << "success" << endl;
        }
        try{
            if(input == "INSERT"){
                int start;
                int end;
                int weight;

                cin >> start;
                cin >> end;
                cin >> weight;

                if(start <= 0 || start > 50000 || end <= 0 || end > 50000 || weight <= 0){
                    throw illegal_exception();
                }
                else{
                    myGraph->insert(start, end, weight);
                }
            }
        }
        catch(illegal_exception e1){
            cout << "illegal argument" << endl;
        }
        try{
            if(input == "PRINT"){
                int vertex;
                cin >> vertex;

                if(vertex <= 0 || vertex > 50000){
                    throw illegal_exception();
                }
                else{
                    myGraph->print(vertex);
                }
            }
        }
        catch(illegal_exception e2){
            cout << "illegal argument" << endl;
        }
        try{
            if(input == "DELETE"){
                int delVal;
                cin >> delVal;

                if(delVal <= 0 || delVal > 50000){
                    throw illegal_exception();
                }
                else{
                    myGraph->del(delVal);
                }
            }
        }
        catch(illegal_exception e3){
            cout << "illegal argument" << endl;
        }
        if(input == "MST"){
            myGraph->mst(cost);
        }
        if(input == "COST"){
            myGraph->cost(cost);
        }
    }
    delete myGraph;
    return 0;
}