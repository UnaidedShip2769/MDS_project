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
set<int> getUser_tags();
vector<node*> NNsearch_trees(vector<node *> &kdtrees, vector<int> &word_shingle);
vector<int> get_order_by_similarity(vector<node*> results,node* n);
vector<int> quadtree_get_order_by_similarity(vector<vector<float>> &results, vector<float> &word_shingle);
vector<int> order_by_hits(vector<int> hits);
vector<vector<int>> searchAll_interface(vector<node *> &trees, vector<File *> &textFilePruned, vector<int> &word_shingle);
vector<int> searchForWordInQuadtrees(vector<Quadtree> &quadtrees, vector<File *> &textFilePruned, vector<int> word_shingle, int dimensions, bool print, vector<int> &numberoffhits);
vector<int> nnSearchForWordInQuadtrees(vector<Quadtree> &quadtrees, vector<File*> textFilesPruned, vector<int> word_shingle, int dimensions, bool print);
vector<int> NNsearch_interface(vector<node *> &trees, vector<File *> &textFilePruned, vector<int> &word_shingle);
void KD_Interface(vector<node *> &kdtrees, int dimensions, vector<vector<vector<int>>> &sign, set<string> &vocub,
                  vector<File *> &textFilePruned);
void Quad_Interface(vector<Quadtree> &quadtrees, int dimensions, vector<vector<vector<int>>> &sign, set<string> &vocub,
                    vector<File *> &textFilePruned);
vector<vector<int>>get_results(vector<vector<int>>hits,vector<int>nn);
void quadtree_combined_search(vector<Quadtree> &quadtrees, vector<File *> &textFilePruned, vector<int> word_shingle, int dimensions);

#endif //MDS_PROJECT_INTERFACE_HPP