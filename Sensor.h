#ifndef SENSOR_H
#define SENSOR_H
#include "Marker.h"

class Sensor{

    public:
        Sensor();
        array <array <float, 1>, 2> get_measurement();
        array <array <float, 1>, 2> marker_pos(float, float, float, WorldState&);
        void observation_model(float, float, float);

    protected:

    private:
        float range;
        float phi;
        //array <array <float, 1>, 2> marker_position;
        //array <float, 3> temp;
        int last_id = 0;
        vector <Marker> marker_vec;
        array <array <float, 1>, 2> z_predicted;


};

#endif // SENSOR_H
