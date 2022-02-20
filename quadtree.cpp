#include "quadtree.hpp"
#include <iostream>
#include <vector>
#include <math.h>
#include <stack>

using namespace std;

vector<vector<DimensionSpace>> Quadtree::makeNewDimensionSpaces()
{
    int num = pow(2,this->dimension);
    DimensionSpace newRanges[num][this->dimension];
    for(int i = 0; i < this->dimension; i++)
    {
        bool flag = false;
        for (int j = 0; j < pow(2,this->dimension); j++)
        {
            if(j % (i+1) == 0)
            {
                if(flag == false)
                {
                    flag = true;
                }
                else if (flag == true)
                {
                    flag = false;
                }
            }
            if (flag == false)
            {
                newRanges[j][i].start = this->boundrySpace.at(i).start;
                newRanges[j][i].end = this->head.contents.at(i);
            }
            else
            {
                newRanges[j][i].start = this->head.contents.at(i);
                newRanges[j][i].end = this->boundrySpace.at(i).end;
            }
        }
    }

    vector<vector<DimensionSpace>> newVectorRanges;
    for(int j = 0; j < pow(2,this->dimension); j++)
    {
        vector<DimensionSpace> b;
        for(int i = 0; i < this->dimension; i++)
        {
            DimensionSpace a (newRanges[j][i].start, newRanges[j][i].end);
            b.push_back(a);
        }
        newVectorRanges.push_back(b);
    }
    return newVectorRanges;
};

QuadNode::QuadNode(vector<float> numbers)
{
    this->contents = numbers;
}

QuadLeaf::QuadLeaf(vector<DimensionSpace> boundrySpace)
{
    this->boundrySpace = boundrySpace;
}

DimensionSpace::DimensionSpace(float start, float end)
{
    this->start = start;
    this-> end = end;
}

Quadtree::Quadtree(int dimensions, vector<DimensionSpace> boundrySpace)
{
    bool flag = false;
    while(!flag)
    {
        if (dimensions < 2)
        {
            cout << "Error!!! Dimension value less than 2!" << endl;
        }
        else
        {
            this->dimension = dimensions;
            flag = true;
            int i = 0;
            for(DimensionSpace &dim : boundrySpace)
            {
                this->boundrySpace.push_back(dim);
                this->head.contents.push_back((this->boundrySpace.at(i).end + this->boundrySpace.at(i).start) / 2);
                i++;
            }
            vector<vector<DimensionSpace>> newDimensionSpaces = this->makeNewDimensionSpaces();
            for (vector<DimensionSpace> i : newDimensionSpaces)
            {
                this->head.leaves.push_back(i);
            }
        }
    }
}

Quadtree::Quadtree(int dimensions)
{
    bool flag = false;
    while(!flag)
    {
        if (dimensions < 2)
        {
            cout << "Error!!! Dimension value less than 2!" << endl;
        }
        else
        {
            this->dimension = dimensions;
            flag = true;
            for(int i = 0; i < dimensions; i++)
            {
                int dimentionStart;
                int dimentionEnd;
                cout << "Enter the start value for dimension number " << i+1 << ": ";
                cin >> dimentionStart;
                cout << "Enter the end value for dimension number " << i+1 << ": ";
                cin >> dimentionEnd;
                DimensionSpace dim (dimentionStart, dimentionEnd);
                this->boundrySpace.push_back(dim);
                this->head.contents.push_back((this->boundrySpace.at(i).end + this->boundrySpace.at(i).start) / 2);
            }
            vector<vector<DimensionSpace>> newDimensionSpaces = this->makeNewDimensionSpaces();
            for (vector<DimensionSpace> i : newDimensionSpaces)
            {
                this->head.leaves.push_back(i);
            }
        }
    }
}

