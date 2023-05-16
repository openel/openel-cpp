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

#include "openEL_SensorSim.hpp"
#include <chrono>
#include <ctime>
#include <cmath>

std::string SensorSim::strDevName = "SimLinuxSensor";

std::vector<std::string> SensorSim::strFncLst =
{
    "Init",
    "ReInit",
    "Finalize",
    "AddObserver",
    "RemoveObserver",
    "GetProperty",
    "GetTime",
    "GetValueList",
    "GetTimedValueList"
};

static int32_t timeOrg;
Property SensorSim::SensorSim_property;

ReturnCode SensorSim::fncInit(HALComponent *pHALComponent)
{
    auto tp = std::chrono::system_clock::now();
    std::time_t timeWk = std::chrono::system_clock::to_time_t(tp);
	timeOrg = (int32_t)timeWk;
    pHALComponent->time = timeOrg;

	printf("HalInit SensorSim HAL-ID %d %d %d %d\n",
			pHALComponent->hALId.deviceKindId,
			pHALComponent->hALId.vendorId,
			pHALComponent->hALId.productId,
			pHALComponent->hALId.instanceId );

    return HAL_OK;
}

ReturnCode SensorSim::fncReInit(HALComponent *pHALComponent)
{
    return HAL_OK;
}


ReturnCode SensorSim::fncFinalize(HALComponent *pHALComponent)
{
    return HAL_OK;
}

ReturnCode SensorSim::fncAddObserver(HALComponent *pHALComponent, HALObserver **halObserver)
{
    return HAL_OK;
}

ReturnCode SensorSim::fncRemoveObserver(HALComponent *pHALComponent, HALObserver **halObserver)
{
    return HAL_OK;
}

ReturnCode SensorSim::fncGetProperty(HALComponent *pHALComponent, Property **property)
{
    SensorSim_property.deviceName = strDevName;
    SensorSim_property.functionList = strFncLst;
    (**property).functionList.resize(strFncLst.size());
    **property = SensorSim_property;

    return HAL_OK;
}

ReturnCode SensorSim::fncGetTime(HALComponent *pHALComponent, int32_t **timeValue)
{
    auto tp = std::chrono::system_clock::now();
    std::time_t timeWk = std::chrono::system_clock::to_time_t(tp);
    pHALComponent->time = (int32_t)timeWk;
	**timeValue = pHALComponent->time - timeOrg;
    return HAL_OK;
}

ReturnCode SensorSim::fncGetValLst(HALComponent *pHALComponent, HALFLOAT_T **valueList, int **num)
{
    **num = 1;
    **valueList = 1.234;

    return HAL_OK;
}

ReturnCode SensorSim::fncGetTimedValLst(HALComponent *pHALComponent, HALFLOAT_T **valueList, int32_t **timeValue, int32_t **num)
{
    auto tp = std::chrono::system_clock::now();
    std::time_t timeWk = std::chrono::system_clock::to_time_t(tp);
    pHALComponent->time = (int32_t)timeWk;
	**timeValue = pHALComponent->time - timeOrg;
    **num = 1;
    **valueList = std::sin((HALFLOAT_T)**timeValue*10/180*M_PI);

    return HAL_OK;
}

ReturnCode SensorSim::fncSetValue(HALComponent *pHALComponent, Request request, float value)
{
    return HAL_ERROR;
}

ReturnCode SensorSim::fncGetValue(HALComponent *pHALComponent, Request request, float **value)
{
    return HAL_ERROR;
}

ReturnCode SensorSim::fncNop(HALComponent *pHALComponent, HAL_ARGUMENT_T *pCmd)
{
    return HAL_ERROR;
}

ReturnCode SensorSim::fncDeviceVendorSpec(HALComponent *pHALComponent, HAL_ARGUMENT_T *pCmd, HAL_ARGUMENT_DEVICE_T *pCmdDev)
{
    return HAL_ERROR;
}

HAL_FNCTBL_T HalSensorSimTbl =
{
    SensorSim::fncInit,			    /* 0x00 */
    SensorSim::fncReInit,			/* 0x01 */
    SensorSim::fncFinalize,		    /* 0x02 */
    SensorSim::fncAddObserver,		/* 0x03 */
    SensorSim::fncRemoveObserver,	/* 0x04 */
    SensorSim::fncGetProperty,		/* 0x05 */
    SensorSim::fncGetTime,	    	/* 0x06 */
    SensorSim::fncNop,			    /* 0x07 */
    SensorSim::fncNop,			    /* 0x08 */
    SensorSim::fncNop,			    /* 0x09 */
    SensorSim::fncNop,			    /* 0x0A */
    SensorSim::fncNop,			    /* 0x0B */
    SensorSim::fncNop,			    /* 0x0C */
    SensorSim::fncNop,			    /* 0x0D */
    SensorSim::fncNop,			    /* 0x0E */
    SensorSim::fncNop,			    /* 0x0F */
    SensorSim::fncNop,			    /* 0x10 */
    SensorSim::fncNop,  			/* 0x11 */
    SensorSim::fncNop,	    		/* 0x12 */
    SensorSim::fncNop,		    	/* 0x13 */
    SensorSim::fncNop,  			/* 0x14 */
    SensorSim::fncNop,	    		/* 0x15 */
    SensorSim::fncNop,		    	/* 0x16 */
    SensorSim::fncNop,			    /* 0x17 */
    SensorSim::fncSetValue,	    	/* 0x18 */
    SensorSim::fncGetValue,		    /* 0x19 */
    SensorSim::fncGetValLst,		/* 0x1A */
    SensorSim::fncGetTimedValLst,	/* 0x1B */
    SensorSim::fncDeviceVendorSpec,	/* 0x1C */
    SensorSim::fncDeviceVendorSpec,	/* 0x1D */
    SensorSim::fncDeviceVendorSpec,	/* 0x1E */
    SensorSim::fncDeviceVendorSpec,	/* 0x1F */
};
