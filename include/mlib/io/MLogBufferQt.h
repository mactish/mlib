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
/// @file MLogBufferQt.h
/// @brief Класс буфера журнала
/// @author Mitrokhin S.V.
/// @date 01.11.2019
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MLOGBUFFERQT_H
#define MLOGBUFFERQT_H
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../core/MGlobal.h"
#ifdef MLIB_LIB_QT
#include "MLogQt.h"
#include <QString>
#include <QTextStream>
#include <QDebug>
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_BEGIN_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
#define LOG_ALL 0xFFFFFFFF
////////////////////////////////////////////////////////////////////////////////////////////////////
enum MessageType
{
    LogMsgNormal    = 0,    // Стандартное сообщение логирования
    LogMsgInfo      = 1,    // Сообщение информирования
    LogMsgWarning   = 2,    // Сообщение о внимании
    LogMsgError     = 3,    // Сообщение о ошибке
    LogMsgCritical  = 4     // Сообщение о критической ошибке
};

struct _Level
{
    uint level;
};

inline _Level level(uint level)
{
    return {level};
}

struct _Category
{
    uint cat;
};

inline _Category cat(uint cat)
{
    return {cat};
}
////////////////////////////////////////////////////////////////////////////////////////////////////
class MLogQt;
class MLogBufferQt;

typedef MLogBufferQt& (*MLogFunction)(MLogBufferQt &);

struct MLogBufferParams
{

};

class MLogBufferQt
{
public:

    MLogBufferQt() = delete;

    inline MLogBufferQt(MLogQt * logQt) : m_logQt       (logQt),
                                          m_tsBuffer    (new QTextStream(&m_buffer)),
                                          m_level       (0),
                                          m_category    (LOG_ALL)
    { ; }

    inline MLogBufferQt(MLogQt * logQt, uint cat) : m_logQt     (logQt),
                                                    m_tsBuffer  (new QTextStream(&m_buffer)),
                                                    m_level     (0),
                                                    m_category  (cat)
    { ; }

    ~MLogBufferQt();

    MLogBufferQt(const MLogBufferQt & logBufferQt);

    MLogBufferQt & operator =(const MLogBufferQt & logBufferQt);

    inline MLogBufferQt & operator <<(char value)
    {
        (*m_tsBuffer) << value;
        return *this;
    }

    inline MLogBufferQt & operator <<(signed short value)
    {
        (*m_tsBuffer) << value;
        return *this;
    }

    inline MLogBufferQt & operator <<(unsigned short value)
    {
        (*m_tsBuffer) << value;
        return *this;
    }

    inline MLogBufferQt & operator <<(signed int value)
    {
        (*m_tsBuffer) << value;
        return *this;
    }

    inline MLogBufferQt & operator <<(unsigned int value)
    {
        (*m_tsBuffer) << value;
        return *this;
    }

    inline MLogBufferQt & operator <<(signed long value)
    {
        (*m_tsBuffer) << value;
        return *this;
    }

    inline MLogBufferQt & operator <<(unsigned long value)
    {
        (*m_tsBuffer) << value;
        return *this;
    }

    inline MLogBufferQt & operator <<(signed long long value)
    {
        (*m_tsBuffer) << value;
        return *this;
    }

    inline MLogBufferQt & operator <<(unsigned long long value)
    {
        (*m_tsBuffer) << value;
        return *this;
    }

    inline MLogBufferQt & operator <<(float value)
    {
        (*m_tsBuffer) << value;
        return *this;
    }

    inline MLogBufferQt & operator <<(double value)
    {
        (*m_tsBuffer) << value;
        return *this;
    }

    inline MLogBufferQt & operator <<(const char * ptr)
    {
        (*m_tsBuffer) << ptr;
        return *this;
    }

    inline MLogBufferQt & operator <<(const void * ptr)
    {
        (*m_tsBuffer) << ptr;
        return *this;
    }

    inline MLogBufferQt & operator <<(QChar c)
    {
        (*m_tsBuffer) << c;
        return *this;
    }

    inline MLogBufferQt & operator <<(const QString & str)
    {
        (*m_tsBuffer) << str;
        return *this;
    }

    inline MLogBufferQt & operator <<(_Level level)
    {
        m_level = level.level;
        return *this;
    }

    inline MLogBufferQt & operator <<(_Category cat)
    {
        m_category = cat.cat;
        return *this;
    }

    inline MLogBufferQt & operator<<(MLogFunction func)
    {
        return (*func)(*this);
    }

    QString type() const;

    void flush();

    inline void clear(){    m_buffer.clear(); }
    inline uint category() const {  return m_category; }

protected:

    MLogQt *        m_logQt;
    QString         m_buffer;
    QTextStream *   m_tsBuffer;
    uint            m_type;
    uint            m_level;    
    uint            m_category;

    friend MLogBufferQt & flush(MLogBufferQt & log);
    friend MLogBufferQt & endl(MLogBufferQt & log);
    friend MLogBufferQt & eol(MLogBufferQt & log);
    friend MLogBufferQt & info(MLogBufferQt & log);
    friend MLogBufferQt & warning(MLogBufferQt & log);
    friend MLogBufferQt & error(MLogBufferQt & log);
    friend MLogBufferQt & critical(MLogBufferQt & log);
};
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
inline MLogBufferQt & operator<<(MLogBufferQt & log, MLogFunction func)
{
    return (*func)(log);
}*/
////////////////////////////////////////////////////////////////////////////////////////////////////
inline MLogBufferQt & flush(MLogBufferQt & log)
{
    log.flush();
    return log;
}
inline MLogBufferQt &endl(MLogBufferQt &log)
{
    log << QLatin1Char('\n');// << mlib::flush;
    return log;
}
inline MLogBufferQt &eol(MLogBufferQt &log)
{
    log << QLatin1Char('\n');
    return log;
}
inline MLogBufferQt & info(MLogBufferQt & log)
{
    log.m_type = LogMsgInfo;
    return log;
}
inline MLogBufferQt & warning(MLogBufferQt & log)
{
    log.m_type = LogMsgWarning;
    return log;
}
inline MLogBufferQt & error(MLogBufferQt & log)
{
    log.m_type = LogMsgError;
    return log;
}
inline MLogBufferQt & critical(MLogBufferQt & log)
{
    log.m_type = LogMsgCritical;
    return log;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_END_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // MLIB_LIB_QT
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // MLOGBUFFERQT_H
////////////////////////////////////////////////////////////////////////////////////////////////////
