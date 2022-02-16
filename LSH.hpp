#ifndef MDS_PROJECT_LSH_HPP
#define MDS_PROJECT_LSH_HPP
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include "KDtree.hpp"
#include "Files.hpp"
#include "quadtree.hpp"

using namespace std;


///////minHash

bool rules(vector<char>&words);
vector<vector<char>>get_words(string path);
vector<vector<string>> Shingling(vector<vector<char>>&words,int k);
void make_vocub_and_order_alphabetically(vector<string> &vocub, vector<vector<vector<string>>>&text);
int hash_func(string s,int n);
void make_vocub_and_shuffle(vector<string> &vocub, vector<vector<vector<string>>>&text);
void make_sign(vector<vector<vector<int>>> &sigs, set<string> &vocub, vector<vector<vector<string>>> &text);
///interface function
void get_data(vector<vector<vector<int>>>&text,int k,vector<File*>&textFileNames,set<string> &vocub);
void make_KD_trees(vector<vector<vector<int>>>&sign,vector<node*>&trees,int k);
void make_quad_trees(vector<vector<vector<int>>>&sign,vector<Quadtree>&quadtrees,int k,set<string>&vocub);
void update_vocub(set<string> &vocub, vector<string> &secondaryVocub, vector<string>&shingles);
vector<int> get_word_data(string &word, int k, set<string> &vocub, vector<string> &secondaryVocub);
vector<string> word_Shingling(string &word, int k);
void make_word_sign(vector<int> &sign, set<string> &vocub, vector<string> &secondaryVocub, vector<string> shingles);



//////similarity

float JaccardCoefficient(vector<int>s1,vector<int>s2);
#endif //MDS_PROJECT_LSH_HPP
