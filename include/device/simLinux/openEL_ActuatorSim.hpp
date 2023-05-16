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

#ifndef OPENEL_ACTUATOR_SIM_HPP
#define OPENEL_ACTUATOR_SIM_HPP

#include "Actuator.hpp"

#define MAX_AXIS	2

enum Instance {
    MOTOR_LEFT = 1,
    MOTOR_RIGHT,
    InstanceNum
};

class ActuatorSim : public Actuator
{
private:
    static std::string strDevName;
    static std::vector<std::string> strFncLst;
    static HALFLOAT_T valueList[16];
    static HALFLOAT_T posSenAr[MAX_AXIS];
    static HALFLOAT_T posCmdAr[MAX_AXIS];

public:
    static Property ActuatorSim_property;

    static ReturnCode fncInit(HALComponent *pHALComponent);
    static ReturnCode fncReInit(HALComponent *pHALComponent);
    static ReturnCode fncFinalize(HALComponent *pHALComponent);
    static ReturnCode fncAddObserver(HALComponent *pHALComponent, HALObserver **halObserver);
    static ReturnCode fncRemoveObserver(HALComponent *pHALComponent, HALObserver **halObserver);
    static ReturnCode fncGetProperty(HALComponent *pHALComponent, Property **property);
    static ReturnCode fncGetTime(HALComponent *pHALComponent, int32_t **timeValue);
    static ReturnCode fncGetValLst(HALComponent *pHALComponent, float **valueList, int32_t **num);
    static ReturnCode fncGetTimedValLst(HALComponent *pHALComponent, float **valueList, int32_t **time, int32_t **num);
    static ReturnCode fncSetValue(HALComponent *pHALComponent, Request request, float value);
    static ReturnCode fncGetValue(HALComponent *pHALComponent, Request request, float **value);
    static ReturnCode fncNop(HALComponent *pHALComponent, HAL_ARGUMENT_T *pCmd);
    static ReturnCode fncDeviceVendorSpec(HALComponent* pHALComponent, HAL_ARGUMENT_T *pCmd, HAL_ARGUMENT_DEVICE_T *pCmdDev);
};

extern HAL_FNCTBL_T HalActuatorSimTbl;

#endif // OPENEL_ACTUATOR_SIM_HPP
