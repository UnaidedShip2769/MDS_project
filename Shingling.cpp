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


        if((letter>64)&&(letter<91)){
            letter+=32;
        }


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


/*int bin_vocub_search(vector<string> &vocub,int l,int r,string shin,int letter){
    if(r>=l){
        int mid=l+(r-l)/2;
        if(vocub.at(mid)==shin)
            return -1;
        if(vocub.at(mid).at(letter)==shin.at(letter)){
            while(vocub.at(mid).at(letter)==shin.at(letter)){
                mid--;
                if(vocub.at(mid)==shin)
                    return -1;
            }

            return bin_vocub_search(vocub,mid,r,shin,letter+1);
        }
        if(vocub.at(mid).at(letter)>shin.at(letter)){
            return bin_vocub_search(vocub,l,mid-1,shin,letter);
        }
    }
}
void make_vocub(vector<string> &vocub, vector<vector<vector<string>>>&text){
    for(vector<vector<string>> texts : text){
        for(vector<string> word : texts){
            for(string shin : word){
                if(vocub.size()==0)
                    vocub.push_back(shin);
                else{
                    ////search for the place to insert the word
                    int letter=0;
                    int tmp=vocub.size()/2;
                    if(vocub.at(tmp).at(letter)>shin.at(letter)){

                    }
                }
            }
        }
    }
}*/

void make_vocub(set<string>&vocub,vector<vector<vector<string>>>&text){
    for(vector<vector<string>> texts : text) {
        for (vector<string> word: texts) {
            for (string shin: word) {
                vocub.insert(shin);
            }
        }
    }
}
void make_vocub_and_shuffle(vector<string> &vocub, vector<vector<vector<string>>>&text)
{

    for(vector<vector<string>> texts : text)
    {
        for(vector<string> word : texts)
        {
            for(string shin : word)
            {
                int pos=0;
                bool alreadyExists = false;

                for(string shin_vocub : vocub)
                {

                    if (shin == shin_vocub)
                    {
                        alreadyExists = true;
                        break;
                    }
                    else if(shin.at(0)<shin_vocub.at(0))
                        break;




                    pos++;
                }
                if(!alreadyExists){///insted of insterting order to the second letter
                    alreadyExists= false;
                    for(string shin_vocub : vocub){
                        if(shin == shin_vocub){
                            alreadyExists=true;
                            break;
                        }
                        else if(shin.at(1)<shin_vocub.at(1))
                            break;
                        pos++;

                    }
                    if(!alreadyExists){
                        vocub.insert(vocub.begin()+pos,shin);
                    }
                }

            }
        }
    }

}



void make_sign(vector<vector<vector<int>>> &sign,set<string> &vocub, vector<vector<vector<string>>> &text)
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

void get_data(char* dir_path,vector<vector<vector<int>>>&sign,int k,vector<string> &textFileNames,set<string>&vocub){
    vector<vector<vector<string>>>text;
    textFileNames= get_files(dir_path);
    vector<vector<string>>shin;

    vector<vector<char>>words;
    for(int i=0;i<textFileNames.size();i++){
        words= get_words(textFileNames.at(i));
        shin= Shingling(words,k);
        text.push_back(shin);
        //sign= get_sig(shin,vocub);
        //text.push_back(sign);
    }
    make_vocub(vocub, text);
    //make_vocub_and_order_alphabetically(vocub,text);
    make_sign(sign, vocub, text);

}


void make_KD_trees(vector<vector<vector<int>>>&sign,vector<node*>&trees,int k){
    //vector<string> textFileNames not needed
    node* tree;
    for(vector<vector<int>> file_signs : sign)
    {
        tree = NULL;
        for(vector<int> sig : file_signs)
        {
            vector<int> t = sig;
            t.resize(k,0);
            tree=insert(tree,t);
        }
        trees.push_back(tree);
    }
}

vector<string> word_Shingling(string &word, int k)
{
    vector<string> shingles;
    string temp_word;
    for(int i=0; i<word.size()-k+1; i++)
    {
        temp_word.clear();
        for(int j=0; j<k; j++)
        {
            temp_word=temp_word+word.at(i+j);
        }
        shingles.push_back(temp_word);
    }
    return shingles;
}

void update_vocub(set<string> &vocub, vector<string> &secondaryVocub, vector<string>&shingles)
{
    for(string shin : shingles)
    {
        bool alreadyExists = false;
        for(string shin_vocub : vocub)
        {
            if (shin == shin_vocub)
            {
                alreadyExists = true;
                break;
            }
            else if(shin.at(0)<shin_vocub.at(0))
                break;
        }
        if(!alreadyExists)
        {
            secondaryVocub.push_back(shin);
        }
    }
}

void make_word_sign(vector<int> &sign, set<string> &vocub, vector<string> &secondaryVocub, vector<string> shingles)
{
    for(string shin : shingles)
    {

        int position = 0;
        for(string voc_shin : vocub)
        {
            if(shin == voc_shin)
            {
                sign.push_back(position);
                break;
            }
            else if(shin.at(0) < voc_shin.at(0))
            {
                int sec_position = 0;
                for(string secvoc_shin: secondaryVocub)
                {
                    if(shin == secvoc_shin) {
                        sign.push_back(sec_position + vocub.size());
                        break;
                    }
                    sec_position++;
                }
                break;
            }
            position++;
        }
    }
}

vector<int> get_word_data(string &word, int k, set<string> &vocub, vector<string> &secondaryVocub)
{
    vector<string> shingles = word_Shingling(word,3);
    update_vocub(vocub, secondaryVocub, shingles);
    vector<int> signatures;
    make_word_sign(signatures,vocub,secondaryVocub,shingles);
    return signatures;

}


