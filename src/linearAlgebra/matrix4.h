/*!
 * \file matrix4.h
 * \date 2015/12/17 15:43
 *
 * \author Alin Stroe
 *
 * \brief 4x4 matrix support
 *
 * \note original version date 2010/02/18
 * \version 2.0
*/

#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include <memory.h>
#include "vector3.h"
#include "../utils/constants.h"

//! a 4x4 four matrix support 
/*!  
    the 4x4 matrix is very well established in 3D graphics
    this class implements basic 4x4 matrix operations
*/
template <typename type>
class matrix4
{
protected:
    union
    {
        type matrix[4][4];
        type vector[16];
    };

public:
    static const matrix4 identity;/*!< the identity matrix */

    //! default constructor
    matrix4()
    {
        matrix[0][0] = 1; matrix[0][1] = 0; matrix[0][2] = 0; matrix[0][3] = 0; 
        matrix[1][0] = 0; matrix[1][1] = 1; matrix[1][2] = 0; matrix[1][3] = 0; 
        matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = 1; matrix[2][3] = 0; 
        matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 0; matrix[3][3] = 1; 
    }

    //! copy constructor
    /*!      
        \param const matrix4 & rhs - matrix to be copied into this
    */
    matrix4(const matrix4& rhs)
    {
        memcpy(vector, rhs.vector, 16 * sizeof(type));
    }

    //! initialization constructor
    /*!      
        \param type matrix00 - matrix element
        \param type matrix01 - matrix element
        \param type matrix02 - matrix element
        \param type matrix03 - matrix element
        \param type matrix10 - matrix element
        \param type matrix11 - matrix element
        \param type matrix12 - matrix element
        \param type matrix13 - matrix element
        \param type matrix20 - matrix element
        \param type matrix21 - matrix element
        \param type matrix22 - matrix element
        \param type matrix23 - matrix element
        \param type matrix30 - matrix element
        \param type matrix31 - matrix element
        \param type matrix32 - matrix element
        \param type matrix33 - matrix element
    */
    inline matrix4(  type matrix00, type matrix01, type matrix02, type matrix03
                   , type matrix10, type matrix11, type matrix12, type matrix13
                   , type matrix20, type matrix21, type matrix22, type matrix23
                   , type matrix30, type matrix31, type matrix32, type matrix33)
    {
        matrix[0][0] = matrix00; matrix[0][1] = matrix01; matrix[0][2] = matrix02; matrix[0][3] = matrix03; 
        matrix[1][0] = matrix10; matrix[1][1] = matrix11; matrix[1][2] = matrix12; matrix[1][3] = matrix13; 
        matrix[2][0] = matrix20; matrix[2][1] = matrix21; matrix[2][2] = matrix22; matrix[2][3] = matrix23; 
        matrix[3][0] = matrix30; matrix[3][1] = matrix31; matrix[3][2] = matrix32; matrix[3][3] = matrix33; 
    }

    //! constructs this matrix using a 16-element vector
    /*!      
        \param const type from_vector[16] - the vector used to construct the matrix
    */
    inline matrix4(const type from_vector[16])
    {
        memcpy(vector, from_vector, 16 * sizeof(type));
    }

    //! sets the elements for this matrix
    /*!      
        \param type matrix00 - matrix element
        \param type matrix01 - matrix element
        \param type matrix02 - matrix element
        \param type matrix03 - matrix element
        \param type matrix10 - matrix element
        \param type matrix11 - matrix element
        \param type matrix12 - matrix element
        \param type matrix13 - matrix element
        \param type matrix20 - matrix element
        \param type matrix21 - matrix element
        \param type matrix22 - matrix element
        \param type matrix23 - matrix element
        \param type matrix30 - matrix element
        \param type matrix31 - matrix element
        \param type matrix32 - matrix element
        \param type matrix33 - matrix element
    */
    inline void set(  type matrix00, type matrix01, type matrix02, type matrix03
                    , type matrix10, type matrix11, type matrix12, type matrix13
                    , type matrix20, type matrix21, type matrix22, type matrix23
                    , type matrix30, type matrix31, type matrix32, type matrix33)
    {
        matrix[0][0] = matrix00; matrix[0][1] = matrix01; matrix[0][2] = matrix02; matrix[0][3] = matrix03; 
        matrix[1][0] = matrix10; matrix[1][1] = matrix11; matrix[1][2] = matrix12; matrix[1][3] = matrix13; 
        matrix[2][0] = matrix20; matrix[2][1] = matrix21; matrix[2][2] = matrix22; matrix[2][3] = matrix23; 
        matrix[3][0] = matrix30; matrix[3][1] = matrix31; matrix[3][2] = matrix32; matrix[3][3] = matrix33; 
    }

