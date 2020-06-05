#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "prediction.h"

std::vector<float> readFile(std::string file_name, std::string actual_date);
std::vector<std::string> split(std::string s, char delim);
std::vector<std::string> previousDates7(std::vector<std::string> date);
std::vector<std::string> previousDates14(std::vector<std::string> date);

std::vector<std::string> previousDates7(std::vector<std::string> date){
  std::vector<std::string> date7;
  int day = std::stoi(date[1]);
  int month = std::stoi(date[0]);
  int year = std::stoi(date[2]);
  for(int i = 0; i < 7; i++){
    day--;
    if(day == 0){
      if(month == 1 || month == 5 || month == 7 || month == 10 || month == 12){
        month--;
        day = 30;
      } else if(month == 2 || month == 4 || month == 6 || month == 8 || month == 9 || month == 11){
        month--;
        day = 31;
      } else if (year % 4 == 0){
        day = 29;
      } else day = 28;
      if(month == 0){
        year--;
        month = 12;
        day = 31;
      }
    }
    std::string s = std::to_string(month) + "/" + std::to_string(day) + "/" + std::to_string(year);
    date7.push_back(s);
  }
  return date7;
}

std::vector<std::string> previousDates14(std::vector<std::string> date){
  std::vector<std::string> date14;
  int day = std::stoi(date[1]);
  int month = std::stoi(date[0]);
  int year = std::stoi(date[2]) - 1;

  for(int i = 0; i < 14; i++){
    day--;
    if(day == 0){
      if(month == 1 || month == 5 || month == 7 || month == 10 || month == 12){
        month--;
        day = 30;
      } else if(month == 2 || month == 4 || month == 6 || month == 8 || month == 9 || month == 11){
        month--;
        day = 31;
      } else if (year % 4 == 0){
        day = 29;
      } else day = 28;
      if(month == 0){
        year--;
        month = 12;
        day = 31;
      }
    }
    std::string s = std::to_string(month) + "/" + std::to_string(day) + "/" + std::to_string(year);
    date14.push_back(s);
  }
  return date14;
}

std::vector<std::string> split(std::string s, char delim) {
        std::stringstream ss(s);
        std::string item;
        std::vector<std::string> tokens;
        while(getline(ss, item, delim)) {
            tokens.push_back(item);
        }
        return tokens;
    }

std::vector<float> readFile(std::string file_name, std::string actual_date){
  std::vector<float> record;
  std::ifstream file;
  file.open(file_name);
  bool record_found = false;

  std::string field_one;
  std::string field_two;
  std::string field_three;
  std::string field_four;
  std::string field_five;

  while(getline(file, field_one, ',') && !record_found){
    getline(file, field_two, ',');
    getline(file, field_three, ',');
    getline(file, field_four, ',');
    getline(file, field_five, '\n');
    if(field_one == actual_date){
      record_found = true;
      // record.push_back(field_one);
      record.push_back(std::stof(field_two));
      record.push_back(std::stof(field_three));
      record.push_back(std::stof(field_four));
      record.push_back(std::stof(field_five));
    }
  }
  return record;
}

int main(int argc, char** argv) {
  std::vector<std::string> date = split("1/3/2019", '/');
  std::vector<std::string> date7 = previousDates7(date);
  std::vector<std::string> date14 = previousDates14(date);
  std::vector<std::vector<float>> cd;
  std::vector<std::vector<float>> pd;
  std::vector<float> actualD = readFile("../data/2169646.csv", "1/3/2019");

  for(int i = 0; i < 7; i++){
   std::vector<float> s = readFile("../data/2169646.csv", date7[i]);
    cd.push_back(s);
    // std::cout << cd[i][0];
  }  
  for(int i = 0; i < 14; i++){
    std::vector<float> s = readFile("../data/2169646.csv", date14[i]);
    pd.push_back(s);
    // std::cout << pd[i][0];
  } 
  std::vector<std::vector<float>> sw  = euclideanDistance(cd, pd);
  std::vector<std::vector<float>> vsw = varianza(cd);
  std::vector<std::vector<float>> vcd = varianza(sw);
  std::vector<float> mvrz = mediaVarianza(vcd, vsw);
  std::vector<float> aprox = aproximacion(actualD, mvrz);

  for(int i = 0; i < aprox.size(); i++){
    // for(int j = 0; j < vsw[i].size(); j++){
    //   std::cout << vsw[i][j] << " " << vcd[i][j] << " ";
    // }
     std::cout << aprox[i] << std::endl;
  }
  return 0;
}