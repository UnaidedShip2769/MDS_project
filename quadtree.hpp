//
// Created by Gregory on 12/3/2021.
//

#ifndef MDS_PROJECT_QUADTREE_HPP
#define MDS_PROJECT_QUADTREE_HPP

#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;

struct DimensionSpace
{
    float start;
    float end;
public:
    DimensionSpace(float start, float end);
    DimensionSpace() {};
};

struct QuadLeaf
{
    bool used = false;
    vector<float> contents;
    int timesInserted = 0;
    QuadLeaf() {};
    //QuadLeaf(vector<int> numbers);
    QuadLeaf(vector<DimensionSpace> boundrySpace);
    vector<DimensionSpace> boundrySpace;
public:
    void printContent();
};

struct QuadNode
{
    vector<float> contents;
    QuadNode() {};
    QuadNode(vector<float> values);
    vector<QuadLeaf> leaves;
};

class Quadtree
{
    int dimension;
    QuadNode head;
    vector<Quadtree> subtrees;
    vector<DimensionSpace> boundrySpace;
public:
    vector<vector<DimensionSpace>> makeNewDimensionSpaces();
    Quadtree(int dimensions, vector<DimensionSpace> boundrySpace);
    Quadtree(int dimensions);
    Quadtree(int dimensions, set<string> &vocub);
    void print();
    void print(QuadNode start);
    void insert(vector<float> number);
    void insertnumber(vector<float> number);
    void delete_element(vector<float> deleteNumber);
    void reinsert_elements(vector<vector<float>> &reinserts);
    bool find_and_remove_elements(vector<float> deleteNumber, vector<vector<float>> &reinserts);
    void update(QuadLeaf &leaf);
    vector<float> NN(vector<float> searchNumber);
    bool search(vector<float> searchNumber, bool increment, int &timesinserted);
};

float distance(QuadLeaf leaf, float searchNumber, int dimension);
float distance(QuadNode node, float searchNumber, int dimension);

#endif //MDS_PROJECT_QUADTREE_HPP