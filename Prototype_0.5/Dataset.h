//
// Created by Carlo on 11/30/2023.
//

#ifndef PROTOTYPE_0_5_DATASET_H
#define PROTOTYPE_0_5_DATASET_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using label = short;

class Dataset {
    std::vector<std::pair<std::vector<double>,label>> training_data;
    std::vector<std::pair<std::vector<double>,label>> test_data;
    std::vector<std::pair<std::vector<double>,label>> validation_data;
    std::vector<double> image_2b_predicted;
public:
    Dataset();
    template<template<typename...> class Container>
    Dataset(const Container<double>&, const Container<double>&, const Container<double>& = nullptr);
    ~Dataset();

    void load_data_from_csv(const std::string&, const std::string&, const std::string& = "");

    std::pair<std::vector<double>,label> get_training_example(const size_t&) const;
    std::pair<std::vector<double>,label> get_test_example(const size_t&) const;
    std::pair<std::vector<double>,label> get_validation_example(const size_t&) const;

    size_t get_training_size() const;
    size_t get_test_size() const;
    size_t get_validation_size() const;
    void leer_imagen_2predict(const std::string&);
};

#endif //PROTOTYPE_0_5_DATASET_H