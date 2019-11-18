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
/// @file MDataFormat.h
/// @brief Функции преобразования данных
/// @author Mitrokhin S.V.
/// @date 18.09.2019
///
// toBinStdString
// toBinSepStdString
// toBinQString
// toBinSepQString

// printBin
// printBin_fast
// printBinSep
// printBinSep_fast

// toHexStdString
// toHexSepStdString
// toHexQString
// toHexSepQString

// printHex(T var)
// printHexSep(T var, size_t count = 4, char sep = ' ')
// printHexExt(T var)
// printHex(void * ptr, size_t count)
// printHexReverse(void * ptr, size_t count)
// printHexSepReverse(void * ptr, size_t count)
// printHexTable(const void * ptr, size_t count, size_t columns = 8, char sep = ' ')
// printHexTableReverse(const void * ptr, size_t count, size_t columns = 8, char sep = ' ')
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MDATAFORMAT_H
#define MDATAFORMAT_H
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>  // std::setfill, std::setw
#include <bitset>
#include <cfloat>
#include <cstdint>
#include <string>
#include <sstream>

#include <cstdio>
#include <cmath>

#include "MGlobal.h"

#ifdef MLIB_LIB_QT
#include <QString>
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_BEGIN_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
// to bin

/// @brief Преобразование значения переменной в строку с переводом в двоичную систему счисления
/// Вывод числа в обычном порядке байт - от старшего к младшему (big-endian): An,...,A0
template <typename T>
std::string toBinStdString(T var)
{
    static_assert(std::is_integral<T>::value, "Integer type required.");

    std::bitset<sizeof(T) * 8> bs(var);
    return bs.to_string();
}

/// @brief Преобразование значения переменной в строку с переводом в двоичную систему счисления
/// с настраиваемой побитной группировкой
/// Вывод числа в обычном порядке байт - от старшего к младшему (big-endian): An,...,A0
/// @param[in]  var     Шаблонная переменная
/// @param[in]  count   Количество бит до разделителя (по умолчанию, 8 бит)
/// @param[in]  sep     Разделительный символ (по умолчанию, символ пробела)
template <typename T>
std::string toBinSepStdString(T var, size_t count = 8, char sep = ' ')
{
    if (count == 0) { return toBinStdString(var); }

    MLIB_CONSTEXPR size_t size = sizeof(T) * 8;
    const size_t strSize = size + (std::ceil(static_cast<float>(size) / count) - 1);
    
    std::string str;
    str.resize(strSize);
    std::string::reverse_iterator it = str.rbegin();
    register size_t pos = 0;

    while (it != str.rend())
    {
        if (pos == count)
        {
            *it = sep;
            ++it;
            pos = 0;
            continue;
        }

        *it = ((var & 1) ? '1' : '0');
        var >>= 1;
        ++it;
        ++pos;
    }
    return str;
}

#ifdef MLIB_LIB_QT

/// @brief Преобразование значения переменной в строку с переводом в двоичную систему счисления
/// Вывод числа в обычном порядке байт - от старшего к младшему (big-endian): An,...,A0
template <typename T>
QString toBinQString(T var)
{
    std::bitset<sizeof(T) * 8> bs(var);
    return QString::fromStdString(bs.to_string());
}

#if QT_VERSION >= QT_VERSION_CHECK(5,6,0)

/// @brief Преобразование значения переменной в строку с переводом в двоичную систему счисления
/// с настраиваемой побитной группировкой
/// Вывод числа в обычном порядке байт - от старшего к младшему (big-endian): An,...,A0
/// @param[in]  var     Шаблонная переменная
/// @param[in]  count   Количество бит до разделителя (по умолчанию, 8 бит)
/// @param[in]  sep     Разделительный символ (по умолчанию, символ пробела)
template <typename T>
QString toBinSepQString(T var, size_t count = 8, QChar sep = ' ')
{
    if (count == 0) { return toBinQString(var); }

    MLIB_CONSTEXPR size_t size = sizeof(T) * 8;
    const size_t strSize = size + (std::ceil(static_cast<float>(size) / count) - 1);
    
    QString str;
    str.resize(strSize);
    QString::reverse_iterator it = str.rbegin();
    register size_t pos = 0;

    while (it != str.rend())
    {
        if (pos == count)
        {
            *it = sep;
            ++it;
            pos = 0;
            continue;
        }

        *it = ((var & 1) ? QChar('1') : QChar('0'));
        var >>= 1;
        ++it;
        ++pos;
    }
    return str;
}
#else
template <typename T>
QString toBinSepQString(T var, size_t count = 8, QChar sep = ' ')
{
    if (count == 0) { return toBinQString(var); }

    MLIB_CONSTEXPR size_t size = sizeof(T) * 8;
    const size_t strSize = size + (std::ceil(static_cast<float>(size) / count) - 1);

    QString str;
    str.resize(strSize);
    QString::iterator it = str.end();
    register size_t pos = 0;
    --it;

    while (it != str.begin())
    {
        if (pos == count)
        {
            *it = sep;
            --it;
            pos = 0;
            continue;
        }

        *it = ((var & 1) ? QChar('1') : QChar('0'));
        var >>= 1;
        --it;
        ++pos;
    }
    return str;
}
#endif
#endif

