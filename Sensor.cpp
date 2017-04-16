#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include "global.h"
#include "WorldState.h"
#include "Robot.h"
#include "Sensor.h"
#include "Marker.h"


Sensor::Sensor()
{
    //ctor
    generate_noise_matrix2(q_matrix);
}


array <array <float, 1>, 2> Sensor::get_measurement()
{
    array <array <float, 1>, 2> ret_matrix;
    // This code will be replaced by the sensor readings from RGB-D Camera.
    range = 1.0;
    phi = 0;
    ret_matrix = {{{range}, {phi}}};
    /*for (int i = 0; i < 2; i++)
    {
        cout << ret_matrix[i][0] << "\n";
    }*/
    return ret_matrix;
}


array <array <float, 1>, 2> Sensor::marker_pos(float x, float y, float theta, WorldState& segway_world)
{
    float m_x;
    float m_y;
    float delta_x;
    float delta_y;
    int curr_id;
    m_x = x + range * cos((theta + phi) * PI / 180);
    m_y = y + range * sin((theta + phi) * PI / 180);
    int flag = 0;
    for (size_t i = 0; i < marker_vec.size(); i++)
    {
        // Keep an eye on this.....value 0.5 may require change.
        if ((abs(m_x - marker_vec[i].marker_x()) < 0.5) && (abs(m_y - marker_vec[i].marker_y()) < 0.5))
        {
            array <float, dim> w_state = segway_world.get_wstate();
            curr_id = marker_vec[i].marker_id();
            flag = 1;
            m_x = w_state[3 + 2 * curr_id];
            m_y = w_state[4 + 2 * curr_id];
        }
    }

    if (last_id != marker_num && flag == 0)
    {

        /*Marker *m = new Marker(last_id, m_x, m_y);
        marker_vec.push_back(*m);
        delete m;*/
        // Note that emplace_back will forward the arguments to appropriate constructor; in this case, Marker.
        marker_vec.emplace_back(last_id, m_x, m_y);
        curr_id = last_id;
        last_id++;
        segway_world.update_wstate(marker_vec);
        //cout << marker_vec[0].marker_x();

    }

    delta_x = m_x - x;
    delta_y = m_y - y;

    observation_model(delta_x, delta_y, theta, curr_id);
    return z_predicted;
}


void Sensor::observation_model(float delta_x, float delta_y, float theta, int curr_id)
{
    float q = pow(delta_x, 2) + pow(delta_y, 2);
    z_predicted[0][0] = sqrt(q);
    z_predicted[0][1] = ((atan2(delta_y, delta_x)) * (180 / PI)) - theta;  // Correct dr_slam_report_2.pdf
    // Completed Equation 12.
    jacobian_obs(q, delta_x, delta_y, curr_id);
}

void Sensor::jacobian_obs(float q, float delta_x, float delta_y, int curr_id)
{
    // Check if this jacobian is correct
    jacobian[0][0] = -delta_x / sqrt(q);
    jacobian[0][1] = -delta_y / sqrt(q);
    jacobian[0][(3 + 2 * curr_id)] = delta_x / sqrt(q);
    jacobian[0][(4 + 2 * curr_id)] = delta_y / sqrt(q);

    jacobian[1][0] = delta_y / q;
    jacobian[1][1] = -delta_x / q;
    jacobian[1][2] = -q;
    jacobian[1][(3 + 2 * curr_id)] = -delta_y / q;
    jacobian[1][(4 + 2 * curr_id)] = delta_x / q;
    //cout << "Jacobian\n";
    //print_matrix<2, dim>(jacobian);

}

array <array <float, 2>, dim> Sensor::kalman_gain(WorldState& segway_world)
{
    array <array <float, dim>, dim> cmatrix = segway_world.get_cmatrix();
    array <array <float, 2>, dim> jacobian_transpose;
    array <array <float, 2>, dim> temp;
    array <array <float, 2>, dim> kg;
    array <array <float, 2>, 2> mat_to_invert;
    array <array <float, 2>, 2> inverted_mat;

    transpose<2, dim>(jacobian, jacobian_transpose);
    mat_mult(cmatrix, jacobian_transpose, temp);
    mat_mult(jacobian, temp, mat_to_invert);

    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
           mat_to_invert[i][j] += q_matrix[i][j];
        }
    }

    //Invert matrix
    mat_invert(mat_to_invert, inverted_mat);
    //print mat_to_invert, inverted_mat, q_matrix
    /*cout << "Mat_to_invert\n";
    print_matrix(mat_to_invert);
    cout << "Inverted Mat\n";
    print_matrix(inverted_mat);
    cout << "Q matrix\n";
    print_matrix(q_matrix);*/

    mat_mult(jacobian_transpose, inverted_mat, temp);
    mat_mult(cmatrix, temp, kg);
    //print_matrix(kg);
    // Equation 15 complete
}
