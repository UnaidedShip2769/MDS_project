#include <iostream>
#include <vector>
#include "LSH.hpp"
#include "KDtree.hpp"
#include "Interface.hpp"


int main() {
    using namespace std;
    vector<vector<vector<int>>>sign;
    vector<node*>trees;
    char* direcory="../data";
    vector<string>vocub;
    vector<string> textFileNames;
    get_data(direcory,sign,3,textFileNames,vocub);
    make_KD_trees(sign,trees,2);

    cout<<"pedafari";

    return 0;
}//planning

