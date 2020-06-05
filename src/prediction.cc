#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>

std::vector<std::vector<float>> euclideanDistance(std::vector<std::vector<float>> &cd, std::vector<std::vector<float>> &pd) {
  float dst = 99999.9f;
  int index = 0;
  std::vector<std::vector<float>> w;

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
  for(int i = 0; i < diaA.size(); i++){
    float aux = mediaV[i] + diaA[i];
    aprox.push_back(aux);
  }
  return aprox;
}

// int main(int argc, const char** argv) {
//   // 4/23/2019
//   std::vector<std::vector<float>> pd  = {{3.8,12.2,1.7,3.3},{10,12.8,5.6,7.8},{0,14.4,1.7,6.1},{0,16.7,2.8,3.3},{0,11.1,3.3,5.6},{5.8,11.1,4.4,6.7},{25.9,10.6,2.2,6.7},{38.4,10.6,2.8,3.3},{53.3,11.1,6.1,7.8},{23.9,11.1,3.3,10},{11.7,9.4,4.4,5},{9.7,14.4,6.7,7.8},{4.3,17.2,6.7,11.1},{9.7,10.6,6.7,6.7}};
//   std::vector<std::vector<float>> cd  = {{10,12.2,6.1,6.7},{10,13.9,7.8,9.4},{0,12.8,6.7,7.8},{7.1,15,10,10.6},{1.3,12.2,9.4,10.6},{6.4,12.8,6.1,10},{2.5,13.3,3.9,6.1}};
//   std::vector<std::vector<float>> sw  = euclideanDistance(cd, pd);
//   std::vector<std::vector<float>> vsw = varianza(cd);
//   std::vector<std::vector<float>> vcd = varianza(sw);
//   std::vector<float> mvrz = mediaVarianza(vcd, vsw);
//   std::vector<float> aprox = aproximacion(diaA, mvrz);

  // for(int i = 0; i < aprox.size(); i++){
  //   // for(int j = 0; j < vsw[i].size(); j++){
  //   //   std::cout << vsw[i][j] << " " << vcd[i][j] << " ";
  //   // }
  //    std::cout << aprox[i] << std::endl;
  // }

//   return 0;
// }