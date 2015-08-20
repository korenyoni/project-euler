#ifndef ATKIN_H
#define ATKIN_H
#include <vector>
#include "atkin.cpp"

std::vector<int> atkin(int limit);
std::vector<bool> boolAtkin(int limit);
std::vector<int> atkinFromBoolVector(std::vector<bool> &boolPrimeVector);

#endif
