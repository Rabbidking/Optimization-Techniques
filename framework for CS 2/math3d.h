
#pragma once
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <cassert>
#include <memory>
#include <array>
#include <cstring>

//"""Classes for 2D and 3D matrix/vector math."""

// ~ Some of these functions (individually noted) are based on code from TDL.
// ~ The TDL copyright is as follows:
 
// ~ Copyright 2009, Google Inc.
// ~ All rights reserved.

// ~ Redistribution and use in source and binary forms, with or without
// ~ modification, are permitted provided that the following conditions are
// ~ met:

// ~ *  Redistributions of source code must retain the above copyright
// ~ notice, this list of conditions and the following disclaimer.
// ~ *  Redistributions in binary form must reproduce the above
// ~ copyright notice, this list of conditions and the following disclaimer
// ~ in the documentation and/or other materials provided with the
// ~ distribution.
// ~ *  Neither the name of Google Inc. nor the names of its
// ~ contributors may be used to endorse or promote products derived from
// ~ this software without specific prior written permission.

// ~ THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// ~ "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// ~ LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// ~ A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// ~ OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// ~ SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// ~ LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// ~ DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// ~ THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// ~ (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// ~ OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.




template<typename DataType,unsigned N,typename VecType>
class Matrix{
    
    typedef Matrix<DataType,N,VecType> MyType;
    
    public:
    DataType _M[N][4];
    
    Matrix(){
        std::memset(_M,0,sizeof(_M));
    }
    
    private:
    template<typename T>
    Matrix(const std::initializer_list<T>& L){
        if( L.size() != N*N )
            throw std::runtime_error("Bad number of arguments");
        auto x = L.begin();
        for(unsigned i=0;i<N;++i){
            for(unsigned j=0;j<N;++j){
                (*this)[i][j] = *x++;
            }
        }
    }
    public:

    Matrix(DataType m0, DataType m1, DataType m2, DataType m3) : Matrix({m0,m1,m2,m3}){}
    Matrix( DataType m0, DataType m1, DataType m2,
                DataType m3, DataType m4, DataType m5,
                DataType m6, DataType m7, DataType m8) : Matrix({m0,m1,m2,m3,m4,m5,m6,m7,m8}){}
    Matrix( DataType m0, DataType m1, DataType m2, DataType m3,
                DataType m4, DataType m5, DataType m6, DataType m7,
                DataType m8, DataType m9, DataType ma, DataType mb,
                DataType mc, DataType md, DataType me, DataType mf) : Matrix({m0,m1,m2,m3,m4,m5,m6,m7,m8,m9,ma,mb,mc,md,me,mf}){}
    
    MyType operator+(const MyType& m2) const {
        MyType r;
        for(unsigned i=0;i<N;++i){
            for(unsigned j=0;j<N;++j){
                r[i][j] = (*this)[i][j] + m2[i][j];
            }
        }
        return r;
    }
        
    MyType operator-(const MyType& m2) const {
        MyType r;
        for(unsigned i=0;i<N;++i){
            for(unsigned j=0;j<N;++j){
                r[i][j] = (*this)[i][j] - m2[i][j];
            }
        }
        return r;
    }
       
    MyType operator*(const MyType& o) const { 
        //mat * mat
        MyType R;
        for(unsigned i=0;i<N;++i){
            for(unsigned j=0;j<N;++j){
                DataType total=0;
                for(unsigned k=0;k<N;++k){
                    total += (*this)[i][k] * o[k][j];
                }
                R[i][j] = total;
            }
        }
        return R;
    }
    
    VecType operator*(const VecType& o) const { 
        //mat * vector
        VecType R;
        for(unsigned i=0;i<N;++i){
            DataType total = 0.0;
            for(unsigned j=0;j<N;++j){
                total += (*this)[i][j] * o[j];
            }
            R[i] = total;
        }
        return R;
    }

    MyType operator*(float o) const { 
        //mat * scalar
        MyType R;
        for(unsigned i=0;i<N;++i){
            for(unsigned j=0;j<N;++j){
                R[i][j] = (*this)[i][j] * o;
            }
        }
        return R;
    }
    MyType operator*(int o) const { 
        return *this * (float)o;
    }
    
    //Vector<N> operator*(const Vector<N>& v) const ;
    
    MyType operator+() const {
        return *this;
    }
    MyType operator-() const {
        return *this * -1.0f;
    }
    
    const void* tobytes() const {
        return _M;
    }
    
    struct MatRow{
        MyType& m;
        unsigned i;
        MatRow(MyType& mm,int ii) : m(mm), i(ii){ }
        DataType& operator[](unsigned j){
            //each row is padded out to be a vec4
            if( j >= N )
                throw std::runtime_error("Bad index");
            return this->m._M[i][j];
        }
    };
    struct CMatRow{
        const MyType& m;
        unsigned i;
        CMatRow(const MyType& mm,int ii) : m(mm), i(ii){ }
        DataType operator[](unsigned j) const {
            //each row is padded out to be a vec4
            if( j >= N )
                throw std::runtime_error("Bad index");
            //~ std::cout << "[" << i << "][" << j << "] = index " << i*4+j << "\n";
            return this->m._M[i][j];
        }
    };
    
    MatRow operator[](unsigned i) {
        return MatRow(*this,i);
    }
    CMatRow operator[](unsigned i) const  {
        return CMatRow(*this,i);
    }
        
    bool operator==(const MyType& o) const {
        for(unsigned i=0;i<N;++i){
            for(unsigned j=0;j<N;++j){
                if( (*this)[i][j] != o[i][j] )
                    return false;
            }
        }
        return true;
    }
    
    bool operator!=(const MyType& o) const {
        return ! (*this==o);
    }
    
    operator std::string() const {
        std::ostringstream oss;
        for(unsigned i=0;i<N;++i){
            oss << "[";
            for(unsigned j=0;j<N;++j){
                oss <<  (*this)[i][j] << "   ";
            }
            oss << "]\n";
        }
        return oss.str();
    }
        
    MyType transpose() const {
        MyType R;
        for(unsigned i=0;i<N;++i){
            for(unsigned j=0;j<N;++j){
                R[i][j] = (*this)[j][i];
            }
        }
        return R;
    }
    
    static MyType identity(){
        MyType R;
        for(unsigned i=0;i<N;++i){
            R[i][i]=1;
        }
        return R;
    }
};
 

