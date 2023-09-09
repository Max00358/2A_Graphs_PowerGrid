#include <iostream>
#include <vector>
#include "graph.hpp"
using namespace std;

Graph::~Graph(){
    for (int i = 0; i < list.size(); i++) {
        Edge* current = list[i];
        Edge* temp = list[i];

        while (current != NULL) {
            current = current->next;
            delete temp;
            temp = current;
        }
    }
    list.clear();
}
void Graph::load(int verticesNum, vector<int> set){
    Edge* insert_one = new Edge(set[0], set[1], set[2]);
    Edge* insert_two = new Edge(set[1], set[0], set[2]);

    while(list.size() < set[0] || list.size() < set[1]){
        Edge* temp = new Edge();
        temp->set_val(list.size()+1);
        temp->next = NULL;
        list.push_back(temp);
    }

    Edge* trav = list[set[0]-1];
    while(trav->next != NULL){
        trav = trav->next;
    }
    trav->next = insert_one;
    insert_one->next = NULL;

    trav = list[set[1]-1];
    while(trav->next != NULL){
        trav = trav->next;
    }
    trav->next = insert_two;
    insert_two->next = NULL;
    return;
}
bool Graph::findEdge(int start, int end){   //helper function for insert
    if(start > list.size() || end > list.size()){
        return false;   //if the list size is smaller than start number, this means vertex is never inserted
    }

    Edge* temp = list[start-1];
    int count = 0;
    while(temp != NULL){
        if(temp->get_val() == end){
            count++; //this means that the destination is found in neighbouring vertices
        }
        temp = temp->next;
    }
    temp = list[end-1];
    while(temp != NULL){
        if(temp->get_val() == start){
            count++;
            if(count == 2){
                return true;
            }
        }
        temp = temp->next;
    }
    return false;
}
void Graph::insert(int start, int end, int weight){
    if(findEdge(start, end) == true){   //if edge already in graph, print failure REGARDLESS of weight
        cout << "failure" << endl;
        return;
    }

    Edge* insert_one = new Edge(start, end, weight);
    Edge* insert_two = new Edge(end, start, weight); //because this is adjacent list, we have to insert twice for one edge

    while(list.size() < end || list.size() < start){
        Edge* temp = new Edge();
        temp->set_val(list.size()+1);
        temp->next = NULL;
        list.push_back(temp);
    }

    Edge* trav = list[start-1];
    while(trav->next != NULL){
        trav = trav->next;
    }
    trav->next = insert_one;
    insert_one->next = NULL;

    trav = list[end-1];
    while(trav->next != NULL){
        trav = trav->next;
    }
    trav->next = insert_two;
    insert_two->next = NULL;

    cout << "success" << endl;
    return;
}
void Graph::print(int a){
    if(list.size() == 0 || list[a-1] == NULL){
        cout << "failure" << endl;
        return;
    }
    Edge* temp = list[a-1]->next;
    if(list[a-1]->next == NULL || a > list.size()){    //if vertex A doesn't exist
        cout << "failure" << endl;
        return;
    }
    else{
        while(temp != NULL){
            cout << to_string(temp->get_val()) + " ";
            temp = temp->next;
        }
    }
    cout << "\n";
    return;
}
Edge* Graph::find(int i, int a){
    if(list[i] == NULL){
        return NULL;
    }
    Edge* temp = list[i]->next;
    while(temp != NULL){
        if(temp->get_val() == a){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
void Graph::del(int a){
    if(list.size() == 0 || list[a-1]->next == NULL){//list[a-1] == NULL
        cout << "failure" << endl;
        return;
    }

    Edge* cur = list[a-1];
    Edge* after = cur;
    while(cur->next != NULL){     //delete everything under list[a-1]
        // if(cur->next->next == NULL){
        //     delete cur->next;
        //     cur->next = NULL;
        // }
        // else{
        after = cur->next->next;
        delete cur->next;
        cur->next = after;
        //}
    }
    //find edge a in other locations and remove them
    for(int i = 0; i < list.size(); i++){
        if(list[i] == NULL || list[i]->next == NULL || find(i,a) == NULL){
            continue;
        }
        else{
            //3 types of deletion: delete at front, delete in middle and delete at end
            Edge* temp = list[i];
            Edge* trav = temp;
            if(temp->next->get_val() == a){     //if vertex is at front
                if(temp->next->next == NULL){   //if there's only one node in chain
                    delete temp->next;
                    temp->next = NULL;
                }
                else{                           //if there's more than one node in chain
                    trav = trav->next->next;
                    delete temp->next;
                    temp->next = trav;
                }
            }
            else if(find(i,a)->next == NULL){  //if vertex is at the end
                while(trav->next->get_val() != a){  //eventually we will be behind the node to be deleted
                    trav = trav->next;
                }
                delete trav->next;
                trav->next = NULL;
            }
            else{       //if vertex is in the middle
                while(trav->next->get_val() != a){
                    trav = trav->next;
                }
                temp = trav->next->next;
                delete trav->next;
                trav->next = temp;
            }
        }
    }
    cout << "success" << endl;
    return;
}
void Graph::mergeSort(vector< Edge* > &chain){
    if(chain.size() < 2){
        return;
    }
    int mid = chain.size()/2;

    vector< Edge* > left;
    vector< Edge* > right;
    left.resize(mid);
    right.resize(chain.size()-mid);

    for(int i = 0; i < mid; i++){
        if(chain[i] == NULL){
            continue;
        }
        left[i] = chain[i];
    }
    for(int j = mid; j < chain.size(); j++){
        if(chain[j] == NULL){
            continue;
        }
        right[j-mid] = chain[j];
    }

    mergeSort(left);
    mergeSort(right);
    merge(chain, left, right);
}
void Graph::merge(vector< Edge* > &chain, vector< Edge* > left, vector< Edge* > right){
    int indexLeft = 0;
    int indexRight = 0;
    int indexChain = 0;

    while(indexLeft < left.size() && indexRight < right.size()){
        if(left[indexLeft]->get_weight() <= right[indexRight]->get_weight()){
            chain[indexChain] = left[indexLeft];
            indexLeft++;
        }
        else if(left[indexLeft]->get_weight() > right[indexRight]->get_weight()){
            chain[indexChain] = right[indexRight];
            indexRight++;
        }
        indexChain++;
    }
    while(indexLeft < left.size()){
        chain[indexChain] = left[indexLeft];
        indexLeft++;
        indexChain++;
    }
    while(indexRight < right.size()){
        chain[indexChain] = right[indexRight];
        indexRight++;
        indexChain++;
    }
    left.clear();
    right.clear();
    return;
}
//mst function is completed with the help of Xiaoliang Zhou. Appreciate him for teaching me the concept of disjoint set union and helping me debug my code
void Graph::mst(int &cost){
    cost = 0;
    if(list.size() == 0){
        cout << "failure" << endl;
        return;
    }
    vector<Edge*> chain;
    for(int i = 0; i < list.size(); i++){   //this for loop pushes all the nodes into the chain
        if(list[i] == NULL || list[i]->next == NULL){
            continue;
        }
        else{
            Edge* temp = list[i]->next;
            while(temp != NULL){
                if(list[i]->get_val() < temp->get_val()){   //remove repeated insertions
                    chain.push_back(temp);
                }
                temp = temp->next;
            }
        }
    }
    mergeSort(chain);

    vector<int> size;
    vector<int> parent;
    size.resize(list.size());   //change size to size of the list because that's how many non-repeated numbers there are
    parent.resize(list.size());

    for(int i = 0; i < list.size(); i++){
        parent[i] = i+1;
        size[i] = 1;
    }

    for(int i = 0; i < chain.size(); i++){
        int parentOne = findParentIndex(chain[i]->get_val(), parent);
        int parentTwo = findParentIndex(chain[i]->get_top(), parent);

        if(parentOne == parentTwo){ //if both nodes have same parent, then don't need to union, just skip. This avoids nodes from forming cycles
            continue;
        }
        else{
            if(size[parentOne-1] >= size[parentTwo-1]){
                parent[parentTwo-1] = parentOne;
                size[parentOne-1] = size[parentOne-1] + size[parentTwo-1];
            }
            else{
                parent[parentOne-1] = parentTwo;
                size[parentTwo-1] = size[parentTwo-1] + size[parentOne-1];
            }

            cout << to_string(chain[i]->get_top()) + " " + to_string(chain[i]->get_val()) + " " + to_string(chain[i]->get_weight()) + " ";
            cost = cost + chain[i]->get_weight();
        }
    }
    cout << endl;
    return;
}
bool Graph::mst_for_cost(int &cost){
    cost = 0;
    if(list.size() == 0){
        return false;
    }
    vector<Edge*> chain;
    for(int i = 0; i < list.size(); i++){   //this for loop pushes all the nodes into the chain
        if(list[i] == NULL || list[i]->next == NULL){
            continue;
        }
        else{
            Edge* temp = list[i]->next;
            while(temp != NULL){
                if(list[i]->get_val() < temp->get_val()){   //remove repeated insertions
                    chain.push_back(temp);
                }
                temp = temp->next;
            }
        }
    }
    mergeSort(chain);

    vector<int> size;
    vector<int> parent;
    size.resize(list.size());   //change size to size of the list because that's how many non-repeated numbers there are
    parent.resize(list.size());

    for(int i = 0; i < list.size(); i++){
        parent[i] = i+1;
        size[i] = 1;
    }

    for(int i = 0; i < chain.size(); i++){
        int parentOne = findParentIndex(chain[i]->get_val(), parent);
        int parentTwo = findParentIndex(chain[i]->get_top(), parent);
        if(parentOne == parentTwo){ //if both nodes have same parent, then don't need to union, just skip. This avoids nodes from forming cycles
            continue;
        }
        else{
            if(size[parentOne-1] >= size[parentTwo-1]){
                parent[parentTwo-1] = parentOne;
                size[parentOne-1] = size[parentOne-1] + size[parentTwo-1];
            }
            else{
                parent[parentOne-1] = parentTwo;
                size[parentTwo-1] = size[parentTwo-1] + size[parentOne-1];
            }
            cost = cost + chain[i]->get_weight();
        }
    }
    return true;
}
int Graph::findParentIndex(int val, vector<int> parent){
    if(parent[val-1] != val){
        parent[val-1] = findParentIndex(parent[val-1], parent);
    }
    return parent[val-1];
}
void Graph::cost(int cost){
    if(list.size() == 0 || mst_for_cost(cost) == false){
        cout << "cost is 0" << endl;
    }
    else{
        if(mst_for_cost(cost) == true){
            cout << "cost is " + to_string(cost)<< endl;
        }
    }
    return;
}