    //! gets the matrix representation for the OpenGL library
    /*!      
        \return the matrix representation for the OpenGL library     
    */
    inline const type* get_openglmatrix() const
    {
        return vector;
    }

    inline operator const type*() const
    {
        return vector;
    }

    //! forms this matrix from the given OpenGL matrix
    /*!      
        \param const type openglMatrix[16] - the OpenGL matrix
    */
    inline void from_openglmatrix(const type openglMatrix[16])
    {
        memcpy(vector, openglMatrix, 16 * sizeof(type));
    }

    //! gets the coefficient at row, columns
    /*!      
        \param int i - row
        \param int j - columns
        \return the element      
    */
    inline const type get_coefficient(int i, int j) const
    {
        return matrix[i][j];
    }

    //! changes the matrix element at row, column with the give value
    /*!      
        \param int i - row
        \param int j - column
        \param type val - value to change the element to
        \return this matrix's reference (for chaining)
    */
    inline matrix4& set_coefficient(int i, int j, type val)
    {
        matrix[i][j] = val;
        return *this;
    }

    //! assignment operator
    /*!      
        \param const matrix4 & rhs - right hand side operand
        \return this matrix
    */
    inline matrix4& operator = (const matrix4& rhs)
    {
        memcpy(vector, rhs.vector, 16 * sizeof(type));
        return *this;
    }

    //! adds this matrix to rhs and returns a new matrix
    /*!      
        \param const matrix4 & rhs - right hand side operand
        \return the resulting matrix      
    */
    inline matrix4 operator + (const matrix4& rhs)
    {
        return matrix4(
            matrix[0][0] + rhs.matrix[0][0], matrix[0][1] + rhs.matrix[0][1], matrix[0][2] + rhs.matrix[0][2], matrix[0][3] + rhs.matrix[0][3],
            matrix[1][0] + rhs.matrix[1][0], matrix[1][1] + rhs.matrix[1][1], matrix[1][2] + rhs.matrix[1][2], matrix[1][3] + rhs.matrix[1][3],
            matrix[2][0] + rhs.matrix[2][0], matrix[2][1] + rhs.matrix[2][1], matrix[2][2] + rhs.matrix[2][2], matrix[2][3] + rhs.matrix[2][3],
            matrix[3][0] + rhs.matrix[3][0], matrix[3][1] + rhs.matrix[3][1], matrix[3][2] + rhs.matrix[3][2], matrix[3][3] + rhs.matrix[3][3]
        );
    }

    //! accumulated addition
    /*!      
        \param const matrix4 & rhs - the right hand side operand
        \return this matrix after the addition      
    */
    inline matrix4& operator += (const matrix4& rhs)
    {
        matrix[0][0] += rhs.matrix[0][0]; matrix[0][1] += rhs.matrix[0][1]; matrix[0][2] += rhs.matrix[0][2]; matrix[0][3] += rhs.matrix[0][3];
        matrix[1][0] += rhs.matrix[1][0]; matrix[1][1] += rhs.matrix[1][1]; matrix[1][2] += rhs.matrix[1][2]; matrix[1][3] += rhs.matrix[1][3];
        matrix[2][0] += rhs.matrix[2][0]; matrix[2][1] += rhs.matrix[2][1]; matrix[2][2] += rhs.matrix[2][2]; matrix[2][3] += rhs.matrix[2][3];
        matrix[3][0] += rhs.matrix[3][0]; matrix[3][1] += rhs.matrix[3][1]; matrix[3][2] += rhs.matrix[3][2]; matrix[3][3] += rhs.matrix[3][3];

        return *this;
    }

