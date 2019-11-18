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
/// @file MGlobal.h
/// @brief Общий файл библиотеки
/// @author Mitrokhin S.V.
/// @date 18.11.2019
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MGLOBAL_H
#define MGLOBAL_H
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cstddef>
#include "MPlatformIdentification.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
#define MLIB_VERSION_STR "1.0.7"
#define MLIB_VERSION 0x010007
#define MLIB_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))
#define MLIB

#if defined (__cplusplus)
#define MLIB_NAMESPACE mlib
#define MLIB_BEGIN_NAMESPACE namespace MLIB_NAMESPACE {
#define MLIB_END_NAMESPACE }
#define MLIB_USE_NAMESPACE using namespace MLIB_NAMESPACE;
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_UNICODE) || defined(UNICODE)
    #define txt(text)           L##text
    #define TXT(text)           L##text
#else
    #define txt(text)           text
    #define TXT(text)           text
#endif

/// Macro for unised variables
#define MLIB_UNISED(x)  (void)(x)
////////////////////////////////////////////////////////////////////////////////////////////////////
#if MLIB_SUPPORT_CPP11
    #define MLIB_CONSTEXPR constexpr
#else
    #define MLIB_CONSTEXPR
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // MGLOBAL_H
////////////////////////////////////////////////////////////////////////////////////////////////////
