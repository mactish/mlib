/*
 * Copyright (C) 2011-2017 Mitrokhin S.V. All Rights Reserved.
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
/// @file MRandom.h
/// @brief MRandom - обертка над стандартными функциями генерации случайного числа библиотеки C
/// @author Mitrokhin S.V.
/// @date 01.12.2017
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MRANDOM_H
#define MRANDOM_H
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MGlobal.h"
#include <cstdlib>
#include <ctime>
#include <climits>
//#include <random>
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_BEGIN_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
class MRandom
{
public:

    /// @brief Инициализация генератора случайного числа
    /// Задает стартовое начальное значение для генератора псевдослучайных чисел
    static inline void init()
    {
        // in Windows time_t is __time64_t
        std::srand(static_cast<unsigned>(time(NULL)));
    }

    /// @brief Функция возвращает псевдослучайное целое число в интервале [0; RAND_MAX]=[0; 32767]
    /// Обертка rand()
    /// @return Псевдослучайное целое число в диапазоне от 0 до RAND_MAX
    static inline int random()
    {
        return std::rand();
    }

    /// @brief Функция возвращает псевдослучайное целое число в интервале [min; max]
    /// min <= random number <= max
    static inline int randomRange(int min, int max)
    {
        return std::rand() % (max - min + 1) + min;
    }

    static inline int64 randomRange(int64 min, int64 max)
    {
        return std::rand() % (max - min + 1) + min;
    }

    /// @brief Функция возвращает псевдослучайное целое число в интервале [min; max]
    /// min <= random number <= max
    static inline double randomRange(double min, double max)
    {
        return (static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * (max - min) + min;
    }

    /// @brief Функция возвращает псевдослучайное целое число в интервале [0; 1]
    static inline bool random_bool()
    {
        return static_cast<bool>(randomRange(0, 1));
    }

    /// @brief Функция возвращает псевдослучайное целое число в интервале [CHAR_MIN; CHAR_MAX]=[-128; 127]
    static inline char random_char()
    {
        return static_cast<char>(std::rand() % (CHAR_MAX - CHAR_MIN + 1) + CHAR_MIN);
    }

    /// @brief Функция возвращает псевдослучайное целое число в интервале [0; UCHAR_MAX]=[0; 255]
    static inline uchar random_uchar()
    {
        return static_cast<unsigned char>(std::rand() % (UCHAR_MAX + 1));
    }

    /// @brief Функция возвращает псевдослучайное целое число в интервале [CHAR_MIN; CHAR_MAX]=[-128; 127]
    static inline int8 random_int8()
    {
        return static_cast<int8>(std::rand() % (CHAR_MAX - CHAR_MIN + 1) + CHAR_MIN);
    }

    /// @brief Функция возвращает псевдослучайное целое число в интервале [0; UCHAR_MAX]
    static inline uint8 random_uint8()
    {
        return static_cast<uint8>(std::rand() % (UCHAR_MAX + 1));
    }

    /// @brief Функция возвращает псевдослучайное целое число в интервале [SHRT_MIN; SHRT_MAX]=[-32768; 32767]
    static inline int16 random_int16()
    {
        return static_cast<int16>(std::rand() % (SHRT_MAX - SHRT_MIN + 1) + SHRT_MIN);
    }

    /// @brief Функция возвращает псевдослучайное целое число в интервале [0; USHRT_MAX]=[0; 65535]
    static inline uint16 random_uint16()
    {
        return static_cast<uint16>(std::rand() % (USHRT_MAX + 1));
    }

    /// @brief Функция возвращает псевдослучайное целое число в интервале [INT_MIN; INT_MAX]=[-2,147,483,648; 2,147,483,647]
    static inline int32 random_int32()
    {
        return static_cast<int32>(static_cast<double>(std::rand()) /
                                  static_cast<double>(RAND_MAX) *
                                  (static_cast<double>(INT_MAX) - static_cast<double>(INT_MIN)) + INT_MIN);
    }

    /// @brief Функция возвращает псевдослучайное целое число в интервале [0; ULONG_MAX]=[0; 4,294,967,295]
    static inline uint32 random_uint32()
    {
        return static_cast<uint32>(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX) * static_cast<double>(ULONG_MAX));
    }
};
MLIB_END_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // MRANDOM_H
////////////////////////////////////////////////////////////////////////////////////////////////////
