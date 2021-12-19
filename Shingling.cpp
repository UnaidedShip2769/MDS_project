//
// Created by peri on 27/11/21.
//
#include <iostream>
#include <vector>
#include "KDtree.hpp"
#include <algorithm>
#include "LSH.hpp"
#include <string>
#include <dirent.h>
#include <random>

using namespace std;

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
            if((temp!="../data/..")&&(temp!="../data/."))
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
    /*for(vector<string> temp1 : shingles)
    {
        for(string temp2 : temp1)
        {
            cout << temp2 << " , ";
        }
        cout << endl;
    }*/
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
    bool flag =false;
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
        if(!(((letter>64)&&(letter<91))||((letter>96)&&(letter<123))))
            flag=true;

        if(flag){
            if(rules(tmp))
                words.push_back(tmp);
            tmp.clear();
            flag=false;
        }
        else
            tmp.push_back(letter);
    }
    return words;
}
/*vector<vector<int>>get_sig(vector<vector<string>>&shingles,vector<string>&vocub) {
    vector<vector<int>> sigs;
    vector<int> s;
    for (int i = 0; i < shingles.size(); i++) {
        s = signats(shingles.at(i), vocub);
        sigs.push_back(s);
    }
    return sigs;
}
vector<int>signats(vector<string>&s,vector<string>&vocub)
{
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
}*/



void make_vocub_and_shuffle(vector<string> &vocub, vector<vector<vector<string>>>&text)
{
    for(vector<vector<string>> texts : text)
    {
        for(vector<string> word : texts)
        {
            for(string shin : word)
            {
                //bool alreadyExists = false;
                for(string shin_vocub : vocub)
                {
                    if (shin == shin_vocub)
                    {
                        //alreadyExists = true;
                        break;
                    }
                }
                //if(!alreadyExists)
                //{
                vocub.push_back(shin);
                //}
            }
        }
    }
    random_device rd;
    default_random_engine rng(rd());
    shuffle(vocub.begin(), vocub.end(), rng);
}

void make_sign(vector<vector<vector<int>>> &sign, vector<string> &vocub, vector<vector<vector<string>>> &text)
{
    vector<vector<int>> s;
    for(vector<vector<string>> texts : text)
    {
        s.clear();
        for(vector<string> word : texts)
        {
            vector<int> temp_sig;
            for(string shin : word)
            {
                int position = 0;
                for(string voc_shin : vocub)
                {
                    if(shin == voc_shin)
                    {
                        temp_sig.push_back(position);
                        break;
                    }
                    position++;
                }
            }

            s.push_back(temp_sig);
        }
        sign.push_back(s);
    }
}

//////interface type faction that calls all the above to  iterate
//////thew all files and return them in signatures and add them to `text`

void get_data(char* dir_path,vector<vector<vector<int>>>&sign,int k,vector<string> &textFileNames){
    vector<vector<vector<string>>>text;
    textFileNames= get_files(dir_path);
    vector<string>vocub;
    vector<vector<string>>shin;

    vector<vector<char>>words;
    for(int i=0;i<textFileNames.size();i++){
        words= get_words(textFileNames.at(i));
        shin= Shingling(words,k);
        text.push_back(shin);
        //sign= get_sig(shin,vocub);
        //text.push_back(sign);
    }
    make_vocub_and_shuffle(vocub, text);
    make_sign(sign, vocub, text);

}

/*
 * vectro<vector<vectro<string>>> shingle
 * make_vocub(&)vector<string> suffle;
 * shingle + vocub->vector<vector<vectro<int>>> sig
 */

/*void make_trees(char*dir_path,vector<node*>&trees,int l,int k){
    vector<string>files= get_files(dir_path);
    vector<string>vocub;
    vocub.resize(13000,"??");
    vector<vector<string>>shin;
    vector<vector<int>>sign;
    vector<vector<char>>words;
    node* tree;
    for(int i=0;i<files.size();i++){
        tree=NULL;
        words= get_words(files.at(i));
        shin= Shingling(words,l);
        sign= get_sig(shin,vocub);
        for(int i=0;i<sign.size();i++){
            vector<int> t=sign.at(i);
            t.resize(k);
            tree=insert(tree,t);
        }
        trees.push_back(tree);
    }
}*/
