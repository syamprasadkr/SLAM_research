#include <iostream>
#include <cstdio>
#include <cmath>
#include "global.h"
#include "WorldState.h"
#include "Robot.h"
#include "Sensor.h"
#include "Marker.h"


Marker::Marker(int idno){

    //ctor
    id = idno;
    mx = 0.0;
    my = 0.0;
}
