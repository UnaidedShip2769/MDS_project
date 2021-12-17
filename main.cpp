#include <iostream>
#include <vector>
#include "LSH.hpp"
#include "KDtree.hpp"


int main() {
    using namespace std;
    char* direcory="../data";
    vector<string>files= get_files(direcory);
    vector<vector<char>> t = get_words(files.at(0));

    vector<string>vocub;


    vector<vector<string>> s1= Shingling(t,3);





    vector<vector<int>>min;
    min= get_sig(s1,vocub);


    node* tree1=NULL;
    for (int i=0;i<min.size();i++){
        tree1= insert(tree1,min.at(i));
    }




    return 0;
}//planning