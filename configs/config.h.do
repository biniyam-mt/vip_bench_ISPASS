#ifndef CONFIG_SE_H
#define CONFIG_SE_H

#include "common/utils.h"

/*****************************************/
#if defined(VIP_NA_MODE)

#include <valarray>
#include <vector>


#define VIP_INIT
#define VIP_ENCCHAR         char
#define VIP_ENCINT          int
#define VIP_ENCUINT         unsigned int
#define VIP_ENCUINT64       uint64_t
#define VIP_ENCLONG         long
#define VIP_ENCULONG        unsigned long
#define VIP_ENCBOOL         bool
#define VIP_ENCFLOAT        float
#define VIP_ENCDOUBLE       double
#define VIP_VEC_ENCDOUBLE   std::valarray<VIP_ENCDOUBLE>
#define VIP_VEC_ENCINT      std::valarray<VIP_ENCINT>
#define VIP_DEC(X)          (X)
#define VIP_DEC_VEC(X)      (X) 

extern inline void vip_init_vector(VIP_VEC_ENCINT* dest, std::vector<int>* source) {
    std::copy(source->begin(), source->end(), std::begin(*dest));
}
inline VIP_VEC_ENCINT   operator<<   (VIP_VEC_ENCINT lhs, int rhs)   { return lhs.cshift(rhs); }
inline VIP_VEC_ENCINT   operator>>   (VIP_VEC_ENCINT lhs, int rhs)   { return lhs.cshift(-rhs); }


/*****************************************/
#elif defined(VIP_DO_MODE)

#include <valarray>
#include <vector>
#include "lib/do-characterization/do.h"

#define VIP_INIT
#define VIP_ENCCHAR         char
#define VIP_ENCINT          int
#define VIP_ENCUINT         unsigned int
#define VIP_ENCUINT64       uint64_t
#define VIP_ENCLONG         long
#define VIP_ENCULONG        unsigned long
#define VIP_ENCBOOL         bool
#define VIP_ENCFLOAT        float
#define VIP_ENCDOUBLE       double
#define VIP_DEC(X)          (X)
#define VIP_CMOV(P,A,B)         CMOV((P), (A), (B))
#define VIP_CMOV_char(P,A,B)    CMOV_char((P), (A), (B))



/*****************************************/
//#elif defined(VIP_ENC_MODE)

#endif
#endif

