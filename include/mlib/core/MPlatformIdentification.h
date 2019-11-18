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
/// @file MPlatformIdentification.h
/// @brief Identify the current platform.
/// @author Mitrokhin S.V.
/// @date 05.11.2019
///
/// # Definition of OS, compiler and libraries.
///
/// ## Pre-defined operating systems macroses
///
/// ### Linux
///
/// | Macros                | Used                                              |
/// | --------------------: | :------------------------------------------------ |
/// | `__linux__`           | Centos, Debian, Fedora, OpenSUSE, RedHat, Ubuntu  |
/// | `linux`               | Obsolete                                          |
/// | `__linux`             | Obsolete                                          |
///
/// ### MSDOS
///
/// | Macros                                  | Used                            |
/// | --------------------------------------: | :------------------------------ |
/// | MSDOS, `__MSDOS__`, `__DOS__`, `_MSDOS` | MS DOS                          |
///
/// ### QNX
///
/// | Macros                | Used                                              |
/// | --------------------: | :------------------------------------------------ |
/// | `__QNX__`             | QNX OS (QNX 4 & QNX Neutrino)                     |
/// | `__QNXNTO__`          | QNX Neutrino                                      |
/// | `_NTO_VERSION VRR`    | for QNX 6.x Version (V = Version RR = Revision)   |
///
/// ### Windows
///
/// | Macros                | Used                                                                  |
/// | --------------------: | :-------------------------------------------------------------------- |
/// | `_WIN32`              | MSVS Defined for both 32-bit and 64-bit environments. Always defined. |
/// | `_WIN64`              | MSVS Defined for 64-bit environments.                                 |
/// | `__WIN32__`           | Defined by Borland C++                                                |
/// | WIN32, `__WIN32__`    | GNU GCC/G++, MinGW                                                    |
/// | WIN64, `__WIN64__`    | GNU GCC/G++, MinGW                                                    |
/// More: https://docs.microsoft.com/ru-ru/cpp/preprocessor/predefined-macros
///
///
/// ## Compilers
///
/// ### GCC C/C++
/// <table>
/// <tr><th> Macros </th>                       <th> Used </th>                                                                         </tr>
///
/// <tr><td> `__GNUC__`,<br>`__GNUG__` </td>    <td> These macros are defined by all GNU compilers that use the C preprocessor. <br>
///                                                  The GNU C++ compiler defines this (__GNUC__ && __cplusplus).               </td>   </tr>
/// </table>
/// More: https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html
///
/// ### MinGW and MinGW-w64
/// | Macros                | Used                                              |
/// | --------------------: | :------------------------------------------------ |
/// | `__MINGW32__`         | Defined for both MinGW and MinGW-w64              |
/// | `__MINGW64__`         | Defined for MinGW-w64                             |
///
/// ### Microsoft Visual C++
/// | Macros                | Used                                              |
/// | --------------------: | :------------------------------------------------ |
/// | `_MSC_VER`            | Defined version                                   |
/// | `_MSC_BUILD`          | Defined build number                              |
/// More: https://docs.microsoft.com/ru-ru/cpp/preprocessor/predefined-macros
///
/// ### Borland C++
/// | Macros                ||
/// | --------------------: ||
/// | `__BORLANDC__`        ||
///
///
/// ## Libraries
///
/// ### Standard C Libraries
///
/// #### GNU glibc
/// | Macros                | Used                                              |
/// | --------------------: | :------------------------------------------------ |
/// | `__GLIBC__`           | Deprecated. From version 6                        |
/// | `__GLIBC_MINOR__`     | Deprecated. From version 6                        |
///
/// ### Standard C++ Libraries
///
/// #### GNU libstdc++ (The GNU C++ Library)
/// <table>
/// <tr><th> Macros </th>               <th> Used </th>                                         </tr>
/// <tr><td> `__GLIBCPP__`      </td>   <td> From GCC 3.0.0 until GCC 3.4.0. </td>              </tr>
/// <tr><td> `__GLIBCXX__`      </td>   <td> From GCC 3.4.0 until now. </td>                    </tr>
/// <tr><td> `_GLIBCXX_RELEASE` </td>   <td> The revision date (current version) of the libstdc++ source code, <br>
///                                          in compressed ISO date format, as an unsigned long. <br>
///                                          From GCC 7.1 until now. <br>
///                                          The major release number. </td>                    </tr>
/// </table>
/// More: https://gcc.gnu.org/onlinedocs/libstdc%2B%2B/manual/using_macros.html
///
/// #### Dinkumware
/// | Macros                ||
/// | --------------------: ||
/// | `__CPPLIB_VER`        ||
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MPLATFORMTYPE_H
#define MPLATFORMTYPE_H
////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    #ifndef MLIB_OS_WIN
        #define MLIB_OS_WIN
    #endif

    #define MLIB_OS_WIN32

    #if defined(_WIN64) || defined(WIN64)
        #define MLIB_OS_WIN64
    #endif
