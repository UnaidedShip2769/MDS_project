#include <iostream>
#include <vector>
#include "LSH.hpp"
#include "KDtree.hpp"
#include "Interface.hpp"
#include "Files.hpp"
#include "quadtree.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

int Interface(vector<node*>&kdtrees, vector<Quadtree> &quadtrees){
    cout << "Reading files from directory ../data" << endl;
    char* directory="../data";
    int shingle_size=3;
    int dimensions=2;
    int programexit = 1;
    while(programexit == 1)
    {
        vector<File*> textFileNames=get_files(directory);
        vector<vector<vector<int>>>sign;
        set<string>vocub;
        vector<File*> textFilePruned=prune_files(textFileNames, getUser_tags());
        get_data(sign,shingle_size,textFilePruned,vocub);
        bool exit = false;
        int selector;
        while(!exit)
        {
            cout << "Select your tree type!" << endl << " 1. KD-Trees" << endl << " 2. Quadtrees" << endl << " 0. Exit"
            << endl << "Please choose by entering a number from 0 to 2: ";
            cin >> selector;
            switch(selector)
            {
                case 1:
                {
                    KD_Interface(kdtrees, dimensions, sign, vocub, textFilePruned);
                    break;
                }
                case 2:
                {
                    Quad_Interface(quadtrees, dimensions, sign, vocub, textFilePruned);
                    break;
                }
                case 0:
                {
                    exit = true;
                    break;
                }
                default:
                {
                    cout << "Please enter a valid number: " << endl;
                    cin >> selector;
                    break;
                }
            }
        }
        cout << "Do you want to change the text file tags and prune again in order to index the texts again?" << endl << " 0. No" << endl << " 1. Yes" <<
        endl << "Please enter 0 or 1: ";
        cin >> programexit;
        if(programexit != 0 && programexit != 1)
        {
            cout << "Please enter a valid number!!!" << endl << "Please enter 0 or 1: ";
            cin >> programexit;
        }
    }

}

void kdtrees_combined_search(vector<node *> &trees, vector<File *> &textFilePruned, vector<int> &word_shingle) {
    vector<int> nn=NNsearch_interface(trees, textFilePruned, word_shingle);
    vector<vector<int>> hits=searchAll_interface(trees, textFilePruned, word_shingle);
    vector<vector<int>>t= get_results(hits,nn);
    for(int i=0;i<t.size();i++){
        cout<<textFilePruned.at(t.at(i).at(0))->path<<" -- with "<<t.at(i).at(1)<<" hits\n";
    }
}

void KD_Interface(vector<node *> &kdtrees, int dimensions, vector<vector<vector<int>>> &sign, set<string> &vocub,
                  vector<File *> &textFilePruned) {
    //auto start = high_resolution_clock::now();
    make_KD_trees(sign, kdtrees, dimensions);
    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds>(stop - start);
    //cout << "Time taken by function: "
    //     << duration.count() << " microseconds" << endl;
    cout << "Reading files from directory ../data" << endl;
    string word;
    int wordexit = 1;
    while(wordexit == 1)
    {
        cout <<"Enter the word you want to index the texts by: ";
        cin>>word;
        vector<string>sec_vocub;
        vector<int>word_shingle=get_word_data(word,3,vocub,sec_vocub);
        bool exit = false;
        int selector;
        while(!exit) {
            cout << "Select indexing method!" << endl
                 << " 1. Search: Order by most times the word signature was found in each text" << endl <<
                 " 2. NNSearch: Index by NNSearch result from each text ordered by highest Jaccard coefficient when comared to the word signature"
                 << endl
                 << " 3. CombinedSearch: Results from search come first, NNSearch results come later" << endl
                 << " 0. Exit" << endl
                 << "Please enter a number from 0 to 3: ";
            cin >> selector;
            int searchagain = 0;
            switch (selector) {
                case 1: {
                    vector<vector<int>> results;
                    //auto start = high_resolution_clock::now();
                    results=searchAll_interface(kdtrees, textFilePruned, word_shingle);
                    //auto stop = high_resolution_clock::now();
                    //auto duration = duration_cast<microseconds>(stop - start);
                    //cout << "Time taken by function: "
                    //     << duration.count() << " microseconds" << endl;
                    for(int i=0;i<results.size();i++){
                      cout<<textFilePruned.at(results.at(i).at(0))->path<<" -- with "<<results.at(i).at(1)<<" hits\n";
                    }
                    cout << "Search finished! Do you want to search for the same word again?" << endl << " 0. No"
                         << endl << " 1. Yes" << endl <<
                         "Please enter 0 or 1: ";
                    cin >> searchagain;
                    while(searchagain != 0 && searchagain != 1)
                    {
                        cout << "Please enter a valid number!!!" << endl << "Please enter 0 or 1: ";
                        cin >> searchagain;
                    }
                    if (searchagain == 0) {
                        exit = true;
                    }
                    break;
                }
                case 2: {
                    vector<int> results;
                    //auto start = high_resolution_clock::now();
                    results=NNsearch_interface(kdtrees, textFilePruned, word_shingle);
                    //auto stop = high_resolution_clock::now();
                    //auto duration = duration_cast<microseconds>(stop - start);
                    //cout << "Time taken by function: "
                    //     << duration.count() << " microseconds" << endl;
                    for(int i=0;i<results.size();i++){
                      cout<<textFilePruned.at(results.at(i))->path<<"\n";
                    }
                    cout << "Search finished! Do you want to search for the same word again?" << endl << " 0. No"
                         << endl << " 1. Yes" << endl <<
                         "Please enter 0 or 1: ";
                    cin >> searchagain;
                    while(searchagain != 0 && searchagain != 1)
                    {
                        cout << "Please enter a valid number!!!" << endl << "Please enter 0 or 1: ";
                        cin >> searchagain;
                    }
                    if (searchagain == 0) {
                        exit = true;
                    }
                    break;
                }
                case 3: {
                    kdtrees_combined_search(kdtrees, textFilePruned, word_shingle);
                    cout << "Search finished! Do you want to search for the same word again?" << endl << " 0. No"
                         << endl << " 1. Yes" << endl <<
                         "Please enter 0 or 1: ";
                    cin >> searchagain;
                    while(searchagain != 0 && searchagain != 1)
                    {
                        cout << "Please enter a valid number!!!" << endl << "Please enter 0 or 1: ";
                        cin >> searchagain;
                    }
                    if (searchagain == 0) {
                        exit = true;
                    }
                    break;
                }
                case 0: {
                    exit = true;
                    break;
                }
                default: {
                    cout << "Please enter a valid number: ";
                    cin >> selector;
                    break;
                }
            }
        }
        cout << "Do you want to to index the texts by another word?" << endl << " 0. No" << endl << " 1. Yes" << endl << "Please enter 0 or 1: ";
        cin >> wordexit;
        while(wordexit != 0 && wordexit != 1)
        {
            cout << "Please enter a valid number!!!" << endl << "Please enter 0 or 1: ";
            cin >> wordexit;
        }
    }
}

