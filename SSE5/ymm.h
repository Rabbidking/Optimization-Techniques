#pragma once

#include <xmmintrin.h>
#include <nmmintrin.h>
#include <smmintrin.h>
#include <emmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>
#include <iostream>

//thin wrapper around m256i to make intrinsics a bit more convenient
class ymm_u8{
public:
    __m256i data;
    
    operator __m256i() { 
        return data;
    }
    void store(void* p) const {
        _mm256_storeu_si256( (__m256i*)p, data );
    }
    ymm_u8(void* p){
        data = _mm256_lddqu_si256( (__m256i*)p);
    }
    ymm_u8(std::uint8_t v){
        data = _mm256_set1_epi8(v);
    }
    ymm_u8(std::uint16_t v){
        data = _mm256_set1_epi8(v);
    }
    ymm_u8(std::uint32_t v){
        data = _mm256_set1_epi8(v);
    }
    ymm_u8(int v){
        data = _mm256_set1_epi8(v);
    }
    ymm_u8(const ymm_u8& v){
        data = v.data;
    }
    ymm_u8(__m256i v){
        data = v;
    }
    ymm_u8(ymm_u8&& v){
        data = v.data;
    }
    ymm_u8 operator=(ymm_u8 v2){
        data=v2.data;
        return *this;
    }
    //saturation arithmetic
    ymm_u8 operator+(ymm_u8 v2){
        return ymm_u8( _mm256_adds_epi8(data,v2.data) );
    }
    //saturation arithmetic
    ymm_u8 operator-(ymm_u8 v2){
        return ymm_u8( _mm256_subs_epi8(data,v2.data) );
    }
    //saturation arithmetic
    void operator+=(ymm_u8 v2){
        data = _mm256_adds_epi8(data,v2.data);
    }
    //saturation arithmetic
    void operator-=(ymm_u8 v2){
        data = _mm256_subs_epi8(data,v2.data);
    }
    void operator&=(ymm_u8 v2){
        data = _mm256_and_si256(data,v2.data);
    }
    void operator|=(ymm_u8 v2){
        data = _mm256_or_si256(data,v2.data);
    }
    void operator^=(ymm_u8 v2){
        data = _mm256_xor_si256(data,v2.data);
    }
    ymm_u8 operator==(ymm_u8 v2){
        return ymm_u8( _mm256_cmpeq_epi8(data, v2.data) );
    }  
    ymm_u8 operator>=(ymm_u8 v2){
        return ymm_u8( _mm256_cmpeq_epi8( data, _mm256_max_epu8(data,v2.data) ) );
    }
    ymm_u8 operator<=(ymm_u8 v2){
        return v2>=*this;
    }
    ymm_u8 operator>(ymm_u8 v2){
        //less -> (NOT(is equal)) AND (is greater-or-equal)
        return (*this==v2).andnot( *this>=v2 );
    }
    ymm_u8 operator<(ymm_u8 v2){
        return v2>*this;
    }  
    ymm_u8 operator!=(ymm_u8 v2){
        return ymm_u8( (*this<v2) | (*this>v2) );
    }
    ymm_u8 operator|(ymm_u8 v2){
        return ymm_u8( _mm256_or_si256( data, v2.data) );
    } 
    ymm_u8 operator&(ymm_u8 v2){
        return ymm_u8( _mm256_and_si256( data, v2.data) );
    }
    ymm_u8 operator^(ymm_u8 v2){
        return ymm_u8( _mm256_xor_si256( data, v2.data) );
    }
    ymm_u8 andnot(ymm_u8 v2){
        // (~this->data) & v2.data
        return ymm_u8( _mm256_andnot_si256( data, v2.data) );
    }    
};

inline ymm_u8 max(ymm_u8 a, ymm_u8 b){
    return ymm_u8( _mm256_max_epu8( a,b ) );
}
inline ymm_u8 min(ymm_u8 a, ymm_u8 b){
    return ymm_u8( _mm256_min_epu8( a,b ) );
}
inline ymm_u8 avg(ymm_u8 a, ymm_u8 b){
    return ymm_u8( _mm256_avg_epu8( a,b ) );
}
// (~a) & b
inline ymm_u8 andnot(ymm_u8 a, ymm_u8 b){
    return a.andnot(b);
}


inline
std::ostream& operator<<(std::ostream& o, const ymm_u8& v){
    alignas(32) uint32_t tmp[32];
    v.store(tmp);
    for(int i=0;i<32;++i){
        o << (unsigned)(tmp[i]);
        if( i != 31 )
            o << " ";
    }
    return o;
}