    //! multiplies elements of this matrix with the given scalar
    /*!      
        \param const type scalar - the scalar to multiply this matrix with
        \return a new matrix, the product of this matrix multiplied with a scalar      
    */
    inline matrix4 operator * (const type scalar)
    {
        return matrix4( matrix[0][0] * scalar, matrix[0][1] * scalar, matrix[0][2] * scalar, matrix[0][3] * scalar,
                        matrix[1][0] * scalar, matrix[1][1] * scalar, matrix[1][2] * scalar, matrix[1][3] * scalar,
                        matrix[2][0] * scalar, matrix[2][1] * scalar, matrix[2][2] * scalar, matrix[2][3] * scalar,
                        matrix[3][0] * scalar, matrix[3][1] * scalar, matrix[3][2] * scalar, matrix[3][3] * scalar);
    }

    //! multiplies elements of this matrix with the given scalar
    /*!      
        \param const type scalar - the scalar to multiply this matrix with
        \return this matrix, the product of this matrix multiplied with a scalar      
    */
    inline matrix4& operator *= (const type scalar)
    {
        matrix[0][0] *= scalar; matrix[0][1] *= scalar; matrix[0][2] *= scalar; matrix[0][3] *= scalar; 
        matrix[1][0] *= scalar; matrix[1][1] *= scalar; matrix[1][2] *= scalar; matrix[1][3] *= scalar; 
        matrix[2][0] *= scalar; matrix[2][1] *= scalar; matrix[2][2] *= scalar; matrix[2][3] *= scalar; 
        matrix[3][0] *= scalar; matrix[3][1] *= scalar; matrix[3][2] *= scalar; matrix[3][3] *= scalar; 

        return *this;
    }

    //! multiplies this matrix with rhs and returns the result in a new matrix
    /*!      
        \param const matrix4 & rhs - the right hand side operand
        \return the result matrix (a new one)
    */
    inline matrix4 operator * (const matrix4& rhs) const
    {
        return matrix4(
            matrix[0][0] * rhs.matrix[0][0] + matrix[0][1] * rhs.matrix[1][0] + matrix[0][2] * rhs.matrix[2][0] + matrix[0][3] * rhs.matrix[3][0],
            matrix[0][0] * rhs.matrix[0][1] + matrix[0][1] * rhs.matrix[1][1] + matrix[0][2] * rhs.matrix[2][1] + matrix[0][3] * rhs.matrix[3][1],
            matrix[0][0] * rhs.matrix[0][2] + matrix[0][1] * rhs.matrix[1][2] + matrix[0][2] * rhs.matrix[2][2] + matrix[0][3] * rhs.matrix[3][2],
            matrix[0][0] * rhs.matrix[0][3] + matrix[0][1] * rhs.matrix[1][3] + matrix[0][2] * rhs.matrix[2][3] + matrix[0][3] * rhs.matrix[3][3],

            matrix[1][0] * rhs.matrix[0][0] + matrix[1][1] * rhs.matrix[1][0] + matrix[1][2] * rhs.matrix[2][0] + matrix[1][3] * rhs.matrix[3][0],
            matrix[1][0] * rhs.matrix[0][1] + matrix[1][1] * rhs.matrix[1][1] + matrix[1][2] * rhs.matrix[2][1] + matrix[1][3] * rhs.matrix[3][1],
            matrix[1][0] * rhs.matrix[0][2] + matrix[1][1] * rhs.matrix[1][2] + matrix[1][2] * rhs.matrix[2][2] + matrix[1][3] * rhs.matrix[3][2],
            matrix[1][0] * rhs.matrix[0][3] + matrix[1][1] * rhs.matrix[1][3] + matrix[1][2] * rhs.matrix[2][3] + matrix[1][3] * rhs.matrix[3][3],

            matrix[2][0] * rhs.matrix[0][0] + matrix[2][1] * rhs.matrix[1][0] + matrix[2][2] * rhs.matrix[2][0] + matrix[2][3] * rhs.matrix[3][0],
            matrix[2][0] * rhs.matrix[0][1] + matrix[2][1] * rhs.matrix[1][1] + matrix[2][2] * rhs.matrix[2][1] + matrix[2][3] * rhs.matrix[3][1],
            matrix[2][0] * rhs.matrix[0][2] + matrix[2][1] * rhs.matrix[1][2] + matrix[2][2] * rhs.matrix[2][2] + matrix[2][3] * rhs.matrix[3][2],
            matrix[2][0] * rhs.matrix[0][3] + matrix[2][1] * rhs.matrix[1][3] + matrix[2][2] * rhs.matrix[2][3] + matrix[2][3] * rhs.matrix[3][3],

            matrix[3][0] * rhs.matrix[0][0] + matrix[3][1] * rhs.matrix[1][0] + matrix[3][2] * rhs.matrix[2][0] + matrix[3][3] * rhs.matrix[3][0],
            matrix[3][0] * rhs.matrix[0][1] + matrix[3][1] * rhs.matrix[1][1] + matrix[3][2] * rhs.matrix[2][1] + matrix[3][3] * rhs.matrix[3][1],
            matrix[3][0] * rhs.matrix[0][2] + matrix[3][1] * rhs.matrix[1][2] + matrix[3][2] * rhs.matrix[2][2] + matrix[3][3] * rhs.matrix[3][2],
            matrix[3][0] * rhs.matrix[0][3] + matrix[3][1] * rhs.matrix[1][3] + matrix[3][2] * rhs.matrix[2][3] + matrix[3][3] * rhs.matrix[3][3]
        );
    }