Quadtree::Quadtree(int dimensions, set<string> &vocub)
{
    bool flag = false;
    while(!flag)
    {
        if (dimensions < 2)
        {
            cout << "Error!!! Dimension value less than 2!" << endl;
        }
        else
        {
            this->dimension = dimensions;
            flag = true;
            for(int i = 0; i < dimensions; i++)
            {
                DimensionSpace dim (0, vocub.size());
                this->boundrySpace.push_back(dim);
                this->head.contents.push_back((this->boundrySpace.at(i).end + this->boundrySpace.at(i).start) / 2);
            }
            vector<vector<DimensionSpace>> newDimensionSpaces = this->makeNewDimensionSpaces();
            for (vector<DimensionSpace> i : newDimensionSpaces)
            {
                this->head.leaves.push_back(i);
            }
        }
    }
}

void Quadtree::print()
{
    cout << "QuadNode contents: ";
    int k = 0;
    for(float &j : this->head.contents)
    {
        cout << j;
        k++;
        if(k < this->head.contents.size())
        {
            cout << "-";
        }
    }
    cout << endl;
    cout << "boundrySpace: " << endl;
    for (DimensionSpace &i : this->boundrySpace)
    {
        cout << i.start << "-" << i.end << endl;
    }
    for (QuadLeaf &j : this->head.leaves)
    {
        int k = 0;
        cout << "QuadLeaf contents: ";
        for (int i : j.contents)
        {
            cout << i;
            k++;
            if(k < j.contents.size())
            {
                cout << ",";
            }
        }
        cout << "\t\tTimes inserted: " << j.timesInserted << endl;
    }
    cout << endl;
    for (Quadtree &i : this->subtrees)
    {
        i.print();
    }
}

bool inSpace(vector<DimensionSpace> boundrySpace, vector<float> number)
{
    int j = 0;
    bool inSpace = true;
    for(DimensionSpace &dimension : boundrySpace)
    {
        if(!(number.at(j) >= dimension.start && number.at(j) <= dimension.end))
        {
            inSpace = false;
            break;
        }
        j++;
    }
    return inSpace;
}

void Quadtree::insertnumber(vector<float> number)
{
    if (!inSpace(this->boundrySpace, number))
    {
        return;
    }
    else
    {
        int leafnum = 0;
        for(QuadLeaf &i : this->head.leaves)
        {
            bool flag = true;
            int k = 0;
            for(DimensionSpace &j : i.boundrySpace)
            {
                if(!(number.at(k) >= j.start && number.at(k) <= j.end))
                {
                    flag = false;
                    break;
                }
                k++;
            }
            if(flag == true)
            {
                if(i.used == false)
                {
                    i.used = true;
                    for (int num : number)
                    {
                        this->head.leaves.at(leafnum).contents.push_back(num);
                    }
                    this->head.leaves.at(leafnum).timesInserted++;
                }
                else
                {
                    if(this->subtrees.empty())
                    {
                        Quadtree a (this->dimension, i.boundrySpace);
                        a.insertnumber(number);
                        this->subtrees.push_back(a);
                        this->update(i);
                    }
                    else
                    {
                        bool okay = false;
                        for(Quadtree &subtree : this->subtrees)
                        {
                            if(inSpace(subtree.boundrySpace, number))
                            {
                                okay = true;
                                subtree.insertnumber(number);
                            }
                        }
                        if(!okay)
                        {
                            Quadtree a (this->dimension, i.boundrySpace);
                            a.insertnumber(number);
                            this->subtrees.push_back(a);
                            this->update(i);
                        }
                    }
                }
            }
            leafnum++;
        }
    }
}

void Quadtree::insert(vector<float> number)
{
    int temp = 0;
    if(!this->search(number, true, temp))
    {
        this->insertnumber(number);
    }
}

void Quadtree::delete_element(vector<float> deleteNumber)
{
    vector<vector<float>> reinserts;
    this->find_and_remove_elements(deleteNumber, reinserts);
    reinsert_elements(reinserts);
}

