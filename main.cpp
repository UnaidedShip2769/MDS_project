#include <iostream>
#include <vector>
#include <set>
#include "LSH.hpp"
#include "KDtree.hpp"


int main() {

    using namespace std;
    vector<char> text= read_text("../data/test.txt");
    vector<char> text2= read_text("../data/test2.txt");
    vector<set<string>> s1= Shingling(text,3);
    vector<set<string>> s2= Shingling(text2,3);
    set<string> vocub;
    vector<vector<bool>>onehot1;

    Merge(s1,vocub);
    Merge(s2,vocub);
    onehot1= onehot_encode(s1,vocub);
    vector<vector<int>>min;
    min= minhash(onehot1,2);


    node* tree1=NULL;
    for (int i=0;i<min.size();i++){
        tree1= insert(tree1,min.at(i));
    }




    return 0;
}//planning