/// @brief Преобразование и вывод значения переменной в двоичной системе счисления
/// Вывод числа в обычном порядке байт - от старшего к младшему (big-endian): An,...,A0
template <typename T>
void printBin(T var)
{
    static_assert(std::is_integral<T>::value, "Integer type required.");

    std::bitset<sizeof(T) * 8> bs(var);
    std::cout << bs.to_string() << std::endl;
}

/// @brief Преобразование и вывод значения переменной в двоичной системе счисления
/// Для LE машин: вывод числа в обычном порядке байт - от старшего к младшему (big-endian): An,...,A0
/// Оптимизированная на скорость Быстрая реализация с C строками
template <typename T>
void printBin_fast(T var)
{
    static_assert(std::is_integral<T>::value, "Integer type required.");

    MLIB_CONSTEXPR size_t size = sizeof(T) * 8;
    char szBuffer[size + 1];
    szBuffer[size] = 0;
    register int i = size - 1;      // индекс для обратной записи в буффер
    while (i >= 0)
    {
        szBuffer[i] = (var & 1) ? '1' : '0';
        var >>= 1;
        --i;
    }

    std::cout << szBuffer << std::endl;
}

/// @brief Преобразование и вывод значения переменной в двоичной системе счисления
/// с настраиваемой побитной группировкой
/// Вывод числа в обычном порядке байт - от старшего к младшему (big-endian): An,...,A0
/// @param[in]  var     Шаблонная переменная
/// @param[in]  count   Количество бит до разделителя (по умолчанию, 8 бит)
/// @param[in]  sep     Разделительный символ (по умолчанию, символ пробела)
template <typename T>
void printBinSep(T var, size_t count = 8, char sep = ' ')
{
    static_assert(std::is_integral<T>::value, "Integer type required.");

    if (count == 0)
    {
        printBin(var);
        return;
    }

    MLIB_CONSTEXPR size_t size = sizeof(T) * 8;
    const size_t strSize = size + (std::ceil(static_cast<float>(size) / count) - 1);
    std::bitset<sizeof(T) * 8> bs(var);

    std::string srcStr = bs.to_string();
    std::string dstStr;
    dstStr.resize(strSize);

    std::string::iterator dstIter = dstStr.begin();
    std::string::iterator srcIter = srcStr.begin();

    for (size_t i = 1; i <= size; ++i)
    {
        *dstIter = *srcIter;

        if (i % count == 0)
        {
            ++dstIter;
            *dstIter = sep;
        }
        ++dstIter;
        ++srcIter;
    }
    std::cout << dstStr << std::endl;
}

