//
// Created by Gregory on 12/3/2021.
//

#include "quadtree.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <set>
#include <math.h>

using namespace std;

QuadNode::QuadNode(vector<int> numbers)
{
    this->contents = numbers;
}

QuadLeaf::QuadLeaf(vector<int> numbers)
{
    this->contents = numbers;
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
                //int dimentionStart;
                //int dimentionEnd;
                //cout << "Enter the start value for dimension number " << i+1 << ": ";
                //cin >> dimentionStart;
                //cout << "Enter the end value for dimension number " << i+1 << ": ";
                //cin >> dimentionEnd;
                //DimensionSpace dim (dimentionStart, dimentionEnd);
                this->boundrySpace.push_back(dim);
                this->head.contents.push_back((this->boundrySpace.at(i).end + this->boundrySpace.at(i).start) / 2);
                i++;
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
        if(this->head.leaves.size() < this->dimension)
        {
            cout << "Entering number!" << endl;
            this->head.leaves.push_back(number);
        }
        else
        {
            int num = pow(2,this->dimension);
            DimensionSpace newRanges[num][this->dimension];
            //for(int i = 0; i < 2^this->dimension; i++)
           //{
                //DimensionSpace a (0,0);
                //for(int j = 0; j < this->dimension; j++)
                //{
                //    newRanges[i].push_back(a);
                //}
           // }
            //cout << "Dimension is " << (2^this->dimension) << endl;
            for(int i = 0; i < this->dimension; i++)
            {
               // cout << "Entering Values for " << i << "st Dimention"<< endl;
                bool flag = false;
                for (int j = 0; j < pow(2,this->dimension); j++)
                {
                    //cout << "Entering " << j << "st combination" << endl;
                    int number = pow(2,i);
                    if(j % (i+1) == 0)
                    {
                        if(flag == false)
                        {
                            flag = true;
                            //cout << "Hit if" << endl;
                        }
                        else if (flag == true)
                        {
                            //cout << "Hit else if" << endl;
                            flag = false;
                        }
                        //cout << "Hit if" << endl;
                        //newRanges[j][i].start = this->boundrySpace.at(i).start;
                        //newRanges[j][i].end = this->head.contents.at(i);
                        //DimensionSpace a (this->boundrySpace.at(i).start, this->head.contents.at(i));
                        //newRanges[j].at(i) = a;
                        //cout << "Combination: " << a.start << "-" << a.end << endl;
                    }
                    if (flag == false)
                    {
                        newRanges[j][i].start = this->boundrySpace.at(i).start;
                        newRanges[j][i].end = this->head.contents.at(i);
                    }
                    else
                    {
                       // cout << "Hit else" << endl;
                        newRanges[j][i].start = this->head.contents.at(i);
                        newRanges[j][i].end = this->boundrySpace.at(i).end;
                        //DimensionSpace a (this->head.contents.at(i), this->boundrySpace.at(i).end);
                        //newRanges[j].at(i) = a;
                        //cout << "Combination: " << a.start << "-" << a.end << endl;;
                    }
                }

                //vector<DimensionSpace> newDimensionRange;
                //newDimensionRange.push_back(DimensionSpace(this->boundrySpace.at(i).start, this->head.contents.at(i)));
                //newDimensionRange.push_back(DimensionSpace(this->head.contents.at(i), this->boundrySpace.at(i).start));
                //newRanges.push_back(newDimensionRange);
            }

            vector<vector<DimensionSpace>> newVectorRanges;
            for(int j = 0; j < pow(2,this->dimension); j++)
            {
                vector<DimensionSpace> b;
                for(int i = 0; i < this->dimension; i++)
                {
                    DimensionSpace a (newRanges[j][i].start, newRanges[j][i].end);
                    //cout <<  a.start << "-" << a.end << " , ";
                    b.push_back(a);
                }
                cout << endl;
                newVectorRanges.push_back(b);
            }

            /*for(int i = 0; i < pow(2,this->dimension-1); i++)
            {
                cout << i << "st combination" << endl;
                for(int j = 0; j < this->dimension; j++)
                {
                    cout << newRanges[i][j].start << "-" << newRanges[i][j].end << endl;
                }
            }*/

            for(vector<DimensionSpace> i : newVectorRanges)
            {
                Quadtree a (this->dimension, i);
                this->subtrees.push_back(a);
                cout << "Created new quadtree!" << endl;
                a.insert(number);
            }
        }
    }

   /*else
    {
        if(this->subtrees.empty())
        {
            this->head.leaves.push_back(number);
        }
        else
        {

        }
    }


    bool inSpace = true;
    int j = 0;
    for(int i : number)
    {
        if (!(i >= this->boundrySpace.at(j).start && i <= this->boundrySpace.at(j).end))
        {
            inSpace = false;
        }
        j++
    }
    if (!inSpace)
    {
        cout << "Error!!! The point doesn't fit in the boundries of the tree!" << endl;
        return;
    }
     if ((this->subtrees.size() + this->head.leaves.size()) < 2^this->dimension)
    {
        QuadLeaf leaf(number);
        this->head.leaves.push_back(leaf);
    }
    else
    {
        for (Quadtree i : this->subtrees)
        {
            for(int j : number)
            {
                if(j >= i.boundrySpace.at(j).start && j <= i.boundrySpace.at(j).end)
                {
                    i.insert(number);
                }
            }
        }
    }*/
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