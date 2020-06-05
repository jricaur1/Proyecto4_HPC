#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <ctime>
#include <omp.h>
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
  #pragma omp parallel for
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
  #pragma omp parallel for
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
      #pragma omp critical
      record.push_back(std::stof(field_two));
      record.push_back(std::stof(field_three));
      record.push_back(std::stof(field_four));
      record.push_back(std::stof(field_five));
    }
  }
  return record;
}

std::vector<std::string> readFechas(std::string file_name){
  std::vector<std::string> fechas;
  std::ifstream file;
  file.open(file_name);
  std::string fecha;
  while(getline(file, fecha, '\n')){
    #pragma omp critical
    fechas.push_back(fecha);
  }
  return fechas;
}

int main(int argc, char** argv) {
  auto start = std::chrono::system_clock::now();
  std::vector<std::string> fechas = readFechas("../data/sample.csv");
  #pragma omp parallel for
  for(int k = 0; k < fechas.size(); k++){
    std::vector<std::string> date = split(fechas[k], '/');
    std::vector<std::string> date7 = previousDates7(date);
    std::vector<std::string> date14 = previousDates14(date);
    std::vector<std::vector<float>> cd;
    std::vector<std::vector<float>> pd;
    std::vector<float> actualD = readFile("../data/2169646.csv", "1/3/2019");
    #pragma omp critical
    for(int i = 0; i < 7; i++){
    std::vector<float> s = readFile("../data/2169646.csv", date7[i]);
      cd.push_back(s);
    }
    #pragma omp critical  
    for(int i = 0; i < 14; i++){
      std::vector<float> s = readFile("../data/2169646.csv", date14[i]);
      pd.push_back(s);
    } 
    std::vector<std::vector<float>> sw  = euclideanDistance(cd, pd);
    std::vector<std::vector<float>> vsw = varianza(cd);
    std::vector<std::vector<float>> vcd = varianza(sw);
    std::vector<float> mvrz = mediaVarianza(vcd, vsw);
    std::vector<float> aprox = aproximacion(actualD, mvrz);

    std::cout << "En la fecha " << fechas[k] << " la precipitación fue: " << aprox[0]<<  ", la temperatura mínima fue: " << aprox[1] << 
    ", temperatura máxima fue: " << aprox[2] << " y la temperatura observada fue: " << aprox[3] << std::endl;
  }
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "Computo finalizada en " << std::ctime(&end_time)
            << "tiempo de ejecución: " << elapsed_seconds.count() << "s\n";
  return 0;
}