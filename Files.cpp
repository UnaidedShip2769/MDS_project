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

vector<string> tag_names={"Football","Basketball","Sports","Movies"};

vector<File*> get_files(char* path){
    vector<File*>files;
    int add_tags_manually=1;
    cout << "Do you want to add tags to your files manually? \n 0. No \n 1. Yes\nPlease choose by entering 0 or 1: " << endl;
    cin >> add_tags_manually;
    while(add_tags_manually != 0 && add_tags_manually != 1)
    {
        cout << "Please enter a valid number!!!" << endl << "Please choose by entering 0 or 1: " << endl;
        cin >> add_tags_manually;
    }
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
                add_tags(tmp);
                files.push_back(tmp);
            }
        }
        if(add_tags_manually)
        {
            set_tags(files);
        }
        closedir(dir);
    }
    else {
        /* could not open directory */
        perror ("Could not open directory!");
    }

    return files;
}

File* createFile(string path,int id){
    File* file = new File;
    file->path=path;
    file->id=id;
}

void set_tags(vector<File *> &files)
{
    bool finish2 = false;
    while(!finish2)
    {
        cout << "Please enter the ID of the text file you want to change the tags for: ";
        int id;
        cin >> id;
        while(id > files.size()-1)
        {
            cout << "Please enter a valid ID!!!" << endl << "Please enter the ID of the text file you want to change the tags for: ";
            cin >> id;
        }
        cout << "The selected text file is: " << files.at(id)->path << endl;
        cout << "Please enter the tags you want to add to the file!" << endl <<" 1. Football" << endl << " 2. Basketball" << endl << " 3. Sports" <<
             endl << " 4. Movies" << endl << " 5. Print current tags" << endl << " 6. Save tags and move on to next text" << endl << " 0. Save and exit" << endl;
        bool finish = false;
        int selection;
        while(!finish)
        {
            cout << "Please enter a number from 0 to 6: ";
            cin >> selection;
            switch(selection)
            {
                case 1:
                {
                    files.at(id)->tags.insert(1);
                    cout << "Added tag: Football!" << endl;
                    break;
                }
                case 2:
                {
                    files.at(id)->tags.insert(2);
                    cout << "Added tag: Basketball!" << endl;
                    break;
                }
                case 3:
                {
                    files.at(id)->tags.insert(3);
                    cout << "Added tag: Sports!" << endl;
                    break;
                }
                case 4:
                {
                    files.at(id)->tags.insert(4);
                    cout << "Added tag: Movies!" << endl;
                    break;
                }
                case 5:
                {
                    for(int i : files.at(id)->tags)
                    {
                        cout << " " << i << ". " << tag_names.at(i-1) << endl;
                    }
                    break;
                }
                case 6:
                {
                    finish = true;
                    break;
                }
                case 0:
                {
                    finish=true;
                    finish2=true;
                    break;
                }
                default:
                {
                    cout << "Please enter a valid number!!!" << endl;
                    break;
                }
            }
        }
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

bool set_compare(set<int> &inputtags, set<int> &textfiletags){

    bool result = true;
    vector<bool> results;
    for(int i : inputtags)
    {
        auto found = textfiletags.find(i);
        if(found == textfiletags.end())
        {
            results.push_back(false);
        }
        else
        {
            results.push_back(true);
        }
    }
    for(bool temp : results)
    {
        if(temp == false)
        {
            result = false;
            break;
        }
    }
    return result;
}

void add_tags(File* &textFile){
    switch(textFile->id)
    {
        case 0:
        {
            //12AngryMen
            textFile->tags={4};
            break;
        }
        case 1:
        {
            //Baskets_movie
            textFile->tags={2,3,4};
            break;
        }
        case 2:
        {
            //DiegoMaradona
            textFile->tags={1,3};
            break;
        }
        case 3:
        {
            //FA_cup
            textFile->tags={1,3};
            break;
        }
        case 4:
        {
            //FIFA
            textFile->tags={1,3};
            break;
        }
        case 5:
        {
            //Fight_Club
            textFile->tags={4};
            break;
        }
        case 6:
        {
            //Forrest_Gump
            textFile->tags={4};
            break;
        }
        case 7:
        {
            //GeorgeBest
            textFile->tags={1,3};
            break;
        }
        case 8:
        {
            //Goodfellas
            textFile->tags={4};
            break;
        }
        case 9:
        {
            //Inception
            textFile->tags={4};
            break;
        }
        case 10:
        {
            //Kareem_Abdul-Jabbar
            textFile->tags={2,3};
            break;
        }
        case 11:
        {
            //LarryBird
            textFile->tags={2,3};
            break;
        }
        case 12:
        {
            //Manchester_United_F.C
            textFile->tags={1,3};
            break;
        }
        case 13:
        {
            //MichaelJordan
            textFile->tags={2,3};
            break;
        }
        case 14:
        {
            //NBA
            textFile->tags={2,3};
        }
        case 15:
        {
            //Premier_League
            textFile->tags={1,3};
            break;
        }
        case 16:
        {
            //Schindler _sList
            textFile->tags={4};
            break;
        }
        case 17:
        {
            //The_Good,_the_Bad_and_the_Ugly
            textFile->tags={4};
            break;
        }
        case 18:
        {
            //The_Lord_of_the_Rings__The_Fellowship_of_the_Ring
            textFile->tags={4};
            break;
        }
        case 19:
        {
            //The_Lord_of_the_Right__The_Return_of_the_King
            textFile->tags={4};
            break;
        }
        case 20:
        {
            //TheDarkKnight
            textFile->tags={4};
            break;
        }
        case 21:
        {
            //TheGodfather
            textFile->tags={4};
            break;
        }
        case 22:
        {
            //TheGodfatherPart2
            textFile->tags={4};
            break;
        }
        case 23:
        {
            //TheShawshankRedemption
            textFile->tags={4};
            break;
        }
        case 24:
        {
            //UEFA
            textFile->tags={2,3};
            break;
        }
        case 25:
        {
            //Vikings_Valhala
            textFile->tags={4};
            break;
        }
    }
}