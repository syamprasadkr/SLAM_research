#include <iostream>
#include <cstdio>
#include <cmath>
#include "global.h"
#include "WorldState.h"
#include "Robot.h"
#include "Sensor.h"
#include "Marker.h"

template <size_t M, size_t N>
void print_matrix(array <array <float, N>, M>& a)
{
    cout << "Matrix" << endl;
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

}
template void print_matrix(array <array <float, dim>, dim>& a);
template void print_matrix(array <array <float, 3>, 3>& a);
template void print_matrix(array <array <float, 3>, dim>& a);
template void print_matrix(array <array <float, dim>, 3>& a);
template void print_matrix(array <array <float, 2>, 2>& a);
template void print_matrix(array <array <float, dim>, 2>& a);
template void print_matrix(array <array <float, 2>, dim>& a);

template <size_t M, size_t N>
void transpose(array <array <float, N>, M>& a, array <array <float, M>, N>& b)
{
    // This can be made faster
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            b[j][i] = a[i][j];
        }
    }
}
template void transpose(array <array <float, dim>, dim>& a, array <array <float, dim>, dim>& b);
template void transpose(array <array <float, dim>, 2>& a, array <array <float, 2>, dim>& b);

template <size_t M, size_t N, size_t P>
void mat_mult(array <array <float, N>, M>& a, array <array <float, P>, N>& b, array <array <float, P>, M>& c)
{
    c = {{0}};
    //This can be made faster
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < P; j++)
        {
            for (size_t k = 0; k < N; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
template void mat_mult(array <array <float, dim>, dim>& a, array <array <float, dim>, dim>& b, array <array <float, dim>, dim>& c);
template void mat_mult(array <array <float, 3>, 3>& a, array <array <float, dim>, 3>& b, array <array <float, dim>, 3>& c);
template void mat_mult(array <array <float, 3>, dim>& a, array <array <float, dim>, 3>& b, array <array <float, dim>, dim>& c);
template void mat_mult(array <array <float, dim>, dim>& a, array <array <float, 2>, dim>& b, array <array <float, 2>, dim>& c);
template void mat_mult(array <array <float, dim>, 2>& a, array <array <float, 2>, dim>& b, array <array <float, 2>, 2>& c);
template void mat_mult(array <array <float, 2>, dim>& a, array <array <float, 2>, 2>& b, array <array <float, 2>, dim>& c);

void mat_invert(array <array <float, 2>, 2>& a, array <array <float, 2>, 2>& b)
{
    float det;
    det = (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
    b[0][0] = a[1][1] / det;
    b[1][1] = a[0][0] / det;
    b[0][1] = -a[0][1] / det;
    b[1][0] = -a[1][0] / det;
}

void generate_noise_matrix(array <array <float, 3>, 3>& a)
{
        //print_matrix<3, 3>(h1);
        //print_matrix<3, 3>(h2);
        for (int i = 0; i < 3; i++)
        {
            for (int j =0; j < 3; j++)
            {
                a[i][j] = (exp(-(pow(h1[i][j], 2) + pow(h2[i][j], 2))/ (2 * pow(sigma, 2)))) / (sqrt(2 * PI * pow(sigma, 2))) ;
            }
        }
        //print_matrix<3, 3>(a);
}

void generate_noise_matrix2(array <array <float, 2>, 2>& a)
{
        //print_matrix<3, 3>(h1);
        //print_matrix<3, 3>(h2);
        for (int i = 0; i < 2; i++)
        {
            for (int j =0; j < 2; j++)
            {
                a[i][j] = (exp(-(pow(h1[i][j], 2) + pow(h2[i][j], 2))/ (2 * pow(sigma, 2)))) / (sqrt(2 * PI * pow(sigma, 2))) ;
            }
        }
        //print_matrix<2, 2>(a);
}
