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

/*
   DYT library
*/

#define AP_SERIALMANAGER_DYT_BAUD         115200
#define AP_SERIALMANAGER_DYT_BUFSIZE_RX        64
#define AP_SERIALMANAGER_DYT_BUFSIZE_TX        64

#include "AP_DYT.h"

extern const AP_HAL::HAL& hal;

//constructor
AP_DYT::AP_DYT(void)
{
    _port = NULL;
    _step = 0;
}

void AP_DYT::init(const AP_SerialManager& serial_manager)
{
    if ((_port = serial_manager.find_serial(AP_SerialManager::SerialProtocol_DYT, 0))) {
        _port->set_flow_control(AP_HAL::UARTDriver::FLOW_CONTROL_DISABLE);

        _port->begin(AP_SERIALMANAGER_DYT_BAUD, AP_SERIALMANAGER_DYT_BUFSIZE_RX, AP_SERIALMANAGER_DYT_BUFSIZE_TX);
    }
}

bool AP_DYT::update()
{
    if(_port == NULL)
        return false;

    int16_t numc = _port->available();
    uint8_t data;

    for (int16_t i = 0; i < numc; i++) {
        data = _port->read();

        switch(_step) {
            
        case 0:
            if(data == 0xEE)
                _step = 1;
            break;

        case 1:
            if(data == 0x16)
                _step = 2;
            else
                _step = 0;
            break;

        case 2:
            _step = 3;
            break;
        case 3:
            _step = 4;
            break;
        case 4:
            _step = 5;
            break;
        case 5:
            _step = 6;
            break;
        //串口读取目标脱靶量数据
        case 6: 
            _DYT_track_x_temp_low = data;   //DYT x轴脱靶量低八位
            _step = 7;
            break;
        case 7:
             _DYT_track_x_temp_high = data;  //DYT x轴脱靶量高八位
            _step = 8;
            break;

        case 8:
            _DYT_track_y_temp_low = data;  //DYT y轴脱靶量低八位
            _step = 9;

            break;
        case 9:
            _DYT_track_y_temp_high = data;  ////DYT y轴脱靶量高八位
            _step = 10;
            break;
        //end

        case 10:
            _step = 11;
            break;
        case 11:
            _step = 12;
            break;
        case 12:
            _step = 13;
            break;
        case 13:
            _step = 14;
            break;
        case 14:
            _step = 15;
            break;
        case 15:
            _step = 16;
            break;
        case 16:
            _step = 17;
            break;
        case 17:
            _step = 18;
            break;
        case 18:
            _step = 19;
            break;
        case 19:
            _step = 20;
            break;
        case 20:
            _step = 21;
            break;
        case 21:
            _step = 22;
            break;
        case 22:
            _step = 23;
            break;
        case 23:
            _step = 24;
            break;
        case 24:
            _step = 25;
            break;
        case 25:
            _step = 26;
            break;
        case 26:
            _step = 27;
            break;
        case 27:
            _step = 28;
            break;
        case 28:
            _step = 29;
            break;
        case 29:
            _step = 30;
            break;
        case 30:
            _step = 31;
            break;

        case 31:

            temp1[0]=_DYT_track_x_temp_low;
            temp1[1]=_DYT_track_x_temp_high;

            temp2[0]=_DYT_track_y_temp_low;
            temp2[1]=_DYT_track_y_temp_high;

            DYT_track_x  = *((short *)temp1);     //最终获取的 DYT x轴偏移量
            DYT_track_y  = *((short *)temp2);     //最终获取的 DYT y轴偏移量
            
            last_frame_ms = AP_HAL::millis();
            _step = 0;
            break;

        default:
            _step = 0;
        }
    }

    return false;
}
