//
// Created by peri on 17/12/21.
//
#include <vector>
#include <algorithm>
using namespace std;

float JaccardCoefficient(vector<int> s1,vector<int> s2){
    float inter;
    float un;
    vector<int>temp;
    set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(), back_inserter(temp));
    inter=temp.size();
    temp.clear();
    set_union(s1.begin(),s1.end(),s2.begin(),s2.end(), back_inserter(temp));
    un=temp.size();
    float j= inter/un;
    return j;
}