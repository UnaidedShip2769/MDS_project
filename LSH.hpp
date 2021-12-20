//
// Created by peri on 27/11/21.
//

#ifndef MDS_PROJECT_LSH_HPP
#define MDS_PROJECT_LSH_HPP
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include "KDtree.hpp"
using namespace std;


///////minHash
vector<string> get_files(char* path);
bool rules(vector<char>&words);
vector<vector<char>>get_words(string path);
vector<vector<string>> Shingling(vector<vector<char>>&words,int k);
void make_vocub_and_order_alphabetically(vector<string> &vocub, vector<vector<vector<string>>>&text);
//vector<int>signats(vector<string>&s,vector<string>&vocub);
//vector<vector<int>>get_sig(vector<vector<string>>&shingles,vector<string>&vocub);
int hash_func(string s,int n);
void make_vocub_and_shuffle(vector<string> &vocub, vector<vector<vector<string>>>&text);
void make_sign(vector<vector<vector<int>>> &sigs, vector<string> &vocub, vector<vector<vector<string>>> &text);
///interface function
void get_data(char* dir_path,vector<vector<vector<int>>>&text,int k,vector<string>&files,vector<string> &textFileNames);
void make_KD_trees(vector<vector<vector<int>>>&sign,vector<node*>&trees,int k);
//void make_trees(char*dir_path,vector<node*>&trees,int l,int k);

//////similarity
double DSC(vector<char> w1,vector<char> w2,vector<int>s1,vector<int>s2);
double JaccardCoefficient(vector<char> w1,vector<char> w2,vector<int>s1,vector<int>s2);
#endif //MDS_PROJECT_LSH_HPP