void Quad_Interface(vector<Quadtree> &quadtrees, int dimensions, vector<vector<vector<int>>> &sign, set<string> &vocub, vector<File *> &textFilePruned)
{
    //auto start = high_resolution_clock::now();
    make_quad_trees(sign, quadtrees, dimensions, vocub);
    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds>(stop - start);
    //cout << "Time taken by function: "
    //     << duration.count() << " microseconds" << endl;
    string word;
    int wordexit = 1;
    while(wordexit == 1)
    {
        cout << "Enter the word you want to index the texts by: ";
        cin >> word;
        vector<string> sec_vocub;
        vector<int>word_shingle=get_word_data(word, 3, vocub, sec_vocub);
        int selector;
        bool exit = false;
        while(!exit)
        {
            cout << "Select indexing method!" << endl << " 1. Search: Order by most times the word signature was found in each text" << endl <<
                 " 2. NNSearch: Index by NNSearch result from each text ordered by highest Jaccard coefficient when comared to the word signature" << endl
                 << " 3. CombinedSearch: Results from search come first, NNSearch results come later" << endl << " 0. Exit" << endl
                 << "Please enter a number from 0 to 3: ";
            cin >> selector;
            int searchagain = 0;
            switch(selector)
            {
                case 1:
                {
                    vector<int> temp;
                    //auto start = high_resolution_clock::now();
                    searchForWordInQuadtrees(quadtrees, textFilePruned, word_shingle, dimensions, true, temp);
                    //auto stop = high_resolution_clock::now();
                    //auto duration = duration_cast<microseconds>(stop - start);
                    //cout << "Time taken by function: "
                    //     << duration.count() << " microseconds" << endl;
                    cout << "Search finished! Do you want to search for the same word again?" << endl << " 0. No" << endl << " 1. Yes" << endl <<
                         "Please enter 0 or 1: ";
                    cin >> searchagain;
                    while(searchagain != 0 && searchagain != 1)
                    {
                        cout << "Please enter a valid number!!!" << endl << "Please enter 0 or 1: ";
                        cin >> searchagain;
                    }
                    if(searchagain == 0)
                    {
                        exit = true;
                    }
                    break;
                }
                case 2:
                {
                    //auto start = high_resolution_clock::now();
                    nnSearchForWordInQuadtrees(quadtrees, textFilePruned, word_shingle, dimensions, true);
                    //auto stop = high_resolution_clock::now();
                    //auto duration = duration_cast<microseconds>(stop - start);
                    //cout << "Time taken by function: "
                    //     << duration.count() << " microseconds" << endl;
                    cout << "Search finished! Do you want to search for the same word again?" << endl << " 0. No" << endl << " 1. Yes" << endl <<
                         "Please enter 0 or 1: ";
                    cin >> searchagain;
                    while(searchagain != 0 && searchagain != 1)
                    {
                        cout << "Please enter a valid number!!!" << endl << "Please enter 0 or 1: ";
                        cin >> searchagain;
                    }
                    if(searchagain == 0)
                    {
                        exit = true;
                    }
                    break;
                }
                case 3:
                {
                    quadtree_combined_search(quadtrees, textFilePruned, word_shingle, dimensions);
                    cout << "Search finished! Do you want to search for the same word again?" << endl << " 0. No" << endl << " 1. Yes" << endl <<
                         "Please enter 0 or 1: ";
                    cin >> searchagain;
                    while(searchagain != 0 && searchagain != 1)
                    {
                        cout << "Please enter a valid number!!!" << endl << "Please enter 0 or 1: ";
                        cin >> searchagain;
                    }
                    if(searchagain == 0)
                    {
                        exit = true;
                    }
                    break;
                }
                case 0:
                {
                    exit = true;
                    break;
                }
                default:
                    cout << "Please enter a valid number: ";
                    cin >> selector;
                    break;
            }
        }
        cout << "Do you want to to index the texts by another word?" << endl << " 0. No" << endl << " 1. Yes" << endl << "Please enter 0 or 1: ";
        cin >> wordexit;
        while(wordexit != 0 && wordexit != 1)
        {
            cout << "Please enter a valid number!!!" << endl << "Please enter 0 or 1: ";
            cin >> wordexit;
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

vector<int> searchForWordInQuadtrees(vector<Quadtree> &quadtrees, vector<File *> &textFilePruned, vector<int> word_shingle, int dimensions, bool print, vector<int> &numberoffhits)
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
    numberoffhits = hits;
    vector<int> order = order_by_hits(hits);
    if(print)
    {
        for(int i=0;i<order.size();i++){
            cout<<textFilePruned.at(order.at(i))->path<<" -- With "<<hits.at(order.at(i))<<" Hits!\n";
        }
    }
    return order;
}

vector<int> nnSearchForWordInQuadtrees(vector<Quadtree> &quadtrees, vector<File*> textFilesPruned, vector<int> word_shingle, int dimensions, bool print)
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
    if(print)
    {
        for (int i = 0; i < order.size(); i++) {
            int tmp = order.at(i);
            if (tmp == 0)
                break;
            cout << textFilesPruned.at(tmp)->path << "\n";
        }
    }
    return order;
}

void quadtree_combined_search(vector<Quadtree> &quadtrees, vector<File *> &textFilePruned, vector<int> word_shingle, int dimensions)
{
    vector<int> nosearchhits;
    vector<int> searchhits = searchForWordInQuadtrees(quadtrees, textFilePruned, word_shingle, dimensions, false, nosearchhits);
    vector<int> nnhits = nnSearchForWordInQuadtrees(quadtrees, textFilePruned, word_shingle, dimensions, false);
    int initialprintsize = searchhits.size();
    for(int i : nnhits)
    {
        bool found = false;
        for(int j : searchhits)
        {
            if(i == j)
            {
                found = true;
                break;
            }
        }
        if(!found)
        {

            searchhits.push_back(i);
        }
    }
    int i;
    cout << "From Search algorithm:" << endl;
    for(i=0;i<initialprintsize;i++)
    {
        cout<<textFilePruned.at(searchhits.at(i))->path<<" -- With "<<nosearchhits.at(searchhits.at(i))<<" Hits!\n";
    }
    cout << endl << "From NNSearch algorithm:" << endl;
    while(i<searchhits.size())
    {
        cout<<textFilePruned.at(searchhits.at(i))->path<<endl;
        i++;
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

set<int> getUser_tags(){
    set<int> tags;
    bool finish = false;
    cout << "Input a tag to filter the texts by;\n 1. Football\n 2. Basketball\n 3. Sport\n 4. Movie\n 0. Save and exit" << endl;
    while(!finish){
        cout << "Please enter a number from 0 to 4: ";
        int selector;
        cin >> selector;
        switch(selector)
        {
            case 1:
            {
                tags.insert(1);
                cout << "Added tag 'Football' to filter by!" << endl;
                break;
            }
            case 2:
            {
                tags.insert(2);
                cout << "Added tag 'Basketball' to filter by!" << endl;
                break;
            }
            case 3:
            {
                tags.insert(3);
                cout << "Added tag 'Sports' to filter by!" << endl;
                break;
            }
            case 4:
            {
                tags.insert(4);
                cout << "Added tag 'Movies' to filter by!" << endl;
                break;
            }
            case 0:
            {
                finish = true;
                break;
            }
            default:
            {
                cout << "Please enter a valid number!!!" << endl;
                break;
            }
        }
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
        if(tmp.at(pos) > 0)
        {
            f.push_back(pos);
        }
        tmp.at(pos)=-1;
    }
    return f;
}