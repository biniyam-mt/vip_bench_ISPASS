#ifndef DO_H
#define DO_H



template <class T>
inline __attribute__((always_inline)) T CMOV_template(bool cond, T v_true, T v_false) {
    T result;
    __asm__ __volatile__ (
        "test   %1, %1;"
        "cmovz  %3, %0;"  //zero flag cleared?
        "cmovnz %2, %0;" //zero flag not cleared?
        : "=r" (result)
        : "r" (cond), "r" (v_true), "r" (v_false)
        : "cc"
    );
    return result;
}

inline __attribute__((always_inline)) uint16_t CMOV(bool cond, uint16_t v_true, uint16_t v_false)  {
        uint16_t result;
        __asm__ __volatile__ (
            "test   %1, %1;"
            "cmovz  %3, %0;"  //zero flag cleared?
            "cmovnz %2, %0;" //zero flag not cleared?
            : "=r" (result)
            : "r" (cond), "r" (v_true), "r" (v_false)
            : "cc"
        );
        return char(result);
}

inline __attribute__((always_inline)) int CMOV(bool cond, int v_true, int v_false){
        return CMOV_template<int>(cond, v_true, v_false);
}

inline __attribute__((always_inline)) unsigned int CMOV(bool cond, unsigned int v_true, unsigned int v_false){
        return CMOV_template<unsigned int>(cond, v_true, v_false);
}

inline __attribute__((always_inline)) unsigned long CMOV(bool cond, unsigned long v_true, unsigned long v_false){
        return CMOV_template<unsigned long>(cond, v_true, v_false);
}

inline __attribute__((always_inline)) double CMOV(bool cond, double v_true, double v_false){
        return CMOV_template<double>(cond, v_true, v_false);
}

inline __attribute__((always_inline)) float CMOV(bool cond, float v_true, float v_false){
        return CMOV_template<float>(cond, v_true, v_false);
}

inline __attribute__((always_inline)) bool CMOV(bool cond, bool v_true, bool v_false)  {
        uint16_t result;
        __asm__ __volatile__ (
            "test   %1, %1;"
            "cmovz  %3, %0;"  //zero flag cleared?
            "cmovnz %2, %0;" //zero flag not cleared?
            : "=r" (result)
            : "r" (cond), "r" ((uint16_t)v_true), "r" ((uint16_t)v_false)
            : "cc"
        );
        return bool(result);
}




#endif
