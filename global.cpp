#include <iostream>
#include <cstdio>
#include <cmath>
#include "global.h"
#include "WorldState.h"
#include "Robot.h"
#include "Sensor.h"
#include "Marker.h"


void transpose(array <array <float, dim>, dim>& a, array <array <float, dim>, dim>& b)
{
    // This can be made faster
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            b[j][i] = a[i][j];
        }
    }
}

void transpose2(array <array <float, dim>, 2>& a, array <array <float, 2>, dim>& b)
{
    // This can be made faster
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            b[j][i] = a[i][j];
        }
    }
}

void mat_mult(array <array <float, dim>, dim>& a, array <array <float, dim>, dim>& b, array <array <float, dim>, dim>& c)
{
    c = {{0}};
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            for (int k = 0; k < dim; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}


void generate_noise_matrix(array <array <float, 3>, 3>& a)
{
        //print_matrix2(h1);
        //print_matrix2(h2);
       for (int i = 0; i < 3; i++)
        {
            for (int j =0; j < 3; j++)
            {
                a[i][j] = (exp(-(pow(h1[i][j], 2) + pow(h2[i][j], 2))/ (2 * pow(sigma, 2)))) / (sqrt(2 * PI * pow(sigma, 2))) ;
            }
        }
        //print_matrix2(a);
}

void generate_noise_matrix2(array <array <float, 2>, 2>& a)
{
        //print_matrix2(h1);
        //print_matrix2(h2);
       for (int i = 0; i < 2; i++)
        {
            for (int j =0; j < 2; j++)
            {
                a[i][j] = (exp(-(pow(h1[i][j], 2) + pow(h2[i][j], 2))/ (2 * pow(sigma, 2)))) / (sqrt(2 * PI * pow(sigma, 2))) ;
            }
        }
        //print_matrix2(a);
}


void print_matrix1(array <array <float, dim>, dim>& a)
{
    cout << "Matrix" << endl;
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            printf("%0.2f ", a[i][j]);
        }
        cout << endl;
    }

}

void print_matrix2(array <array <float, 3>, 3>& a)
{
    cout << "Matrix" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%0.2f ", a[i][j]);
        }
        cout << endl;
    }
}


void print_ffamily()
{
    cout << "F Matrix" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            printf("%0.2f ", f[i][j]);

        }
        cout << endl;
    }

    cout << "F Transpose Matrix" << endl;
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%0.2f ", f_transpose[i][j]);
        }
        cout << endl;
    }
}

