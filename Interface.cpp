//
// Created by peri on 20/12/21.
//
#include <iostream>
#include <vector>
#include "LSH.hpp"
#include "KDtree.hpp"
#include "Interface.hpp"
#include "Files.hpp"
#include <algorithm>




using namespace std;

int Interface(vector<node*>&trees){

    char* directory="../data";
    int shingle_size=3;
    int dimensions=3;
    vector<File*> textFileNames=get_files(directory);



    vector<string> tag_names={"football","basketball","sport","movies"};

    vector<vector<vector<int>>>sign;
    set<string>vocub;


    vector<File*> textFilePruned=prune_files(textFileNames, getUser_tags());


    get_data(sign,shingle_size,textFilePruned,vocub);


    KD_Interface(trees, dimensions, sign, vocub, textFilePruned);



}
///switch statement here to select between different trees
void KD_Interface(vector<node *> &trees, int dimensions, vector<vector<vector<int>>> &sign, set<string> &vocub,
                  vector<File *> &textFilePruned) {
    make_KD_trees(sign, trees, dimensions);




    string word;
    cout <<"enter word";
    cin>>word;
    vector<string>sec_vocub;
    vector<int>word_shingle=get_word_data(word,3,vocub,sec_vocub);


    Print_results(trees, textFilePruned, word_shingle);


}

void Print_results(vector<node *> &trees, vector<File *> &textFilePruned, vector<int> &word_shingle) {
    vector<int> nn=NNsearch_interface(trees, textFilePruned, word_shingle);


    vector<vector<int>> hits=searchAll_interface(trees, textFilePruned, word_shingle);


    vector<vector<int>>t= get_results(hits,nn);
    for(int i=0;i<t.size();i++){
        cout<<"\n"<<textFilePruned.at(t.at(i).at(0))->path<<" -- with "<<t.at(i).at(1)<<" hits\n";
    }
}


vector<vector<int>>get_results(vector<vector<int>>hits,vector<int>nn){
    vector<vector<int>> results;
    for(int i=0;i<hits.size();i++){
        results.push_back(hits.at(i));
    }
    bool exists= false;
    vector<int> tmp;
    for(int i=0;i<nn.size();i++){
        for(int j=0;j<hits.size();j++){
            if(nn.at(i)==hits.at(j).at(0)){
                exists=true;
                break;
            }


        }
        if(!exists){
            tmp.push_back(nn.at(i));
            tmp.push_back(0);
            results.push_back(tmp);
            tmp.clear();
        }
        else
            exists=false;
    }
    return results;

}

vector<vector<int>> searchAll_interface(vector<node *> &trees, vector<File *> &textFilePruned, vector<int> &word_shingle) {
    vector<vector<int>> result;
    vector<int> tmp;
    vector<int> hits;
    for(int i=0;i<trees.size();i++)
        hits.push_back(searchAll(trees.at(i),word_shingle));


    vector <int>order= order_by_hits(hits);
    for(int i=0;i<order.size();i++){
        tmp.clear();
        tmp.push_back(order.at(i));
        tmp.push_back(hits.at(order.at(i)));
        result.push_back(tmp);
    }
    return result;
}


vector<int> order_by_hits(vector<int> hits){
    vector<int> order;
    for(int i=0;i<hits.size();i++){
        int max=0;
        int pos=-1;
        for(int j=i;j<hits.size();j++){
            if(hits.at(j)>max){
                max=hits.at(j);
                pos=j;
            }
        }
        if (pos>-1){
            order.push_back(pos);
            hits.at(pos)=-1;
        }
    }
    return order;
}

vector<int> NNsearch_interface(vector<node *> &trees, vector<File *> &textFilePruned, vector<int> &word_shingle) {
    vector<int> result;
    vector<node*> results=NNsearch_trees(trees, word_shingle);
    vector<int>order=get_order_by_similarity(results,createNode(word_shingle,-1));
    for(int i=0;i<results.size();i++){
        int tmp=order.at(i);
        if (tmp==0)
            break;
        result.push_back(tmp);

    }
    return result;
}

vector<node*> NNsearch_trees(vector<node *> &trees, vector<int> &word_shingle) {
    vector<node*> results;
    node* n= createNode(word_shingle,-1);
    for (int i=0;i<trees.size();i++){
        results.push_back(NN_search(trees.at(i),n,0));
    }

    return results;
}

vector<node*> KDtree_search(vector<int> word,vector<node*>&trees){
    vector<node*>results;
    node* tmp;
    for(node* tree:trees){
        tmp=search(tree,word);
        results.push_back(tmp);
    }
    return results;
}

set<int> getUser_tags(){
    set<int> tags;
    int tmp;
    while(1){

        cout << "\n input a tag to search \n 1 -> football \n 2 -> basketball \n 3 -> sport \n 4 -> movie \n 0 -> no tag \n";
        cin >> tmp;
        if(tmp==0);
            break;
        tmp--;
        tags.insert(tmp);
    }

    return tags;

}

vector<int> get_order_by_similarity(vector<node*> results,node* n){
    vector<float> tmp;
    vector<int> f;
    for(int i=0;i<results.size();i++){
       tmp.push_back(JaccardCoefficient(results.at(i)->coordinates,n->coordinates));
    }


    for(int i=0;i<results.size();i++){
        int max=0;
        int pos=0;
        for (int j=0;j<results.size();j++){
            if (tmp.at(j)>max){
                max=tmp.at(j);
                pos=j;

            }
        }
        f.push_back(pos);
        tmp.at(pos)=-1;
    }
    return f;
}


