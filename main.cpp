#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>

using namespace std;

class document
{
public:
    vector<string> contents;
    vector<int> hash;

    document()
    {
        bool flag = false;
        while(!flag)
        {
            string path;
            cout << "Enter path for dataset (eg ../datasets/text1.txt): ";
            cin >> path;
            string line;
            ifstream file(path);
            if (file.good())
            {
                flag = true;
                while (getline(file, line)) {
                    this->contents.push_back(line);
                }
            }
            else
            {
                cout << "File not found! Please enter a valid path!" << endl;
            }
        }
    }
    void print()
    {
        for (string i : this->contents)
        {
           cout << i << endl;
        }
    };
};

int main()
{
    document doc1;
    doc1.print();

}
