/*
 ============================================================================
 Name        : projSimLinux.cpp
 Author      : OpenEL-WG
 Version     : 3.2
 Copyright   : Japan Embedded Systems Technology Association(JASA)
 Description : OpenEL Sample program
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "openEL.hpp"
#include "Actuator.hpp"
#include "Sensor.hpp"
#include "HAL4RT.hpp"
#include "HALId.hpp"
#include "ReturnCode.hpp"
#include "HALComponent.hpp"
#include "HALObserver.hpp"
#include "EventTimer.hpp"
#include "TimerObserver.hpp"
#include "Property.hpp"

Actuator *halMotor01;
Actuator *halMotor02;
Sensor *halSensor01;

void cbNotifyTimer101();
void cbNotifyTimer102();
void cbNotifyTimer201();

int32_t event_count1,event_count2,event_count3;
HALFLOAT_T simVal1,simVal2,simVal3,simVal4;
int32_t tmSensor;

static void notify_event201a(int32_t eventID) {
	printf("notify_event201a : %d\n",eventID);
}
static void notify_error201a(int32_t errorID) {
	printf("notify_error201a : %d\n",errorID);
}
static void notify_event201b(int32_t eventID) {
	printf("notify_event201b : %d\n",eventID);
}
static void notify_error201b(int32_t errorID) {
	printf("notify_error201b : %d\n",errorID);
	halSensor01->ReInit();
}

void outProperty(HALComponent *hC);

int main(void) {
	int32_t timeWk;
	uint8_t flgObs;

	printf("openEL Start\n");

	HALId motor01;
	HALId motor02;
	HALId sensor01;
	TimerObserver tmObs101;
	TimerObserver tmObs102;
	TimerObserver tmObs201;
	EventTimer halEvtTm100;
	EventTimer halEvtTm200;
	HALObserver halObs201a;
	HALObserver halObs201b;

	motor01.deviceKindId=0x00000001;
	motor01.vendorId=0x00000000;
	motor01.productId=0x00000000;
	motor01.instanceId=0x00000001;

	motor02.deviceKindId=0x00000001;
	motor02.vendorId=0x00000000;
	motor02.productId=0x00000000;
	motor02.instanceId=0x00000002;

	sensor01.deviceKindId=0x00000002;
	sensor01.vendorId=0x00000000;
	sensor01.productId=0x00000000;
	sensor01.instanceId=0x00000001;

	halMotor01  = new Actuator(motor01);
	halMotor02  = new Actuator(motor02);
	halSensor01  = new Sensor(sensor01);

	if (halMotor01->Init() == HAL_ERROR) {
		printf("Init() Error\n");
		if (halMotor01->ReInit() == HAL_ERROR) {
			printf("ReInit() Error\n");
			exit(0);
		};
	};

	if (halMotor02->Init() == HAL_ERROR) {
		printf("Init() Error\n");
		if (halMotor02->ReInit() == HAL_ERROR) {
			printf("ReInit() Error\n");
			exit(0);
		};
	};

	if (halSensor01->Init() == HAL_ERROR) {
		printf("Init() Error\n");
		if (halSensor01->ReInit() == HAL_ERROR) {
			printf("ReInit() Error\n");
			exit(0);
		};
	};

	outProperty(halMotor01);
	outProperty(halMotor02);
	outProperty(halSensor01);

	tmObs101.notify_timer = &cbNotifyTimer101;
	tmObs102.notify_timer = &cbNotifyTimer102;
	tmObs201.notify_timer = &cbNotifyTimer201;

	halObs201a.notify_event = &notify_event201a;
	halObs201a.notify_error = &notify_error201a;
	halObs201b.notify_event = &notify_event201b;
	halObs201b.notify_error = &notify_error201b;

	printf("motor01  getTime ret=%d\n", halMotor01->GetTime(&timeWk) );
	printf("Motor time = %d\n",timeWk);
	printf("sensor01 getTime ret=%d\n", halSensor01->GetTime(&timeWk) );
	printf("Sensor time = %d\n",timeWk);

	halMotor01->AddObserver(&halObs201a);
	halMotor02->AddObserver(&halObs201b);
	flgObs = 1;

	halEvtTm100.SetEventPeriod(100);
	halEvtTm100.AddObserver(&tmObs101);
	halEvtTm100.AddObserver(&tmObs102);
	halEvtTm100.StartTimer();

	halEvtTm200.SetEventPeriod(200);
	halEvtTm200.AddObserver(&tmObs201);
	halEvtTm200.StartTimer();
	// ループ
	while(1) {
		usleep(500000); /* 0.5s */
		printf("timer %6d , %5d , %6d : ",event_count1,event_count2,event_count3);
		printf("%7.3lf %7.3lf %7.3lf %7.3lf %5d(tmSen)\n",simVal1,simVal2,simVal3,simVal4,tmSensor);
		fflush(stdout);
		if ( (150 <= event_count1) && (1==flgObs) ) {
			halMotor01->RemoveObserver(&halObs201a);
			halMotor02->RemoveObserver(&halObs201b);
			flgObs = 0;
		}
		if( 300 <= event_count1 ) break;
	}
	halMotor01->GetTime(&timeWk);
	printf("Motor time = %d\n",timeWk);
	halSensor01->GetTime(&timeWk);
	printf("Sensor time = %d\n",timeWk);

	halEvtTm100.StopTimer();
	halEvtTm100.RemoveObserver(&tmObs101);
	halEvtTm100.RemoveObserver(&tmObs102);

	halEvtTm200.StopTimer();
	halEvtTm200.RemoveObserver(&tmObs201);

	halMotor01->Finalize();
	halMotor02->Finalize();
	halSensor01->Finalize();

	printf("openEL End\n");
	return EXIT_SUCCESS;
}

void cbNotifyTimer101() {
	DEBUG_PRINTF("%s\n", __func__);
	HALFLOAT_T posX,posY;
	double ph;
	int32_t idxPh;
	Request request;
	request = Request::HAL_REQUEST_POSITION_CONTROL;

	event_count1++;
	idxPh = event_count1 % 150;
	if ( idxPh <= 100 ) {
		ph = ((double)idxPh * 2.0 *M_PI)/100.0;
	} else {
		ph = ((double)100 * 2.0 *M_PI)/100.0;
	}
	posX = 10.0*(1.0-cos(ph));
	posY = 10.0*(sin(ph));
	halMotor01->SetValue(request,posX);
	halMotor02->SetValue(request,posY);
}

void cbNotifyTimer102() {
	DEBUG_PRINTF("%s\n", __func__);
	event_count2 += 10;
	Request request;
	request = Request::HAL_REQUEST_POSITION_CONTROL;
	halMotor01->GetValue(request,&simVal1);
	halMotor02->GetValue(request,&simVal2);
}

void cbNotifyTimer201() {
	DEBUG_PRINTF("%s\n", __func__);
	int size;
	event_count3 += 1;
	halSensor01->GetValueList(&simVal3, &size) ;
	halSensor01->GetTimedValueList(&simVal4,&tmSensor,&size);
}

void outProperty(HALComponent *hC) {
	DEBUG_PRINTF("%s\n", __func__);
	int32_t i;
	Property propertyWk , *property;

	property = &propertyWk;
	hC->GetProperty(&propertyWk);
	printf("PROPERTY - Name : %s\n",property->deviceName.c_str());
	for ( i=0; i<sizeof(property->functionList); i++ ) {
		printf("PROPERTY - fnc%02X : %s\n",i,property->functionList[i].c_str());
	}
}
