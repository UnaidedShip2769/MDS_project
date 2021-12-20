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
using namespace std;
int Init(vector<vector<vector<int>>>&texts,vector<node*>&trees,char* dir,int shingle_size,int dimensions);
int Interface();
#endif //MDS_PROJECT_INTERFACE_HPP
