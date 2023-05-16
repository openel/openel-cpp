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

#include "openEL.hpp"
#include "HALComponent.hpp"

HAL_HANDLER_T HalHandlerTbl[HAL_SZ_HANDLER_TBL];
static int32_t HalIdxHandlerTbl;

HALComponent* HalCreate(int32_t deviceKindID, int32_t vendorID, int32_t productID, int32_t instanceID)
{
    int32_t i;
    int32_t idx = -1;
    HAL_HANDLER_T *pHandler;
    HALComponent *pHalComponent;
    const HAL_REG_T *pReg;

    for (i = 0; i < HAL_SZ_HANDLER_TBL; i++)
    {
	HalIdxHandlerTbl = (HalIdxHandlerTbl + 1) & HAL_MSK_HANDLER_TBL;
	if (0 == HalHandlerTbl[HalIdxHandlerTbl].swUsed )
	{
	    idx = HalIdxHandlerTbl;
	    break;
	}
    }
    if (-1 == idx) return 0;
    pHandler = &HalHandlerTbl[HalIdxHandlerTbl];

    idx = -1;
    for (i = 0; i < hal_szRegTbl; i++)
    {
	if ((deviceKindID == HalRegTbl[i].deviceKindID) && (vendorID == HalRegTbl[i].vendorID) && (productID == HalRegTbl[i].productID))
	{
	    idx = i;
	    break;
	}
    }
    if (-1 == idx) return 0;
    pReg = &HalRegTbl[idx];

    pHalComponent = new HALComponent();
    pHalComponent->handle = HalIdxHandlerTbl;
    pHalComponent->hALId.deviceKindId = deviceKindID;
    pHalComponent->hALId.vendorId = vendorID;
    pHalComponent->hALId.productId = productID;
    pHalComponent->hALId.instanceId = instanceID;

    pHandler->swUsed = 1;
    pHandler->pHalComponent = pHalComponent;
    pHandler->pFncTbl = pReg->pFncTbl;

    return pHalComponent;
}

void HalDestroy(HALComponent *halComponent)
{
    HAL_HANDLER_T *pHandler;

    pHandler = &HalHandlerTbl[halComponent->handle];
    pHandler->swUsed = 0;
    delete halComponent;
}
