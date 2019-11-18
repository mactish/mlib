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
/// @brief Событие времени ожидания
/// @author Mitrokhin S.V.
/// @date 11.01.2019
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MTIMEEVENT_H
#define MTIMEEVENT_H
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MGlobal.h"
#include "MTimeMeter.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_BEGIN_NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////////
// wait time event
class MTimeEvent
{
public:

    MTimeEvent() :  m_isEventExpected   (false),
                    m_isEventOccured    (false),
                    m_waitingTimeMs     (0.0)
    { ; }

    MTimeEvent(double waitingTime) :
        m_isEventExpected   (false),
        m_isEventOccured    (false),
        m_waitingTimeMs     (waitingTime)
    { ; }

    MTimeEvent(const MTimeEvent & timeEvent) :
        m_isEventExpected   (timeEvent.m_isEventExpected),
        m_isEventOccured    (timeEvent.m_isEventOccured),
        m_waitingTimeMs     (timeEvent.m_waitingTimeMs)
    { ; }

    inline MTimeEvent& operator=(const MTimeEvent & timeEvent)
    {
        m_isEventExpected = timeEvent.m_isEventExpected;
        m_isEventOccured = timeEvent.m_isEventOccured;
        m_waitingTimeMs = timeEvent.m_waitingTimeMs;
        return *this;
    }
    
    /// Start an event session.
    inline void start()
    {
        m_isEventExpected = true;
        m_isEventOccured = false;
        m_timeMeter.restart();
    }
    
    inline void restartTime()
    {
        m_timeMeter.restart();
    }
    
    inline void setWaitingTimeMs(double time)
    {
        m_waitingTimeMs = time;
    }
    
    /// End an event session. (rn stop -> finish ?)
    inline void stop()
    {
        m_isEventExpected = false;
        m_isEventOccured = false;
    }

    inline bool check()
    {
        if (m_timeMeter.msecsf() > m_waitingTimeMs)
        {
            m_isEventOccured = true;
            m_isEventExpected = false;
        }
        return m_isEventOccured;
    }

    // Ожидается ли событие
    inline bool isExpected() const { return m_isEventExpected; }

    // Произошло (случилось) ли событие
    inline bool isOccured() const { return m_isEventOccured; }
    
    /// Returns a const reference to the timeMeter object.
    inline const MPosixTimeMeter & timeMeter() const
    {
        return m_timeMeter;
    }
    
    /// @deprecated Returns a reference to the timeMeter object, used to restart the time meter.
    inline MPosixTimeMeter & timeMeterRef()
    {
        return m_timeMeter;
    }

   // bool operator() const { return m_isExecEvent; }

protected:

    bool                m_isEventExpected;  // Ожидается ли событие
    bool                m_isEventOccured;   // Произошло (случилось) ли событие
    double              m_waitingTimeMs;
    MPosixTimeMeter     m_timeMeter;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
MLIB_END_NAMESPACE
#endif // MTIMER_H
////////////////////////////////////////////////////////////////////////////////////////////////////