template<typename A, unsigned int B, typename C>
Matrix<A,B,C> operator*( float f, const Matrix<A,B,C>& m){
    return m*f;
}
template<typename A, unsigned int B, typename C>
Matrix<A,B,C> operator*( double f, const Matrix<A,B,C>& m){
    return m*f;
}
template<typename A, unsigned int B, typename C>
Matrix<A,B,C> operator*( int f, const Matrix<A,B,C>& m){
    return m*f;
}
template<typename A, unsigned int B, typename C>
Matrix<A,B,C> operator*( unsigned f, const Matrix<A,B,C>& m){
    return m*f;
}

#define op2(op) \
    do{ \
        MyType r;                       \
        r.x = this->x op other.x;      \
        r.y = this->y op other.y;      \
        return r;                       \
    } while(0);
#define op3(op) \
    do{ \
        MyType r;                       \
        r.x = this->x op other.x;     \
        r.y = this->y op other.y;     \
        r.z = this->z op other.z;     \
        return r;                       \
    } while(0);
#define op4(op) \
    do{ \
        MyType r;                       \
        r.x = this->x op other.x;     \
        r.y = this->y op other.y;     \
        r.z = this->z op other.z;     \
        r.w = this->w op other.w;     \
        return r;                       \
    } while(0);

#define sop2(op) \
    do{ \
        MyType r;                       \
        r.x = this->x op other;      \
        r.y = this->y op other;      \
        return r;                       \
    } while(0);
#define sop3(op) \
    do{ \
        MyType r;                       \
        r.x = this->x op other;     \
        r.y = this->y op other;     \
        r.z = this->z op other;     \
        return r;                       \
    } while(0);
#define sop4(op) \
    do{ \
        MyType r;                       \
        r.x = this->x op other;     \
        r.y = this->y op other;     \
        r.z = this->z op other;     \
        r.w = this->w op other;     \
        return r;                       \
    } while(0);
    

template<typename T>
struct vec2Base {
    typedef vec2Base<T> MyType;
    T x,y;
    vec2Base(){
        x=y=0;
    }
    vec2Base(T x, T y){
        this->x=x;
        this->y=y;
    }
    vec2Base(const std::initializer_list<T>& L){
        assert(L.size()==2);
        auto F = L.begin();
        this->x = *F++;
        this->y = *F;;
    }
    
    T& operator[](unsigned key){
        switch(key){
            case 0: return x;
            case 1: return y;
            default:  throw std::runtime_error("Bad index");
        }
    }
    const T operator[](unsigned key) const{
        switch(key){
            case 0: return x;
            case 1: return y;
            default:  throw std::runtime_error("Bad index");
        }
    }
    
    unsigned len() const {
        return 2;
    }
    
    void operator+=(const MyType& o){
        x += o.x;
        y += o.y;
    }
    void operator-=(const MyType& o){
        x -= o.x;
        y -= o.y;
    }
    void operator*=(const MyType& o){
        x *= o.x;
        y *= o.y;
    }
    void operator/=(const MyType& o){
        x /= o.x;
        y /= o.y;
    }
    const vec2Base<T> xy(){ return vec2Base<T>(x,y); }
    
    //begin common functions
    MyType operator+(const MyType& other) const {       op2(+);     }
    MyType operator-(const MyType& other) const {       op2(-);     }
    MyType operator*(const MyType& other) const {       op2(*);     }
    MyType operator*(float other) const {               sop2(*);    }
    MyType operator*(double other) const {              sop2(*);    }
    MyType operator*(unsigned other) const {            sop2(*);    }
    MyType operator*(int other) const {                 sop2(*);    }
    float magnitudeSq() const {
        float total;
        total  = this->x*this->x;
        total += this->y*this->y;
        return total;
    }


    MyType operator-() const {
        return *this * -1.0f;
    }
    MyType operator+() const {
        return *this;
    }
    MyType operator/(float f){
        return  *this * float(1.0f/f);
    }
    MyType operator/(double f){
        return  *this * (1.0/f);
    }
    bool operator==(const MyType& o) const {
        for(unsigned i=0;i<len();++i){
            if((*this)[i] != o[i])
                return false;
        }
        return true;
    }

    bool operator!=(const MyType& o)const {
        return ! (*this == o);
    }

    float length() const {
        return magnitude();
    }

    float magnitude() const {
        return (float)sqrt(magnitudeSq());
    }

    MyType normalized() const {
        return  *this * 1.0f/magnitude() ;
    }

    bool isZero() const {
        return magnitudeSq() == 0.0f;
    }

    const std::unique_ptr<T[]> tobytes() const {
        std::unique_ptr<T[]> F(new T[len()]);
        for(unsigned i=0;i<len();++i)
            F[i] = (*this)[i];
        return F;
    }

    operator std::string() const {
        std::ostringstream oss;
        oss << "vec" << len() << "(";
        for(unsigned i=0;i<len();++i){
            oss << " " << (*this)[i];
        }
        oss << ")";
        return oss.str();
    }

};


 

template<typename T>
struct vec3Base{
    typedef vec3Base<T> MyType;
    T x,y,z;
    vec3Base(){
        x=y=z=0;
    }
    vec3Base(T x, T y, T z){
        this->x=x;
        this->y=y;
        this->z=z;
    }
    vec3Base(const std::initializer_list<T>& L){
        assert(L.size()==3);
        auto F = L.begin();
        this->x = *F++;
        this->y = *F++;
        this->z = *F;
    }
    T& operator[](unsigned key){
        switch(key){
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default:  throw std::runtime_error("Bad index");
        }
    }
    const T operator[](unsigned key) const{
        switch(key){
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default:  throw std::runtime_error("Bad index");
        }
    }
    
    unsigned len() const {
        return 3;
    }

    void operator+=(const MyType& o){
        x += o.x;
        y += o.y;
        z += o.z;
    }
    void operator-=(const MyType& o){
        x -= o.x;
        y -= o.y;
        z -= o.z;
    }
    void operator*=(const MyType& o){
        x *= o.x;
        y *= o.y;
        z *= o.z;
    }
    void operator/=(const MyType& o){
        x /= o.x;
        y /= o.y;
        z /= o.z;
    }

    
    const vec2Base<T> xy() const { return vec2Base<T>(x,y); }
    const vec3Base<T> xyz() const { return vec3Base<T>(x,y,z); }
    
    //begin common functions
    MyType operator+(const MyType& other) const {       op3(+);     }
    MyType operator-(const MyType& other) const {       op3(-);     }
    MyType operator*(const MyType& other) const {       op3(*);     }
    MyType operator*(float other) const {               sop3(*);    }
    MyType operator*(double other) const {              sop3(*);    }
    MyType operator*(unsigned other) const {            sop3(*);    }
    MyType operator*(int other) const {                 sop3(*);    }
    float magnitudeSq() const {
        float total;
        total  = this->x*this->x;
        total += this->y*this->y;
        total += this->z*this->z;
        return total;
    }


