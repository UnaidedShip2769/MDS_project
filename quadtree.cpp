//
// Created by Gregory on 12/3/2021.
//

#include "quadtree.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <math.h>

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
        cout << endl;
        newVectorRanges.push_back(b);
    }
    return newVectorRanges;
};

QuadNode::QuadNode(vector<int> numbers)
{
    this->contents = numbers;
}

//QuadLeaf::QuadLeaf(vector<int> numbers)
//{
//    this->contents = numbers;
//}

QuadLeaf::QuadLeaf(vector<DimensionSpace> boundrySpace)
{
    this->boundrySpace = boundrySpace;
    //for (DimensionSpace i : this->boundrySpace)
   // {
        //int median = (i.start + i.end) / 2;
        //this->contents.push_back(median);
    //}
}

DimensionSpace::DimensionSpace(int start, int end)
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
            int numberofsubtrees = 2 ^ dimensions;
            int i = 0;
            for(DimensionSpace dim : boundrySpace)
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
            int numberofsubtrees = 2 ^ dimensions;
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

void Quadtree::print()
{
    //cout << "Printing!!!" << endl;
    cout << "QuadNode contents: ";
    int k = 0;
    for(int j : this->head.contents)
    {
        cout << j;
        k++;
        if(k < this->head.contents.size())
        {
            cout << "-";
        }
    }
    cout << endl;
    for (QuadLeaf j : this->head.leaves)
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
        cout << endl;
    }
    cout << endl;
    for (Quadtree i : this->subtrees)
    {
        i.print();
    }
}

void Quadtree::insert(vector<int> number)
{
    //cout << "Inserting!!" << endl;
    int j = 0;
    bool inSpace = true;
    for(DimensionSpace dimension : this->boundrySpace)
    {
        if(!(j >= dimension.start && j <= dimension.end))
        {
            inSpace = false;
        }
        j++;
    }
    if (!inSpace)
    {
        cout << "Error!!! The point doesn't fit in the boundries of the tree!" << endl;
        return;
    }
    else
    {
        int leafnum = 0;
        for(QuadLeaf i : this->head.leaves)
        {
            bool flag = true;
            int k = 0;
            for(DimensionSpace j : i.boundrySpace)
            {
                if(!(number.at(k) >= j.start && number.at(k) <= j.end))
                {
                    flag = false;
                }
                k++;
            }
            if(flag == true)
            {
                cout << "Flag = true" << endl;
                if(i.contents.empty())
                {
                    cout << "Found empty contents" << endl;
                    //i.contents = number;
                    for (int num : number)
                    {
                        cout << "Pushing back number" << endl;
                        this->head.leaves.at(leafnum).contents.push_back(num);
                    }
                }
                else
                {
                    cout << "Splitting!!!" << endl;
                    vector<vector<DimensionSpace>> newVectorRanges = this->makeNewDimensionSpaces();
                    for(vector<DimensionSpace> l : newVectorRanges)
                    {
                        Quadtree a (this->dimension, l);
                        this->subtrees.push_back(a);
                        cout << "Created new quadtree!" << endl;
                        a.insert(number);
                    }
                }
            }
            leafnum++;
        }
    }
}

void Quadtree::delete_element(vector<int> number)
{

}

void Quadtree::update()
{

}

void Quadtree::kNN(vector<int> number)
{

}