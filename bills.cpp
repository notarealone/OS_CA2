#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <filesystem>
#include "rapidcsv.h"

using namespace std;

int main(int argc, char* argv[]){

    rapidcsv::Document bills("bills.csv", rapidcsv::LabelParams(0, 0));

    vector<int> gas_price = bills.GetColumn<int>("gas");
    vector<int> elec_price = bills.GetColumn<int>("electricity");
    vector<int> water_price = bills.GetColumn<int>("water");
    
}