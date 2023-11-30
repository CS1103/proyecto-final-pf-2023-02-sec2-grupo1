//
// Created by Carlo on 11/30/2023.
//

#ifndef PROTOTYPE_0_5_DATASET_H
#define PROTOTYPE_0_5_DATASET_H

#include <iostream>
#include <vector>

class Dataset {
    std::vector<double> training_data;
    std::vector<double> validation_data;
    std::vector<double> test_data;
public:
    template<template<typename...> class Container>
    Dataset(const Container<double>&, const Container<double>&, const Container<double>&);
    ~Dataset();
};

#endif //PROTOTYPE_0_5_DATASET_H