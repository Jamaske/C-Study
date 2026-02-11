#pragma once
#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <type_traits>

template <typename T>
struct TwiceAsBig;

template <>
struct TwiceAsBig<int8_t> {
    using type = int16_t;
};

template <>
struct TwiceAsBig<int16_t> {
    using type = int32_t;
};

template <>
struct TwiceAsBig<int32_t> {
    using type = int64_t;
};

template <>
struct TwiceAsBig<int64_t> {
    using type = __int128_t;
};

template <>  // костыль
struct TwiceAsBig<__int128_t> {
    using type = __int128_t;
};

template <>
struct TwiceAsBig<uint8_t> {
    using type = uint16_t;
};


template <>
struct TwiceAsBig<uint16_t> {
    using type = uint32_t;
};

template <>
struct TwiceAsBig<uint32_t> {
    using type = uint64_t;
};

template <>
struct TwiceAsBig<uint64_t> {
    using type = __uint128_t;
};

template <>  // костыль
struct TwiceAsBig<__uint128_t> {
    using type = __uint128_t;
};

template <uint8_t bits_precision, typename BaseType = int64_t>
struct FixPoint {
    static_assert(bits_precision <= std::numeric_limits<BaseType>::digits, "can't have more precision bits dot then there are bit in base type");
    static_assert(std::is_integral<BaseType>::value, "BaseType must be an integral type");

    static constexpr TwiceAsBig<BaseType>::type OFFSET = static_cast<TwiceAsBig<BaseType>::type>(1) << bits_precision;
    static constexpr BaseType CAP = (std::numeric_limits<BaseType>::max() >> bits_precision) + 1;
    static constexpr BaseType MIN = (std::numeric_limits<BaseType>::min() >> bits_precision);

   private:
    BaseType value;

    constexpr FixPoint(BaseType internal_val, bool) {
        value = internal_val;
    }

   public:
    constexpr FixPoint()
        : FixPoint(0, false) {}

    template <typename F>
        requires std::is_floating_point<F>::value
    constexpr FixPoint(F raw_value)
        : FixPoint(raw_value * OFFSET, false) {
        if (raw_value < MIN || CAP <= raw_value) throw std::range_error("can't store the value in that type");
    }

    template <typename I>
        requires std::is_integral<I>::value
    constexpr FixPoint(I raw_value)
        : FixPoint(raw_value << bits_precision, false) {
        if (raw_value < MIN || CAP <= raw_value) throw std::range_error("can't store the value in that type");
    }

    constexpr FixPoint(const FixPoint& src)
        : FixPoint(src.value, false) {}

    constexpr FixPoint& operator=(const FixPoint& src) {
        this->value = src.value;
        return *this;
    }

    template <typename F>
        requires std::is_floating_point<F>::value
    explicit constexpr operator F() const { return static_cast<F>(this->value) / OFFSET; }

    template <typename I>
        requires std::is_integral<I>::value
    explicit constexpr operator I() const { return static_cast<I>(this->value >> bits_precision); }


    constexpr FixPoint operator+(const FixPoint& rhs) const {
        return FixPoint(this->value + rhs.value, false);
    }
    constexpr FixPoint operator*(const FixPoint& rhs) const {
        using WideType = typename std::conditional<(sizeof(BaseType) * 2 == sizeof(__int128_t)), __int128_t, int64_t>::type;
        // using WideType = TwiceAsBig<BaseType>::type;
        WideType mul = static_cast<WideType>(this->value) * rhs.value;
        return FixPoint(static_cast<BaseType>((mul >> bits_precision) & -1ULL), false);
    }
};

int main() {
    FixPoint<1> x1(15);
    FixPoint<1> x2(25);
    FixPoint<48, int64_t> v7(-0.999);
    FixPoint<48, int64_t> u7(0.95);
    FixPoint<16, uint16_t>::OFFSET;
    FixPoint<1> y1 = x1 * x2;
    FixPoint<48>, int64_t> w = v7 + u7;
    float f(y1);

    std::cout << static_cast<float>(v7) << ' ' << static_cast<float>(u7) << std::endl;
    std::cout << static_cast<float>(w) << std::endl;
}