//
// Created by Gregory on 12/3/2021.
//

#ifndef MDS_PROJECT_QUADTREE_HPP
#define MDS_PROJECT_QUADTREE_HPP

#endif //MDS_PROJECT_QUADTREE_HPP

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct DimensionSpace
{
    int start;
    int end;
public:
    DimensionSpace(int start, int end);
    DimensionSpace() {};
};

struct QuadLeaf
{
    vector<int> contents;
    QuadLeaf() {};
    QuadLeaf(vector<int> numbers);
};

struct QuadNode
{
    vector<int> contents;
    QuadNode() {};
    QuadNode(vector<int> values);
    vector<QuadLeaf> leaves;
};

class Quadtree
{
    int dimension;
    QuadNode head;
    vector<Quadtree> subtrees;
    vector<DimensionSpace> boundrySpace;
public:
    Quadtree(int dimensions, vector<DimensionSpace> boundrySpace);
    Quadtree(int dimensions);
    void print();
    void print(QuadNode start);
    void insert(vector<int> number);
    void delete_element(vector<int> number);
    void update();
    void kNN(vector<int> number);

};