/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : WIFIReceiver.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/7/3 
*********************************************************************
*********
*/
//

#ifndef CPROJECT_WIFIRECEIVER_H
#define CPROJECT_WIFIRECEIVER_H
#include "deque"
#ifdef __cplusplus
extern "C"
{
#include "Myapplication.h"
#include "IncludeALL.h"
#endif
/*______________________类的声明在这下面________________:*/
class WIFIReceive{
public:
    WIFIReceive();
    void WIFIRecInit();
    void Binary_conversion();
    void Deal_width();
    void TowToTen();
    void Print();
    ~WIFIReceive();
    uint16_t Sizesavwidth;
    uint16_t index;
    uint16_t DealFlag;
    uint16_t width;
    uint16_t * savebuf;
    uint32_t counter;
    uint16_t valueup;
    uint16_t valuedown;
    uint16_t buffid;
    uint16_t recflag;
    uint8_t  isUpCapt;
    uint8_t* final;
    std::deque<std::deque<uint16_t>> save_width;
    std::deque<uint16_t> save_data;
    std::deque<uint16_t > Tow_to_ten;
    std::deque<std::deque<uint16_t > > SaveTow_to_ten;
private:
    MyUsart * WIFIReceiveUsrat;
    TIM_HandleTypeDef *wifihtim;

};
#ifdef __cplusplus
}
#endif
#endif //CPROJECT_WIFIRECEIVER_H
