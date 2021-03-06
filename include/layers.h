//
//  layers.h
//  

#ifndef layers_h
#define layers_h

#include<omp.h>
#include <stdbool.h>
#include<stdlib.h>

struct layer{
    int num_nodes;
    int prev_num_nodes;
    
    float* W;
    float* b;
    float* Z;
    float* A;
    
    float* dW;
    float* db;
    float* dZ;
};

struct model{
    int num_layers;
    int num_features;
    float * input;
    struct layer* layers;
};

struct layer Dense(struct layer prevLayer, int num_nodes){
    
    struct layer denseLayer;
    int rows;
    int cols;
    
    denseLayer.num_nodes = num_nodes;
    
    rows = prevLayer.num_nodes;
    cols = num_nodes;
    
    denseLayer.prev_num_nodes = rows;
    
    /*Initilize the weights, bias, Z, activation matrix and and updation matrices*/
    
    denseLayer.W = (float*) malloc(rows * cols * sizeof(float));
    denseLayer.b = (float*) malloc(cols * sizeof(float));
    denseLayer.dW = (float*) malloc(rows * cols * sizeof(float));
    denseLayer.db = (float*) malloc(cols * sizeof(float));
    
#pragma omp parallel for collapse(2)
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            denseLayer.W[i*rows+j] = -1 + (rand() % 100)/50.0;
        }
    }
#pragma omp parallel for
    for (int i=0;i<cols;i++){
        denseLayer.b[i] = 0.0;
    }
    
    return denseLayer;
}

#endif /* layers_h */
