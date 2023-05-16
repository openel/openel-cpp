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

#ifndef OPENEL_HPP
#define OPENEL_HPP

#include "HAL4RT.hpp"
#include "HALId.hpp"
#include "ReturnCode.hpp"
#include "HALComponent.hpp"
#include "HALObserver.hpp"
#include "EventTimer.hpp"
#include "TimerObserver.hpp"
#include "Property.hpp"

#ifdef DEBUG_BUILD
# define DEBUG_PRINTF(fmt, ...)  printf(fmt, ## __VA_ARGS__);                   
#else
# define DEBUG_PRINTF(fmt, ...)
#endif

typedef union halArgument_ut
{
    int64_t numI64;
    int32_t num;
    struct { HALFLOAT_T value; int32_t _dummy; int32_t num; } FI;
} HAL_ARGUMENT_T;

typedef union halArgumentDevice_ut HAL_ARGUMENT_DEVICE_T;

typedef struct HalFncTbl_st HAL_FNCTBL_T;

class HALComponent;
class HALObserver;

typedef struct HalHandler_st
{
    uint32_t swUsed;
    HALComponent *pHalComponent;
    HAL_FNCTBL_T *pFncTbl;
} HAL_HANDLER_T;

#define HAL_SZ_HANDLER_TBL  (256)
#define HAL_MSK_HANDLER_TBL (HAL_SZ_HANDLER_TBL - 1)

extern HAL_HANDLER_T HalHandlerTbl[HAL_SZ_HANDLER_TBL];

typedef struct HalReg_st
{
    int32_t deviceKindID;
    int32_t vendorID;
    int32_t productID;
    HAL_FNCTBL_T *pFncTbl;
    int32_t szHalComponent;
} HAL_REG_T;

extern const HAL_REG_T HalRegTbl[];
extern const int32_t hal_szRegTbl;

enum class Request
{
    HAL_REQUEST_NO_EXCITE = 0,
    HAL_REQUEST_POSITION_CONTROL,
    HAL_REQUEST_VELOCITY_CONTROL,
    HAL_REQUEST_TORQUE_CONTROL,
    HAL_REQUEST_RESERVED
};

typedef struct HalFncTbl_st
{
    /* 0x00 */ ReturnCode (*pFncInit)(HALComponent*); /**< Initialize */   \
    /* 0x01 */ ReturnCode (*pFncReInit)(HALComponent*); /**< ReInit */	  \
    /* 0x02 */ ReturnCode (*pFncFinalize)(HALComponent*); /**< Finalize */		\
    /* 0x03 */ ReturnCode (*pFncAddObserver)(HALComponent*, HALObserver **halObserver); /**< AddObserver */ \
    /* 0x04 */ ReturnCode (*pFncRemoveObserver)(HALComponent*, HALObserver **halObserver); /**< RemoveObserver */ \
    /* 0x05 */ ReturnCode (*pFncGetProperty)(HALComponent*, Property **property); /**< GetProperty */ \
    /* 0x06 */ ReturnCode (*pFncGetTime)(HALComponent*, int32_t **); /**< GetTime */ \
    /* 0x07 */ ReturnCode (*pFncDummy07)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */

    /* 0x08 */ ReturnCode (*pFncDummy08)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */
    /* 0x09 */ ReturnCode (*pFncDummy09)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */
    /* 0x0A */ ReturnCode (*pFncDummy0A)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */
    /* 0x0B */ ReturnCode (*pFncDummy0B)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */
    /* 0x0C */ ReturnCode (*pFncDummy0C)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */
    /* 0x0D */ ReturnCode (*pFncDummy0D)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */
    /* 0x0E */ ReturnCode (*pFncDummy0E)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */
    /* 0x0F */ ReturnCode (*pFncDummy0F)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */

    /* 0x10 */ ReturnCode (*pFncDummy10)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */
    /* 0x11 */ ReturnCode (*pFncDummy11)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */
    /* 0x12 */ ReturnCode (*pFncDummy12)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */
    /* 0x13 */ ReturnCode (*pFncDummy13)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */
    /* 0x14 */ ReturnCode (*pFncDummy14)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */
    /* 0x15 */ ReturnCode (*pFncDummy15)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */
    /* 0x16 */ ReturnCode (*pFncDummy16)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */
    /* 0x17 */ ReturnCode (*pFncDummy17)(HALComponent*, HAL_ARGUMENT_T*); /**< Reserved */

    /* 0x18 */ ReturnCode (*pFncSetValue)(HALComponent *, Request, float);    /**< SetValue */
    /* 0x19 */ ReturnCode (*pFncGetValue)(HALComponent *, Request, float **); /**< GetValue */
    /* 0x1A */ ReturnCode (*pFncGetValueList)(HALComponent*, HALFLOAT_T **, int32_t **); /**< GetValueList */
    /* 0x1B */ ReturnCode (*pFncGetTimedValueList)(HALComponent*, HALFLOAT_T **, int32_t **, int32_t **); /**< GetTimedValueList */
    /* 0x1C */ ReturnCode (*pFncDeviceVendor1C)(HALComponent*, HAL_ARGUMENT_T*,HAL_ARGUMENT_DEVICE_T *); /**< Device Vendor Function */
    /* 0x1D */ ReturnCode (*pFncDeviceVendor1D)(HALComponent*, HAL_ARGUMENT_T*,HAL_ARGUMENT_DEVICE_T *); /**< Device Vendor Function */
    /* 0x1E */ ReturnCode (*pFncDeviceVendor1E)(HALComponent*, HAL_ARGUMENT_T*,HAL_ARGUMENT_DEVICE_T *); /**< Device Vendor Function */
    /* 0x1F */ ReturnCode (*pFncDeviceVendor1F)(HALComponent*, HAL_ARGUMENT_T*,HAL_ARGUMENT_DEVICE_T *); /**< Device Vendor Function */
} HAL_FNCTBL_T;

HALComponent* HalCreate(int32_t deviceKindID, int32_t vendorID, int32_t productID, int32_t instanceID);
void HalDestroy(HALComponent *halComponent);

ReturnCode HalInit(HALComponent *halComponent);
ReturnCode HalReInit(HALComponent *halComponent);
ReturnCode HalFinalize(HALComponent *halComponent);
ReturnCode HalAddObserver(HALComponent *halComponent, HALObserver *halObserver);
ReturnCode HalRemoveObserver(HALComponent *halComponent, HALObserver *halObserver);
ReturnCode HalGetProperty(HALComponent *halComponent, Property *property);
ReturnCode HalGetTime(HALComponent *halComponent, int32_t *timeValue);

#endif // OPENEL_HPP