template <typename T>
void printBinSep_fast(T var, size_t count = 8, char sep = ' ')
{
    static_assert(std::is_integral<T>::value, "Integer type required.");

    if (count == 0)
    {
        printBin_fast(var);
        return;
    }

    MLIB_CONSTEXPR size_t size = sizeof(T) * 8;
    const size_t strSize = size + (std::ceil(static_cast<float>(size) / count) - 1);

    char szBuffer[strSize + 1];
    szBuffer[strSize] = 0;
    register int i = strSize - 1;
    register size_t pos = 0;

    while (i >= 0)
    {
        if (pos == count)
        {
            szBuffer[i] = sep;
            --i;
            pos = 0;
            continue;
        }

        szBuffer[i] = ((var & 1) ? '1' : '0');
        var >>= 1;
        --i;
        ++pos;
    }
    std::cout << szBuffer << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// to hex

/// @brief Преобразование значения переменной в строку с переводом в шестнадцатеричную систему счисления
/// с настраиваемой побайтной группировкой
/// Вывод числа в обычном порядке байт - от старшего к младшему (big-endian): An,...,A0
/// @note См. проект, надо подумать
template <typename T>
std::string toHexStdString(T var)
{
    static_assert(std::is_integral<T>::value, "Integer type required.");

    typedef typename std::make_unsigned<T>::type UT;

    const size_t size = sizeof(T) * 2;
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setw(size) << std::setfill('0') << static_cast<UT>(var);
    return ss.str();
}

template <typename T>
std::string toHexStdStringExt(T var)
{
    uint8_t * ptrBegin = reinterpret_cast<uint8_t*>(&var);
    uint8_t * ptr = ptrBegin + sizeof(T);
    std::stringstream ss;

    ss << std::hex << std::uppercase << std::setfill('0');

    while (--ptr >= ptrBegin)
    {
        ss << std::setw(2) << (unsigned)*ptr;
    }
    return ss.str();
}

/// @brief Преобразование значения переменной в строку с переводом в шестнадцатеричную систему счисления
/// с настраиваемой побайтной группировкой
/// Вывод числа в обычном порядке байт - от старшего к младшему (big-endian): An,...,A0
/// @param[in]  var     Шаблонная переменная
/// @param[in]  count   Количество байт до разделителя (по умолчанию, 4 байта)
/// @param[in]  sep     Разделительный символ (по умолчанию, символ пробела)
template <typename T>
std::string toHexSepStdString(T var, size_t count = 4, char sep = ' ')
{
    if (count == 0) { return toHexStdString(var); }
    
    MLIB_CONSTEXPR size_t size = sizeof(T) * 2;
    const size_t strSize = size + (std::ceil(static_cast<float>(sizeof(T)) / count) - 1);
    const size_t countBytes = count * 2;

    const std::string srcStr = toHexStdString(var);
    std::string dstStr;
    dstStr.resize(strSize);

#if MLIB_SUPPORT_CPP11
    std::string::const_reverse_iterator srcIter = srcStr.crbegin();
#else
    std::string::const_reverse_iterator srcIter = srcStr.rbegin();
#endif
    std::string::reverse_iterator dstIter = dstStr.rbegin();
    register size_t pos = 0;

    while (dstIter != dstStr.rend())
    {
        if (pos == countBytes)
        {
            *dstIter = sep;
            ++dstIter;            
            pos = 0;
            continue;
        }

        *dstIter = *srcIter;

        ++dstIter;
        ++srcIter;
        ++pos;
    }
    return dstStr;
}


#ifdef MLIB_LIB_QT

/// @brief Преобразование значения переменной в строку с переводом в шестнадцатеричную систему счисления
/// Вывод числа в обычном порядке байт - от старшего к младшему (big-endian): An,...,A0
template <typename T>
QString toHexQString(T var)
{
    static_assert(std::is_integral<T>::value, "Integer type required.");

    const size_t size = sizeof(T) * 2;
    return (QString("%1").arg(var, size, 16, QChar('0'))).toUpper();
}

#if QT_VERSION >= QT_VERSION_CHECK(5,6,0)

/// @brief Преобразование значения переменной в строку с переводом в шестнадцатеричную систему счисления
/// с настраиваемой побайтной группировкой
/// Вывод числа в обычном порядке байт - от старшего к младшему (big-endian): An,...,A0
/// @param[in]  var     Шаблонная переменная
/// @param[in]  count   Количество байт до разделителя (по умолчанию, 4 байта)
/// @param[in]  sep     Разделительный символ (по умолчанию, символ пробела)
template <typename T>
QString toHexSepQString(T var, size_t count = 4, QChar sep = ' ')
{
    if (count == 0) { return toHexQString(var); }

    MLIB_CONSTEXPR size_t size = sizeof(T) * 2;
    const size_t strSize = size + (std::ceil(static_cast<float>(sizeof(T)) / count) - 1);
    const size_t countBytes = count * 2;
    
    const QString srcStr = toHexQString(var);
    QString dstStr;
    dstStr.resize(strSize);

    QString::const_reverse_iterator srcIter = srcStr.crbegin();
    QString::reverse_iterator dstIter = dstStr.rbegin();
    register size_t pos = 0;

    while (dstIter != dstStr.rend())
    {
        if (pos == countBytes)
        {
            *dstIter = sep;
            ++dstIter;            
            pos = 0;
            continue;
        }

        *dstIter = *srcIter;

        ++dstIter;
        ++srcIter;
        ++pos;
    }
    return dstStr;
}
#else
template <typename T>
QString toHexSepQString(T var, size_t count = 4, QChar sep = ' ')
{
    if (count == 0) { return toHexQString(var); }

    MLIB_CONSTEXPR size_t size = sizeof(T) * 2;
    const size_t strSize = size + (std::ceil(static_cast<float>(sizeof(T)) / count) - 1);
    const size_t countBytes = count * 2;

    const QString srcStr = toHexQString(var);
    QString dstStr;
    dstStr.resize(strSize);
    register int i = strSize - 1, j = srcStr.size() - 1;
    register size_t pos = 0;

    while (i >= 0)
    {
        if (pos == countBytes)
        {
            dstStr[i] = sep;
            --i;
            pos = 0;
            continue;
        }

        dstStr[i] = srcStr[j];
        --i; --j;
        ++pos;
    }
    return dstStr;
}
#endif
#endif

/// @brief Преобразование и вывод значения переменной в шестнадцатеричной системе счисления
/// Вывод числа в обычном порядке байт - от старшего к младшему (big-endian): An,...,A0
template <typename T>
void printHex(T var)
{
    static_assert(std::is_integral<T>::value, "Integer type required.");
    static_assert(std::is_unsigned<T>::value, "Unsigned type required.");

    const size_t size = sizeof(T) * 2;
    std::cout << std::hex << std::uppercase << std::setw(size) << std::setfill('0') << +var << std::endl;
}

/// @brief Преобразование и вывод значения переменной в шестнадцатеричной системе счисления
/// с настраиваемой побайтной группировкой
/// Вывод числа в обычном порядке байт - от старшего к младшему (big-endian): An,...,A0
/// @param[in]  var     Шаблонная переменная
/// @param[in]  count   Количество бит до разделителя (по умолчанию, 4 байта)
/// @param[in]  sep     Разделительный символ (по умолчанию, символ пробела)
template <typename T>
void printHexSep(T var, size_t count = 4, char sep = ' ')
{
    static_assert(std::is_integral<T>::value, "Integer type required.");
    static_assert(std::is_unsigned<T>::value, "Unsigned type required.");

    std::cout << toHexSepStdString(var, count, sep) << std::endl;
}

/// @brief Преобразование и вывод значения переменной в шестнадцатеричной системе счисления
/// Для LE машин: вывод числа в обычном порядке байт - от старшего к младшему (big-endian): An,...,A0
/// @note Медленная реализация, преобразовывает и выводит любой тип
template <typename T>
void printHexExt(T var)
{
    uint8_t * ptrBegin = reinterpret_cast<uint8_t*>(&var);
    uint8_t * ptr = ptrBegin + sizeof(T);

    std::cout << std::hex << std::uppercase << std::setfill('0');

    while (--ptr >= ptrBegin)
    {
        std::cout << std::setw(2) << +*ptr;
    }
    std::cout << std::endl;
}

inline
void printHex(void * ptr, size_t count)
{
    uint8_t * ptrBegin = reinterpret_cast<uint8_t*>(ptr);
    uint8_t * ptrEnd = ptrBegin + count;

    std::cout << std::hex << std::uppercase << std::setfill('0');

    while (ptrBegin < ptrEnd)
    {
        std::cout << std::setw(2) << +*ptrBegin;
        ++ptrBegin;
    }
    std::cout << std::endl;
}

inline
void printHexReverse(void * ptr, size_t count)
{
    uint8_t * ptrBegin = reinterpret_cast<uint8_t*>(ptr);
    uint8_t * ptrEnd = ptrBegin + count;

    std::cout << std::hex << std::uppercase << std::setfill('0');

    while (--ptrEnd >= ptrBegin)
    {
        std::cout << std::setw(2) << +*ptrEnd;
    }
    std::cout << std::endl;
}

inline
void printHexSepReverse(void * ptr, size_t count)
{
    uint8_t * ptrBegin = reinterpret_cast<uint8_t*>(ptr);
    uint8_t * ptrEnd = ptrBegin + count;

    std::cout << std::hex << std::uppercase << std::setfill('0');

    while (--ptrEnd >= ptrBegin)
    {
        std::cout <<std::setw(2) << +*ptrEnd << ' ';
    }
    std::cout << std::endl;
}

inline
void printHexTable(const void * ptr, size_t count, size_t columns = 8, char sep = ' ')
{
    const uint8_t * ptrBegin = reinterpret_cast<const uint8_t*>(ptr);
    const uint8_t * ptrEnd = ptrBegin + count;
    uint col = 0;

    std::cout << std::hex << std::uppercase << std::setfill('0');

    while (ptrBegin < ptrEnd)
    {
        if (col < columns)
        {
            std::cout << std::setw(2) << +*ptrBegin << sep;
            ++col;
        }
        else
        {
            col = 0;
            std::cout << std::endl;
        }
        ++ptrBegin;
    }
    std::cout << std::endl;
}

inline
void printHexTableReverse(const void * ptr, size_t count, size_t columns = 8, char sep = ' ')
{
    const uint8_t * ptrBegin = reinterpret_cast<const uint8_t*>(ptr);
    const uint8_t * ptrEnd = ptrBegin + count;
    uint col = 0;

    std::cout << std::hex << std::uppercase << std::setfill('0');

    while (--ptrEnd >= ptrBegin)
    {
        if (col < columns)
        {
            std::cout << std::setw(2) << +*ptrEnd << sep;
            ++col;
        }
        else
        {
            col = 0;
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_END_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // MDATAFORMAT_H
////////////////////////////////////////////////////////////////////////////////////////////////////
