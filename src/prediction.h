#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <omp.h>


#pragma omp parallel
std::vector<std::vector<float>> euclideanDistance(std::vector<std::vector<float>> &cd, std::vector<std::vector<float>> &pd);

#pragma opm parallel
std::vector<std::vector<float>> varianza(std::vector<std::vector<float>> diff);

#pragma opm parallel
std::vector<float> mediaVarianza(std::vector<std::vector<float>> cdv, std::vector<std::vector<float>> pdv);

#pragma opm parallel
std::vector<float> aproximacion(std::vector<float> diaA, std::vector<float> mediaV);