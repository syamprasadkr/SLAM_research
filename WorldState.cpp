#include <iostream>
#include <cstdio>
#include <cmath>
#include "global.h"
#include "WorldState.h"
#include "Robot.h"
#include "Sensor.h"
#include "Marker.h"



WorldState::WorldState(array <float, dim>& a, array <array <float, dim>, dim>& b){
    //ctor
    w_state = a;
    covar_matrix = b;
}

void WorldState::print_wstate(){

    cout << "World State:" << endl;
    for (int i = 0; i < dim; i++){
        printf("%0.2f ", w_state[i]);
    }
    cout << endl;
}

void WorldState::print_cmatrix(){

    cout << "Covariance Matrix:" << endl;
    for (int i = 0; i < dim; i++){
            for (int j = 0; j < dim; j++){
                printf("%0.2f ", covar_matrix[i][j]);

            }
            cout << endl;
    }
}

void WorldState::predict_wstate(float a, float b, float c){

    w_state[0] = a;
    w_state[1] = b;
    w_state[2] = c;
}
