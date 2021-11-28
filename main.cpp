#include <iostream>
#include <vector>
#include <set>
#include "LSH.hpp"


int main() {

    using namespace std;
    vector<char> text= read_text("../data/test.txt");
    vector<char> text2= read_text("../data/test2.txt");
    vector<set<string>> s1= Shingling(text,3);
    vector<set<string>> s2= Shingling(text2,3);
    set<string> vocub;

    Merge(s1,vocub);
    Merge(s2,vocub);


    return 0;
}

