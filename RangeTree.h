//
// Created by xrist on 21/1/22.
//

#ifndef UNTITLED9_RANGETREE_H
#define UNTITLED9_RANGETREE_H


#include <vector>


using namespace std;

typedef struct RangeTree_node{
    vector<int>coordinates;
    struct RangeTree_node* left;
    struct RangeTree_node* right;
    struct RangeTree_node*  dim;

}RangeNode;

RangeNode* InsertNodeR(RangeNode* root,RangeNode* point,int depth);
RangeNode* CreateNodeR(vector<int>point,int size);
RangeNode* insertR(RangeNode* root,vector<int> point);



#endif //UNTITLED9_RANGETREE_H