#ifndef SENSOR_H
#define SENSOR_H
#include "Marker.h"

class Sensor{

    public:
        Sensor();
        array <array <float, 1>, 2> get_measurement();
        array <array <float, 1>, 2> marker_pos(float, float, float, WorldState&);
        void observation_model(float, float, float, int);
        void jacobian_obs(float, float, float, int);
        array <array <float, 2>, dim> kalman_gain(WorldState&);
        array <array <float, dim>, dim> calc_ktht(array <array <float, 2>, dim>&);


    protected:

    private:
        float range;
        float phi;
        //array <array <float, 1>, 2> marker_position;
        int last_id = 0;
        vector <Marker> marker_vec;
        array <array <float, 1>, 2> z_predicted;
        array <array <float, dim>, 2> jacobian{{}};
        array <array <float, 2>, 2> q_matrix;
};

#endif // SENSOR_H
