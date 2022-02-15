//
// Created by peri on 27/1/22.
// Created by xrist on 21/1/22.
//

#include "RangeTree.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <math.h>
#include<algorithm>
using namespace std;


RangeNode* InsertNodeR(RangeNode* root,RangeNode* point,int d){

    if(root==NULL)
        return point;
    if(root->right==NULL){//node is leaf
        RangeNode* tmp= CreateNodeR(root->coordinates,root->coordinates.size());
        root->right=tmp;
        root->left=point;
        root->coordinates=point->coordinates;
    }

    else if(point->coordinates.at(d)>root->coordinates.at(d))
        InsertNodeR(root->right,point,d);
    else
        InsertNodeR(root->left,point,d);

    return root;
}



RangeNode* CreateNodeR(vector<int>point,int size){
    point.resize(size,0);
    RangeNode* tmp=new RangeNode;
    for(int i=0;i<point.size();i++)
        tmp->coordinates.push_back(point.at(i));
    tmp->left=NULL;
    tmp->right=NULL;
    return tmp;
}



RangeNode* insertR(RangeNode* root,vector<int> point){
    return InsertNodeR(root, CreateNodeR(point,2),0);
}



RangeNode* RemoveLeafNodes (RangeNode* root, vector<int> target) {

    // Root is nullptr, there is nothing to be deleted.
    if (root == nullptr)
        return nullptr;

    // If root's left child deleted, root left should be updated.
    root->left  = RemoveLeafNodes(root->left, target);

    // If root's right child deleted, root right should be updated.
    root->right = RemoveLeafNodes(root->right, target);

    if (root->left == nullptr && root->right == nullptr && root->coordinates == target){
        //cout << "\nRemoving leaf node with data : " << target;
        delete root;
        return nullptr;
    }
    return root;
}


/*

RangeNode * minValueNode(struct RangeNode* node)
{
    struct node* current = node;

    */
/* loop to find the leftmost leaf *//*

    while (current->left != NULL)
        current = current->left;

    return current;
}*/
