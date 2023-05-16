# openel-cpp
OpenEL implemented in C++

# OpenEL
OpenEL(Open Embedded Library) is a unified API(Application Programming Interface) for actuators and sensors. The specifications and implementation have been developed by JASA(Japan Embedded Systems Technology Association) since 2011.

## Specification
https://openel.github.io/

## About this document
This document explains about Package contents and How to use OpenEL version 3.2.x.

## Package contents

<pre>
openel-cpp -+- include
            +- lib
            +- sample
            +- LICENSE
            +- README.md (This file)

</pre>

<pre>
include             --- Header files for OpenEL
lib                 --- Library files for OpenEL
sample              --- A sample program which use OpenEL API
LICENSE             --- License file
README.md           --- This file
</pre>

## How to use OpenEL API

### Header file
When you compile a program which use OpenEL API, set PATH to openel-cpp/include/surface and openel-cpp/include/device/your_component
directory to use the header file(openEL.hpp etc.) for OpenEL.

For examples, when you use gcc
<pre>
  -Iopenel-cpp/include/surface
  -Iopenel-cpp/include/device/your_component
</pre>

Include the header file named "openEL.hpp" etc. to use OpenEL API

For examples,
<pre>
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
</pre>

### Library files
When you compile a program which use OpenEL API, set LIBRARY PATH to openel-cpp/lib/surface and openel-cpp/lib/device/your_component to link the library file for OpenEL.

For examples, when you use gcc
<pre>
-Lopenel-cpp/lib
-Lopenel-cpp/lib/device/your_component
</pre>>

Link the library file named "libopenel.a" to use OpenEL API.

For examples,
<pre>
　gcc -o sample sample.cpp -I/.../openel-cpp/include/surface -lopenel -lstdc++
</pre>

See sample/simLinux/Makefile for details.

