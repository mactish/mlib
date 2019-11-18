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
#include "MLogQt.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef MLIB_LIB_QT
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_BEGIN_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
MLogQt::MLogQt() :  m_conFile       (0),
                    m_file          (0),
                    m_level         (0),
                    m_category      (LOG_ALL)
{ ; }
////////////////////////////////////////////////////////////////////////////////////////////////////
MLogQt::~MLogQt()
{
    closeConOutput();
    closeFileOutput();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool MLogQt::openConOutput(FILE * file)
{
    if (file == 0)
        return false;

    QFile * conFile = new QFile;
    if (conFile->open(file, QFile::WriteOnly) == false)
    {
        delete conFile;
        return false;
    }

    m_mxConsole.lock();
    _clearPtr(m_conFile);
    m_conFile = conFile;    
    m_mxConsole.unlock();
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MLogQt::closeConOutput()
{
    m_mxConsole.lock();
    if (m_conFile)
    {
        m_conFile->close();
        _clearPtr(m_conFile);
    }
    m_mxConsole.unlock();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool MLogQt::openFileOutput(const char * filename)
{
    if (filename == 0)
        return false;
    return openFileOutput(QString::fromLatin1(filename));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool MLogQt::openFileOutput(const std::string &filename)
{
    return openFileOutput(QString::fromStdString(filename));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool MLogQt::openFileOutput(const QString &filename)
{
    QFile * file= new QFile(filename);
    if (file->open(QFile::WriteOnly) == false)
    {
        delete file;
        return false;
    }

    m_mxFile.lock();
    _clearPtr(m_file);
    m_file = file;    
    m_mxFile.unlock();
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MLogQt::closeFileOutput()
{
    m_mxFile.lock();
    if (m_file)
    {
        m_file->close();
        _clearPtr(m_file);
    }
    m_mxFile.unlock();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool MLogQt::isOpenFileOutput()
{
    QMutexLocker ml(&m_mxFile);
    return (m_file != 0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
MLogBufferQt MLogQt::log()
{
    return MLogBufferQt(this);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
MLogBufferQt MLogQt::log(uint category)
{
    return MLogBufferQt(this, category);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
MLogBufferQt MLogQt::logWarning()
{
    return MLogBufferQt(this) << mlib::warning;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
MLogBufferQt MLogQt::logWarning(uint category)
{
    return MLogBufferQt(this, category) << mlib::warning;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
MLogBufferQt MLogQt::logError()
{
    return MLogBufferQt(this) << mlib::error;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
MLogBufferQt MLogQt::logError(uint category)
{
    return MLogBufferQt(this, category) << mlib::error;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MLogQt::write(const QString & string)
{
    QByteArray byteArray = string.toLatin1();

    m_mxConsole.lock();
    if (m_conFile)
    {
        m_conFile->write(byteArray);
        m_conFile->flush();
    }
    m_mxConsole.unlock();

    m_mxFile.lock();
    if (m_file)
    {
        m_file->write(byteArray);
        m_file->flush();
    }
    m_mxFile.unlock();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MLogQt::writeLine(const QString &string)
{
    write(QString("%1\n").arg(string));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_END_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // MLIB_LIB_QT
////////////////////////////////////////////////////////////////////////////////////////////////////