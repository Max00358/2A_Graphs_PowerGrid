#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_
#include <iostream>
#include <exception>
#include <vector>
using namespace std;

class illegal_exception{

};

class Edge{
public:
    Edge(int newTop, int newVal, int newWeight){
        this->val = newVal;
        this->top = newTop;   //top represent the other value the edge is attached to
        this->weight = newWeight;
    }
    Edge(){
        this->val = 0;
        this->top = 0;
        this->weight = 0;
    }
    Edge* next;

    int get_weight(){
        return this->weight;
    }
    void set_weight(int newWeight){
        this->weight = newWeight;
        return;
    }
    int get_val(){
        return this->val;
    }
    void set_val(int newVal){
        this->val = newVal;
        return;
    }
    void set_top(int newTop){
        this->top = newTop;
        return;
    }
    int get_top(){
        return this->top;
    }
private:
    int weight;
    int val;
    int top;
};

class Graph{
public:
    vector<Edge*> list;   //the vector list contains vector of edges
    Graph(){

    }
    Graph(int inputSize){   //for LOAD command because fixed size is given for load
        list.resize(inputSize);
        for(int i = 0; i<inputSize; i++){
            list[i] = new Edge();
            list[i]->next = NULL;
        }
    }
    ~Graph();

    void load(int verticesNum, vector<int> set);
    bool findEdge(int start, int end); 
    void insert(int a, int b, int weight);
    void print(int a);
    Edge* find(int i, int a);
    void del(int a);
    void mergeSort(vector< Edge* > &chain);
    void merge(vector< Edge* > &chain, vector< Edge* > left, vector< Edge* > right);
    void cost(int cost);

    void mst(int &cost);
    int findParentIndex(int weight, vector<int> parent);
    bool mst_for_cost(int &cost);
};
#endif