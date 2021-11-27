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

std::vector<char> read_text(char* path);  //returns vector with the content of the file or '?' if error
std::set<std::string>  Shingling(std::vector<char>text,int k);//return vector of vectors of k-shinles
set<string>  Merge (set<string> s1,set<string> s2);
vector <int> onehot_encode(set<string> shingle,set<string>vocub);
#endif //MDS_PROJECT_LSH_HPP
