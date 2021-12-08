//
// Created by peri on 7/12/21.
//

#include "KDtree.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <math.h>


//////////////////////
///INSERT
node* insertNode(node* root, node* point,int depth){
    //dimensions
    int k=point->coordinates.size();
    //tree empty
    if(root==NULL)
        return point;
    int dimension=depth%k;

    if(point->coordinates.at(dimension)<(root->coordinates.at(dimension)))
        root->left= insertNode(root->left,point,depth+1);
    else
        root->right= insertNode(root->right,point,depth+1);
    return root;
}

//interface like function that calls insertNode with depth==0
node* insert(node* root,vector<int> point){

    return insertNode(root, createNode(point),0);
}

node* createNode(vector<int>point){
    node* tmp=new node;
    for(int i=0;i<point.size();i++)
        tmp->coordinates.push_back(point.at(i));
    tmp->left=tmp->right=NULL;
    return tmp;

}



////////////////////////
///SEARCH
bool areSame(node* point1,node* point2){
    for(int i=0;i<point1->coordinates.size();i++){
        if(point1->coordinates.at(i)!=point2->coordinates.at(i))
            return false;
    }
    return true;
}

node* searchNode(node* root,node* point,int depth){
    if(root==NULL)
        return NULL;
    if(areSame(point,root))
        return root;
    int dimensions=depth%(point->coordinates.size());
    if(point->coordinates.at(dimensions)<root->coordinates.at(dimensions))
        return searchNode(root->left,point,depth+1);
    else
        return searchNode(root->right,point,depth+1);

}

//interface like function that calls searchNode with depth==0
node* search(node* root,vector<int>point){
    return searchNode(root, createNode(point),0);
}



//////////////////////////
///DELETE
node* findMin(node* root,int d,int depth){
    if (root==NULL)
        return NULL;
    int dimension=depth%root->coordinates.size();
    node* tmpL=findMin(root->left,d,depth+1);
    if(dimension==d){
        if(root->left==NULL)
            return root;


        if((root->coordinates.at(d))<tmpL->coordinates.at(d))
            return root;

        return tmpL;
    }
    node* tmpR=findMin(root->right,d,depth+1);
    if((root->coordinates.at(d)<tmpL->coordinates.at(d))&&
    (root->coordinates.at(d)<tmpR->coordinates.at(d))){
        return root;
    }
    else if((tmpL->coordinates.at(d)<tmpR->coordinates.at(d))&&
    (tmpL->coordinates.at(d)<root->coordinates.at(d))){
        return tmpL;
    }
    else
        return tmpR;
}

///interface like function that calls findMin with depth==0
node* Min(node* root,int d){
    findMin(root,d,0);
}

node* delNode(node* root,node* point, int depth){
    ////////
}



///////////////////////////
//NearestNeighbor SEARCH

//returns the squared distance between two points (squared to save cpu cycles)
double dist(node* n1,node* n2){
    double dist=0;
    for(int i=0;i<n1->coordinates.size();i++){
        dist=dist+pow(((n1->coordinates.at(i))-(n2->coordinates.at(i))),2);
    }
    return dist;
}

node* closest(node* n1,node* n2,node* point){
    if(dist(n1,point)<dist(n2,point))
        return n1;
    else
        return n2;
}
node* NNsearch(node* root,node* point,int depth){
    if (root==NULL)
        return NULL;

    node* nextBranch=NULL;
    node* otherBranch=NULL;
    int d=depth%point->coordinates.size();

    if(point->coordinates.at(d)<root->coordinates.at(d)){
        nextBranch=root->left;
        otherBranch=root->right;
    }
    else{
        nextBranch=root->right;
        otherBranch=root->left;
    }
    node* tmp= NNsearch(nextBranch,point,depth+1);
    node* best= closest(tmp,best,point);

    double radius=dist(best,point);
    double distance=point->coordinates.at(d)-root->coordinates.at(d);

    if(radius>=distance*distance){
        tmp= NNsearch(otherBranch,point,depth+1);
        best= closest(tmp,best,point);
    }


}