    MyType operator-() const {
        return *this * -1.0f;
    }
    MyType operator+() const {
        return *this;
    }
    MyType operator/(float f){
        return  *this * float(1.0f/f);
    }
    MyType operator/(double f){
        return  *this * (1.0/f);
    }
    bool operator==(const MyType& o) const {
        for(unsigned i=0;i<len();++i){
            if((*this)[i] != o[i])
                return false;
        }
        return true;
    }

    bool operator!=(const MyType& o)const {
        return ! (*this == o);
    }

    float length() const {
        return magnitude();
    }

    float magnitude() const {
        return (float)sqrt(magnitudeSq());
    }

    MyType normalized() const {
        return  *this * 1.0f/magnitude() ;
    }

    bool isZero() const {
        return magnitudeSq() == 0.0f;
    }

    const std::unique_ptr<T[]> tobytes() const {
        std::unique_ptr<T[]> F(new T[len()]);
        for(unsigned i=0;i<len();++i)
            F[i] = (*this)[i];
        return F;
    }

    operator std::string() const {
        std::ostringstream oss;
        oss << "vec" << len() << "(";
        for(unsigned i=0;i<len();++i){
            oss << " " << (*this)[i];
        }
        oss << ")";
        return oss.str();
    }
};


template<typename T>
struct vec4Base{
    typedef vec4Base<T> MyType;
    T x,y,z,w;
    vec4Base(){
        x=y=z=w=0;
    }
    vec4Base(T x, T y, T z, T w){
        this->x=x;
        this->y=y;
        this->z=z;
        this->w=w;
    }
    vec4Base(const vec3Base<T>& v, T w){
        this->x=v.x;
        this->y=v.y;
        this->z=v.z;
        this->w=w;
    }
    vec4Base(const std::initializer_list<T>& L){
        assert(L.size()==4);
        auto F = L.begin();
        this->x = *F++;
        this->y = *F++;
        this->z = *F++;
        this->w = *F++;
    }
    T& operator[](unsigned key){
        switch(key){
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default:  throw std::runtime_error("Bad index");
        }
    }
    const T operator[](unsigned key) const{
        switch(key){
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default:  throw std::runtime_error("Bad index");
        }
    }

    void operator+=(const MyType& o){
        x += o.x;
        y += o.y;
        z += o.z;
        w += o.w;
    }
    void operator-=(const MyType& o){
        x -= o.x;
        y -= o.y;
        z -= o.z;
        w -= o.w;
    }
    void operator*=(const MyType& o){
        x *= o.x;
        y *= o.y;
        z *= o.z;
        w *= o.w;
    }
    void operator/=(const MyType& o){
        x /= o.x;
        y /= o.y;
        z /= o.z;
        w /= o.w;
    }
    
    unsigned len() const {
        return 4;
    }
    
    const vec2Base<T> xy() const { return vec2Base<T>(x,y); }
    const vec3Base<T> xyz() const { return vec3Base<T>(x,y,z); }
    const vec4Base<T> xyzw() const{ return vec4Base<T>(x,y,z,w); }

    //begin common functions
    MyType operator+(const MyType& other) const {       op4(+);     }
    MyType operator-(const MyType& other) const {       op4(-);     }
    MyType operator*(const MyType& other) const {       op4(*);     }
    MyType operator*(float other) const {               sop4(*);    }
    MyType operator*(double other) const {              sop4(*);    }
    MyType operator*(unsigned other) const {            sop4(*);    }
    MyType operator*(int other) const {                 sop4(*);    }
    float magnitudeSq() const {
        float total;
        total  = this->x*this->x;
        total += this->y*this->y;
        total += this->z*this->z;
        total += this->w*this->w;
        return total;
    }


    MyType operator-() const {
        return *this * -1.0f;
    }
    MyType operator+() const {
        return *this;
    }
    MyType operator/(float f){
        return  *this * float(1.0f/f);
    }
    MyType operator/(double f){
        return  *this * (1.0/f);
    }
    bool operator==(const MyType& o) const {
        for(unsigned i=0;i<len();++i){
            if((*this)[i] != o[i])
                return false;
        }
        return true;
    }

    bool operator!=(const MyType& o)const {
        return ! (*this == o);
    }

    float length() const {
        return magnitude();
    }

    float magnitude() const {
        return (float)sqrt(magnitudeSq());
    }

    MyType normalized() const {
        return  *this * 1.0f/magnitude() ;
    }

    bool isZero() const {
        return magnitudeSq() == 0.0f;
    }

    const std::unique_ptr<T[]> tobytes() const {
        std::unique_ptr<T[]> F(new T[len()]);
        for(unsigned i=0;i<len();++i)
            F[i] = (*this)[i];
        return F;
    }

    operator std::string() const {
        std::ostringstream oss;
        oss << "vec" << len() << "(";
        for(unsigned i=0;i<len();++i){
            oss << " " << (*this)[i];
        }
        oss << ")";
        return oss.str();
    }
};

template<typename ST, typename VT>
inline vec2Base<VT> operator*(ST f, const vec2Base<VT>& v){
    return v*f;
}
template<typename ST, typename VT>
inline vec3Base<VT> operator*(ST f, const vec3Base<VT>& v){
    return v*f;
}
template<typename ST, typename VT>
inline vec4Base<VT> operator*(ST f, const vec4Base<VT>& v){
    return v*f;
}



typedef vec4Base<float> vec4;
typedef vec4Base<int32_t> ivec4;
typedef vec4Base<uint32_t> uvec4;
typedef vec3Base<float> vec3;
typedef vec3Base<int32_t> ivec3;
typedef vec3Base<uint32_t> uvec3;
typedef vec2Base<float> vec2;
typedef vec2Base<int32_t> ivec2;
typedef vec2Base<uint32_t> uvec2;
typedef Matrix<float,4,vec4> mat4;
typedef Matrix<float,3,vec3> mat3;
typedef Matrix<float,2,vec2> mat2;
typedef Matrix<int32_t,4,ivec4> imat4;
typedef Matrix<int32_t,3,ivec3> imat3;
typedef Matrix<int32_t,2,ivec2> imat2;



//vector-matrix multiplication
template<typename VT, typename MT, unsigned int n>
VT operator*(const VT& v, const Matrix<MT,n,VT>& o)  {
    VT R;
    for(unsigned i=0;i<n;++i){
        float total=0;
        for(unsigned j=0;j<n;++j){
            total += v[j]*o[j][i];
        }
        R[i]=total;
    }
    return R;
}


