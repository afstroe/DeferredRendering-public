/*!
 * \file vector3.h
 * \date 2015/12/19 15:07
 *
 * \author Alin Stroe
 *
 * \brief the 3D vector
 *
 * \note original version date 2010/02/15
 * \version 2.0
*/

#ifndef __VECTOR3_H__
#define __VECTOR3_H__

//! the humble 3D vector; the workhorse of any 3D graphics application 
template <class type>
class vector3
{
public:    
    union { type x; type h; type longitude; type i; type red;};/*!< the first component of the 3D vector */
    union { type y; type p; type latitude; type j; type green;};/*!< the second component of the 3D vector */
    union { type z; type r; type altitude; type k; type blue;};/*!< the third component of the 3D vector */
public:

    //! default c-tor
    inline vector3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    //! copy ctor
    /*!      
        \param const vector3<type> & rhs - the vector to copy to this one
    */
    inline vector3(const vector3& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
    }

    //! initialization ctor
    /*!      
        \param type x - first component of the vector
        \param type y - second component of the vector
        \param type z - third component of the vector
    */
    inline vector3(type x, type y, type z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    //! sets the elements of this vector
    /*!      
        \param type x - first component of the vector
        \param type y - second component of the vector
        \param type z - third component of the vector
    */
    inline void set(type x, type y, type z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }


    //! assignment operator
    /*!      
        \param const vector3 & rhs - the right hand side operand
        \return this vector
    */
    inline vector3& operator = (const vector3& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;

        return *this;
    }


    //! vector addition operator
    /*!      
        \param const vector3 & rhs - right hand side operand
        \return the addition result (new vector)
    */
    inline vector3 operator + (const vector3& rhs) const
    {
        return vector3(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    //! vector accumulated addition
    /*!      
        \param const vector3 & rhs - the right hand side operand
        \return this vector
    */
    inline vector3& operator += (const vector3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    //! vector subtraction operator
    /*!      
        \param const vector3 & rhs - the right hand side operand
        \return the operation result vector (new vector)      
    */
    inline vector3 operator - (const vector3& rhs) const
    {
        return vector3(x - rhs.x, y - rhs.y, z - rhs.z);
    }


    //! accumulated vector subtraction operator
    /*!      
        \param const vector3 & rhs - the right hand side operand
        \return the subtraction result stored in this vector      
    */
    inline vector3& operator -= (const vector3& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }


    //! vector negation operator
    /*!      
        \return this vector negated      
    */
    inline vector3 operator - () const
    {
        vector3<type> negate;
        negate.x = -x;
        negate.y = -y;
        negate.z = -z;
        return negate;
    }


    //! negates this vector
    /*!      
        \return this vector negated      
    */
    inline vector3& negate()
    {
        x = -x;
        y = -y;
        z = -z;

        return *this;
    }


    //! vector - scalar multiplication operator
    /*!      
        \param const type & sc - the scalar
        \return this vector multiplied by the scalar      
    */
    inline vector3 operator * (const type& sc) const
    {
        return (vector3(x * sc, y * sc, z * sc));
    }


    //! vector - scalar accumulated multiplication
    /*!      
        \param const type & sc - the scalar
        \return this vector multiplied by the scalar      
    */
    inline vector3& operator *= (const type& sc)
    {
        x *= sc;
        y *= sc;
        z *= sc;
        return *this;
    }


    //! vector dot product
    /*!      
        \param const vector3 & rhs - the right hand side operand
        \return the result of the dot product
    */
    inline type operator * (const vector3& rhs) const
    {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }


    //! vector cross product
    /*!      
        \param const vector3 & rhs - the right hand side operand
        \return the resulted vector of the cross product      
    */
    inline vector3 operator ^ (const vector3& rhs) const
    {
        return vector3(  y * rhs.z - z * rhs.y
                       , z * rhs.x - x * rhs.z
                       , x * rhs.y - y * rhs.x);
    }


    //! accumulated vector cross product
    /*!      
        \param const vector3 & rhs - the right hand side operand
        \return this vector after the cross product
    */
    inline vector3& operator ^= (const vector3& rhs)
    {
        type tempx = (type)0;
        type tempy = (type)0;
        type tempz = (type)0;

        tempx =  y * rhs.z - z * rhs.y;
        tempy =  z * rhs.x - x * rhs.z;
        tempz =  x * rhs.y - y * rhs.x;

        x = tempx;
        y = tempy;
        z = tempz;

        return *this;
    }



    //! compute the projection of this vector along the rhs vector
    /*!      
        \param const vector3 & rhs - the right hand side operand
        \return the operation's result vector
    */
    inline vector3 operator & (const vector3& rhs)
    {
        vector3 _u(*this), _pv;
        type _v_l = ((vector3)rhs).get_length();
        if(_v_l > 0)
        {
            type _s = (_u * ((vector3)rhs)) / (_v_l * _v_l);
            _pv = ((vector3)rhs) * _s;
        }
        else
        {
            _pv.x = (type)0;
            _pv.y = (type)0;
            _pv.z = (type)0;
        }
        return _pv;
    }


    //! compute and accumulate the projection of this vector along the rhs vector
    /*!      
        \param const vector3 & rhs - the right hand side operand
        \return this vector after being projected
    */
    inline vector3& operator &= (const vector3& rhs)
    {
        vector3 _u(*this);
        type _v_l = ((vector3)rhs).get_length();
        if(_v_l > 0)
        {
            type _s = (_u * ((vector3)rhs)) / (_v_l * _v_l);
            *this = ((vector3)rhs) * _s;
        }
        else
        {
            x = (type)0;
            y = (type)0;
            z = (type)0;
        }
        return *this;
    }


    //! returns the length of this vector
    /*!      
        \return the length of this vector
    */
    inline const type get_length() const
    {
        return sqrt(x * x + y * y + z * z);
    }


    //! normalizes this vector
    /*!      
        \return this vector after being normalized      
    */
    inline vector3& normalize()
    {
        type length = get_length();
        if(length > 0)
        {
            type invLength = 1 / length;
            x *= invLength;
            y *= invLength;
            z *= invLength;
        }
        return (vector3&)*this;
    }


    //! gets the direction cosines of the vector
    /*!      
        \param type & cosAlpha - the cosine of the angle made with the Ox axis
        \param type & cosBeta - the cosine of the angle made with the Oy axis
        \param type & cosGamma - the cosine of the angle made with the Oz axis
    */
    inline void get_direction_cosines(type& cosAlpha, type& cosBeta, type& cosGamma) const
    {
        type length = get_length();
        if(length > 0)
        {
            cosAlpha = x / length;
            cosBeta  = y / length;
            cosGamma = z / length;
        }
        else
        {
            cosAlpha = cosBeta = cosGamma = (type)0;
        }
    }


    //! gets the angles made by this vector with the axes
    /*!      
        \param type & alpha - the angle (in radians) made by this vector and the Ox axis
        \param type & beta - the angle (in radians) made by this vector and the Oy axis
        \param type & gamma - the angle (in radians) made by this vector and the Oz axis
    */
    inline void get_direction_angles(type& alpha, type& beta, type& gamma) const
    {
        get_direction_cosines(alpha, beta, gamma);
        alpha = acos(alpha);
        beta  = acos(beta);
        gamma = acos(gamma);
    }


    //! gets the cosine of the angle this vector makes with the other vector
    /*!      
        \param const vector3 & rhs - the other vector
        \return the cosine of the angle 
    */
    inline type get_cos_angle_made_with(const vector3& rhs) const
    {
        type length_multiplication = get_length() * rhs.get_length();
        type cosine = (type)0;

        if(length_multiplication > 0)
        {
            cosine = (*this * rhs) / length_multiplication;
        }
        return cosine;
    }


    //! gets the sine of the angle this vector makes with the other vector
    /*!      
        \param const vector3 & rhs - the other vector
        \return the cosine of the angle      
    */
    inline type get_sin_angle_made_with(const vector3& rhs) const
    {
        type length_multiplication = get_length() * rhs.get_length();
        type sine = (type)1;

        if(length_multiplication > 0)
        {
            sine = (*this ^ rhs).get_length() / length_multiplication;
        }
        return sine;
    }


    //! projects this vector to the given plane
    /*!      
        \param const vector3 & pn - 
        \return ReturnDescriptionHere      
        \sa <a href="http://www.euclideanspace.com/maths/geometry/elements/plane/lineOnPlane/index.htm">mechanism description</a>
    */
    inline vector3& project_to_plane(const vector3& pn)
    {
        *this = (pn) ^ (*this ^ pn);
        return *this;
    }

   
    //! normalizes the input vector
    /*!      
        \param const vector3 & input - vector to be normalized
        \return the normalized vector (new vector)      
    */
    inline static vector3 normalize(const vector3& input)
    {
	    type len = input.get_length();
	    return vector3(input.x / len, input.y / len, input.z / len);
    }

    //! casting operator to vector of other
    /*!      
        \return the casted vector
    */
    template <typename other>
    operator vector3<other>()
    {
        return vector3<other>((other)x, (other)y, (other)z);
    }

    //! cast to type*
    /*!      
        \return the vector as a type*
    */
    operator type* ()
    {
        return &x;
    }

    //! check if rhs equals to this
    /*!      
        \param const vector3 & rhs - the right hand side operand
        \return 
            - true: rhs is equal to this
            - false: rhs is nor equal to this
    */
    bool operator ==(const vector3& rhs) const
    {
        bool ret = true;
        type espilon = (type)1.0E-3;

        type dx = x - rhs.x;
        type dy = y - rhs.y;
        type dz = z - rhs.z;

        type d = max(dx, max(dy, dz));

        if(d > espilon || d < -espilon)
        {
            ret = false;
        }

        return ret;
    }

    //! cast operator to type*
    /*!      
        \return address of the first coordinate
    */
    operator const type*() const
    {
        return &x;
    }

};

#endif// __VECTOR3_H__