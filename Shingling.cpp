//
// Created by peri on 27/11/21.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <queue>
#include <iterator>
using namespace std;
vector<set<string>>  Shingling(std::vector<char>text,int k){

    //check if vector is corectly loaded
    if ((text.size()==1&&text.at(0)=='?') || text.size()==0){
        std::cout << "error loading vector";
    }





    vector<set <string>> shingles;
    set<string> temporary;
    vector<char> temp ;
    string tmp;
    char space= ' ';
    bool flag=false;
    int itt=0;
    for(int i =0;i<k;i++)
        temp.push_back(text.at(i));
    int i=k-1;
    while(i<text.size()-k+1){
        tmp.clear();
        for (int j=0;j<k;j++)
            tmp=tmp+temp.at(j);

        if(temp[k-1]==space){
            //check if it is word with under k # of letters


            if(temporary.size()==0){
                //if so discard

                temporary.clear();
            }



            else{
                //else discard and add new set to vector
                itt++;

                shingles.push_back(temporary);
                temporary.clear();

            }
            i++;
            for(int j =0;j<k;j++)

                temp[j]=text.at(j+i);
            i+=(k-1);
        }
        else{

            temporary.insert(tmp);
            i++;
            for (int j=0;j<k-1;j++){
                temp[j]=temp[j+1];
            }

            temp [k-1]=text.at(i);
        }

    }

    return shingles;

}

void Merge (vector<set<string>> &v, set<string> &vocub){

    for (int i=0;i<v.size();i++){
        vocub.insert(v.at(i).begin(),v.at(i).end());
    }


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

vector <vector<bool>> onehot_encode(vector<set<string>> &shingle,set<string>&vocub){
    set<string>::iterator it,it1;
    vector<bool> tmp(vocub.size(),0);
    vector<vector<bool>> onehot(shingle.size(),tmp);
    int i=0;
    for(it=vocub.begin();it!=vocub.end();++it){

        string tmp=*it;
        for(int j=0;j<shingle.size();j++){
            if(shingle.at(j).find(tmp)!=shingle.at(j).end())
                onehot.at(j).at(i)=true;
        }

        i++;
    }
    return onehot;

}

vector<int> minHash(vector<bool> &onehot,int num){
    vector <int>minHash(num,0);
    int j=0;
    for(int i=0;i<onehot.size();i++){
        if(j>=num)
            break;
        if(onehot.at(i)==true){
            minHash.at(j)=i;
            j++;
        }

    }
    return minHash;
}

vector<vector<int>>minhash(vector<vector<bool>> &onehot,int num){
    vector<vector<int>> minhash;
    for (int i=0;i< onehot.size();i++){
        minhash.push_back( minHash(onehot.at(i),num));
    }
    return minhash;
}
//compiles