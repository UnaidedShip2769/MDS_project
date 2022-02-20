#include <vector>
#include "quadtree.hpp"
#include <chrono>
#include "KDtree.hpp"
#include "Interface.hpp"
#include "KDtree.hpp"

using namespace std;
using namespace std::chrono;

int main()
{
    //auto start = high_resolution_clock::now();

    vector<node*>kdtrees;
    vector<Quadtree> quadtrees;

    int stat=Interface(kdtrees, quadtrees);

    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds>(stop - start);

    //cout << "Time taken by function: "
    //     << duration.count() << " microseconds" << endl;

    return 0;
}