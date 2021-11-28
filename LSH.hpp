//
// Created by peri on 27/11/21.
//

#ifndef MDS_PROJECT_LSH_HPP
#define MDS_PROJECT_LSH_HPP
#include <vector>
#include <set>
#include <fstream>
#include <string>
using namespace std;

vector<char> read_text(char* path);  //returns vector with the content of the file or '?' if error
vector<set<string>>  Shingling(vector<char>text,int k);//return vector of vectors of k-shinles
void  Merge (vector<set<string>> v,set<string> &vocub);
vector <int> onehot_encode(set<string> shingle,set<string>vocub);
#endif //MDS_PROJECT_LSH_HPP
