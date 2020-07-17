#include "constants.h"

const double constants::math::deg_to_rad= 0.017453292519943295769236907684886;
const double constants::math::rad_to_deg = 57.295779513082320876798154814105;
const double constants::math::pi = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706;
const double constants::math::pi_over_2 = pi / 2;
const double constants::math::pi_over_4 = pi / 4;
const double constants::math::pi_over_6 = pi / 6;
const double constants::math::pi_times_2 = 2 * pi;

const double constants::physics::mps_to_kmph = 3.6;
const double constants::physics::kmph_to_mps = 0.277777777778;

const double constants::physics::ms_to_s = 1.0 / 1.E3;
const double constants::physics::s_to_ms = 1 / ms_to_s;

const double constants::physics::ms_to_ns = 1000000.0;
const double constants::physics::ns_to_ms = 1.0 / ms_to_ns;

double constants::math::angle0to2Pi(double angle)
{

    angle = fmod(angle, pi_times_2);
    if(angle < 0)
    {
        angle += pi_times_2;
    }
    return angle;
}

double constants::math::angle0to360(double angle)
{
    double angle0 = fmod(angle, 360);
    if(angle0 < 0)
    {
        angle0 += 360;
    }
    return angle0;
}
