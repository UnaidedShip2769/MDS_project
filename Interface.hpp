#ifndef MDS_PROJECT_INTERFACE_HPP
#define MDS_PROJECT_INTERFACE_HPP
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include "KDtree.hpp"
#include "Files.hpp"
#include "quadtree.hpp"

using namespace std;
int Interface(vector<node*>&kdtrees, vector<Quadtree> &quadtrees);
vector<node*> KDtree_search(vector<int> word,vector<node*>&kdtrees);
set<int> getUser_tags();
vector<node*> NNsearch_trees(vector<node *> &kdtrees, vector<int> &word_shingle);
vector<int> get_order_by_similarity(vector<node*> results,node* n);
vector<int> order_by_hits(vector<int> hits);
void searchAll_interface(vector<node *> &kdtrees, vector<File *> &textFilePruned, vector<int> &word_shingle);
void searchForWordInQuadtrees(vector<Quadtree> &quadtrees, vector<File *> &textFilePruned, vector<int> word_shingle, int dimensions);
void NNsearch_interface(vector<node *> &kdtrees, vector<File *> &textFilePruned, vector<int> &word_shingle);
void KD_Interface(vector<node *> &kdtrees, int dimensions, vector<vector<vector<int>>> &sign, set<string> &vocub,
                  vector<File *> &textFilePruned);
void Quad_Interface(vector<Quadtree> &quadtrees, int dimensions, vector<vector<vector<int>>> &sign, set<string> &vocub, vector<File *> &textFilePruned);
#endif //MDS_PROJECT_INTERFACE_HPP
