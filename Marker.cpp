#include <iostream>
#include <cstdio>
#include <cmath>
#include "global.h"
#include "WorldState.h"
#include "Robot.h"
#include "Sensor.h"
#include "Marker.h"


Marker::Marker(int idno, float x, float y)
{
    //ctor
    id = idno;
    mx = x;
    my = y;
}

int Marker::marker_id()
{
    return id;
}

float Marker::marker_x()
{
    return mx;
}

float Marker::marker_y()
{
    return my;
}

