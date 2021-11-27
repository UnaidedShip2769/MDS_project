//
// Created by peri on 27/11/21.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <iterator>
using namespace std;
set<string>  Shingling(std::vector<char>text,int k){

    //check if vector is corectly loaded
    if ((text.size()==1&&text.at(0)=='?') || text.size()==0){
        std::cout << "error loading vector";
    }
    string tmp;
    set <string> shingles;
    char temp=' ';
    for (int i = 0;i<text.size()-k+1;i++){

        for(int j=0;j<k;j++){
            if(text.at(i+j)==temp)
                tmp=tmp+'_';
            else
                tmp= tmp+(text.at(i+j));
        }
        shingles.insert(tmp);
        tmp.clear();
    }

    return shingles;

}

set<string>  Merge (set<string> s1,set<string> s2){

    set<string> tmp;
    tmp.insert(s2.begin(),s2.end());
    return tmp;

}

vector<char> read_text(char* path){

    vector<char> text;
    ifstream File(path);
    char letter;
    if (!File.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        text.push_back('?');
        return text;
    }

    while (File.get(letter)){
        text.push_back(letter);
    }


}

vector <int> onehot_encode(set<string> shingle,set<string>vocub){
    set<string>::iterator it,it1;
    vector<int>onehot(shingle.size(),0);
    string tmp;
    for (it=shingle.begin();it!=shingle.end();++it){
        tmp= *it;
        int i=0;
        for(it1=vocub.begin();it1!=vocub.end();++it1){
            i++;
            if(tmp==*it1){
                onehot[i]=1;
            }
        }
    }
}
