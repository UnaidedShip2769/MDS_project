#include <iostream>
#include <vector>
#include "LSH.hpp"
#include "KDtree.hpp"
#include "Interface.hpp"
#include "Files.hpp"
#include "quadtree.hpp"
#include <algorithm>


using namespace std;


int Interface(vector<node*>&kdtrees, vector<Quadtree> &quadtrees){

    cout << "Reading files from directory ../data" << endl;
    char* directory="../data";
    int shingle_size=3;
    int dimensions=2;

    vector<File*> textFileNames=get_files(directory);



    vector<string> tag_names={"football","basketball","sport","movies"};

    vector<vector<vector<int>>>sign;
    set<string>vocub;


    vector<File*> textFilePruned=prune_files(textFileNames, getUser_tags());


    get_data(sign,shingle_size,textFilePruned,vocub);


    cout << "Select your tree type!" << endl << " 1. KD-Trees" << endl << " 2. Quadtrees" << endl << " 3. R-Trees" << endl << " 4. Range Trees" << endl
    << " 5. Exit" << endl << "Please choose by entering a number from 1 to 4: ";
    int selector;
    cin >> selector;
    bool exit = false;
    while(!exit)
    {
        switch(selector)
        {
            case 1:
            {
                KD_Interface(kdtrees, dimensions, sign, vocub, textFilePruned);
                exit = true;
                break;
            }
            case 2:
            {
                Quad_Interface(quadtrees, dimensions, sign, vocub, textFilePruned);
                exit = true;
                break;
            }
            case 3:
            {
                cout << "R-Trees have not yet been implemented!" << endl << "Please choose another tree type: ";
                cin >> selector;
                exit = false;
                break;
            }
            case 4:
            {
                cout << "Range Trees have not yet been implemented!" << endl << "Please choose another tree type: ";
                cin >> selector;
                exit = false;
                break;
            }
            case 5:
            {
                cout << "Exiting!" << endl;
                exit = true;
                break;
            }
            default:
            {
                cout << "Please enter a valid number: " << endl;
                cin >> selector;
                exit = false;
                break;
            }
        }
    }
}

void kdtrees_combined_search(vector<node *> &trees, vector<File *> &textFilePruned, vector<int> &word_shingle) {
    vector<int> nn=NNsearch_interface(trees, textFilePruned, word_shingle);


    vector<vector<int>> hits=searchAll_interface(trees, textFilePruned, word_shingle);


    vector<vector<int>>t= get_results(hits,nn);
    for(int i=0;i<t.size();i++){
        cout<<"\n"<<textFilePruned.at(t.at(i).at(0))->path<<" -- with "<<t.at(i).at(1)<<" hits\n";
    }
}

void KD_Interface(vector<node *> &kdtrees, int dimensions, vector<vector<vector<int>>> &sign, set<string> &vocub,
                  vector<File *> &textFilePruned) {
    make_KD_trees(sign, kdtrees, dimensions);
    string word;
    cout <<"Enter the word you want to index the texts by: ";
    cin>>word;
    vector<string>sec_vocub;
    vector<int>word_shingle=get_word_data(word,3,vocub,sec_vocub);
    cout << "Select indexing method!" << endl << " 1. Search: Order by most times the word signature was found in each text" << endl <<
         " 2. NNSearch: Index by NNSearch result from each text ordered by highest Jaccard coefficient when comared to the word signature" << endl
         << " 3. CombinedSearch: Results from search come first, NNSearch results come later" << endl
         << "Please enter 1 or 3: ";
    int selector;
    cin >> selector;
    bool exit = false;
    while(!exit)
    {
        switch(selector)
        {
            case 1:
            {
                vector<vector<int>> results;
                results=searchAll_interface(kdtrees, textFilePruned, word_shingle);
                for(int i=0;i<results.size();i++){
                    cout<<"\n"<<textFilePruned.at(results.at(i).at(0))->path<<" -- with "<<results.at(i).at(1)<<" hits\n";
                }
                exit = true;
                break;
            }
            case 2:
            {
                vector<int> results;
                results=NNsearch_interface(kdtrees, textFilePruned, word_shingle);
                for(int i=0;i<results.size();i++){
                    cout<<"\n"<<textFilePruned.at(results.at(i))->path<<"\n";
                }
                exit = true;
                break;
            }
            case 3:
            {
                kdtrees_combined_search(kdtrees, textFilePruned, word_shingle);
                exit = true;
                break;
            }
            default:
                cout << "Please enter a valid number: ";
                cin >> selector;
                break;
        }
    }
}

