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
/// @file MTimeMeter.h
/// @brief Классы счетчиков времени
/// @author Mitrokhin S.V.
/// @date 09.01.2019
///
/// Счетчики времени, по умолчанию, высокого разрешения
/// см. комментарии к реализации
///
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MTIMEMETER_H
#define MTIMEMETER_H
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MGlobal.h"
#if defined(MLIB_OS_WIN)    
    #include <windows.h>
#endif
#if defined(MLIB_LIB_QT)
    #include <QTime>
#endif
#include <ctime>
#include <chrono>
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_BEGIN_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
class MAbstractTimeMeter
{
public:
    inline MAbstractTimeMeter() { ; }

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isActive() const = 0;
};


#if defined(MLIB_OS_WIN) && (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
/// @brief Cчетчик времени низкого разрешения
/// Используются функции подсчета тиков (разрешение в диапазоне 10 - 16 ms)
class MWinTimeMeterLr
{
public:
    inline MWinTimeMeterLr() : m_uSaveTime(0)
    { ; }

    inline MWinTimeMeterLr(const MWinTimeMeterLr& timeMeter)
    { *this = timeMeter; }

    inline MWinTimeMeterLr & operator=(const MWinTimeMeterLr& timeMeter)
    {
        this->m_uSaveTime = timeMeter.m_uSaveTime;
        return *this;
    }

    /// @brief Начать измерение
    inline void start()
    { m_uSaveTime = ::GetTickCount64(); }

    /// @brief Начать измерение заново
    /// return  Время прошедшее от начала измерения (в миллисекундах)
    inline uint64_t restart()
    {
        uint64_t uTime = msecs();
        start();
        return uTime;
    }

    /// @brief Время прошедшее от начала измерения (в секундах)
    inline double secs()
    { return msecs() / 1e+3; }

    /// @brief Время прошедшее от начала измерения (в миллисекундах)
    inline uint64_t msecs()
    { return ::GetTickCount64() - m_uSaveTime; }

protected:
    uint64_t m_uSaveTime;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Cчетчик времени высокого разрешения реализованный на API ОС Windows
/// В документации упоминается как Windows High-Resolution Timer
class MWinTimeMeter : public MAbstractTimeMeter
{
public:

    /// @brief Конструктор
    inline MWinTimeMeter()
    {
        ::QueryPerformanceFrequency(&m_frequency);
        m_time.QuadPart = 0;
    }

    inline MWinTimeMeter(const MWinTimeMeter& timeMeter)
    { *this = timeMeter; }

    inline MWinTimeMeter & operator=(const MWinTimeMeter& timeMeter)
    {
        this->m_time = timeMeter.m_time;
        return *this;
    }

    /// @brief Начать измерение времени
    inline void start()
    { ::QueryPerformanceCounter(&m_time); }

    /// @brief Начать измерение время
    /// @return Время прошедшее от начала измерения (в секундах)
    inline double restart()
    {
        double dTime = secsf();
        start();
        return dTime;
    }

    /// @brief Остановить измерение времени
    inline void stop()
    {   m_time.QuadPart = 0; }

    /// @brief Измеряется ли время
    inline bool isActive() const
    {   return (m_time.QuadPart != 0) ? true : false; }

    /// @brief Прошедшее время в секундах
    inline double secsf() const
    {
        if (!isActive())
            return 0.0;
        LARGE_INTEGER largeTime;
        ::QueryPerformanceCounter(&largeTime);
        // Вычисляем количество тиков
        largeTime.QuadPart -= m_time.QuadPart;
        // Переводим тики в секунды
        return static_cast<double>(largeTime.QuadPart)/static_cast<double>(m_frequency.QuadPart);
    }

    inline int64_t secsi() const
    {
        if (!isActive())
            return 0.0;
        LARGE_INTEGER largeTime;
        ::QueryPerformanceCounter(&largeTime);
        // Вычисляем количество тиков
        largeTime.QuadPart -= m_time.QuadPart;
        // Переводим тики в секунды
        return largeTime.QuadPart / m_frequency.QuadPart;
    }

    /// @brief Прошедшее время в миллисекундах
    inline double msecsf() const
    { return secsf() * 1e+3; }

