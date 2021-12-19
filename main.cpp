#include <iostream>
#include <vector>
#include "LSH.hpp"
#include "KDtree.hpp"


int main() {
    using namespace std;
    vector<vector<vector<int>>>texts;
    vector<node*>trees;



    char* direcory="../data";
    get_data(direcory,texts,3);
    //make_trees(direcory,trees,3,2);





    return 0;
}//planning