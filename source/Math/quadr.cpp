#include "quadr.h"

inline void quadr::precise_ordered_accum(double &acc, double &inc){
    //принимает acc, inc:  acc+inc<inf,  acc > inc
    //round(acc + inc) -> acc
    //error(acc + inc) -> inc
    double t = acc + inc;
    inc -=(t - acc);
    acc = t;
}

inline double quadr::precise_accum(double &acc, const double &inc){
    //принимает acc, inc:  acc+inc<inf
    //round(acc + inc) -> acc
    //error(acc + inc) -> return
    double s = acc + inc, r = s - inc;
    r = (acc - r) + (inc - (s - r));
    acc = s;
    return r;
}

inline double quadr::precise_sum(const double &a,const double &b, double &r){
    //принимает a, b:  a+b<inf
    //round(acc + inc) -> return
    //error(acc + inc) -> r
    double s = a + b;
    double t = s - b;
    r = (a - t) + (b - (s - t));
    return s;
}

inline double quadr::precise_ordered_sum(const double &high, const double &low, double &r){
    //принимает high, low:  high+low<inf, high > low
    //round(acc + inc) -> return
    //error(acc + inc) -> r
    double s = high + low;
    r = low - (s - high);
    return s;
}

void quadr::arr_acurate_sum(const double* arr, unsigned int len){
    for(unsigned int i = 0; i < len; ++i){
        low += arr[i];//следующее число + прошлая погрешность
        precise_ordered_accum(high, low);//аккумулируем сумму в high, и погрешность операции в low
    }
}

/*    double arr_precise_sum(const double* arr, unsigned int len){
        for(unsigned int i = 0; i < len; ++i){
            low += arr[i];//следующее число + накопленная погрешность
            precise_ordered_accum(high, low);//аккумулируем сумму в high, и погрешность операции в low
        }

    }*/

quadr::quadr(): high(0), low(0){};
quadr::quadr(double el): high(el), low(0){};
quadr::quadr(double high, double low): high(high), low(low){};
quadr::quadr(const quadr &src): high(src.high), low(src.low){};
quadr& quadr::operator=(const double & RHS){
    high = RHS;
    low = 0;
    return *this;
}
quadr& quadr::operator=(const quadr& RHS){
    if(this != &RHS){
        high = RHS.high;
        low = RHS.low;
    }
    return *this;
}

inline bool quadr::fast_compare(const double &LHS,const double &RHS){

}

const quadr quadr::operator+(const double & RHS){
    double p,q,k;
    q = precise_sum(low, RHS, p);
    k = precise_accum(q, high);
    return quadr(q,p+k);
}
quadr& quadr::inc(const double &RHS){
    low = precise_accum(low, RHS) + precise_accum(high,low);
    return *this;
}

const quadr operator+(quadr LHS, quadr RHS){
    quadr::precise_ordered_accum(LHS.high,RHS.high);
    quadr::precise_ordered_accum(LHS.low,RHS.low);

    quadr::precise_ordered_accum(LHS.low, RHS.high);

    quadr::precise_ordered_accum(LHS.high,LHS.low);
    quadr::precise_ordered_accum(RHS.high,RHS.low);

    quadr::precise_ordered_accum(LHS.low, RHS.high);
}

quadr& quadr::inc(quadr RHS){
    precise_ordered_accum(high,RHS.high);
    precise_ordered_accum(low,RHS.low);
    precise_ordered_accum(low, RHS.high);
    precise_ordered_accum(high,low);
    precise_ordered_accum(RHS.high,RHS.low);
    precise_ordered_accum(low, RHS.high);
    return *this;
}