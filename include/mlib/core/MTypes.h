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
/// @file MTypes.h
/// @brief Определение типов данных для библиотеки
/// @author Mitrokhin S.V.
/// @date 21.05.2019
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MTYPES_H
#define MTYPES_H
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MGlobal.h"
#include <cstdint>
#include <cfloat>
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_BEGIN_NAMESPACE

typedef unsigned char           uchar_t;
typedef unsigned short int      ushort_t;
typedef unsigned long int       uint_t;
typedef unsigned long long int  ullint_t;

// Универсальные типы данных (могут быть многократно переопределены)
#if defined(MLIB_DISABLE_UNIVERSAL_TYPES) or !defined(MLIB_LIB_QT)
    typedef unsigned char               uchar;
    typedef unsigned short int          ushort;
    typedef unsigned long int           uint;
    typedef unsigned long               ulong;
    typedef unsigned long long int      ullint;
#endif

#define MLIB_USING_TYPES_EXT

typedef char                            mint8;
#if MLIB_SUPPORT_STD_CPP11
typedef char16_t                        mchar16;
typedef char32_t                        mchar32;
#endif
typedef unsigned char                   muint8;
typedef wchar_t                         mwchar;
typedef short int                       mint16;
typedef unsigned short int              muint16;
typedef long int                        mint32;
typedef unsigned long int               muint32;
typedef long long int                   mint64;
typedef unsigned long long int          muint64;

#if defined(MLIB_USING_TYPES_EXT)
typedef char                            int8;
#if MLIB_SUPPORT_STD_CPP11
typedef char16_t                        char16;
typedef char32_t                        char32;
#endif
typedef unsigned char                   uint8;
typedef wchar_t                         wchar;
typedef short int                       int16;
typedef unsigned short int              uint16;
typedef long int                        int32;
typedef unsigned long int               uint32;
typedef long long int                   int64;
typedef unsigned long long int          uint64;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// Floating point types

// IEEE754 Single precision 32-bit
typedef union
{
    struct
    {
        uint32_t f : 23;    // fraction (also mantissa, see wiki)
        uint32_t e : 8;     // exponent
        uint32_t s : 1;     // sign
    }b;                     // binary32 bit field
    float       f;
    uint32_t    u;
} binary32;

// IEEE754 Double precision 64-bit
typedef union
{
    struct
    {
        uint64_t f : 52;    // fraction (also mantissa, see wiki)
        uint64_t e : 11;    // exponent
        uint64_t s : 1;     // sign
    }b;                     // binary64 bit field
    double      f;
    uint64_t    u;
} binary64;

MLIB_END_NAMESPACE
#endif // MTYPES_H
////////////////////////////////////////////////////////////////////////////////////////////////////
