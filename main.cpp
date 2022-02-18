#include <iostream>
#include <vector>
#include "LSH.hpp"
#include "quadtree.hpp"
#include <stack>
#include <chrono>
#include "KDtree.hpp"
#include "Interface.hpp"
#include "KDtree.hpp"
#include "RangeTree.h"
#include "Files.hpp"

using namespace std;
using namespace std::chrono;

int main()
{
    /*
    vector<float> number1;
    number1.push_back(1);
    number1.push_back(1);
    vector<float> number2;
    number2.push_back(99);
    number2.push_back(99);
    vector<float> number3;
    number3.push_back(1);
    number3.push_back(99);
    vector<float> number4;
    number4.push_back(99);
    number4.push_back(1);
    vector<float> number5;
    number5.push_back(24);
    number5.push_back(24);
    vector<float> number6;
    number6.push_back(23);
    number6.push_back(23);
    vector<float>number7;
    number7.push_back(22);
    number7.push_back(22);
    vector<float>number8;
    number8.push_back(10);
    number8.push_back(10);
    vector<float>number9;
    number9.push_back(49);
    number9.push_back(49);
    vector<float>number10;
    number10.push_back(48);
    number10.push_back(48);

    Quadtree quad1(2);
    quad1.insert(number1);
    quad1.insert(number1);
    quad1.insert(number1);
    quad1.insert(number2);
    quad1.insert(number3);
    quad1.insert(number4);
    quad1.insert(number1);
    quad1.insert(number5);
    quad1.insert(number6);
    quad1.insert(number7);
    quad1.insert(number8);
    quad1.insert(number9);
    quad1.insert(number10);
    quad1.insert(number1);
    quad1.print();
    int foundtimes = 0;

    vector<float> result = quad1.NN({2,2});
    for(float res : result)
    {
        cout << res << ",";
    }
    cout << endl;*/
    /*for(float number : result)
    {
        cout << number << " ";
    }*/
    //cout << result << endl;
    //quad1.delete_element(number6);
    //quad1.print();

    /*quad1.insert(number)
    quad1.update();
    quad1.insert(number2);
    quad1.update();
    quad1.kNN(number2);
    quad1.delete_element(number);
    quad1.update();
    quad1.print();*/

    auto start = high_resolution_clock::now();

    vector<node*>kdtrees;
    vector<Quadtree> quadtrees;

    int stat=Interface(kdtrees, quadtrees);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
    /*cout << "Reading files from directory ../data" << endl;
    char* directory="../data";
    vector<File*> textFileNames=get_files(directory);
    vector<vector<vector<int>>>sign;
    set<string>vocub;
    set<int> userset = getUser_tags();
    vector<File*> textFilePruned=prune_files(textFileNames, userset);*/


    return 0;
}
