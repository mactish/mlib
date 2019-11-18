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
/// @file MErrorText.h
/// @brief Класс для получения текста сообщения об ошибке
/// @author Mitrokhin S.V.
/// @date 18.11.2019
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MERRORTEXT_H
#define MERRORTEXT_H
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cstring>
#include <cerrno>
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MGlobal.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_BEGIN_NAMESPACE

/// @brief Номер последней ошибки
inline int lastError() { return errno; }

/// @brief Текст последней ошибки
inline char * lastErrorStr(){ return std::strerror(errno); }

MLIB_END_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //MERRORTEXT_H
////////////////////////////////////////////////////////////////////////////////////////////////////
