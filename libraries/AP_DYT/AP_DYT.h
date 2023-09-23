/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <AP_HAL/AP_HAL.h>
#include <AP_AHRS/AP_AHRS.h>
#include <AP_SerialManager/AP_SerialManager.h>

class AP_DYT {
public:
    AP_DYT();

    AP_DYT(const AP_DYT &other) = delete;
    AP_DYT &operator=(const AP_DYT&) = delete;

    void init(const AP_SerialManager& serial_manager);

    bool update(void);

    int16_t DYT_track_x;   //目标脱靶量x轴偏移角度
    int16_t DYT_track_y;   //目标脱靶量y轴偏移角度

    uint32_t last_frame_ms;

private:
    AP_HAL::UARTDriver *_port;              // UART used to send data to receiver

    uint8_t _step;

    uint8_t _DYT_track_x_temp_low;      
    uint8_t _DYT_track_x_temp_high;      

    uint8_t _DYT_track_y_temp_low;         
    uint8_t _DYT_track_y_temp_high;        

    uint8_t temp1[2];       
    uint8_t temp2[2];   
};