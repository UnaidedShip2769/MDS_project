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


///////minHash
vector<string> get_files(char* path);
bool rules(vector<char>&words);
vector<vector<char>>get_words(string path);
vector<vector<string>> Shingling(vector<vector<char>>&words,int k);
vector<int>signats(vector<string>&s,vector<string>&vocub);
vector<vector<int>>get_sig(vector<vector<string>>&shingles,vector<string>&vocub);

//////similarity
double DSC(vector<char> w1,vector<char> w2,vector<int>s1,vector<int>s2);
double JaccardCoefficient(vector<char> w1,vector<char> w2,vector<int>s1,vector<int>s2);
#endif //MDS_PROJECT_LSH_HPP