void Quadtree::reinsert_elements(vector<vector<float>> &reinserts)
{
    for (vector<float> temp : reinserts)
    {
        this->insertnumber(temp);
    }
}

bool Quadtree::find_and_remove_elements(vector<float> deleteNumber, vector<vector<float>> &reinserts)
{
    bool flag = true;
    bool found = false;
    for(QuadLeaf &tempLeaf : this->head.leaves)
    {
        if(tempLeaf.contents == deleteNumber)
        {
            tempLeaf.contents.clear();
            tempLeaf.used = false;
            found = true;
            break;
        }
    }
    if(found)
    {
        for(QuadLeaf &tempLeaf : this->head.leaves)
        {
            if(!(tempLeaf.contents.empty()))
            {
                reinserts.push_back(tempLeaf.contents);
                tempLeaf.contents.clear();
                tempLeaf.used = false;
            }
        }
    }
    else
    {
        int index = 0;
        for(Quadtree &tempQuadtree : this->subtrees)
        {
            flag = tempQuadtree.find_and_remove_elements(deleteNumber, reinserts);
            if(flag)
            {
                this->subtrees.clear();
                this->head.leaves.at(index).used = false;
            }
            index++;
        }
    }
    for(QuadLeaf tempLeaf : this->head.leaves)
    {
        if (!tempLeaf.used == false)
        {
            flag = false;
            break;
        }
    }
    return flag;
}

void Quadtree::update(QuadLeaf &leaf)
{
    if(leaf.used == true && !(this->subtrees.empty()))
    {
        for(Quadtree &subtree : this->subtrees)
        {
            subtree.insert(leaf.contents);
        }
        vector<float>content = leaf.contents;
        leaf.contents.clear();
        int temp = 0;
        for(int i = 0; i < leaf.timesInserted-1; i++)
        {
            this->search(content, true, temp);
        }
        leaf.timesInserted = 0;
    }
}

float distance(QuadNode node, vector<float> searchNumber, int dimension)
{
    float result = 0;
    for(int i = 0; i < dimension; i++)
    {
        result += pow(searchNumber.at(i) - node.contents.at(i), 2);
    }
    result = sqrt(result);
    return result;
}

float distance(QuadLeaf leaf, vector<float> searchNumber, int dimension)
{
    float result = 0;
    for(int i = 0; i < dimension; i++)
    {
        result += pow(searchNumber.at(i) - leaf.contents.at(i), 2);
    }
    result = sqrt(result);
    return result;
}

vector<float> Quadtree::NN(vector<float> searchNumber)
{
    float r = 50000;
    QuadLeaf result;
    stack<Quadtree> searchStack;
    searchStack.push(*this);
    while(!searchStack.empty())
    {
        Quadtree tempTree = searchStack.top();
        searchStack.pop();
        for(Quadtree tempChild : tempTree.subtrees)
        {
            if(distance(tempChild.head, searchNumber, this->dimension) < r)
            {
                searchStack.push(tempChild);
            }
        }
        for(QuadLeaf tempLeaf : tempTree.head.leaves)
        {
            if(!tempLeaf.contents.empty())
            {
                if(distance(tempLeaf, searchNumber, this->dimension) < r)
                {
                    r = distance(tempLeaf, searchNumber, this->dimension);
                    result = tempLeaf;
                }
            }
        }
    }
    return result.contents;
}

bool Quadtree::search(vector<float> searchNumber, bool increment, int &timesinserted)
{
    bool found = false;
    for (QuadLeaf &tempLeaf : this->head.leaves)
    {
        if (tempLeaf.contents == searchNumber)
        {
            found = true;
            if(increment)
            {
                tempLeaf.timesInserted++;
            }
            timesinserted = tempLeaf.timesInserted;
            break;
        }
    }
    if(!found)
    {
        for (Quadtree &tempQuadtree : this->subtrees)
        {
            found = tempQuadtree.search(searchNumber, increment, timesinserted);
            if(found)
            {
                break;
            }
        }
    }
    return found;
}