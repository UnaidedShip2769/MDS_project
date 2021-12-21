//
// Created by peri on 20/12/21.
//
#include <iostream>
#include <vector>
#include "LSH.hpp"
#include "KDtree.hpp"
#include "Interface.hpp"
using namespace std;

int Interface(vector<node*>&trees,vector<string> &textFileNames){

    char* direcory="../data";
    int shingle_size=3;
    int dimensions=2;

    vector<vector<vector<int>>>sign;
    vector<string>vocub;


    get_data(direcory,sign,shingle_size,textFileNames,vocub);

    make_KD_trees(sign,trees,dimensions);///switch statement here to select between different trees

    string word;
    cout <<"enter word";
    cin>>word;
    vector<string>sec_vocub;
    vector<int>word_shingle=get_word_data(word,3,vocub,sec_vocub);
    node* point= search(trees.at(0),word_shingle);

}



