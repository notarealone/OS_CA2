#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;



void extract_buildings(vector<string>&buildings, string path){
    for (const auto & entry : fs::directory_iterator(path)){
        struct stat sb;
        string s = entry.path().string();
        const char* temp_path = s.c_str();
        if ((stat(temp_path, &sb) == 0) && (sb.st_mode & S_IFDIR)){
            int pos = 0;
            while(pos < s.size()){
                pos = s.find("/");
                s.erase(0, pos+1);
            }
            buildings.push_back(s);

        }
    }
}


int main(int argc, char* argv[]){
    string buildings_path = argv[1];
    struct stat sb;
    vector<string> Buildings;
    extract_buildings(Buildings, buildings_path);
    for(int i = 0; i < Buildings.size(); i++){
        cout << Buildings[i] << "\n";
    }


    return 0;
}