//
// Created by peri on 20/12/21.
//

#ifndef MDS_PROJECT_INTERFACE_HPP
#define MDS_PROJECT_INTERFACE_HPP
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include "KDtree.hpp"
#include "Files.hpp"
using namespace std;
int Interface(vector<node*>&trees);
vector<node*> KDtree_search(vector<int> word,vector<node*>&trees);
set<int> getUser_tags();
vector<node*> NNsearch_trees(vector<node *> &trees, vector<int> &word_shingle);
vector<int> get_order_by_similarity(vector<node*> results,node* n);
vector<int> order_by_hits(vector<int> hits);
vector<vector<int>> searchAll_interface(vector<node *> &trees, vector<File *> &textFilePruned, vector<int> &word_shingle);
vector<int> NNsearch_interface(vector<node *> &trees, vector<File *> &textFilePruned, vector<int> &word_shingle);
void KD_Interface(vector<node *> &trees, int dimensions, vector<vector<vector<int>>> &sign, set<string> &vocub,
                  vector<File *> &textFilePruned);
vector<vector<int>>get_results(vector<vector<int>>hits,vector<int>nn);
void Print_results(vector<node *> &trees, vector<File *> &textFilePruned, vector<int> &word_shingle);
#endif //MDS_PROJECT_INTERFACE_HPP
