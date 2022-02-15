//
// Created by peri on 3/2/22.
//

#include <vector>
#include <algorithm>
#include <string>
#include <dirent.h>
#include "Files.hpp"
#include <iostream>

using namespace std;

vector<File*> get_files(char* path){
    vector<File*>files;
    bool add_tags_manualy=true;
    cout << "do you want to add tags manually? \n Yes-->1 \n No-->0" << endl;
    cin >> add_tags_manualy;
    string temp;
    File* tmp;
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(path))!=NULL){
        while((ent= readdir(dir))!=NULL){
            temp=path;
            temp+='/';
            temp+=ent->d_name;
            if((temp!="../data/..")&&(temp!="../data/.")){
                tmp=createFile(temp,files.size());
                if(add_tags_manualy)
                    tmp->tags=get_tags(temp);
                files.push_back(tmp);
            }

        }
        closedir(dir);
    }
    else {
        /* could not open directory */
        perror ("could not open directory");
    }

    return files;
}

File* createFile(string path,int id){
    File* file = new File;
    file->path=path;
    file->id=id;
}

set<int> get_tags(string path){
    set<int> tags;
    int tag;
    while(true){
        cout << "for file:"<< path <<"\n input a tag \n 1 -> football \n 2 -> basketball \n 3 -> sport \n 4 -> movie \n 0 -> no tag \n";
        cin >> tag;
        if(tag==0)
            break;
        tag--;
        tags.insert(tag);


    }
}

vector<File*> prune_files(vector<File*> &textFiles,set<int> tags){
    if(tags.size()==0)
        return textFiles;
    vector<File*> Files;
    for(int i=0;i<textFiles.size();i++){
        if(set_compare(tags,textFiles.at(i)->tags)==1)
            Files.push_back(textFiles.at(i));
    }
    return Files;

}

bool set_compare(set<int> &lhs, set<int> &rhs){
    return lhs.size() == rhs.size()
           && equal(lhs.begin(), lhs.end(), rhs.begin());
}

void add_tags(vector<File*> &textFiles){



}