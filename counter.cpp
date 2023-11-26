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
#define DAY_OFFSET 2

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

vector<float> cal_avg(vector<vector<int>> list){

    vector<float> avg_per_month;
    float sum = 0;

    for(int i = 1; i < list.size(); i++){
        for(int j = 0; j < 6; j++){
            sum += list[i][j + HOUR_OFFSET];
        }
        if(list[i][DAY_OFFSET] == 30){
            avg_per_month.push_back(sum/30);
            sum = 0;
        }
    }

    return avg_per_month;
}


int main(int argc, char* argv[]){
    rapidcsv::Document counter(argv[1], rapidcsv::LabelParams(-1, -1));
    vector<vector<int>> usage_stats;
    for(int i = 1; i <= 360; i++){
        usage_stats.push_back(counter.GetRow<int>(i));
    }
    
    int peak_hour = cal_peak(usage_stats);              //Calculated based of the whole year usage
    vector<float> avg_usage = cal_avg(usage_stats);     //Calculates per month average usage
    
}