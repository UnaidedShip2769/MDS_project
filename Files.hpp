//
// Created by peri on 3/2/22.
//

#ifndef MDS_PROJECT_FILES_HPP
#define MDS_PROJECT_FILES_HPP

#include <set>
#include <algorithm>

using namespace std;
typedef struct file{
    string path;
    set<int> tags;
    int id;
}File;
vector<File*> get_files(char* path);
File* createFile(string path,int id);
bool set_compare(set<int> &inputtags, set<int> &textfiletags);
vector<File*> prune_files(vector<File*> &textFiles,set<int> tags);
void add_tags(File* &textFile);
void set_tags(vector<File *> &files);
#endif //MDS_PROJECT_FILES_HPP