    //! accumulated matrix to matrix multiplication
    /*!      
        \param const matrix4 & rhs - the right hand side operand
        \return this matrix multiplied by rhs
    */
    inline matrix4& operator *= (const matrix4& rhs)
    {
        type tk[4][4] = {(type)0};
        tk[0][0] = matrix[0][0] * rhs.matrix[0][0] + matrix[0][1] * rhs.matrix[1][0] + matrix[0][2] * rhs.matrix[2][0] + matrix[0][3] * rhs.matrix[3][0];
        tk[0][1] = matrix[0][0] * rhs.matrix[0][1] + matrix[0][1] * rhs.matrix[1][1] + matrix[0][2] * rhs.matrix[2][1] + matrix[0][3] * rhs.matrix[3][1];
        tk[0][2] = matrix[0][0] * rhs.matrix[0][2] + matrix[0][1] * rhs.matrix[1][2] + matrix[0][2] * rhs.matrix[2][2] + matrix[0][3] * rhs.matrix[3][2];
        tk[0][3] = matrix[0][0] * rhs.matrix[0][3] + matrix[0][1] * rhs.matrix[1][3] + matrix[0][2] * rhs.matrix[2][3] + matrix[0][3] * rhs.matrix[3][3];

        tk[1][0] = matrix[1][0] * rhs.matrix[0][0] + matrix[1][1] * rhs.matrix[1][0] + matrix[1][2] * rhs.matrix[2][0] + matrix[1][3] * rhs.matrix[3][0];
        tk[1][1] = matrix[1][0] * rhs.matrix[0][1] + matrix[1][1] * rhs.matrix[1][1] + matrix[1][2] * rhs.matrix[2][1] + matrix[1][3] * rhs.matrix[3][1];
        tk[1][2] = matrix[1][0] * rhs.matrix[0][2] + matrix[1][1] * rhs.matrix[1][2] + matrix[1][2] * rhs.matrix[2][2] + matrix[1][3] * rhs.matrix[3][2];
        tk[1][3] = matrix[1][0] * rhs.matrix[0][3] + matrix[1][1] * rhs.matrix[1][3] + matrix[1][2] * rhs.matrix[2][3] + matrix[1][3] * rhs.matrix[3][3];

        tk[2][0] = matrix[2][0] * rhs.matrix[0][0] + matrix[2][1] * rhs.matrix[1][0] + matrix[2][2] * rhs.matrix[2][0] + matrix[2][3] * rhs.matrix[3][0];
        tk[2][1] = matrix[2][0] * rhs.matrix[0][1] + matrix[2][1] * rhs.matrix[1][1] + matrix[2][2] * rhs.matrix[2][1] + matrix[2][3] * rhs.matrix[3][1];
        tk[2][2] = matrix[2][0] * rhs.matrix[0][2] + matrix[2][1] * rhs.matrix[1][2] + matrix[2][2] * rhs.matrix[2][2] + matrix[2][3] * rhs.matrix[3][2];
        tk[2][3] = matrix[2][0] * rhs.matrix[0][3] + matrix[2][1] * rhs.matrix[1][3] + matrix[2][2] * rhs.matrix[2][3] + matrix[2][3] * rhs.matrix[3][3];

        tk[3][0] = matrix[3][0] * rhs.matrix[0][0] + matrix[3][1] * rhs.matrix[1][0] + matrix[3][2] * rhs.matrix[2][0] + matrix[3][3] * rhs.matrix[3][0];
        tk[3][1] = matrix[3][0] * rhs.matrix[0][1] + matrix[3][1] * rhs.matrix[1][1] + matrix[3][2] * rhs.matrix[2][1] + matrix[3][3] * rhs.matrix[3][1];
        tk[3][2] = matrix[3][0] * rhs.matrix[0][2] + matrix[3][1] * rhs.matrix[1][2] + matrix[3][2] * rhs.matrix[2][2] + matrix[3][3] * rhs.matrix[3][2];
        tk[3][3] = matrix[3][0] * rhs.matrix[0][3] + matrix[3][1] * rhs.matrix[1][3] + matrix[3][2] * rhs.matrix[2][3] + matrix[3][3] * rhs.matrix[3][3];

        memcpy(matrix, tk, 4 * 4 * sizeof(type));
        return *this;
    }

