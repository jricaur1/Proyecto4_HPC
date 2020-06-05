#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <omp.h>


std::vector<std::vector<float>> euclideanDistance(std::vector<std::vector<float>> &cd, std::vector<std::vector<float>> &pd) {
  float dst = 99999.9f;
  int index = 0;
  std::vector<std::vector<float>> w;
  #pragma omp for
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < cd.size(); j++){
      float dstaux = 0.0f;
      for (size_t k = 0; k < pd[i].size(); k++){
        dstaux += pow((cd[j][k] + pd[j + i][k]),2);
      }
      dstaux = sqrt(dst);
      if(dstaux < dst){
        dst = dstaux;
        index = i;
      } 
      
    }
    
  }
  for(int i = index; i < cd.size() + index; i++){
    w.push_back(pd[i]);
  }
  return w;
}


std::vector<std::vector<float>> varianza(std::vector<std::vector<float>> diff){
  std::vector<std::vector<float>> dfv; // difference vectors
  #pragma omp for
  for (int i = 0; i < diff.size() - 1; i++){
    std::vector<float> temp;
    for (int j = 0; j < diff[i].size(); j++){
      float f = fabs(diff[i + 1][j] - diff[i][j]);
      temp.push_back(f);
    }
    dfv.push_back(temp);
  }

  return dfv;
}


std::vector<float> mediaVarianza(std::vector<std::vector<float>> cdv, std::vector<std::vector<float>> pdv){
  std::vector<float> dfv; // difference vectors
  float meanc = 0.0f;
  float meanv = 0.0f;
  float mean  = 0.0f;
  #pragma omp for
  for (int i = 0; i < cdv[0].size(); i++){
    for (int j = 0; j < pdv.size(); j++){
      meanc += cdv[j][i];
      meanv += pdv[j][i];
    }
    meanc = meanc/7;
    meanv = meanv/7;
    mean = meanc + meanv;
    dfv.push_back(mean);
  }

  return dfv;
}

std::vector<float> aproximacion(std::vector<float> diaA, std::vector<float> mediaV) {
  std::vector<float> aprox;
  #pragma omp for
  for(int i = 0; i < diaA.size(); i++){
    float aux = mediaV[i] + diaA[i];
    aprox.push_back(aux);
  }
  return aprox;
}