## Sample program for Linux
<pre>
$ cd sample/simLinux
$ make
$ ./sample
openEL Start
HalInit ActuatorSim HAL-ID 1 0 0 1
HalInit ActuatorSim HAL-ID 1 0 0 2
HalInit SensorSim HAL-ID 2 0 0 1
PROPERTY - Name : SimLinuxActuator
PROPERTY - fnc00 : Init
PROPERTY - fnc01 : ReInit
PROPERTY - fnc02 : Finalize
PROPERTY - fnc03 : AddObserver
PROPERTY - fnc04 : RemoveObserver
PROPERTY - fnc05 : SetValue
PROPERTY - fnc06 : GetValue
PROPERTY - fnc07 : (null)
PROPERTY - fnc08 : (null)
PROPERTY - fnc09 : (null)
PROPERTY - fnc0A : (null)
PROPERTY - fnc0B : (null)
PROPERTY - fnc0C : (null)
PROPERTY - fnc0D : (null)
PROPERTY - fnc0E : (null)
PROPERTY - fnc0F : (null)
PROPERTY - fnc10 : (null)
PROPERTY - fnc11 : (null)
PROPERTY - fnc12 : (null)
PROPERTY - fnc13 : (null)
PROPERTY - fnc14 : (null)
PROPERTY - fnc15 : (null)
PROPERTY - fnc16 : (null)
PROPERTY - fnc17 : (null)
PROPERTY - Name : SimLinuxActuator
PROPERTY - fnc00 : Init
PROPERTY - fnc01 : ReInit
PROPERTY - fnc02 : Finalize
PROPERTY - fnc03 : AddObserver
PROPERTY - fnc04 : RemoveObserver
PROPERTY - fnc05 : SetValue
PROPERTY - fnc06 : GetValue
PROPERTY - fnc07 : (null)
PROPERTY - fnc08 : (null)
PROPERTY - fnc09 : (null)
PROPERTY - fnc0A : (null)
PROPERTY - fnc0B : (null)
PROPERTY - fnc0C : (null)
PROPERTY - fnc0D : (null)
PROPERTY - fnc0E : (null)
PROPERTY - fnc0F : (null)
PROPERTY - fnc10 : (null)
PROPERTY - fnc11 : (null)
PROPERTY - fnc12 : (null)
PROPERTY - fnc13 : (null)
PROPERTY - fnc14 : (null)
PROPERTY - fnc15 : (null)
PROPERTY - fnc16 : (null)
PROPERTY - fnc17 : (null)
PROPERTY - Name : SimLinuxSensor
PROPERTY - fnc00 : Init
PROPERTY - fnc01 : ReInit
PROPERTY - fnc02 : Finalize
PROPERTY - fnc03 : AddObserver
PROPERTY - fnc04 : RemoveObserver
PROPERTY - fnc05 : GetProperty
PROPERTY - fnc06 : GetTime
PROPERTY - fnc07 : GetValueList
PROPERTY - fnc08 : GetTimedValueList
PROPERTY - fnc09 : (null)
PROPERTY - fnc0A : (null)
PROPERTY - fnc0B : (null)
PROPERTY - fnc0C : (null)
PROPERTY - fnc0D : (null)
PROPERTY - fnc0E : (null)
PROPERTY - fnc0F : (null)
PROPERTY - fnc10 : (null)
PROPERTY - fnc11 : (null)
PROPERTY - fnc12 : (null)
PROPERTY - fnc13 : (null)
PROPERTY - fnc14 : (null)
PROPERTY - fnc15 : (null)
PROPERTY - fnc16 : (null)
PROPERTY - fnc17 : (null)
motor01  getTime ret=0
Motor time = 0
sensor01 getTime ret=0
Sensor time = 0
notify_event201a : 1234
notify_error201a : 5678
notify_event201b : 1234
notify_error201b : 5678
timer      4 ,    40 ,      2 :   0.314   2.487   1.234   0.174     1(tmSen)
timer     10 ,   100 ,      5 :   1.910   5.878   1.234   0.174     1(tmSen)
timer     15 ,   150 ,      7 :   4.122   8.090   1.234   0.342     2(tmSen)
timer     20 ,   200 ,     10 :   6.910   9.511   1.234   0.342     2(tmSen)
timer     25 ,   250 ,     12 :  10.000  10.000   1.234   0.500     3(tmSen)
timer     30 ,   300 ,     15 :  13.090   9.511   1.234   0.500     3(tmSen)
timer     35 ,   350 ,     17 :  15.878   8.090   1.234   0.643     4(tmSen)
timer     40 ,   400 ,     20 :  18.090   5.878   1.234   0.643     4(tmSen)
timer     45 ,   450 ,     22 :  19.511   3.090   1.234   0.766     5(tmSen)
timer     50 ,   500 ,     25 :  20.000   0.000   1.234   0.766     5(tmSen)
timer     55 ,   550 ,     27 :  19.511  -3.090   1.234   0.866     6(tmSen)
timer     60 ,   600 ,     30 :  18.090  -5.878   1.234   0.866     6(tmSen)
timer     65 ,   650 ,     32 :  15.878  -8.090   1.234   0.940     7(tmSen)
timer     70 ,   700 ,     35 :  13.090  -9.511   1.234   0.940     7(tmSen)
timer     75 ,   750 ,     37 :  10.000 -10.000   1.234   0.985     8(tmSen)
timer     80 ,   800 ,     40 :   6.910  -9.511   1.234   0.985     8(tmSen)
timer     85 ,   850 ,     42 :   4.122  -8.090   1.234   1.000     9(tmSen)
timer     90 ,   900 ,     45 :   1.910  -5.878   1.234   1.000     9(tmSen)
timer     95 ,   950 ,     47 :   0.489  -3.090   1.234   0.985    10(tmSen)
timer    100 ,  1000 ,     50 :   0.000  -0.000   1.234   0.985    10(tmSen)
timer    105 ,  1050 ,     52 :   0.000  -0.000   1.234   0.940    11(tmSen)
timer    110 ,  1100 ,     55 :   0.000  -0.000   1.234   0.940    11(tmSen)
timer    115 ,  1150 ,     57 :   0.000  -0.000   1.234   0.866    12(tmSen)
timer    120 ,  1200 ,     60 :   0.000  -0.000   1.234   0.866    12(tmSen)
timer    125 ,  1250 ,     62 :   0.000  -0.000   1.234   0.766    13(tmSen)
timer    130 ,  1300 ,     65 :   0.000  -0.000   1.234   0.766    13(tmSen)
timer    135 ,  1350 ,     67 :   0.000  -0.000   1.234   0.643    14(tmSen)
timer    140 ,  1400 ,     70 :   0.000  -0.000   1.234   0.643    14(tmSen)
timer    145 ,  1450 ,     72 :   0.000  -0.000   1.234   0.500    15(tmSen)
timer    150 ,  1500 ,     75 :   0.000   0.000   1.234   0.500    15(tmSen)
timer    155 ,  1550 ,     77 :   0.489   3.090   1.234   0.342    16(tmSen)
timer    160 ,  1600 ,     80 :   1.910   5.878   1.234   0.342    16(tmSen)
timer    165 ,  1650 ,     82 :   4.122   8.090   1.234   0.174    17(tmSen)
timer    170 ,  1700 ,     85 :   6.910   9.511   1.234   0.174    17(tmSen)
timer    175 ,  1750 ,     87 :  10.000  10.000   1.234   0.000    18(tmSen)
timer    180 ,  1800 ,     90 :  13.090   9.511   1.234   0.000    18(tmSen)
timer    185 ,  1850 ,     92 :  15.878   8.090   1.234  -0.174    19(tmSen)
timer    190 ,  1900 ,     95 :  18.090   5.878   1.234  -0.174    19(tmSen)
timer    195 ,  1950 ,     97 :  19.511   3.090   1.234  -0.342    20(tmSen)
timer    200 ,  2000 ,    100 :  20.000   0.000   1.234  -0.342    20(tmSen)
timer    205 ,  2050 ,    102 :  19.511  -3.090   1.234  -0.500    21(tmSen)
timer    210 ,  2100 ,    105 :  18.090  -5.878   1.234  -0.500    21(tmSen)
timer    215 ,  2150 ,    107 :  15.878  -8.090   1.234  -0.643    22(tmSen)
timer    220 ,  2200 ,    110 :  13.090  -9.511   1.234  -0.643    22(tmSen)
timer    225 ,  2250 ,    112 :  10.000 -10.000   1.234  -0.766    23(tmSen)
timer    230 ,  2300 ,    115 :   6.910  -9.511   1.234  -0.766    23(tmSen)
timer    235 ,  2350 ,    117 :   4.122  -8.090   1.234  -0.866    24(tmSen)
timer    240 ,  2400 ,    120 :   1.910  -5.878   1.234  -0.866    24(tmSen)
timer    245 ,  2450 ,    122 :   0.489  -3.090   1.234  -0.940    25(tmSen)
timer    250 ,  2500 ,    125 :   0.000  -0.000   1.234  -0.940    25(tmSen)
timer    255 ,  2550 ,    127 :   0.000  -0.000   1.234  -0.985    26(tmSen)
timer    260 ,  2600 ,    130 :   0.000  -0.000   1.234  -0.985    26(tmSen)
timer    265 ,  2650 ,    132 :   0.000  -0.000   1.234  -1.000    27(tmSen)
timer    270 ,  2700 ,    135 :   0.000  -0.000   1.234  -1.000    27(tmSen)
timer    275 ,  2750 ,    137 :   0.000  -0.000   1.234  -0.985    28(tmSen)
timer    280 ,  2800 ,    140 :   0.000  -0.000   1.234  -0.985    28(tmSen)
timer    285 ,  2850 ,    142 :   0.000  -0.000   1.234  -0.940    29(tmSen)
timer    290 ,  2900 ,    145 :   0.000  -0.000   1.234  -0.940    29(tmSen)
timer    295 ,  2950 ,    147 :   0.000  -0.000   1.234  -0.866    30(tmSen)
timer    300 ,  3000 ,    150 :   0.000   0.000   1.234  -0.866    30(tmSen)
Motor time = 31
Sensor time = 31
openEL End
</pre>
