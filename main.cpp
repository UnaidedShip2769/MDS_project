#include <iostream>
#include <vector>
#include "LSH.hpp"
#include "KDtree.hpp"
#include "Interface.hpp"
#include <chrono>
#include "RangeTree.h"
#include "Files.hpp"


int main() {

    using namespace std;

    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    vector<node*>trees;

    int stat=Interface(trees);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;





    return 0;
}//planning