    /// @brief Прошедшее время в микросекундах
    inline double mksecsf() const
    { return secsf() * 1e+6; }

    /// @brief Прошедшее время в наносекундах (погрешность!)
    inline double nsecsf() const
    { return secsf() * 1e+9; }

protected:
    LARGE_INTEGER m_frequency;
    LARGE_INTEGER m_time;
};

typedef MWinTimeMeter   MTimeMeterWin;
#endif // defined(MLIB_OS_WIN)

/// @brief Cчетчик времени высокого разрешения на базе библиотеки C POSIX
/// @warning В библиотеке GNU C вы можете просто вычесть значения time_t. Но в других системах тип данных time_t может использовать другую кодировку, где вычитание не работает непосредственно.
class MPosixTimeMeter : public MAbstractTimeMeter
{
public:

    /// @brief Конструктор
    inline MPosixTimeMeter()
    {
        m_startTime.tv_nsec = 0;
        m_startTime.tv_sec = 0;
    }

    inline MPosixTimeMeter(const MPosixTimeMeter& timeMeter)
    { *this = timeMeter; }

    inline MPosixTimeMeter & operator=(const MPosixTimeMeter& timeMeter)
    {
        this->m_startTime = timeMeter.m_startTime;
        return *this;
    }

    ///
    /// @brief Начать измерение времени
    inline void start()
    {   clock_gettime(CLOCK_MONOTONIC, &m_startTime); }

    ///
    /// @brief Начать измерение времени
    /// @return Время прошедшее от начала измерения (в секундах)
    inline double restart()
    {
        double dTime = secsf();
        start();
        return dTime;
    }

    ///
    /// @brief Остановить измерение времени
    inline void stop()
    {   m_startTime.tv_nsec = m_startTime.tv_sec = 0; }

    ///
    /// @brief Измеряется ли время
    inline bool isActive() const
    {   return !((m_startTime.tv_nsec == 0) && (m_startTime.tv_sec == 0)); }    

    ///
    /// @brief Прошедшее время в секундах
    inline double secsf() const
    {
        if (!isActive())
            return 0.0;
        timespec time;
        clock_gettime(CLOCK_MONOTONIC, &time);
        return (time.tv_sec - m_startTime.tv_sec) + ((time.tv_nsec - m_startTime.tv_nsec) / 1e+9) ;
    }

    inline std::time_t secsi() const
    {
        if (!isActive())
            return 0.0;
        timespec time;
        clock_gettime(CLOCK_MONOTONIC, &time);
        return (time.tv_sec - m_startTime.tv_sec);
    }

    ///
    /// @brief Прошедшее время в миллисекундах
    inline double msecsf() const
    { return secsf() * 1e+3; }

    inline std::time_t msecsi() const
    { return static_cast<std::time_t>(secsf() * 1e+3); }

    ///
    /// @brief Прошедшее время в микросекундах
    inline double usecsf() const
    { return secsf() * 1e+6; }

    inline std::time_t usecsi() const
    { return static_cast<std::time_t>(secsf() * 1e+6); }

    ///
    /// @brief Прошедшее время в наносекундах
    /// @return Число типа double (дробная часть не используется)
    inline double nsecsf() const
    {
        if (!isActive())
            return 0.0;
        timespec time;
        clock_gettime(CLOCK_MONOTONIC, &time);
        return (((time.tv_sec - m_startTime.tv_sec) * 1e+9) + (time.tv_nsec - m_startTime.tv_nsec));
    }

    ///
    /// @brief Прошедшее время в наносекундах
    /// @return Целое число типа time_t, которое переопределяется в зависимости от платформы в 32 или 64 бита
    inline std::time_t nsecsi() const
    {
        if (!isActive())
            return 0.0;
        timespec time;
        clock_gettime(CLOCK_MONOTONIC, &time);
        return (((time.tv_sec - m_startTime.tv_sec) * 1e+9) + (time.tv_nsec - m_startTime.tv_nsec));
    }