    //! computes a minor of this matrix; 
    /*!      
        In linear algebra a minor of a matrix is the determinant of some smaller square matrix
        cut down from the matrix by removing one or more of its rows or columns.

        \param int r0 - row index of the 3x3 matrix for which we compute the determinant
        \param int r1 - row index of the 3x3 matrix for which we compute the determinant
        \param int r2 - row index of the 3x3 matrix for which we compute the determinant
        \param int c0 - column index of the 3x3 matrix for which we compute the determinant
        \param int c1 - column index of the 3x3 matrix for which we compute the determinant
        \param int c2 - column index of the 3x3 matrix for which we compute the determinant
        \return the minor      
    */
    inline type minor(int r0, int r1, int r2, int c0, int c1, int c2) const
    {
        return matrix[r0][c0] *(matrix[r1][c1] * matrix[r2][c2] - matrix[r2][c1] * matrix[r1][c2]) -
               matrix[r0][c1] *(matrix[r1][c0] * matrix[r2][c2] - matrix[r2][c0] * matrix[r1][c2]) +
               matrix[r0][c2] *(matrix[r1][c0] * matrix[r2][c1] - matrix[r2][c0] * matrix[r1][c1]);
    }

    //! computes the adjugate matrix of this matrix
    /*!      
        \return the adjugate matrix      
    */
    inline matrix4 adjugate() const
    {
        return matrix4(
                 minor(1, 2, 3, 1, 2, 3),
                -minor(0, 2, 3, 1, 2, 3),
                 minor(0, 1, 3, 1, 2, 3),
                -minor(0, 1, 2, 1, 2, 3),

                -minor(1, 2, 3, 0, 2, 3),
                 minor(0, 2, 3, 0, 2, 3),
                -minor(0, 1, 3, 0, 2, 3),
                 minor(0, 1, 2, 0, 2, 3),

                 minor(1, 2, 3, 0, 1, 3),
                -minor(0, 2, 3, 0, 1, 3),
                 minor(0, 1, 3, 0, 1, 3),
                -minor(0, 1, 2, 0, 1, 3),

                -minor(1, 2, 3, 0, 1, 2),
                 minor(0, 2, 3, 0, 1, 2),
                -minor(0, 1, 3, 0, 1, 2),
                 minor(0, 1, 2, 0, 1, 2)
            );
    }

    //! computes the determinant of this matrix
    /*!      
        \return the value of the determinant      
    */
    inline type determinant() const
    {
        return matrix[0][0] * minor(1, 2, 3, 1, 2, 3) -
               matrix[0][1] * minor(1, 2, 3, 0, 2, 3) +
               matrix[0][2] * minor(1, 2, 3, 0, 1, 3) -
               matrix[0][3] * minor(1, 2, 3, 0, 1, 2);
    }

