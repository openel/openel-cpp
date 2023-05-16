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

#include "openEL_ActuatorSim.hpp"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <ctime>

std::string ActuatorSim::strDevName = "SimLinuxActuator";

std::vector<std::string> ActuatorSim::strFncLst =
{
    "Init",
    "ReInit",
    "Finalize",
    "AddObserver",
    "RemoveObserver",
    "SetValue",
    "GetValue"
};

static int32_t timeOrg;
Property ActuatorSim::ActuatorSim_property;
HALFLOAT_T ActuatorSim::posSenAr[MAX_AXIS];
HALFLOAT_T ActuatorSim::posCmdAr[MAX_AXIS];

ReturnCode ActuatorSim::fncInit(HALComponent *pHALComponent)
{
    auto tp = std::chrono::system_clock::now();
    std::time_t timeWk = std::chrono::system_clock::to_time_t(tp);
	timeOrg = (int32_t)timeWk;
    pHALComponent->time = timeOrg;

	printf("HalInit ActuatorSim HAL-ID %d %d %d %d\n",
			pHALComponent->hALId.deviceKindId,
			pHALComponent->hALId.vendorId,
			pHALComponent->hALId.productId,
			pHALComponent->hALId.instanceId );
    return HAL_OK;
}

ReturnCode ActuatorSim::fncReInit(HALComponent *pHALComponent)
{
    return HAL_OK;
}

ReturnCode ActuatorSim::fncFinalize(HALComponent *pHALComponent)
{
    return HAL_OK;
}

ReturnCode ActuatorSim::fncAddObserver(HALComponent *pHALComponent, HALObserver **halObserver)
{
    pHALComponent->observerList.push_back(**halObserver);

    // Test call to see if added.
    for (std::vector<HALObserver>::iterator it = pHALComponent->observerList.begin(); it != pHALComponent->observerList.end(); ++it) {
		it->notify_event(1234);
		it->notify_error(5678);
	}
    return HAL_OK;
}

ReturnCode ActuatorSim::fncRemoveObserver(HALComponent *pHALComponent, HALObserver **halObserver)
{
    for (auto it = pHALComponent->observerList.begin(); it != pHALComponent->observerList.end();) {
        if (*it->notify_event == *(*halObserver)->notify_event && *it->notify_error == *(*halObserver)->notify_error) {
            it = pHALComponent->observerList.erase(it);
        }
        else {
            ++it;
        }
    }

    // Test call to see if removed.
    for (std::vector<HALObserver>::iterator it = pHALComponent->observerList.begin(); it != pHALComponent->observerList.end(); ++it) {
		it->notify_event(1234);
		it->notify_error(5678);
	}

    return HAL_OK;
}

ReturnCode ActuatorSim::fncGetProperty(HALComponent *pHALComponent, Property **property)
{
    ActuatorSim_property.deviceName = strDevName;
    ActuatorSim_property.functionList = strFncLst;
    (**property).functionList.resize(strFncLst.size());
    **property = ActuatorSim_property;

    return HAL_OK;
}

ReturnCode ActuatorSim::fncGetTime(HALComponent *pHALComponent, int32_t **timeValue)
{
    auto tp = std::chrono::system_clock::now();
    std::time_t timeWk = std::chrono::system_clock::to_time_t(tp);
    pHALComponent->time = (int32_t)timeWk;
	**timeValue = pHALComponent->time - timeOrg;
    return HAL_OK;
}

ReturnCode ActuatorSim::fncGetValLst(HALComponent *pHALComponent, float **valueList, int32_t **num)
{
    return HAL_ERROR;
}

ReturnCode ActuatorSim::fncGetTimedValLst(HALComponent *pHALComponent, float **valueList, int32_t **timeValue, int32_t **num)
{
    return HAL_ERROR;
}

