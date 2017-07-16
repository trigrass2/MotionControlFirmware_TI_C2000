/******************************************************************************
 * Copyright (C) 2017 by Yifan Jiang                                          *
 * jiangyi@student.ethz.com                                                   *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 ******************************************************************************/

/*
* implement power stage control functions
*/


#include "PowerStageControl.h"
#include "Drivers/GpioDriver/GpioDriver.h"
#include "F2837xD_epwm.h"

/**
 *  enable current, voltage, and temperature sampling
 */
void SensorEnable(void){
  // enable EPWM1 triggering ADC
  EPwm1Regs.ETSEL.bit.SOCAEN = 1;
}

/**
  * enable PWM timers
  */
void PwmTimerEnable(void){

  EPwm1Regs.TBCTL.bit.CTRMODE = 0; //unfreeze, and enter up count mode
  EPwm4Regs.TBCTL.bit.CTRMODE = 2;  //unfreeze, and enter up-down mode
  EPwm5Regs.TBCTL.bit.CTRMODE = 2;
  EPwm6Regs.TBCTL.bit.CTRMODE = 2;

  // synchronize PWM timer counters
  EPwm1Regs.TBCTL.bit.SWFSYNC = 1;
}

/**
  * enable power stage output
  */
void PwrEnable(void){
  // enable PWM output by clearing PWM trip
  EPwm4Regs.TZCLR.bit.OST = 1;
  EPwm5Regs.TZCLR.bit.OST = 1;
  EPwm6Regs.TZCLR.bit.OST = 1;

  // set DRV8301 gate enable
  SetDrv8301GateEnable();
}

/**
  * disable power stage output
  */
void PwrDisable(void){
  // Clear DRV8301 gate enable
  ClearDrv8301GateEnable();

  // force PWM trip
  EPwm4Regs.TZFRC.bit.OST = 1;
  EPwm5Regs.TZFRC.bit.OST = 1;
  EPwm6Regs.TZFRC.bit.OST = 1;

  EPwm4Regs.CMPA.bit.CMPA = 0;
  EPwm5Regs.CMPA.bit.CMPA = 0;
  EPwm6Regs.CMPA.bit.CMPA = 0;
}

/**
  * apply PWM duty
  * @param duty    PWM Compare Match values
  *                should be between PWM_MAX_DUTY and PWM_MIN_DUTY
  */
#pragma CODE_SECTION(PwrSetPwmDuty, ".TI.ramfunc");
void PwrSetPwmDuty(PwmDutyVec * duty){

  EPwm4Regs.CMPA.bit.CMPA = duty->A;
  EPwm5Regs.CMPA.bit.CMPA = duty->B;
  EPwm6Regs.CMPA.bit.CMPA = duty->C;
}
