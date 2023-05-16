/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2018-2023, Japan Embedded Systems Technology Association(JASA)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//#include <vector>

#include "EventTimer.hpp"
#include <signal.h>
#include <string.h>
#include <algorithm>

static void callback(union sigval arg)
{
	DEBUG_PRINTF("%s\n", __func__);
    std::for_each(reinterpret_cast<EventTimer *>(arg.sival_ptr)->observerList.cbegin(), reinterpret_cast<EventTimer *>(arg.sival_ptr)->observerList.cend(), [](TimerObserver *x){
        x->notify_timer();
    });
}

EventTimer::EventTimer()
{

}

EventTimer::~EventTimer()
{

}

ReturnCode EventTimer::StartTimer()
{
    struct itimerspec itval;
    struct sigevent se;
	DEBUG_PRINTF("%s\n", __func__);

    itval.it_value.tv_sec = 0;
    itval.it_value.tv_nsec = eventPeriod * 1000000;
    itval.it_interval.tv_sec = 0;
    itval.it_interval.tv_nsec = eventPeriod * 1000000;

    memset(&se, 0, sizeof(se));
    se.sigev_value.sival_ptr = this;
    se.sigev_notify = SIGEV_THREAD;
    se.sigev_notify_function = callback;
    se.sigev_notify_attributes = NULL;

    timer_create(CLOCK_REALTIME, &se, &timerID);
    timer_settime(timerID, 0, &itval, NULL);

    return HAL_OK;
}

ReturnCode EventTimer::StopTimer()
{
	DEBUG_PRINTF("%s\n", __func__);
    if (timerID == nullptr)
        return HAL_ERROR;
    timer_delete(timerID);
    timerID = nullptr;
    return HAL_OK;
}

ReturnCode EventTimer::SetEventPeriod(int32_t value)
{
	DEBUG_PRINTF("%s\n", __func__);
    eventPeriod = value;
    return HAL_OK;
}

ReturnCode EventTimer::AddObserver(TimerObserver *timerObserver)
{
	DEBUG_PRINTF("%s\n", __func__);
    observerList.push_back(timerObserver);
    return HAL_OK;
}

ReturnCode EventTimer::RemoveObserver(TimerObserver *timerObserver)
{
	DEBUG_PRINTF("%s\n", __func__);
    observerList.remove(timerObserver);
    return HAL_OK;
}

