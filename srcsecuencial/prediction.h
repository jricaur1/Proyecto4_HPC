#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>


std::vector<std::vector<float>> euclideanDistance(std::vector<std::vector<float>> &cd, std::vector<std::vector<float>> &pd);

std::vector<std::vector<float>> varianza(std::vector<std::vector<float>> diff);

std::vector<float> mediaVarianza(std::vector<std::vector<float>> cdv, std::vector<std::vector<float>> pdv);

std::vector<float> aproximacion(std::vector<float> diaA, std::vector<float> mediaV);