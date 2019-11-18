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
/// @file MLogQt.h
/// @brief Класс журналирования событий
/// @author Mitrokhin S.V.
/// @date 18.11.2019
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MLOGQT_H
#define MLOGQT_H
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../core/MGlobal.h"
#ifdef MLIB_LIB_QT
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MLogBufferQt.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMutex>
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_BEGIN_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
class MLogBufferQt;
class MLogQt
{
public:    

    MLogQt();

    virtual ~MLogQt();

    inline MLogQt(FILE * con, const char * filename)
    {
        openConOutput(con);
        openFileOutput(filename);
    }

    inline MLogQt(FILE * con, const std::string & filename)
    {
        openConOutput(con);
        openFileOutput(filename);
    }

    inline MLogQt(FILE * con, const QString & filename)
    {
        openConOutput(con);
        openFileOutput(filename);
    }

    inline MLogQt(FILE * con, FILE * file)
    {
        openConOutput(con);
        openFileOutput(file);
    }


    bool openConOutput(FILE * file);
    void closeConOutput();


    bool openFileOutput(const char * filename);
    bool openFileOutput(const std::string & filename);
    bool openFileOutput(const QString & filename);
    bool openFileOutput(FILE * file);
    void closeFileOutput();
    bool isOpenFileOutput();




    uint level() const  {   return m_level; }
    void setLevel(uint level){ m_level = level; }

    uint category() const { return m_category; }
    void setCategory(uint category){    m_category = category; }

    MLogBufferQt log();
    MLogBufferQt log(uint category);

    MLogBufferQt logWarning();
    MLogBufferQt logWarning(uint category);

    MLogBufferQt logError();
    MLogBufferQt logError(uint category);

    void write(const QString & string);
    void writeLine(const QString & string);

protected:

    template <class T>
    inline void _clearPtr(T* & ptr)
    {
        if (ptr)
        {
            delete ptr;
            ptr = 0;
        }
    }

protected:

    uint            m_mask;    

    QFile *         m_conFile;
    QFile *         m_file;

    uint            m_level;
    uint            m_category;
    QMutex          m_mxConsole;
    QMutex          m_mxFile;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_END_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // MLIB_LIB_QT
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // MLOGQT_H
////////////////////////////////////////////////////////////////////////////////////////////////////
