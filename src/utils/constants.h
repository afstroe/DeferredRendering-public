/*!
 * \file constants.h
 * \date 2015/12/19 14:21
 *
 * \author Alin Stroe
 *
 * \brief constants definition
 *
 *
 * \note original version's date is 2010/02/18
 * \version 2.0
*/

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <algorithm>

#define BIT0  1 << 0
#define BIT1  1 << 1
#define BIT2  1 << 2
#define BIT3  1 << 3
#define BIT4  1 << 4
#define BIT5  1 << 5
#define BIT6  1 << 6
#define BIT7  1 << 7
#define BIT8  1 << 8
#define BIT9  1 << 9
#define BIT10 1 << 10
#define BIT11 1 << 11
#define BIT12 1 << 12
#define BIT13 1 << 13
#define BIT14 1 << 14
#define BIT15 1 << 15
#define BIT16 1 << 16
#define BIT17 1 << 17
#define BIT18 1 << 18
#define BIT19 1 << 19
#define BIT20 1 << 20
#define BIT21 1 << 21
#define BIT22 1 << 22
#define BIT23 1 << 23
#define BIT24 1 << 24
#define BIT25 1 << 25
#define BIT26 1 << 26
#define BIT27 1 << 27
#define BIT28 1 << 28
#define BIT29 1 << 29
#define BIT30 1 << 30
#define BIT31 1 << 31

#define WORD0 ((BIT0) | (BIT1) | (BIT2) | (BIT3) | (BIT4) | (BIT5) | (BIT6) | (BIT7))
#define WORD1 ((BIT8) | (BIT9) | (BIT10) | (BIT11) | (BIT12) | (BIT13) | (BIT14) | (BIT15))
#define WORD2 ((BIT16) | (BIT17) | (BIT18) | (BIT19) | (BIT20) | (BIT21) | (BIT22) | (BIT23))
#define WORD3 ((BIT24) | (BIT25) | (BIT26) | (BIT27) | (BIT28) | (BIT29) | (BIT30) | (BIT31))

#define MAXIMUM_TEXTURE_LAYERS 3
//#define MAXIMUM_TEXTURE_SLICE_SIZE 16384
#define MAXIMUM_TEXTURE_SIZE 4096 * 2

//! PurtyPicures constants definition 
class constants
{
public:

    //! mathematics related constants
    class math
    {
    public:
        static const double deg_to_rad;/*!< degrees to radians */
        static const double rad_to_deg;/*!< radians to degrees */
        static const double pi;/*!< pi */
        static const double pi_over_2;/*!< pi/2 */
        static const double pi_over_4;/*!< pi/4 */
        static const double pi_over_6;/*!< pi/6 */
        static const double pi_times_2;/*!< 2pi */

        //! takes an angle into the [0, 2pi] interval
        /*!      
            \param double angle - the angle to be taken into [0, 2pi] interval
            \return the angle in [0, 2pi]
        */
        static double angle0to2Pi(double angle);

        //! takes an angle into the [0, 360] interval
        /*!      
            \param double angle - the angle to be taken into the [0, 360] interval
            \return the angle into the [0, 360] interval
        */
        static double angle0to360(double angle);

        //! checks if the given value is in the interval defined by lhs and rhs; the interval is considered closed at both ends
        /*!      
            \param type lhs - the left hand side end of the interval
            \param type rhs - the right hand side end of the interval
            \param type value - the value to be checked against the interval
            \return 
                - true: value is inside [lhs, rhs]
                - false: value is outside [lhs, rhs]
            \note rhs must be greater than lhs
        */
        template <typename type>
        static bool in_interval_closed_both(type lhs, type rhs, type value)
        {
            if(value >= lhs && value <= rhs)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        //! checks if the given value is in the interval defined by lhs and rhs; the interval is considered closed at left end
        /*!      
            \param type lhs - the left hand side end of the interval
            \param type rhs - the right hand side end of the interval
            \param type value - the value to be checked against the interval
            \return 
                - true: value is inside [lhs, rhs)
                - false: value is outside [lhs, rhs)
            \note rhs must be greater than lhs
        */
        template <typename type>
        static bool in_interval_closed_left(type lhs, type rhs, type value)
        {
            if(value >= lhs && value < rhs)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        //! checks if the given value is in the interval defined by lhs and rhs; the interval is considered closed at the right end
        /*!      
            \param type lhs - the left hand side end of the interval
            \param type rhs - the right hand side end of the interval
            \param type value - the value to be checked against the interval
            \return 
                - true: value is inside (lhs, rhs]
                - false: value is outside (lhs, rhs]
            \note rhs must be greater than lhs
        */
        template <typename type>
        static bool in_interval_closed_right(type lhs, type rhs, type value)
        {
            if(value > lhs && value <= rhs)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        //! checks if the given value is in the interval defined by lhs and rhs; the interval is considered open at both ends
        /*!      
            \param type lhs - the left hand side end of the interval
            \param type rhs - the right hand side end of the interval
            \param type value - the value to be checked against the interval
            \return 
                - true: value is inside (lhs, rhs)
                - false: value is outside (lhs, rhs)
            \note rhs must be greater than lhs
        */
        template <typename type>
        static bool in_interval_open_both(type lhs, type rhs, type value)
        {
            if(value > lhs && value < rhs)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        //! checks if the 'left' and 'right' parameters are equal within a tolerance
        /*!      
            \param const type & lhs - the 'left' term to check with the right
            \param const type & rhs - the 'right' term to check with the left
            \param type eps - the epsilon value to check against
            \return
                -true: 'left' and 'right' values are equal wrt the provided tolerance value
                -false: 'left' and 'right' values are not equal wrt the provided tolerance value
        */
        template <typename type>
        static bool equals(const type& lhs, const type& rhs, type eps = (type)10E-5)
        {
            return fabs(lhs - rhs) < eps;
        }

        //! clamps a value to a given interval
        /*!      
            \param type val - value to be clamped to interval
            \param type left - the left border of the interval
            \param type right - the right border of the interval
            \return the clamped value
        */
        template <typename type>
        static type clamp_to_interval(type val, type left, type right)
        {
            return std::max<type>(std::min<type>(val, right), left);
        }

        //! computes the angular difference between two given angles
        /*!      
            \param type first - the first angle [degrees]
            \param type second - the second angle [degrees]
            \return the angular difference between the given angles [degrees]
        */
        template <typename type>
        static type compute_angular_difference(type first, type second)
        {
            type start_agl_rad = first * deg_to_rad;
            type end_agl_rad = second * deg_to_rad;
            return static_cast<type>(atan2(sin(end_agl_rad - start_agl_rad), cos(end_agl_rad - start_agl_rad)) * rad_to_deg);
        }
    };

    //! physics related constants
    class physics
    {
    public:
        static const double mps_to_kmph;/*!< meters per second to kilometers per hour */
        static const double kmph_to_mps;/*!< kilometers per hour to meters per second */
        static const double s_to_ms;/*!< seconds to milliseconds */
        static const double ms_to_s;/*!< milliseconds to seconds */
        static const double ms_to_ns;/*!< milliseconds to nanoseconds */
        static const double ns_to_ms;/*!< nanoseconds to milliseconds */
    };
};


#endif// __CONSTANTS_H__