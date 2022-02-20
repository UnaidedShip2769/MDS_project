#ifndef MDS_PROJECT_KDTREE_HPP
#define MDS_PROJECT_KDTREE_HPP
#include <vector>

using namespace std;

typedef struct KDtree_node{
    vector<int>coordinates;
    struct KDtree_node* left;
    struct KDtree_node* right;

}node;

///insert
node* createNode(vector<int>point);
node* insertNode(node* root, node* point,int depth);
node* insert(node* root, vector<int> point);

///search
bool areSame(node* point1,node* point2);
node* searchNode(node* root,node* point,int depth);


///search for hits
int searchAll(node* root,vector<int>point);
int searchNode(node* root, node* point,int depth,int hits);

///delete
node* findMin(node* root,int d,int depth);


///NNsearch
double dist(node* n1,node* n2);
node* closest(node* n1,node* n2,node* point);
node* NN_search(node* root,node* point,int depth);

#endif //MDS_PROJECT_KDTREE_HPP