#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <filesystem>
#include "rapidcsv.h"

#define HOUR_OFFSET 3

using namespace std;

int cal_peak(vector<vector<int>> list){

    int time[6] = {0, 0, 0, 0, 0, 0};
    int temp_max = 0;
    int temp_max_index = 0;

    for(int i = 1; i < list.size(); i++){
        temp_max = list[i][0 + HOUR_OFFSET];
        temp_max_index = 0;
        for(int j = 0; j < 6; j++){
            if(list[i][j] > temp_max){
                temp_max = list[i][j + HOUR_OFFSET];
                temp_max_index = j;
            }
        }
        time[temp_max_index] += 1;
    }
    temp_max = 0;
    temp_max_index = 0;
    for(int i = 0; i < 6; i++){
        if(temp_max < time[i]){
            temp_max = time[i];
            temp_max_index = i;
        }
    }

    return temp_max_index;
}

int main(int argc, char* argv[]){
    rapidcsv::Document water("Water.csv", rapidcsv::LabelParams(-1, -1));
    vector<vector<int>> usage_stats;
    for(int i = 1; i <= 360; i++){
        usage_stats.push_back(water.GetRow<int>(i));
    }
    
    int peak_hour = cal_peak(usage_stats); //Calculated based of the whole year usage
    
}