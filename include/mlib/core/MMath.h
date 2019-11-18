/*
 * Copyright (C) 2011-2019 Mitrokhin S.V. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file MMath.h
/// @brief Библиотека математических функций
/// @author Mitrokhin S.V.
/// @date 09.10.2019
/// 
/// Точность представление чисел с плавающей точкой в разных форматах и в частности числа Пи
/// В формате float сохраняется точность 6 (включительно) цифр после запятой
///      ===!!!
/// 3.141592653589793238462643383279502884197
///
/// В формате double сохраняется точность 15 (включительно) цифр после запятой
///               ===!!!
/// 3.141592653589793238462643383279502884197
///
/// В формате long double сохраняется точность 18 (включительно) цифр после запятой
///                   ==!!
/// 3.141592653589793238462643383279502884197
///
/// Важно помнить, что
/// float представлен согласно стандарту IEEE 754 как binary32
/// double представлен согласно стандарту IEEE 754 как binary64
/// long double не стандартизован
///
/// Для значений float рекомендуется использовать float версии функции во избежании непредвиденных
/// погрешностей (подробнее см. примеры к библиотеке)
///
/// Список сокращений
/// т.д. - тысячная доля, представляет собой 1/1000 доля радиана, что равно 1/6283 (1 / 2ПИ*1000)
/// оборота, округленные до 6000 (для стран бывшего СССР и др.)
///
/// Эпсилон (положительное сколь угодно малое вещественное число)
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MMATH_H
#define MMATH_H
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MGlobal.h"
#include <cmath>
#include <cfloat>
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_BEGIN_NAMESPACE
namespace math {
////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constants

/// Epsilon constant type float
/// \return The number of type float
inline MLIB_CONSTEXPR float cEpsFlt()
{ return FLT_EPSILON; }

/// Epsilon constant type double
/// \return The number of type double
inline MLIB_CONSTEXPR double cEpsDbl()
{ return DBL_EPSILON; }

/// Epsilon constant type long double
/// \return The number of type long double
inline MLIB_CONSTEXPR long double cEpsLdbl()
{ return LDBL_EPSILON; }

/// Epsilon template
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty cEps();

/// Epsilon template specialization for type float
template <>
inline MLIB_CONSTEXPR float cEps()
{ return cEpsFlt(); }

/// Epsilon template specialization for type double
template <>
inline MLIB_CONSTEXPR double cEps()
{ return cEpsDbl()/*1.0E-15*/; }

/// Epsilon template specialization for type long double
template <>
inline MLIB_CONSTEXPR long double cEps()
{ return cEpsLdbl(); }


/// PI constant type float
inline MLIB_CONSTEXPR float cPiFlt()
{   return 3.141592653589793238462643383279502884197f; }

/// PI constant type double
inline MLIB_CONSTEXPR double cPiDbl()
{   return 3.141592653589793238462643383279502884197; }

/// PI constant type long double
inline MLIB_CONSTEXPR long double cPiLdbl()
{   return 3.141592653589793238462643383279502884197l; }

/// PI constant template
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty cPi();

/// PI constant template specialization for type float
template <>
inline MLIB_CONSTEXPR float cPi()
{ return cPiFlt(); }

/// PI constant template specialization for type double
template <>
inline MLIB_CONSTEXPR double cPi()
{ return cPiDbl(); }

/// PI constant template specialization for type long double
template <>
inline MLIB_CONSTEXPR long double cPi()
{ return cPiLdbl(); }


/// 2*PI constant type float
inline MLIB_CONSTEXPR float c2piFlt()
{   return 6.283185307179586476925286766559005768394f; }

/// 2*PI constant type double
inline MLIB_CONSTEXPR double c2piDbl()
{   return 6.283185307179586476925286766559005768394; }

/// 2*PI constant type long double
inline MLIB_CONSTEXPR long double c2piLdbl()
{   return 6.283185307179586476925286766559005768394l; }

/// 2*PI constant template
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty c2pi();

/// 2*PI constant template specialization for type float
template <>
inline MLIB_CONSTEXPR float c2pi()
{   return c2piFlt(); }

/// 2*PI constant template specialization for type double
template <>
inline MLIB_CONSTEXPR double c2pi()
{   return c2piDbl(); }

/// 2*PI constant template specialization for type long double
template <>
inline MLIB_CONSTEXPR long double c2pi()
{   return c2piLdbl(); }


/// PI/2 constant type float
inline MLIB_CONSTEXPR float cHalfPiFlt()
{   return 1.570796326794896619231321691639751442099f; }

/// PI/2 constant type double
inline MLIB_CONSTEXPR double cHalfPiDbl()
{   return 1.570796326794896619231321691639751442099; }