    ///
    /// @brief Прошедшее время в наносекундах
    /// @return Целое число типа time_t, которое переопределяется в зависимости от платформы в 32 или 64 бита
    inline uint64_t nsecsi64() const
    {
        if (!isActive())
            return 0.0;
        timespec time;
        clock_gettime(CLOCK_MONOTONIC, &time);
        return (((time.tv_sec - m_startTime.tv_sec) * 1000000000ull) + (time.tv_nsec - m_startTime.tv_nsec));
    }

protected:
    timespec m_startTime;
};

// Для совместимости
#define time_secs   secsf
#define time_msecs  msecsf
#define time_mksecs mksecsf
#define time_nsecf  nsecsf

#define secs   secsf
#define msecs  msecsf
#define mksecs usecsf
#define nsecf  nsecsf

#if MLIB_SUPPORT_STD_CPP11

class MTimeMeter : public MAbstractTimeMeter
{
public:

    /// @brief Начать измерение времени
    inline void start()
    {   m_startTimePoint = std::chrono::steady_clock::now(); }

    /// @brief Начать измерение времени
    inline double restart()
    {
        double dTime = secsf();
        start();
        return dTime;
    }

    /// @brief Остановить измерение времени
    inline void stop()
    {   m_isStart = false; }

    /// @brief Измеряется ли время
    inline bool isActive() const
    {   return true;/*m_startTimePoint.time_since_epoch() != 0;*/ }

    /// @brief Прошедшее время в секундах
   /*
    template <typename _type>
    inline _type secs() const
    {
        if (!isActive())
            return static_cast<double>(0);
        std::chrono::steady_clock::time_point endTimePoint = std::chrono::steady_clock::now();
        std::chrono::duration<_type, 1> elapsedTime = endTimePoint - m_startTimePoint;
        return elapsedTime.count();
    }*/

    //typedef inline double secsf() const = secs<double>();


    inline double secsf() const
    {
        if (!isActive())
            return static_cast<double>(0);
        std::chrono::steady_clock::time_point endTimePoint = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime = endTimePoint - m_startTimePoint;
        return elapsedTime.count();
    }

    inline int64_t secsi() const
    {
        if (!isActive())
            return static_cast<int64_t>(0);
        std::chrono::steady_clock::time_point endTimePoint = std::chrono::steady_clock::now();
        //std::chrono::duration<int64_t> elapsedTime = std::chrono::duration_cast<std::chrono::duration<int64_t>>(endTimePoint - m_startTimePoint);
        std::chrono::seconds elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(endTimePoint - m_startTimePoint);
        return elapsedTime.count();
    }

    inline double msecsf() const
    {
        if (!isActive())
            return static_cast<double>(0);
        std::chrono::steady_clock::time_point endTimePoint = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> elapsedTime = endTimePoint - m_startTimePoint;
        return elapsedTime.count();
    }

    inline int64_t msecsi() const
    {
        if (!isActive())
            return static_cast<double>(0);
        std::chrono::steady_clock::time_point endTimePoint = std::chrono::steady_clock::now();
        std::chrono::duration<int64_t, std::milli> elapsedTime = std::chrono::duration_cast<std::chrono::duration<int64_t, std::milli>>(endTimePoint - m_startTimePoint);
        return elapsedTime.count();
    }

protected:

    std::chrono::steady_clock::time_point m_startTimePoint;
    bool m_isStart;
};

#else
typedef MPosixTimeMeter MTimeMeter;

#endif // MLIB_SUPPORT_STD_CPP11

//system_clock::now();
//auto now = system_clock::now();
//time_t now_t = system_clock::to_time_t(now);
//auto now2 = system_clock::from_time_t(now_t);



#ifdef MLIB_LIB_QT
class MQtTimeMeter
{
public:

    inline void start()
    {
        m_time = QTime::currentTime();
    }

    inline double secs()
    {
        return m_time.msecsTo( QTime::currentTime() )  / 1e+3;
    }

    inline int msecs()
    {
        return m_time.msecsTo( QTime::currentTime() );
    }

protected:

    QTime m_time;
};
#endif // MLIB_LIB_QT
////////////////////////////////////////////////////////////////////////////////////////////////////
// Для совместимости
typedef MPosixTimeMeter MTimeMeterPosix;
#ifdef MLIB_LIB_QT
typedef MQtTimeMeter    MTimeMeterQt;
#endif // MLIB_LIB_QT
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_END_NAMESPACE
#endif // MTIMEMETER_H
////////////////////////////////////////////////////////////////////////////////////////////////////
