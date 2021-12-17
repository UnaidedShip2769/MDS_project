//
// Created by peri on 27/11/21.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <queue>
#include <iterator>
#include <algorithm>
#include "LSH.hpp"
#include <string>
#include <dirent.h>

using namespace std;
//namespace fs = std::filesystem;
vector<string> get_files(char* path){
    vector<string>files;
    string temp;
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(path))!=NULL){
        while((ent= readdir(dir))!=NULL){
            temp=path;
            temp+='/';
            temp+=ent->d_name;
            files.push_back(temp);
        }
        closedir(dir);
    }
    else {
        /* could not open directory */
        perror ("could not open directory");
    }

    return files;
}

vector<vector<string>> Shingling(vector<vector<char>>&words,int k){
    vector<vector<string>> shingles;
    vector<string> tmp;
    string word;
    for(int i=0;i<words.size();i++){
        tmp.clear();
        for(int j=0;j<words.at(i).size()-k+1;j++){
            word.clear();
            for(int l=0;l<k;l++){
                word=word+words.at(i).at(j+l);
            }
            tmp.push_back(word);
        }
        shingles.push_back(tmp);
    }
    return shingles;
}

bool rules(vector<char>&words){
    //set rules for keyword selection
    int MinSize=4;
    if(words.size()<MinSize)
        return false;
    return true;
}

vector<vector<char>>get_words(string path){
    vector<vector<char>> words;
    char letter;
    vector<char> tmp;
    ifstream File(path);
    if (!File.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        return words;
    }
    while (File.get(letter)){
        if((letter==' ') || (letter=='\n') ||(letter=='-')||(letter==',')||(letter=='.')){
            if(rules(tmp))
                words.push_back(tmp);
            tmp.clear();
        }
        else
            tmp.push_back(letter);
    }
    return words;
}


vector<vector<int>>get_sig(vector<vector<string>>&shingles,vector<string>&vocub){
    vector<vector<int>>sigs;
    vector<int> s;
    for(int i=0;i<shingles.size();i++){
        s= signats(shingles.at(i),vocub);
        sigs.push_back(s);
    }

    return sigs;
}
vector<int>signats(vector<string>&s,vector<string>&vocub){
    vector<int>sig;
    string tmp;
    int pos=-1;
    for(int i=0;i<s.size();i++){
        tmp=s.at(i);
        for(int j=0;j<vocub.size();j++){
            if(vocub.at(j)==tmp){
                pos=j;
                break;
            }

        }
        if(pos>=0){
            sig.push_back(pos);
            pos=-1;
        }
        else{
            vocub.push_back(tmp);
            sig.push_back(vocub.size()-1);
        }
    }
    return sig;

}

