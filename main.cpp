#include <iostream>
#include <vector>
#include <set>
#include "LSH.hpp"
#include "quadtree.hpp"
#include <stack>

int main()
{
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

    bool result = quad1.search(number1, false, foundtimes);
    if (result)
    {
        cout << "Found the number searched for " << foundtimes << " times!" << endl;
    }
    else
    {
        cout << "404" << endl;
    }
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

    return 0;
}



/*int main() {
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
    min= minhash(onehot1,3);

    return 0;
}//planning*/
