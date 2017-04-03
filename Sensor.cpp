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
                marker_vec.emplace_back(Marker(last_id, m_x, m_y));
                last_id++;
                segway_world.update_wstate(marker_vec);
                //cout << marker_vec[0].marker_x();
            }

    }
}