#elif defined(__linux__) || defined(linux) || defined(_linux)
    #ifndef(MLIB_OS_LINUX)
        #define MLIB_OS_LINUX
    #endif
#elif defined(MSDOS) || defined(__MSDOS__) || defined(__DOS__) || defined(_MSDOS)
    #ifndef MLIB_OS_MSDOS
        #define MLIB_OS_MSDOS
    #endif
#elif defined(__QNXNTO__)
    #ifndef MLIB_OS_QNX
        #define MLIB_OS_QNX
    #endif    
    #define MLIB_OS_QNX_VERSION _NTO_VERSION
#else
    #ifndef MLIB_OS_UNKNOWN
        #define MLIB_OS_UNKNOWN
    #endif
    #error "Unknown OS, no support this OS"
#endif

#if defined(QT_VERSION)
    #ifndef MLIB_LIB_QT
        #define MLIB_LIB_QT
    #endif
#elif defined(__ATLBASE_H__) || defined(_AFX)
    #ifndef MLIB_LIB_MFC
        #define MLIB_LIB_MFC
    #endif
#endif

#if defined(__GLIBCXX__) || defined(__GLIBCPP__)
    #define MLIB_LIBCPP_VERSION
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// C ISO standart support
#define MLIB_STD_C99 199901L    // Full support C99
#define MLIB_STD_C11 201112L    // Full support C11

#define MLIB_SUPPORT_STD_C99 __STDC_VERSION__ >= MLIB_STD_C99
#define MLIB_SUPPORT_STD_C11 __STDC_VERSION__ >= MLIB_STD_C11

////////////////////////////////////////////////////////////////////////////////////////////////////
// CPP ISO standart support
// If the macro __cplusplus is defined, then the CPP compiler is used.
// Its value depends on the version of the standart supported by the compiler.
#if defined(__cplusplus)
    #define MLIB_CPP_STANDART __cplusplus
    #define MLIB_CPP_STD __cplusplus

    #define MLIB_STD_CPP98 199711L  // C++98 (ISO C++ 1998/2003)
    #define MLIB_STD_CPP11 201103L  // C++11 (ISO C++ 2011)
    #define MLIB_STD_CPP14 201402L  // C++14 (ISO C++ 2014)
    #define MLIB_STD_CPP17 201703L  // C++17 (ISO C++ 2017)

    #define MLIB_CPP_98 MLIB_STD_CPP98
    #define MLIB_CPP_11 MLIB_STD_CPP11
    #define MLIB_CPP_14 MLIB_STD_CPP14
    #define MLIB_CPP_17 MLIB_STD_CPP17

    #define MLIB_SUPPORT_CPP98 __cplusplus >= MLIB_STD_CPP98
    #define MLIB_SUPPORT_CPP11 __cplusplus >= MLIB_STD_CPP11
    #define MLIB_SUPPORT_CPP14 __cplusplus >= MLIB_STD_CPP14
    #define MLIB_SUPPORT_CPP17 __cplusplus >= MLIB_STD_CPP17

    #define MLIB_USING_CPP98 __cplusplus == MLIB_STD_CPP98
    #define MLIB_USING_CPP11 __cplusplus == MLIB_STD_CPP11
    #define MLIB_USING_CPP14 __cplusplus == MLIB_STD_CPP14
    #define MLIB_USING_CPP17 __cplusplus == MLIB_STD_CPP17
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// Compiler

#if defined(__GNUC__) || defined(__GNUG__)
    // GNU C/C++ compiler
    #define MLIB_GCC
    #define MLIB_C_GCC

    #define MLIB_GCC_VERSION (__GNUC__ * 10000 \
                              + __GNUC_MINOR__ * 100 \
                              + __GNUC_PATCHLEVEL__)

    #if defined(__MINGW32__) || defined(__MINGW64__)
        #define MLIB_MINGW
        #define MLIB_C_MINGW
    #endif

    #if defined(__MINGW32__)
        #define MLIB_MINGW32
        #define MLIB_C_MINGW32
    #endif

    #if defined(__MINGW64__)
        #define MLIB_MINGW64
        #define MLIB_C_MINGW64
    #endif

    // MS C/C++ Compiler
#elif defined(_MSC_VER)
    #define MLIB_MSC
    #define MLIB_С_MSС
#else
    #error "Undefened compiler"
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //MPLATFORMTYPE_H
////////////////////////////////////////////////////////////////////////////////////////////////////
