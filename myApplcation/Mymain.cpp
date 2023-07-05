/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : Mymain.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/27 
*********************************************************************
*********
*/
//
#include "Myapplication.h"
#include "IncludeALL.h"
#include "MySchedule.h"
#include "WIFIReceiver.h"
#define SIZE 1024


MyUsart myUsartthis(&huart1);
ESP esp;
WIFIReceive wifiReceive;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance==TIM1) {
        wifiReceive.counter++;
    }
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
    if (wifiReceive.isUpCapt){
        wifiReceive.valueup= HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_1);
        wifiReceive.isUpCapt=0;
        __HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);
        wifiReceive.counter=0;
    }
    else{
        wifiReceive.valuedown= HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_1);
        wifiReceive.isUpCapt=1;
        __HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);
        wifiReceive.Binary_conversion();
    }
}
//输入捕获转换
static void Task1()
{
    if (wifiReceive.recflag){
#if Test
        wifiReceive.Print();
#endif
        wifiReceive.recflag=0;
        wifiReceive.Deal_width();
        myUsartthis.SendString(wifiReceive.final,wifiReceive.DealFlag);
        wifiReceive.WIFIRecInit();


    }

}
//二进制转为十进制
static void Task2()
{
    HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);
}
//显示转换完成的数字或字母
static void Task3(){
    HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
}
void Mymain()
{
    MySchedule mySchedule;
//    MyLCD myLcd;
//    myLcd.MyLCDInit();
//    myLcd.MyLDshowLable();
//    myLcd.MyLCDDrawCoorDinat();
    HAL_TIM_Base_Start_IT(&htim1);//定时器更新时产生中断
    HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_1);
    wifiReceive.WIFIRecInit();
    mySchedule.MyScheduleSetPeriod(25);
    mySchedule.MyTaskGreat(Task1,1,5,0);
    mySchedule.MyTaskGreat(Task2,2,5,0);
    for (;;) {
        Task1();
//        mySchedule.MyScheduleWhile();
    }

    /*MyUsart myUsart(&huart1);
    esp.ESP_Init(&huart3);
    esp.WIFIConnect();
   // WIFIDemo();
    esp.myUsart->ReceiveInit();
    for (;;) {
        if (esp.myUsart->GetRECV()==1)
        {
            myUsart.SendString(esp.myUsart->Re_GetData(),esp.myUsart->GetRecvLenth());
            esp.myUsart->ReceiveInit();
        }

    }*/


}
/***************************************************************
  *  @brief     让中断文件可以调用c++函数
  *  @param     参数
  *  @note      备注 ：此函数放在it文件当中
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author     wangzibo
 **************************************************************/

void ItUsart(DMA_HandleTypeDef * hdma_usartx_rx)
{
   esp.myUsart->ReceiveDataCallBack(hdma_usartx_rx);

}