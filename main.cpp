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

#define EFFECT_END "\033[0m"
#define BOLD_RED "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define UNDERLINED_WHITE "\033[4;37m"


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

vector<string> get_requests(string line){
    vector<string> requests;
    int pos = 0;
    while ((pos = line.find(" ")) != string::npos) {
        requests.push_back(line.substr(0, pos));
        line.erase(0, pos + 1);
    }
    requests.push_back(line);
    return requests;
}

int main(int argc, char* argv[]){
    string buildings_path = argv[1];
    struct stat sb;
    vector<string> Buildings;
    extract_buildings(Buildings, buildings_path);

    cout << BOLD_YELLOW << "Amount of Buildings Found : " << EFFECT_END << BOLD_GREEN << Buildings.size() << EFFECT_END << endl << endl;
    cout << BOLD_RED << "Buildings' Names are as follow : " << EFFECT_END << endl;
    for(int i = 0; i < Buildings.size(); i++){
        cout << UNDERLINED_WHITE << Buildings[i] << EFFECT_END << ", ";
    }
    cout << endl << endl << BOLD_GREEN << "Enter the resources and buildings you are looking for : " << EFFECT_END << endl;
    string input_line;
    getline(cin, input_line); //Gets space-seperated input from user
    vector<string> resource_requests = get_requests(input_line);
    getline(cin, input_line);
    vector<string> building_requests = get_requests(input_line); //Assumption -> resource and building requests are mapped 1 by 1


    return 0;
}