void Quad_Interface(vector<Quadtree> &quadtrees, int dimensions, vector<vector<vector<int>>> &sign, set<string> &vocub, vector<File *> &textFilePruned)
{
    make_quad_trees(sign, quadtrees, dimensions, vocub);
    string word;
    cout << "Enter the word you want to index the texts by: ";
    cin >> word;
    vector<string> sec_vocub;
    vector<int>word_shingle=get_word_data(word, 3, vocub, sec_vocub);

    cout << "Select indexing method!" << endl << " 1. Search: Order by most times the word signature was found in each text" << endl <<
    " 2. NNSearch: Index by NNSearch result from each text ordered by highest Jaccard coefficient when comared to the word signature" << endl
    << "Please enter 1 or 2: ";
    int selector;
    cin >> selector;
    bool exit = false;
    while(!exit)
    {
        switch(selector)
        {
            case 1:
            {
                searchForWordInQuadtrees(quadtrees, textFilePruned, word_shingle, dimensions);
                exit = true;
                break;
            }
            case 2:
            {
                nnSearchForWordInQuadtrees(quadtrees, textFilePruned, word_shingle, dimensions);
                exit = true;
                break;
            }
            default:
                cout << "Please enter a valid number: ";
                cin >> selector;
                break;
        }
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

void searchForWordInQuadtrees(vector<Quadtree> &quadtrees, vector<File *> &textFilePruned, vector<int> word_shingle, int dimensions)
{
    word_shingle.resize(dimensions, 0);
    vector<int> hits;
    vector<float> float_word_shingle;
    for(int tempint : word_shingle)
    {
        float_word_shingle.push_back((float)tempint);
    }
    for(Quadtree temptree : quadtrees)
    {
        int temphits = 0;
        temptree.search(float_word_shingle, false, temphits);
        hits.push_back(temphits);
    }

    vector<int> order = order_by_hits(hits);
    for(int i=0;i<order.size();i++){
        cout<<textFilePruned.at(order.at(i))->path<<" -- With "<<hits.at(order.at(i))<<" Hits!\n";
    }
}

void nnSearchForWordInQuadtrees(vector<Quadtree> &quadtrees, vector<File*> textFilesPruned, vector<int> word_shingle, int dimensions)
{
    word_shingle.resize(dimensions, 0);
    vector<vector<float>> results;
    vector<float> float_word_shingle;
    for (int tempint : word_shingle) {
        float_word_shingle.push_back((float) tempint);
    }
    for (Quadtree &temptree : quadtrees) {
        results.push_back(temptree.NN(float_word_shingle));
    }
    vector<int> order = quadtree_get_order_by_similarity(results, float_word_shingle);
    for (int i = 0; i < results.size(); i++) {
        int tmp = order.at(i);
        if (tmp == 0)
            break;
        cout << textFilesPruned.at(tmp)->path << "\n";
    }
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

vector<node*> NNsearch_trees(vector<node *> &kdtrees, vector<int> &word_shingle) {
    vector<node*> results;
    node* n= createNode(word_shingle,-1);
    for (int i=0;i<kdtrees.size();i++){
        results.push_back(NN_search(kdtrees.at(i),n,0));
    }
    return results;
}

vector<node*> KDtree_search(vector<int> word,vector<node*>&kdtrees){
    vector<node*>results;
    node* tmp;
    for(node* tree:kdtrees){
        tmp=search(tree,word);
        results.push_back(tmp);
    }
    return results;
}

set<int> getUser_tags(){
    set<int> tags;
    int tmp;
    while(1){

        cout << "Input a tag to filter the texts by; \n 0. No tag \n 1. Football \n 2. Basketball \n 3. Sport \n 4. Movie\nPlease enter a number from 0 to 4: ";

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

vector<int> quadtree_get_order_by_similarity(vector<vector<float>> &results, vector<float> &word_shingle)
{
    vector<float> tmp;
    vector<int> f;
    for(vector<float> tempres : results)
    {
        tmp.push_back(floatJaccardCoefficient(tempres, word_shingle));
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