ReturnCode ActuatorSim::fncSetValue(HALComponent *pHALComponent, Request request, float value)
{
    ReturnCode retCode = HAL_ERROR;
	int32_t idx = pHALComponent->hALId.instanceId;

    if (idx >= InstanceNum)
    {
        return HAL_ERROR;
    }

    switch (request)
    {
    case Request::HAL_REQUEST_POSITION_CONTROL:
		posSenAr[idx] = posCmdAr[idx];
		posCmdAr[idx] = value;
		retCode = HAL_OK;
        break;
    case Request::HAL_REQUEST_VELOCITY_CONTROL:
		posSenAr[idx] = posCmdAr[idx];
		posCmdAr[idx] = value;
		retCode = HAL_OK;
        break;
    case Request::HAL_REQUEST_TORQUE_CONTROL:
		posSenAr[idx] = posCmdAr[idx];
		posCmdAr[idx] = value;
		retCode = HAL_OK;
        break;
    default:
        break;
    }

    return retCode;
}

ReturnCode ActuatorSim::fncGetValue(HALComponent *pHALComponent, Request request, float **value)
{
    ReturnCode retCode = HAL_ERROR;
	int32_t idx = pHALComponent->hALId.instanceId;

    if (idx >= InstanceNum)
    {
        return HAL_ERROR;
    }

    switch (request)
    {
    case Request::HAL_REQUEST_POSITION_CONTROL:
        **value = posCmdAr[idx];
        break;
    case Request::HAL_REQUEST_VELOCITY_CONTROL:
        **value = posCmdAr[idx];
        break;
    case Request::HAL_REQUEST_TORQUE_CONTROL:
        **value = posCmdAr[idx];
        break;
    default:
        retCode = HAL_ERROR;
        break;
    }

    return retCode;
}

ReturnCode ActuatorSim::fncNop(HALComponent *pHALComponent, HAL_ARGUMENT_T *pCmd)
{
    return HAL_ERROR;
}

ReturnCode ActuatorSim::fncDeviceVendorSpec(HALComponent *pHALComponent, HAL_ARGUMENT_T *pCmd, HAL_ARGUMENT_DEVICE_T *pCmdDev)
{
    return HAL_ERROR;
}

HAL_FNCTBL_T HalActuatorSimTbl =
{
    ActuatorSim::fncInit,			    /* 0x00 */
    ActuatorSim::fncReInit,			    /* 0x01 */
    ActuatorSim::fncFinalize,		    /* 0x02 */
    ActuatorSim::fncAddObserver,	    /* 0x03 */
    ActuatorSim::fncRemoveObserver,	    /* 0x04 */
    ActuatorSim::fncGetProperty,	    /* 0x05 */
    ActuatorSim::fncGetTime,		    /* 0x06 */
    ActuatorSim::fncNop,			    /* 0x07 */
    ActuatorSim::fncNop,			    /* 0x08 */
    ActuatorSim::fncNop,			    /* 0x09 */
    ActuatorSim::fncNop,			    /* 0x0A */
    ActuatorSim::fncNop,			    /* 0x0B */
    ActuatorSim::fncNop,			    /* 0x0C */
    ActuatorSim::fncNop,			    /* 0x0D */
    ActuatorSim::fncNop,			    /* 0x0E */
    ActuatorSim::fncNop,			    /* 0x0F */
    ActuatorSim::fncNop,			    /* 0x10 */
    ActuatorSim::fncNop,			    /* 0x11 */
    ActuatorSim::fncNop,			    /* 0x12 */
    ActuatorSim::fncNop,			    /* 0x13 */
    ActuatorSim::fncNop,			    /* 0x14 */
    ActuatorSim::fncNop,			    /* 0x15 */
    ActuatorSim::fncNop,			    /* 0x16 */
    ActuatorSim::fncNop,			    /* 0x17 */
    ActuatorSim::fncSetValue,		    /* 0x18 */
    ActuatorSim::fncGetValue,		    /* 0x19 */
    ActuatorSim::fncGetValLst,	        /* 0x1A */
    ActuatorSim::fncGetTimedValLst,	    /* 0x1B */
    ActuatorSim::fncDeviceVendorSpec,	/* 0x1C */
    ActuatorSim::fncDeviceVendorSpec,	/* 0x1D */
    ActuatorSim::fncDeviceVendorSpec,	/* 0x1E */
    ActuatorSim::fncDeviceVendorSpec,	/* 0x1F */
};
