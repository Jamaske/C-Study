#pragma once
struct quadr{
    double high, low;
    static inline void precise_ordered_accum(double &acc, double &inc);
    static inline double precise_accum(double &acc, const double &inc);
    static inline double precise_sum(const double &a,const double &b, double &r);
    static inline double precise_ordered_sum(const double &high, const double &low, double &r);
    void arr_acurate_sum(const double* arr, unsigned int len);
/*    double arr_precise_sum(const double* arr, unsigned int len){
        for(unsigned int i = 0; i < len; ++i){
            low += arr[i];//следующее число + накопленная погрешность
            precise_ordered_accum(high, low);//аккумулируем сумму в high, и погрешность операции в low
        }

    }*/
    quadr();
    quadr(double el);
    quadr(double high, double low);
    quadr(const quadr &src);
    quadr& operator=(const double & RHS);
    quadr& operator=(const quadr& RHS);
    inline bool fast_compare(const double &LHS,const double &RHS);
    const quadr operator+(const double & RHS);
    quadr& inc(const double &RHS);
    friend const quadr operator+(quadr LHS, quadr RHS);
    quadr& inc(quadr RHS);
};