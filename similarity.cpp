//
// Created by peri on 17/12/21.
//
#include <vector>
#include <algorithm>
using namespace std;
double JaccardCoefficient(vector<char> w1,vector<char> w2,vector<int>s1,vector<int>s2){
    vector<char> tmp;
    int inter;
    int un;
    set_intersection(w1.begin(),w1.end(),w2.begin(),w2.end(), back_inserter(tmp));
    inter=tmp.size();
    tmp.clear();
    set_union(w1.begin(),w1.end(),w2.begin(),w2.end(), back_inserter(tmp));
    un=tmp.size();
    double j1=inter/un;
    vector<int>temp;
    set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(), back_inserter(temp));
    inter=temp.size();
    temp.clear();
    set_union(s1.begin(),s1.end(),s2.begin(),s2.end(), back_inserter(temp));
    un=temp.size();
    double j2=inter/un;
    return j1/j2;

}
double DSC(vector<char> w1,vector<char> w2,vector<int>s1,vector<int>s2){
    vector<char> tmp;
    int inter;
    set_intersection(w1.begin(),w1.end(),w2.begin(),w2.end(), back_inserter(tmp));
    inter=tmp.size();
    double j1=(2*inter)/(w1.size()+w2.size());
    vector<int>temp;
    set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(), back_inserter(temp));
    inter=temp.size();
    double j2=(2*inter)/(s1.size()+s2.size());
    return j1/j2;

}