/// PI/2 constant type long double
inline MLIB_CONSTEXPR long double cHalfPiLdbl()
{   return 1.570796326794896619231321691639751442099l; }

/// PI/2 constant template
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty cHalfPi();

/// PI/2 constant template specialization for type float
template <>
inline MLIB_CONSTEXPR float cHalfPi()
{   return cHalfPiFlt(); }

/// PI/2 constant template specialization for type double
template <>
inline MLIB_CONSTEXPR double cHalfPi()
{   return cHalfPiDbl(); }

/// PI/2 constant template specialization for type long double
template <>
inline MLIB_CONSTEXPR long double cHalfPi()
{   return cHalfPiLdbl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////

/// \brief Absolute value of a number (Modulus of a number)
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty abs(_Ty value){   return std::abs(value); }

////////////////////////////////////////////////////////////////////////////////////////////////////

/// \brief Возведение в степень
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty pow(_Ty value, _Ty power)
{   return std::pow(value, power); }

/// \brief Возведение в 2 степень
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty pow2(_Ty value){  return value * value; }

/// \brief Возведение в 3 степень
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty pow3(_Ty value){  return value * value * value; }


/// \brief Квадратный корень
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty sqrt(_Ty value){  return std::sqrt(value); }

////////////////////////////////////////////////////////////////////////////////////////////////////
// Тригонометрические функции

/// \brief Синус
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty sin(_Ty value){   return std::sin(value); }

/// \brief Косинус
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty cos(_Ty value){   return std::cos(value); }

/// \brief Тангенс
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty tan(_Ty value){   return std::tan(value); }

/// \brief Арксинус
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty asin(_Ty value){  return std::asin(value); }
#define arcsin asin

/// \brief Арккосинус
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty acos(_Ty value){  return std::acos(value); }
#define arccos acos

/// \brief Арктангенс
template <typename _Ty>
inline _Ty arcTan(_Ty y, _Ty x)
{
    if ( abs(x) < cEps<_Ty>() || abs(y) < cEps<_Ty>() )
    {
        if ( y > cEps<_Ty>() )
            return cHalfPi<_Ty>();
        if ( -y > cEps<_Ty>() )
            return -(cHalfPi<_Ty>());
        if ( -x > cEps<_Ty>() )
            return cPi<_Ty>();
        return 0.0;
    }
    else
        return std::atan2(y, x);
}

/// \brief Логарифм по основанию 10
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty log10(_Ty x){ return std::log10(x); }

/// \brief Остаток от деления
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty fmod(_Ty arg, _Ty mod){   return std::fmod(arg, mod); }
#define mod fmod

/// \brief Округление по правилам математики
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty round(_Ty value){         return std::round(value); }

/// \brief Округление в большую сторону
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty ceil(_Ty value){          return std::ceil(value); }

/// \brief Округление в меньшую сторону
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty floor(_Ty value){         return std::floor(value); }

////////////////////////////////////////////////////////////////////////////////////////////////////
// Функции сравнения

/// \brief Проверка на равенство нулю с учетом погрешности
template <typename _Ty>
inline MLIB_CONSTEXPR
bool isZero(_Ty value)
{
    return abs(value) <= cEps<_Ty>();
}

/// \brief Проверка на не равенство нулю с учетом погрешности
template <typename _Ty>
inline MLIB_CONSTEXPR
bool isNonZero(_Ty value)
{
    return abs(value) > cEps<_Ty>();
}

/// \brief Проверка аргументов на равенство с учетом погрешности
template <typename _Ty>
inline MLIB_CONSTEXPR
bool isEqual(_Ty value1, _Ty value2)
{
    return abs(value1 - value2) <= cEps<_Ty>();
}

/// \brief Максимум из двух чисел
template <typename _Ty>
inline MLIB_CONSTEXPR
_Ty max(_Ty value1, _Ty value2)
{
    return value1 > value2 ? value1 : value2;
}

/// \brief Значение числа в границе минимума и максимума
template <typename _Ty>
inline MLIB_CONSTEXPR
_Ty bound(_Ty value, _Ty min, _Ty max)
{
    if (value > max) return max;
    if (value < min) return min;
    return value;
}

/// \brief Определение знака числа
template <typename _Ty>
inline MLIB_CONSTEXPR
int signat(_Ty value)
{
    if ( value > cEps<_Ty>() )
        return 1;
    if ( value < -(cEps<_Ty>()) )
        return -1;
    return 1;
}

/// \brief Определение знака числа (обёртка)
template <typename _Ty>
inline MLIB_CONSTEXPR
bool signbit(_Ty value){   return std::signbit(value); }

/// \brief Проверяет является ли переменная нечисловым значением (NaN)
template <typename _Ty>
inline MLIB_CONSTEXPR
bool isnan(_Ty value){   return std::isnan(value); }

////////////////////////////////////////////////////////////////////////////////////////////////////
// Функции сокращения радиан

/// \brief Сокращение значения числа радиан до 2ПИ
/// Полный аналог if (value >= math::c2pi()) {value -= math::c2pi();}

template <typename _Ty>
inline _Ty mod2Pi(_Ty value)
{
    _Ty angle = fmod(value, c2pi<_Ty>());
    if (angle < 0)
        angle += c2pi<_Ty>();
    return angle;
}

/// \brief Сокращение значения числа радиан до ПИ
template <typename _Ty>
inline _Ty modPi(_Ty value)
{
    _Ty angle = fmod(value, c2pi<_Ty>());
    if (angle < 0)
        angle += c2pi<_Ty>();
    if (angle > cPi<_Ty>())
        angle -= c2pi<_Ty>();
    return angle;
}

/// \brief Корень
template <typename _Ty>
inline _Ty arcTan2Pi(_Ty y, _Ty x)
{   return mod2Pi(arcTan(y, x)); }

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \defgroup AngleFunctions Функции преобразования угловых мер

///{@

/// \brief Преобразование радианов в градусы (180.0/Pi)
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty radToDeg(_Ty value)
{   return value * static_cast<_Ty>(180.0) / cPi<_Ty>(); }
#define rad2deg   radToDeg
#define radToGrad radToDeg

/// \brief Преобразование градусов в радианы (Pi/180.0)
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty degToRad(_Ty value)
{   return value * cPi<_Ty>() / static_cast<_Ty>(180.0); }
#define grad2rad  degToRad
#define gradToRad degToRad


/// \brief Преобразование радианов в т.д. (3000/Pi)
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty radToTd(_Ty value)
{   return value * static_cast<_Ty>(3000.0) / cPi<_Ty>(); }
#define rad2td radToTd


/// \brief Преобразование т.д. в радианы (Pi/3000)
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty tdToRad(_Ty value)
{   return value * cPi<_Ty>() / static_cast<_Ty>(3000.0); }

inline MLIB_CONSTEXPR float tdToRadFlt(float value)
{   return value * cPiFlt() / static_cast<float>(3000.0); }

inline MLIB_CONSTEXPR double tdToRadDbl(double value)
{   return value * cPiDbl() / static_cast<double>(3000.0); }


/// \brief Преобразование т.д. в градусы (180.0/3000.0)
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty tdToDeg(_Ty value)
{   return value * static_cast<_Ty>(180.0) / static_cast<_Ty>(3000.0); }

inline MLIB_CONSTEXPR float tdToDegFlt(float value)
{   return value * static_cast<float>(180.0) / static_cast<float>(3000.0); }

inline MLIB_CONSTEXPR double tdToDegDbl(double value)
{   return value * static_cast<double>(180.0) / static_cast<double>(3000.0); }


/// \brief Преобразование градусов в радинаны (180.0 / 3000.0)
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty degToTd(_Ty value)
{   return value * static_cast<_Ty>(3000.0) / static_cast<_Ty>(180.0); }

inline MLIB_CONSTEXPR float degToTdFlt(float value)
{   return value * static_cast<float>(3000.0) / static_cast<float>(180.0); }

inline MLIB_CONSTEXPR double degToTdDbl(double value)
{   return value *  static_cast<double>(3000.0) / static_cast<double>(180.0); }


/// \brief Преобразование градусов и минут в радианы
inline double degToRad(int degrees, double minutes)
{
    double full_degrees = minutes / 60 + static_cast<double>(degrees);
    return degToRad(full_degrees);    
}

///@}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Функции преобразования единиц измерения длины

/// \brief Преобразование морских миль в метры
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty nauticalMileToMeter(_Ty value)
{   return value * 1852; }

#define nmi2m  nauticalMileToMeter
#define nmiToM nauticalMileToMeter

/// \brief Преобразование метров в морские мили
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty meterToNauticalMile(_Ty value)
{   return value / 1852; }

#define m2nmi  meterToNauticalMile
#define mToNmi meterToNauticalMile

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Преобразования величин скорости

/// \brief Преобразование узлов в метры в секунду
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty knotToMeterSec(_Ty value)
{   return value * (1852.0 / 3600.0); }
#define knToMs  knotToMeterSec
#define kn2Ms   knotToMeterSec

/// \brief Преобразование метров в секунду в узлы
template <typename _Ty>
inline MLIB_CONSTEXPR _Ty meterSecToKnot(_Ty value)
{   return value * (3600.0 / 1852.0); }
#define msToKn  meterSecToKnot
#define ms2Kn   meterSecToKnot

////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace math
MLIB_END_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // MMATH_H
////////////////////////////////////////////////////////////////////////////////////////////////////
