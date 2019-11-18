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
/// @file MFastCRC32.h
/// @brief Табличный (быстрый) расчет контрольной суммы по алгоритму CRC32/zlib
/// @author Mitrokhin S.V.
/// @date 22.08.2019
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MFASTCRC32_H
#define MFASTCRC32_H
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../core/MGlobal.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_BEGIN_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef unsigned long int crc32_t; ///< Для совместимости кроссплатформенной разработки

/// \brief Инициализация (подготовка) переменной для подсчета контрольной суммы
/// \param crc32    - переменная для подсчета контрольной суммы
extern inline void crc32Init(crc32_t & crc32){ crc32 = (crc32_t)(~0); }


/// \brief Расчет контрольной суммы для массива входных данных
/// \param data     - массив входных данных
/// \param length   - длина массива входных данных
/// \param crc32    - переменная для подсчета контрольной суммы (с промежуточным значением)
extern void crc32Update(const unsigned char * data, crc32_t length, crc32_t & crc32);

/// \brief Получение контрольной суммы в используемой переменной 
/// \param[IN]  crc32 - переменная для подсчета контрольной суммы (с промежуточным значением)
/// \param[OUT] crc32 - контрольная сумма рассчитанная по алгоритму CRC-32-IEEE 802.3
extern inline void crc32Result(crc32_t & crc32){ crc32 = ~crc32; }
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_END_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // MFASTCRC32_H
////////////////////////////////////////////////////////////////////////////////////////////////////
