#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <filesystem>
#include "rapidcsv.h"

#define ARG_OFFSET 1

#define WRITE_PIPE 1
#define READ_PIPE 0

#define MAX_LENGTH 100
#define BUFFER_LEN 2048

using namespace std;

int main(int argc, char* argv[]){
    string building_name = argv[1];
    string folder_path = "buildings/";
    vector<string> csv_path;

    for(int i = 2; i < argc; i++){
        csv_path.push_back(folder_path + building_name);
    }

    //TO DO

    int building_pipes[argc - 2][2];
    pid_t pid;
    for(int i = 2; i < argc; i++){
        if(pipe(building_pipes[i]) == -1){
            exit(EXIT_FAILURE);
        }
        pid = fork();
        if(pid == 0){
            close(building_pipes[i][READ_PIPE]);
            dup2(building_pipes[i][WRITE_PIPE], STDOUT_FILENO);
            char* exec_path = const_cast<char*>("./counter.o");
            char* exec_arg[] = {const_cast<char*>(argv[i]), NULL};
            execvp(exec_path, exec_arg);
            exit(EXIT_FAILURE); // runs only when exec() runs into a problem
        }
    }

    //TO DO
}