    //! computes the inverse of this matrix
    /*!      
        \return the inverse of this matrix      
    */
    inline matrix4 inverse() const
    {
        return adjugate() * ((type)1 / determinant());
    }

    //! gives you the transpose of this matrix
    /*!      
        \return the matrix that is a transpose of this matrix      
    */
    inline matrix4 transpose() const
    {
        return matrix4(
            matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0],
            matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1],
            matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2],
            matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]
            );
    }

    //! computes the trace of this matrix
    /*!      
        \return the trace of this matrix      
    */
    inline type trace() const
    {
        return matrix[0][0] + matrix[1][1] + matrix[2][2] + matrix[3][3];
    }


    //! transforms this matrix by rotating it about Ox axis
    /*!      
        \param const type angle - the angle in radians
        \return this matrix rotated by angle radians about the Ox axis
    */
    inline matrix4& rotate_ox(const type angle)
    {
        type ca = (type)cos(angle);
        type sa = (type)sin(angle);

        matrix4<type> rotOX(
            (type)1, (type)0, (type)0, (type)0,
            (type)0,      ca,      sa, (type)0,
            (type)0,     -sa,      ca, (type)0,
            (type)0, (type)0, (type)0, (type)1
            );
        *this *= rotOX;

        return *this;
    }

    //! transforms this matrix by rotating it about Oy axis
    /*!      
        \param const type angle - the angle in radians
        \return this matrix rotated by angle radians about the Oy axis
    */
    inline matrix4& rotate_oy(const type angle)
    {
        type ca = (type)cos(angle);
        type sa = (type)sin(angle);
        matrix4 rotOY(
                 ca, (type)0,     -sa, (type)0,
            (type)0, (type)1, (type)0, (type)0,
                 sa, (type)0,      ca, (type)0,
            (type)0, (type)0, (type)0, (type)1
            );
        *this *= rotOY;

        return *this;
    }

    //! transforms this matrix by rotating it about Oz axis
    /*!      
        \param const type angle - the angle in radians
        \return this matrix rotated by angle radians about the Oz axis
    */
    inline matrix4& rotate_oz(const type angle)
    {
        type ca = (type)cos(angle);
        type sa = (type)sin(angle);
        matrix4 rotOZ(
                 ca,    -sa,  (type)0, (type)0,
                 sa,     ca,  (type)0, (type)0,
            (type)0, (type)0, (type)1, (type)0,
            (type)0, (type)0, (type)0, (type)1
            );
        *this *= rotOZ;

        return *this;
    }

    //! transforms this matrix by rotating it about an arbitrary axis
    /*!      
        \param const type angle - the angle in radians
        \param const vector3 & axis - the arbitrary axis to rotate this matrix about
        \return this matrix rotated by angle radians about the Oz axis      
    */
    inline matrix4& rotate_axis(const type angle, const vector3<type>& axis)
    {
        type ca = (type)cos(angle);
        type sa = (type)sin(angle);
        // axis.normalize();
        matrix4<type> rotAxis(
                     (type)(ca + (1 - ca) * axis.x * axis.x), (type)((1 - ca) * axis.x * axis.y - axis.z * sa) , (type)((1 - ca) * axis.x * axis.z + axis.y * sa), (type)0,
            (type)((1 - ca) * axis.x * axis.y + axis.z * sa),           (type)(ca + (1 - ca) * axis.y * axis.y), (type)((1 - ca) * axis.y * axis.z - axis.x * sa), (type)0,
            (type)((1 - ca) * axis.x * axis.z - axis.y * sa),  (type)((1 - ca) * axis.y * axis.z + axis.x * sa),          (type)(ca + (1 - ca) * axis.z * axis.z), (type)0,
                                                     (type)0,                                           (type)0,                                          (type)0, (type)1            
            );
        *this *= rotAxis;

        return *this;
    }

    //! translates the given vector using this as a transform matrix
    /*!      
        \param const vector3 & translateVector - the vector to translate
        \return this matrix (for chain operations)
    */
    inline matrix4& translate(const vector3<type>& translateVector)
    {
        matrix[3][0] = matrix[0][0] * translateVector.x + matrix[1][0] * translateVector.y + matrix[2][0] * translateVector.z + matrix[3][0];
        matrix[3][1] = matrix[0][1] * translateVector.x + matrix[1][1] * translateVector.y + matrix[2][1] * translateVector.z + matrix[3][1];
        matrix[3][2] = matrix[0][2] * translateVector.x + matrix[1][2] * translateVector.y + matrix[2][2] * translateVector.z + matrix[3][2];

        return *this;
    }

    //! translates a point using this as a transform matrix
    /*!      
        \param const type x - Ox axis coordinate
        \param const type y - Oy axis coordinate
        \param const type z - Oz axis coordinate
        \return this matrix (for chain operations)
    */
    inline matrix4 translate(const type x, const type y, const type z)
    {
        matrix[3][0] = matrix[0][0] * x + matrix[1][0] * y + matrix[2][0] * z + matrix[3][0];
        matrix[3][1] = matrix[0][1] * x + matrix[1][1] * y + matrix[2][1] * z + matrix[3][1];
        matrix[3][2] = matrix[0][2] * x + matrix[1][2] * y + matrix[2][2] * z + matrix[3][2];

        return *this;
    }

    //! transform the given vector using this as a transform matrix
    /*!      
        \param vector3 & vec - the vector to transform
    */
    inline void transform(vector3<type>& vec) const
    {
        type tvec[4] = {0};
        type tx = vec.x;
        type ty = vec.y;
        type tz = vec.z;
        type tw = (type)1;

        tvec[0] = matrix[0][0] * tx + matrix[0][1] * ty + matrix[0][2] * tz + matrix[0][3] * tw;
        tvec[1] = matrix[1][0] * tx + matrix[1][1] * ty + matrix[1][2] * tz + matrix[1][3] * tw;
        tvec[2] = matrix[2][0] * tx + matrix[2][1] * ty + matrix[2][2] * tz + matrix[2][3] * tw;
        tvec[3] = matrix[3][0] * tx + matrix[3][1] * ty + matrix[3][2] * tz + matrix[3][3] * tw;

        vec.x = tvec[0];
        vec.y = tvec[1];
        vec.z = tvec[2];
    }


    //! transforms the given point using this as a transform matrix
    /*!      
        \param type & x - the Ox coordinate
        \param type & y - the Oy coordinate
        \param type & z - the Oz coordinate
    */
    inline void transform(type& x, type& y, type& z) const
    {
        type tvec[4] = {0};
        type tx = x;
        type ty = y;
        type tz = z;
        /*type tw = (type)1;*/

        tvec[0] = matrix[0][0] * tx + matrix[0][1] * ty + matrix[0][2] * tz + matrix[0][3]/* * tw*/;
        tvec[1] = matrix[1][0] * tx + matrix[1][1] * ty + matrix[1][2] * tz + matrix[1][3]/* * tw*/;
        tvec[2] = matrix[2][0] * tx + matrix[2][1] * ty + matrix[2][2] * tz + matrix[2][3]/* * tw*/;
        tvec[3] = matrix[3][0] * tx + matrix[3][1] * ty + matrix[3][2] * tz + matrix[3][3]/* * tw*/;

        x = tvec[0];
        y = tvec[1];
        z = tvec[2];
    }


    //! builds a perspective projection matrix
    /*!      
        \param type fovY - the vertical opening of the viewing frustum
        \param type aspectRatio - the aspect ratio (fovX / fovY)
        \param type zNear - depth of the near plane
        \param type zFar - depth of the far plane
        \return the perspective projection matrix
    */
    static inline matrix4 perspective(type fovY, type aspectRatio, type zNear, type zFar)
    {
        type f = (type)1 / static_cast<type>(tan((0.5) * fovY));
        return matrix4
            (
                f / aspectRatio, (type)0,                             (type)0,                            (type)0,
                        (type)0,       f,                             (type)0,                            (type)0,
                        (type)0, (type)0,     (zFar + zNear) / (zNear - zFar),                           (type)-1,
                        (type)0, (type)0, (2 * zFar * zNear) / (zNear - zFar),                            (type)0
            );
    }


    //! computes the perspective parameters from this transform matrix
    /*!      
        \param type & fovY - the vertical opening of the viewing frustum - in degrees
        \param type & aspectRatio - the aspect ratio (fovX / fovY)
        \param type & zNear - the depth of the near plane
        \param type & zFar - the depth of the far plane
        \return 
            - true: the data was retrieved from the given matrix
            - false: the method was unable to retrieve the perspective data
    */
    inline bool data_from_perspective(type& fovY, type& aspectRatio, type& zNear, type& zFar)
    {
        if(matrix[1][1] != (type)0)
        {
            fovY = 2 * atan(1.0 / matrix[1][1]) * constants::math::rad_to_deg;        
        }
        else
        {
            return false;
        }
        if(matrix[0][0] != (type)0)
        {
            aspectRatio = matrix[1][1] / matrix[0][0];
        }
        else
        {
            return false;
        }
        if(matrix[2][2] - 1 != (type)0)
        {
            zNear = matrix[2][3] / (matrix[2][2] - 1);
        }
        else
        {
            return false;
        }
        if(matrix[2][2] + 1 != (type)0)
        {
            zFar = matrix[2][3] / (matrix[2][2] + 1);
        }
        else
        {
            return false;
        }
        return true;
    }


    //! builds a parallel perspective matrix 
    /*!      
        \param type left - the left boundary of the parallel perspective
        \param type right - the right boundary of the parallel perspective
        \param type bottom - the bottom boundary of the parallel perspective
        \param type top - the top boundary of the parallel perspective
        \param type near_ - near plane depth
        \param type far_ - the far plane depth
        \return the parallel projection matrix      
    */
    inline static matrix4 ortho(type left, type right, type bottom, type top, type near_, type far_)
    {
        type tx = -(right + left) / (right - left);
        type ty = -(top + bottom) / (top - bottom);
        type tz = -(far_ + near_) / (far_ - near_);

        return matrix4
            (
                  2 / (right - left),                  (type)0,                   (type)0,  (type)0,
                             (type)0, (type)2 / (top - bottom),                   (type)0,  (type)0,
                             (type)0,                  (type)0, (type)-2 / (far_ - near_),  (type)0,
                            (type)tx,                 (type)ty,                   (type)tz, (type)1
            );
    }

    //! casts this matrix from its type to the other type
    /*!      
        \return the casted matrix      
    */
    template <typename other>
    operator matrix4<other>() const
    {
        return matrix4<other>(
            (other)matrix[0][0], (other)matrix[0][1], (other)matrix[0][2], (other)matrix[0][3],
            (other)matrix[1][0], (other)matrix[1][1], (other)matrix[1][2], (other)matrix[1][3],
            (other)matrix[2][0], (other)matrix[2][1], (other)matrix[2][2], (other)matrix[2][3],
            (other)matrix[3][0], (other)matrix[3][1], (other)matrix[3][2], (other)matrix[3][3]
        );
    }

    //! checks if this matrix is equal to a right hand side matrix
    /*!      
        \param const matrix4 & rhs - the right hand side operator
        \return 
            - true: this matrix is the same as the right hand side matrix
            - false: this matrix is not the same as the right hand side matrix
    */
    const bool operator == (const matrix4& rhs) const
    {
        unsigned short chf = 0;
        for(int i = 0; i < 16; ++i)
        {
            chf |= constants::math::equals(vector[i], rhs.vector[i]) ? 1 << i : 0;
        }

        return chf == 0xFFFF ? true : false;
    }

    //! checks if this matrix is different from a right hand side matrix
    /*!      
        \param const matrix4 & rhs - the right hand side operator
        \return 
            - true: this matrix is not the same as the right hand side matrix
            - false: this matrix is the same as the right hand side matrix
    */
    const bool operator != (const matrix4& rhs) const
    {
        return !operator ==(rhs);
    }
};

template <class type>
const matrix4<type> matrix4<type>::identity;

#endif// __MATRIX4_H__