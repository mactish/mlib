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
/// @file MLogBufferQt.cpp
/// @brief Класс буфера журнала
/// @author Mitrokhin S.V.
/// @date 01.11.2019
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MLogBufferQt.h"
#ifdef MLIB_LIB_QT
#include <QDateTime>
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_BEGIN_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
#if QT_VERSION >= QT_VERSION_CHECK(5, 8, 0)
#define LOGTIME (Qt::ISODateWithMs)
#else
#define LOGTIME ("yyyy-MM-ddTHH:mm:ss:zzz")
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////
MLogBufferQt::~MLogBufferQt()
{
    if (m_buffer.isEmpty() == false)
        flush();

    if (m_tsBuffer != 0)
        delete m_tsBuffer;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
MLogBufferQt::MLogBufferQt(const MLogBufferQt &logBufferQt)
{
    m_logQt     = logBufferQt.m_logQt;
    m_buffer    = logBufferQt.m_buffer;
    m_tsBuffer  = new QTextStream(&m_buffer);
    m_type      = logBufferQt.m_type;
    m_level     = logBufferQt.m_level;
    m_category  = logBufferQt.m_category;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
MLogBufferQt &MLogBufferQt::operator =(const MLogBufferQt &logBufferQt)
{
    // m_tsBuffer у каждого свой
    m_logQt     = logBufferQt.m_logQt;
    m_buffer    = logBufferQt.m_buffer;
    m_type      = logBufferQt.m_type;
    m_level     = logBufferQt.m_level;
    m_category  = logBufferQt.m_category;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
QString MLogBufferQt::type() const
{
    switch (m_type)
    {
        case LogMsgNormal:      return QString();
        case LogMsgInfo:        return QString("[Info]");
        case LogMsgWarning:     return QString("[Warning]");
        case LogMsgError:       return QString("[Error]");
        case LogMsgCritical:    return QString("[Critical]");
    }
    return QString();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MLogBufferQt::flush()
{
    if (!m_buffer.isEmpty() && m_level <= m_logQt->level() && (m_category & m_logQt->category()))
    {
        if (m_type == 0)
            m_logQt->write(QString("%1 %2").arg(QDateTime::currentDateTime().toString(LOGTIME)).arg(m_buffer));
        else
            m_logQt->write(QString("%1 %2 %3").arg(QDateTime::currentDateTime().toString(LOGTIME)).arg(type()).arg(m_buffer));
        m_buffer.clear();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_END_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // MLIB_LIB_QT
////////////////////////////////////////////////////////////////////////////////////////////////////
