/*
  -------------------------------------------------------------
  Hello Robot - Hello Stepper

  This code is derived from the Mechaduino project. 
  https://github.com/jcchurch13/Mechaduino-Firmware

  All materials released under the GNU General Public License v3.0 (GNU GPLv3).
  https://www.gnu.org/licenses/gpl-3.0.html

  Copyright (c) 2020 by Hello Robot Inc.
  --------------------------------------------------------------
*/

#ifndef __HELLO_SYNC_MANAGER_H__
#define  __HELLO_SYNC_MANAGER_H__

#include "Common.h"


class SyncManager{
   public: 
    SyncManager();
    
    volatile bool runstop_active;
    volatile bool motor_sync_triggered;
    void setupSyncManager();
    void step();
    bool sync_mode_enabled;
    int last_pulse_duration;
  private:
    int pulse_count;
    uint8_t rs_last;
    uint8_t in_pulse;
};

extern SyncManager sync_manager;
#endif