inline
float dot(const vec2& v, const vec2& w){
    return v.x*w.x + v.y*w.y;
}
inline
float dot(const vec3& v, const vec3& w){
    return v.x*w.x + v.y*w.y + v.z*w.z;
}
inline
float dot(const vec4& v, const vec4& w){
    return v.x*w.x + v.y*w.y + v.z*w.z + v.w*w.w;
}

template<typename T>
float dot(const T& v, const T& w){
    float total = 0;
    for(unsigned i=0;i<v.len();++i){
        total += v[i]*w[i];
    }
    return total;
}

inline
vec3 cross(const vec3& v, const vec3& w){
    return vec3(
        v.y*w.z - w.y*v.z,
        w.x*v.z - v.x*w.z,
        v.x*w.y - w.x*v.y
    );
}

inline
vec3 cross(const vec4& v, const vec4& w){
    return cross(v.xyz(),w.xyz());
}
inline
vec3 cross(const vec4& v, const vec3& w){
    return cross(v.xyz(),w);
}
inline
vec3 cross(const vec3& v, const vec4& w){
    return cross(v,w.xyz());
}


template<typename T>
float length(const T& v){
    return v.length();
}

template<typename T>
T normalize(const T& v){
    auto le=1.0f/length(v);
    return le*v;
}

template<typename T>
T transpose(const T& m){
    return m.transpose();
}

// ~ def det(M) const {
    // ~ """Return matrix determinant. From TDL.
    // ~ @param M: matrix
    // ~ @rtype: number
    // ~ """
    // ~ if type(M) == mat2:
        // ~ return m[0][0]*m[1][1] - m[0][1]*m[1][0]
    // ~ elif type(M) == mat3:
        // ~ return m[2][2] * (m[0][0] * m[1][1] - m[0][1] * m[1][0]) -              m[2][1] * (m[0][0] * m[1][2] - m[0][2] * m[1][0]) +                m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1])
    // ~ elif type(M) == mat4:
        // ~ t01 = m[0][0] * m[1][1] - m[0][1] * m[1][0]
        // ~ t02 = m[0][0] * m[1][2] - m[0][2] * m[1][0]
        // ~ t03 = m[0][0] * m[1][3] - m[0][3] * m[1][0]
        // ~ t12 = m[0][1] * m[1][2] - m[0][2] * m[1][1]
        // ~ t13 = m[0][1] * m[1][3] - m[0][3] * m[1][1]
        // ~ t23 = m[0][2] * m[1][3] - m[0][3] * m[1][2]
        // ~ return (m[3][3] * (m[2][2] * t01 - m[2][1] * t02 + m[2][0] * t12) -
             // ~ m[3][2] * (m[2][3] * t01 - m[2][1] * t03 + m[2][0] * t13) +
             // ~ m[3][1] * (m[2][3] * t02 - m[2][2] * t03 + m[2][0] * t23) -
             // ~ m[3][0] * (m[2][3] * t12 - m[2][2] * t13 + m[2][1] * t23) )
    // ~ else:
        // ~ assert 0

