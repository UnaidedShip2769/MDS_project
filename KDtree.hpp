#ifndef MDS_PROJECT_KDTREE_HPP
#define MDS_PROJECT_KDTREE_HPP
#include <vector>

using namespace std;

typedef struct KDtree_node{
    vector<int>coordinates;
    struct KDtree_node* left;
    struct KDtree_node* right;
    int pos;

}node;

///insert
node* createNode(vector<int>point,int pos);
node* insertNode(node* root, node* point,int depth);
node* insert(node* root, vector<int> point,int pos);

///search
bool areSame(node* point1,node* point2);
node* searchNode(node* root,node* point,int depth);
node* search(node* root,vector<int>point);

///search for hits
int searchAll(node* root,vector<int>point);
int searchNode(node* root, node* point,int depth,int hits);

///delete
node* findMin(node* root,int d,int depth);
node* Min(node* root,int d);

///NNsearch
double dist(node* n1,node* n2);
node* closest(node* n1,node* n2,node* point);
node* NN_search(node* root,node* point,int depth);

#endif //MDS_PROJECT_KDTREE_HPP