//
// Created by Carlo on 11/30/2023.
//

#include "Dataset.h"

template<template<typename...> class Container>
Dataset::Dataset(const Container<double>& trn_d, const Container<double>& val_d, const Container<double>& tst_d) : training_data(trn_d), validation_data(val_d), test_data(tst_d) {}

Dataset::~Dataset() = default;