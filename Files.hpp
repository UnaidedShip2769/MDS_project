//
// Created by peri on 3/2/22.
//

#ifndef MDS_PROJECT_FILES_HPP
#define MDS_PROJECT_FILES_HPP

#include <set>

using namespace std;
typedef struct file{
    string path;
    set<int> tags;
    int id;
}File;
vector<File*> get_files(char* path);
File* createFile(string path,int id);
set<int> get_tags(string path);
bool set_compare(set<int> &lhs, set<int> &rhs);
vector<File*> prune_files(vector<File*> &textFiles,set<int> tags);
void add_tags(vector<File*> &textFiles); //na to kanei o lampro
#endif //MDS_PROJECT_FILES_HPP