inline
mat2 inverse(const mat2& m){
    //Return matrix inverse. From TDL.
    auto d = 1.0f / (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
    return mat2(d * m[1][1], -d * m[0][1], -d * m[1][0], d * m[0][0]);
}
    
inline
mat3 inverse(const mat3& m){
    //Return matrix inverse. From TDL.
    auto t00 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
    auto t10 = m[0][1] * m[2][2] - m[0][2] * m[2][1];
    auto t20 = m[0][1] * m[1][2] - m[0][2] * m[1][1];
    auto d = 1.0f / (m[0][0] * t00 - m[1][0] * t10 + m[2][0] * t20);
    return mat3( d * t00, -d * t10, d * t20,
          -d * (m[1][0] * m[2][2] - m[1][2] * m[2][0]),
           d * (m[0][0] * m[2][2] - m[0][2] * m[2][0]),
          -d * (m[0][0] * m[1][2] - m[0][2] * m[1][0]),
           d * (m[1][0] * m[2][1] - m[1][1] * m[2][0]),
          -d * (m[0][0] * m[2][1] - m[0][1] * m[2][0]),
           d * (m[0][0] * m[1][1] - m[0][1] * m[1][0]) );
}
inline
mat4 inverse(const mat4& m){
    //Return matrix inverse. From TDL.

    auto tmp_0 = m[2][2] * m[3][3];
    auto tmp_1 = m[3][2] * m[2][3];
    auto tmp_2 = m[1][2] * m[3][3];
    auto tmp_3 = m[3][2] * m[1][3];
    auto tmp_4 = m[1][2] * m[2][3];
    auto tmp_5 = m[2][2] * m[1][3];
    auto tmp_6 = m[0][2] * m[3][3];
    auto tmp_7 = m[3][2] * m[0][3];
    auto tmp_8 = m[0][2] * m[2][3];
    auto tmp_9 = m[2][2] * m[0][3];
    auto tmp_10 = m[0][2] * m[1][3];
    auto tmp_11 = m[1][2] * m[0][3];
    auto tmp_12 = m[2][0] * m[3][1];
    auto tmp_13 = m[3][0] * m[2][1];
    auto tmp_14 = m[1][0] * m[3][1];
    auto tmp_15 = m[3][0] * m[1][1];
    auto tmp_16 = m[1][0] * m[2][1];
    auto tmp_17 = m[2][0] * m[1][1];
    auto tmp_18 = m[0][0] * m[3][1];
    auto tmp_19 = m[3][0] * m[0][1];
    auto tmp_20 = m[0][0] * m[2][1];
    auto tmp_21 = m[2][0] * m[0][1];
    auto tmp_22 = m[0][0] * m[1][1];
    auto tmp_23 = m[1][0] * m[0][1];

    auto t0 = (tmp_0 * m[1][1] + tmp_3 * m[2][1] + tmp_4 * m[3][1]) -        (tmp_1 * m[1][1] + tmp_2 * m[2][1] + tmp_5 * m[3][1]);
    auto t1 = (tmp_1 * m[0][1] + tmp_6 * m[2][1] + tmp_9 * m[3][1]) -        (tmp_0 * m[0][1] + tmp_7 * m[2][1] + tmp_8 * m[3][1]);
    auto t2 = (tmp_2 * m[0][1] + tmp_7 * m[1][1] + tmp_10 * m[3][1]) -        (tmp_3 * m[0][1] + tmp_6 * m[1][1] + tmp_11 * m[3][1]);
    auto t3 = (tmp_5 * m[0][1] + tmp_8 * m[1][1] + tmp_11 * m[2][1]) -        (tmp_4 * m[0][1] + tmp_9 * m[1][1] + tmp_10 * m[2][1]);
    auto d = 1.0f / (m[0][0] * t0 + m[1][0] * t1 + m[2][0] * t2 + m[3][0] * t3);

    return mat4(d * t0, d * t1, d * t2, d * t3,
       d * ((tmp_1 * m[1][0] + tmp_2 * m[2][0] + tmp_5 * m[3][0]) -
          (tmp_0 * m[1][0] + tmp_3 * m[2][0] + tmp_4 * m[3][0])),
       d * ((tmp_0 * m[0][0] + tmp_7 * m[2][0] + tmp_8 * m[3][0]) -
          (tmp_1 * m[0][0] + tmp_6 * m[2][0] + tmp_9 * m[3][0])),
       d * ((tmp_3 * m[0][0] + tmp_6 * m[1][0] + tmp_11 * m[3][0]) -
          (tmp_2 * m[0][0] + tmp_7 * m[1][0] + tmp_10 * m[3][0])),
       d * ((tmp_4 * m[0][0] + tmp_9 * m[1][0] + tmp_10 * m[2][0]) -
          (tmp_5 * m[0][0] + tmp_8 * m[1][0] + tmp_11 * m[2][0])),
       d * ((tmp_12 * m[1][3] + tmp_15 * m[2][3] + tmp_16 * m[3][3]) -
          (tmp_13 * m[1][3] + tmp_14 * m[2][3] + tmp_17 * m[3][3])),
       d * ((tmp_13 * m[0][3] + tmp_18 * m[2][3] + tmp_21 * m[3][3]) -
          (tmp_12 * m[0][3] + tmp_19 * m[2][3] + tmp_20 * m[3][3])),
       d * ((tmp_14 * m[0][3] + tmp_19 * m[1][3] + tmp_22 * m[3][3]) -
          (tmp_15 * m[0][3] + tmp_18 * m[1][3] + tmp_23 * m[3][3])),
       d * ((tmp_17 * m[0][3] + tmp_20 * m[1][3] + tmp_23 * m[2][3]) -
          (tmp_16 * m[0][3] + tmp_21 * m[1][3] + tmp_22 * m[2][3])),
       d * ((tmp_14 * m[2][2] + tmp_17 * m[3][2] + tmp_13 * m[1][2]) -
          (tmp_16 * m[3][2] + tmp_12 * m[1][2] + tmp_15 * m[2][2])),
       d * ((tmp_20 * m[3][2] + tmp_12 * m[0][2] + tmp_19 * m[2][2]) -
          (tmp_18 * m[2][2] + tmp_21 * m[3][2] + tmp_13 * m[0][2])),
       d * ((tmp_18 * m[1][2] + tmp_23 * m[3][2] + tmp_15 * m[0][2]) -
          (tmp_22 * m[3][2] + tmp_14 * m[0][2] + tmp_19 * m[1][2])),
       d * ((tmp_22 * m[2][2] + tmp_16 * m[0][2] + tmp_21 * m[1][2]) -
          (tmp_20 * m[1][2] + tmp_23 * m[2][2] + tmp_17 * m[0][2])));
}

    

    
inline
mat4 axisRotation(const vec3& axis, float angle){
    //from TDL
    //axis=normalize(axis)
    float x = axis[0],
    y = axis[1],
    z = axis[2],
    xx = x * x,
    yy = y * y,
    zz = z * z,
    c = (float)cos(angle),
    s = (float)sin(angle),
    oneMinusCosine = 1 - c,
    zs = z*s,
    xs = x*s,
    ys = y*s,
    xy = x*y,
    xz = x*z,
    yz = y*z;
    return mat4(
        xx + (1 - xx) * c,
        xy * oneMinusCosine + zs,
        xz * oneMinusCosine - ys,
        0,
        xy * oneMinusCosine - zs,
        yy + (1 - yy) * c,
        yz * oneMinusCosine + xs,
        0,
        xz * oneMinusCosine + ys,
        yz * oneMinusCosine - xs,
        zz + (1 - zz) * c,
        0,
        0, 0, 0, 1
    );
}

inline
mat4 axisRotation(const vec4& axis, float angle){
    return axisRotation(axis.xyz(),angle);
}
  
inline
mat4 scaling(const vec3& v)  {
    //Return scaling matrix. From TDL.
    return mat4( 
        v[0], 0,0,0,
        0,v[1],0,0,
        0,0,v[2],0,
        0,0,0,1);
}

inline
mat4 scaling(float x, float y, float z)  {
    return scaling(vec3(x,y,z));
}
   
inline
mat4 scaling(float x)  {
    return scaling(vec3(x,x,x));
}

inline
mat4 translation(const vec3& v) {
    //Return translation matrix. From TDL.
    return mat4(
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        v[0],v[1],v[2],1);
}

inline
mat4 translation(const vec4& v) {
    return translation(v.xyz());
}
    
inline
mat4 translation(float x, float y, float z) {
    return translation(vec3(x,y,z));
}

inline
mat3 translation2(const vec2& v){
    return mat3(
        1,0,0,
        0,1,0,
        v[0],v[1],1);
}

inline
mat3 scaling2(const vec2& v){
    return mat3(v[0],0,0,
                0,v[1],0,
                0,0,1);
}

inline
mat3 rotation2(float angle){
    /**Return 2D rotation matrix.
        @type angle: float
        @param angle: Angle in radians
        @rtype:mat3
    */
    auto c=(float)cos(angle),
    s=(float)sin(angle);
    return mat3( c,s,0,     -s,c,0,     0,0,1 );
}

inline    
std::ostream& operator<<(std::ostream& o, const vec4& v){
    o << (std::string)v;
    return o;
}
inline
std::ostream& operator<<(std::ostream& o, const vec3& v){
    o << (std::string)v;
    return o;
}
inline
std::ostream& operator<<(std::ostream& o, const vec2& v){
    o << (std::string)v;
    return o;
}
inline
std::ostream& operator<<(std::ostream& o, const mat4& v){
    o << (std::string)v;
    return o;
}
inline
std::ostream& operator<<(std::ostream& o, const mat3& v){
    o << (std::string)v;
    return o;
}
inline
std::ostream& operator<<(std::ostream& o, const mat2& v){
    o << (std::string)v;
    return o;
}

inline
float radians(float deg){
    return deg/180.0f * 3.14159265358979323f;
}

static_assert(sizeof(vec2) == 8, "");
static_assert(sizeof(vec3) == 12, "");
static_assert(sizeof(vec4) == 16, "");
static_assert(sizeof(ivec2) == 8, "");
static_assert(sizeof(ivec3) == 12, "");
static_assert(sizeof(ivec4) == 16, "");
static_assert(sizeof(mat2) == 32, "");
static_assert(sizeof(mat3) == 48, "");
static_assert(sizeof(mat4) == 64, "");

#ifdef MATH3DTEST
void math3dTest()
{
    using namespace std;
    cout << "sizes:\n";
    cout << "vec2: " << sizeof(vec2) << "\n";
    cout << "vec3: " << sizeof(vec3) << "\n";
    cout << "vec4: " << sizeof(vec4) << "\n";
    cout << "mat2: " << sizeof(mat2) << "\n";
    cout << "mat3: " << sizeof(mat3) << "\n";
    cout << "mat4: " << sizeof(mat4) << "\n";
    
    {
        //vector<float> la({3,-1,4,6});
        //vector<float> lb({2,5,8,9});
        vec4 a = vec4(3,-1,4,6);
        vec4 b(2,5,8,9);
        assert( a+b == vec4(5,4,12,15));
        //assert( a+lb == a+b);
        //assert( la+b == a+b);
        assert( a-b == vec4(1,-6,-4,-3));
        //assert( a-lb == a-b)
        //assert( la-b == a-b)
        assert( a != b);
        assert( a*b == vec4(6,-5,32,54));
        //assert( a*lb == [6,-5,32,54]);
        //assert( la*b == [6,-5,32,54]);
        assert( 2*a == vec4(6,-2,8,12));
        assert( a*2 == 2*a);
        assert( -a == vec4(-3,1,-4,-6));
        assert( a == +a);
        (string)a;
        //assert( a.copy() == a);
        auto c=vec4();
        assert( c.isZero() );
        assert( c == vec4(0,0,0,0));
        assert( c[0] == 0);
        assert( c[1] == 0);
        assert( c[2] == 0);
        assert( c[3] == 0);
        assert( !a.isZero() );
        c[0]=1;
        c[1]=3;
        c[2]=5;
        c[3]=9;
        assert( c == vec4(1,3,5,9));
        //assert( c == [1,3,5,9])
        //assert( c != [2,4,6,8])
        assert( c[0] == 1);
        assert( c.x == 1);
        assert( c[1] == 3);
        assert( c.y == 3);
        assert( c[2] == 5);
        assert( c.z == 5);
        assert( c[3] == 9);
        assert( c.w == 9);
        assert( c.xy() == vec2(1,3));
        assert( c.xyz() == vec3(1,3,5));
        c.x = 8;
        c.y = 9;
        c.z = -8;
        c.w = -7;
        assert( c == vec4(8,9,-8,-7));
        //c.xy() = vec2(3,2);
        //assert( c == vec4(3,2,-8,-7));
        //c.xyz() = vec3(13,12,11);
        //assert( c == vec4(13,12,11,-7));
        //c.xyzw() = vec4(13,12,11,10);
        //assert( c == vec4(13,12,11,10));
        //assert( len(a) == 4);
        {
            vector<float> tmp;
            for(int i=0;i<a.len();++i)  tmp.push_back(a[i]);
            assert(tmp.size() == 4);
            assert(tmp[0] == a[0]);
            assert(tmp[1] == a[1]);
            assert(tmp[2] == a[2]);
            assert(tmp[3] == a[3]);
        }
        assert( length(a) == a.magnitude() );
        assert( abs(length(a)-7.874) < 0.001);
        a.tobytes();
        auto n=a.normalized();
        auto n2=normalize(a);
        assert( n== n2);
        auto n3 = vec4(0.381,-0.127, 0.508, 0.762);
        for(unsigned i=0;i<4;++i){
            assert( abs(n3[i] - n[i]) < 0.001);
        }
        assert( dot(a,b) == 87);
    }
    
    //////
    {
        
        //la = [3,-1,4]
        //lb = [2,5,8]
        auto a = vec3(3,-1,4);
        auto b = vec3(2,5,8);
        assert( a+b == vec3(5,4,12));
        //assert( a+lb == a+b);
        //assert( la+b == a+b);
        assert( a-b == vec3(1,-6,-4));
        //assert( a-lb == a-b);
        //assert( la-b == a-b);
        assert( a != b);
        assert( a*b == vec3(6,-5,32));
        //assert( a*lb == vec3(6,-5,32));
        //assert( la*b == vec3(6,-5,32));
        assert( 2*a == vec3(6,-2,8));
        assert( a*2 == 2*a);
        assert( -a == vec3(-3,1,-4));
        assert( a == +a);
        //assert( id(a) != id(+a));
        //str(a);
        //repr(a);
        //assert( a.copy() == a);
        //assert( id(a.copy()) != a);
        auto c=vec3();
        assert( c.isZero() );
        assert( c == vec3(0,0,0));
        assert( c[0] == 0);
        assert( c[1] == 0);
        assert( c[2] == 0);
        assert( not a.isZero() );
        c[0]=1;
        c[1]=3;
        c[2]=5;
        assert( c == vec3(1,3,5));
        //assert( c == vec3(1,3,5));
        assert( c != vec3(2,4,6));
        assert( c[0] == 1);
        assert( c.x == 1);
        assert( c[1] == 3);
        assert( c.y == 3);
        assert( c[2] == 5);
        assert( c.z == 5);
        assert( c.xy() == vec2(1,3));
        assert( c.xyz() == vec3(1,3,5));
        c.x = 8;
        c.y = 9;
        c.z= -8;
        assert( c == vec3(8,9,-8));
        //~ c.xy = vec2(3,2);
        //~ assert( c == (3,2,-8));
        //~ c.xyz = vec3(13,12,11);
        //~ assert( c == vec3(13,12,11));
        //assert( len(a) == 3);
        vector<float> tmp;
        for(int i=0;i<a.len();++i)  tmp.push_back(a[i]);
        assert(tmp[0] == a.x);
        assert(tmp[1] == a.y);
        assert(tmp[2] == a.z);
        //assert( tmp == la);
        assert( length(a) == a.magnitude());
        a.tobytes();
        auto n=a.normalized();
        auto n2=normalize(a);
        assert( n==n2 );
        auto n3 = vec3(0.58834, -0.196116, 0.7844);
        for(unsigned i=0;i<3;++i){
            assert( abs(n3[i] - n2[i]) < 0.001);
        }
        assert( abs(length(a)-5.099) < 0.001);
        assert( dot(a,b) == 33);
    }
    
    {
        //////////////////////////////////////////////////////////
        vector<float> la({3.0,-1.0});
        auto a = vec2(3,-1);
        auto b = vec2(2,5);
        assert( a+b == vec2(5,4));
        //assert( a+lb == a+b)
        //assert( la+b == a+b)
        assert( a-b == vec2(1,-6));
        //~ assert( a-lb == a-b);
        //~ assert( la-b == a-b)
        assert( a != b);
        assert( a*b == vec2(6,-5));
        //assert( a*lb == vec2(6,-5));
        //assert( la*b == vec2(6,-5));
        assert( 2*a == vec2(6,-2));
        assert( a*2 == 2*a);
        assert( -a == vec2(-3,1));
        assert( a == +a);
        //~ assert( id(a) != id(+a))
        (string)a;
        //~ repr(a)
        //assert( a.copy() == a);
        //~ assert( id(a.copy()) != a)
        auto c=vec2();
        assert( c.isZero() );
        assert( c == vec2(0,0));
        assert( c[0] == 0);
        assert( c[1] == 0);
        assert( !a.isZero());
        c[0]=1;
        c[1]=3;
        assert( c == vec2(1,3));
        assert( c == vec2(1,3));
        assert( c != vec2(2,4));
        assert( c[0] == 1);
        assert( c.x == 1);
        assert( c[1] == 3);
        assert( c.y == 3);
        assert( c.xy() == vec2(1,3));
        c.x = 8;
        c.y = 9;
        assert( c == vec2(8,9));
        //~ c.xy = vec2(3,2)
        //~ assert( c == vec2(3,2))
        //~ assert( len(a) == 2)
        vector<float> tmp;
        for(int i=0;i<a.len();++i)  tmp.push_back(a[i]);
        assert( tmp == la);
        assert( length(a) == a.magnitude());
        a.tobytes();
        auto n=a.normalized();
        auto n2=normalize(a);
        assert( n==n2);
        auto n3 = vec2(0.94868,-0.31622);
        for(unsigned i=0;i<2;++i){
            assert( abs(n3[i] - n[i]) < 0.001);
        }
        assert( abs(length(a)-3.162277) < 0.001);
        assert( dot(a,b) == 1);
    }
    
    ////////////////////////////////////
    {
        auto a = mat4( 3,1,4,5,
                  9,2,6,7,
                  8,-3,-1,-4,
                  -5,-2,-7,-6);
                  
        auto b = mat4( -2,-7,3,8,
                  -1,-5,-10,12,
                  -4,7,2,4,
                  5,-8,1,-3);
        assert( a*b == mat4(
            2,-38,12,37,
            -9,-87,26,99,
            -29,-16,48,36,
            10,44,-15,-74));
        assert( a != b);
        auto c=mat4();
        for(unsigned i=0;i<4;++i){
            for(unsigned j=0;j<4;++j){
                assert( c[i][j] == 0);
            }
        }
          
        {  
            float x[4][4] = {
                    {3,1,4,5},
                    {9,2,6,7},
                    {8,-3,-1,-4},
                    {-5,-2,-7,-6}
            };
            for(unsigned i=0;i<4;++i){
                for(unsigned j=0;j<4;++j){
                    c[i][j] = x[i][j];
                }
            }
            assert( c == a);
            for(unsigned i=0;i<4;++i){
                for(unsigned j=0;j<4;++j){
                    assert( c[i][j] == x[i][j]);
                }
            }
        }
        
        assert( a+b == mat4(1,-6,7,13,8,-3,-4,19,4,4,1,0,0,-10,-6,-9));
        assert( a-b == a+-1*b);
        assert( 2*a == mat4(6,2,8,10,18,4,12,14,16,-6,-2,-8,-10,-4,-14,-12));
        assert( 2*a == a*2 );
        
        c=+a;
        //~ assert( id(c) != id(a))
        assert( c == a);
        assert( -a == -1*a);
        c = -a;
        assert( c == mat4( 
                    -3,-1,-4,-5,
                    -9,-2,-6,-7,
                    -8,3,1,4,
                    5,2,7,6));
        a.tobytes();
        (string)a;
        //~ repr(a)
        assert( transpose(a) == mat4( 3,9,8,-5, 1,2,-3,-2, 4,6,-1,-7, 5,7,-4,-6));
        auto x = inverse(a) * a ;
        auto y = a * inverse(a);
        for(unsigned i=0;i<4;++i){
            for(unsigned j=0;j<4;++j){
                assert( abs(x[i][j] - y[i][j] < 0.001));
                if(i == j)
                    assert( abs(x[i][j] - 1) < 0.001);
                else
                    assert( abs(x[i][j]) < 0.001);
            }
        }
                    
        assert( a*vec4(0.5,1.5,2.5,4.5) == vec4(35.5,54,-21,-50));
        assert( vec4(0.5,1.5,2.5,4.5)*a == vec4(12.5,-13,-23,-24));
        assert( a*vec4(0.5,1.5,2.5,4.5) == vec4(35.5,54,-21,-50));
        assert( vec4(0.5,1.5,2.5,4.5)*a == vec4(12.5,-13,-23,-24));
        assert( a*vec4(0.5,1.5,2.5,4.5) == vec4(35.5,54,-21,-50));
        assert( vec4(0.5,1.5,2.5,4.5)*a == vec4(12.5,-13,-23,-24));
    }
    
    //////////////////////////////////////
    ////////////////////////////////////
    {
        auto a = mat3( 
                    3, 1, 4,
                    9, 2, 6,
                    8,-3,-1);
        auto b = mat3( 
                    -2,-7,  3,
                    -1,-5,-10,
                    -4, 7,  2);
                  
        assert( a*b == mat3(
            -23,2,7,  -44,-31,19,  -9,-48,52 ));
            
        assert( a != b);
        auto c=mat3();
        for(unsigned i=0;i<3;++i){
            for(unsigned j=0;j<3;++j){
                assert( c[i][j] == 0);
            }
        }
             
        {
            float x[3][3] ={     
                    {3,1,4},
                    {9,2,6},
                    {8,-3,-1} 
            };
            for(unsigned i=0;i<3;++i){
                for(unsigned j=0;j<3;++j){
                    c[i][j] = x[i][j];
                }
            }
            assert( c == a);
            for(unsigned i=0;i<3;++i){
                for(unsigned j=0;j<3;++j){
                    assert( c[i][j] == x[i][j]);
                }
            }
        }
        assert( a+b == mat3(1,-6,7,8,-3,-4,4,4,1));
        assert( a-b == a+-1*b);
        assert( 2*a == mat3(6,2,8,   18,4,12,    16,-6,-2));
        assert( 2*a == a*2        );
        
        c=+a;
        //~ assert( id(c) != id(a))
        assert( c == a);
        assert( -a == -1*a);
        c=-a;
        assert( c == mat3( 
                    -3,-1,-4,
                    -9,-2,-6,
                    -8,3,1));
        a.tobytes();
        (string)a;
        //~ repr(a)
        assert( transpose(a) == mat3( 3,9,8, 1,2,-3,   4,6,-1 ));
        
        auto x = inverse(a) * a ;
        auto y = a * inverse(a);
        for(unsigned i=0;i<3;++i){
            for(unsigned j=0;j<3;++j){
                assert( abs(x[i][j] - y[i][j] < 0.001));
                if(i == j)
                    assert( abs(x[i][j] - 1) < 0.001);
                else
                    assert( abs(x[i][j]) < 0.001);
            }
        }
        assert( a*vec3(0.5,1.5,2.5) == vec3(13,22.5,-3));
        assert( vec3(0.5,1.5,2.5)*a == vec3(35,-4,8.5));
        assert( a*vec3(0.5,1.5,2.5) == vec3(13,22.5,-3));
        assert( vec3(0.5,1.5,2.5)*a == vec3(35,-4,8.5));
    }
    
    //////////////////////////////////////////////////////////////////
    {
        auto a = mat2( 3,1,
                  9,2 );
        auto b = mat2( -2,-7,
                  -1,-5 );
        assert( a*b == mat2( -7,-26, -20, -73 ));
        assert( a != b);
        auto c=mat2();
        for(unsigned i=0;i<2;++i){
            for(unsigned j=0;j<2;++j){
                assert( c[i][j] == 0);
            }
        }
        {
            float x[2][2] = { {3,1},{9,2} };
            for(unsigned i=0;i<2;++i){
                for(unsigned j=0;j<2;++j){
                    c[i][j] = x[i][j];
                }
            }
            assert( c == a);
            for(unsigned i=0;i<2;++i){
                for(unsigned j=0;j<2;++j){
                    assert( c[i][j] == x[i][j]);
                }
            }
        }    
        assert( a+b == mat2(1,-6,    8,-3  ));
        assert( a-b == a+-1*b);
        assert( 2*a == mat2(6,2,  18,4  ));
        assert( 2*a == a*2        );
        
        c=+a;
        //~ assert( id(c) != id(a))
        assert( c == a);
        assert( -a == -1*a);
        c=-a;
        assert( c == mat2( -3,-1, -9,-2 ));
        a.tobytes();
        (string)a;
        assert( transpose(a) == mat2( 3,9, 1,2 ));
        
        auto x = inverse(a) * a ;
        auto y = a * inverse(a);
        for(unsigned i=0;i<2;++i){
            for(unsigned j=0;j<2;++j){
                assert( abs(x[i][j] - y[i][j] < 0.001));
                if(i == j)
                    assert( abs(x[i][j] - 1) < 0.001);
                else
                    assert( abs(x[i][j]) < 0.001);
            }
        }
        assert( a*vec2(0.5,1.5) == vec2(3,7.5));
        assert( vec2(0.5,1.5)*a == vec2(15,3.5));
        assert( a*vec2(0.5,1.5) == vec2(3,7.5));
        assert( vec2(0.5,1.5)*a == vec2(15,3.5));
    }
    
    ////////////////////////////////////
    auto c = cross( vec3(2,5,9), vec3(0.5,1.5,3.5) );
    assert( c == vec3(4,-2.5,.5));
    
    c = cross( vec4(2,5,9,0), vec4(0.5,1.5,3.5,0) );
    assert( c == vec3(4,-2.5,.5));

    c = cross( vec4(2,5,9,0), vec4(0.5,1.5,3.5,0) );
    assert( c == vec3(4,-2.5,.5));

    
    //axisRotation, scaling,
    //translation,
     
    //~ v2a=vec2(2,4);
    //~ v2b=vec2(10,11);
    
    //~ assert( v2a+v2b == vec2(12,15));
    //~ assert( v2a-v2b == vec2(-8,-7));
    //~ assert( v2a+v2b != vec2(12,3));
    //~ assert( v2a+v2b != vec2(3,15));
    //~ assert( v2a*v2b == vec2(20,44));
    //~ assert( 5*v2a == vec2(10,20));
    //~ assert( v2a*5 == vec2(10,20));
    
    //~ assert( v2a.xy() == v2a);
    
    //~ v3a=vec3(2,4,6);
    //~ v3b=vec3(10,11,12);
    
    //~ assert( v3a+v3b == vec3(12,15,18));
    //~ assert( v3a-v3b == vec3(-8,-7,-6));
    //~ assert( v3a+v3b != vec3(12,3,18));
    //~ assert( v3a+v3b != vec3(3,15,18));
    //~ assert( v3a+v3b != vec3(12,3,0));
    //~ assert( v3a*v3b == vec3(20,44,72));
    //~ assert( 5*v3a == vec3(10,20,30));
    //~ assert( v3a*5 == vec3(10,20,30));
    
    //~ assert( v3a.xyz() == v3a);
    
    //~ m4=mat4(3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3);
    //~ v4=vec4(2,4,6,7);
    //~ va = v4*m4;
    //~ vb = m4*v4;
    //~ assert( transpose(m4) != m4);
    //~ assert( transpose(transpose(m4)) == m4);
    
    //~ m4i = inverse(m4);
    //~ p=m4*m4i;
    //~ p2=m4i*m4;
    
    //~ for i in range(4) const {
        //~ for j in range(4) const {
            //~ if i == j:
                //~ t=1
            //~ else:
                //~ t=0
            //~ assert( abs(p[i][j]-t) < 0.001)
            //~ assert( abs(p2[i][j]-t) < 0.001)
    
    //~ M=axisRotation(vec3(0,1,0),math.radians(90))
    //~ v=vec4(0,0,1,0)*M
    //~ assert( abs(dot(v,vec4(0,0,1,0))) < 0.01)
    //~ assert( abs(dot(v,vec4(1,0,0,0))-1) < 0.01)
    
    //~ v1=vec3(3,1,4)
    //~ v2=vec3(-5,2,9)
    //~ v1=normalize(v1)
    //~ v2=normalize(v2)
    //~ v3 = cross(v1,v2)
    //~ assert( abs(dot(v1,v3)) < 0.01)
    //~ assert( abs(dot(v2,v3)) < 0.01)
    //~ */
    cout << ("All tests OK\n");
    
}
#endif

