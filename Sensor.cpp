#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include "global.h"
#include "WorldState.h"
#include "Robot.h"
#include "Sensor.h"
#include "Marker.h"


Sensor::Sensor(){

    //ctor
}


array <array <float, 1>, 2> Sensor::get_measurement(){

    array <array <float, 1>, 2> ret_matrix;
    // This code will be replaced by the sensor readings from RGB-D Camera.
    range = 1.0;
    phi = 0;
    ret_matrix = {{{range}, {phi}}};
    /*for (int i = 0; i < 2; i++){

        cout << ret_matrix[i][0] << "\n";
    }*/
    return ret_matrix;
}


array <array <float, 1>, 2> Sensor::marker_pos(float x, float y, float theta, WorldState& segway_world){
    float m_x;
    float m_y;
    float delta_x;
    float delta_y;
    m_x = x + range * cos((theta + phi) * PI / 180);
    m_y = y + range * sin((theta + phi) * PI / 180);

    if (last_id != marker_num){

            int flag = 0;
            for (size_t i = 0; i < marker_vec.size(); i++){

                    //change to abs(m_x - marker_vec[i]marker_x()) < some_value && ...
                    if ((m_x == marker_vec[i].marker_x()) && (m_y == marker_vec[i].marker_y())){

                        flag = 1;
                    }
            }

            if (flag == 0){
                /*Marker *m = new Marker(last_id, m_x, m_y);
                marker_vec.push_back(*m);
                delete m;*/

                // Note that emplace_back will forward the arguments to appropriate constructor; in this case, Marker.
                marker_vec.emplace_back(last_id, m_x, m_y);
                last_id++;
                segway_world.update_wstate(marker_vec);
                //cout << marker_vec[0].marker_x();
            }

    }

    delta_x = m_x - x;
    delta_y = m_y - y;

    observation_model(delta_x, delta_y, theta);

}


void Sensor::observation_model(float delta_x, float delta_y, float theta){

    float q = pow(delta_x, 2) + pow(delta_y, 2);
    z_predicted[0][0] = sqrt(q);
    z_predicted[0][1] = ((atan2(delta_y, delta_x)) * (180 / PI)) - theta;  // Correct dr_slam_report_2.pdf
}
