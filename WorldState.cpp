#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include "global.h"
#include "WorldState.h"
#include "Robot.h"
#include "Sensor.h"
#include "Marker.h"



WorldState::WorldState(array <float, dim>& a, array <array <float, dim>, dim>& b)
{
    //ctor
    w_state = a;
    covar_matrix = b;
}

void WorldState::print_wstate()
{
    cout << "World State:" << endl;
    for (int i = 0; i < dim; i++)
    {
        printf("%0.2f ", w_state[i]);
    }
    cout << endl;
}

void WorldState::print_cmatrix()
{
    cout << "Covariance Matrix:" << endl;
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            printf("%0.2f ", covar_matrix[i][j]);

        }
        cout << endl;
    }
}

array <float, dim> WorldState::get_wstate()
{
    return w_state;
}

array <array <float, dim>, dim> WorldState::get_cmatrix()
{
    return covar_matrix;
}

void WorldState::predict_wstate(float a, float b, float c)
{
    w_state[0] = a;
    w_state[1] = b;
    w_state[2] = c;
}

void WorldState::predict_cmatrix(array <array <float, dim>, dim>& a, array <array <float, dim>, dim>& b,
                                 array <array <float, dim>, dim>& c )
{
    // Noise taken into account.
    mat_mult<dim, dim, dim>(covar_matrix, b, temp);
    covar_matrix = temp;
    mat_mult<dim, dim, dim>(a, covar_matrix, temp);
    covar_matrix = temp;
    //print_cmatrix();
    //print_matrix<dim, dim>(c);
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            covar_matrix[i][j] += c[i][j];
        }
    }
    //print_cmatrix();
    // Equation 7 completed
}

void WorldState::update_wstate(vector <Marker>& marker_vec)
{
    int id;
    float x;
    float y;
    if (!marker_vec.empty())
    {
        id = marker_vec.back().marker_id();
        x = marker_vec.back().marker_x();
        y = marker_vec.back().marker_y();
        w_state[3 + 2 * id] = x;
        w_state[4 + 2 * id] = y;
        //print_wstate();
    }
}
