/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : WIFIReceiver.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/7/3 
*********************************************************************
*********
*/
//

#include "WIFIReceiver.h"


WIFIReceive::WIFIReceive() {

}

WIFIReceive::~WIFIReceive() {
    delete WIFIReceiveUsrat;
}

void WIFIReceive::Binary_conversion() {

   // WIFIReceiveUsrat->Myprintf("startBinary\n");
    width=valuedown+counter*65536-valueup;
#if Test
    WIFIReceiveUsrat->Myprintf("width:%d\n",width);
#endif
    if(width>8000&&width<12000){
        recflag=1;
    }
    if (width>38000&&width<42000){
        this->DealFlag++;
       this->buffid++;
       save_data.push_back(width);
    }
    else if(this->buffid>0){
        save_data.push_back(width);
        this->buffid++;
        if (this->buffid>8){
            //recflag=1;
            buffid=0;
            save_width.push_back(save_data);
            save_data.clear();
        }

        //WIFIReceiveUsrat->Myprintf("%d",this->buffid);
    }
}

void WIFIReceive::WIFIRecInit() {
    this->WIFIReceiveUsrat=new MyUsart(&huart1);
    WIFIReceiveUsrat->Myprintf("Receive\n");
    this->isUpCapt=1;
    this->DealFlag=this->buffid=this->recflag=this->width=this->valuedown=this->valueup=0;
    this->index=0;
    this->SaveTow_to_ten.clear();
    this->save_width.clear();
    this->save_data.clear();
    this->Tow_to_ten.clear();


}

void WIFIReceive::Print() {
int cnt=0;
    for ( auto it=save_width.begin();  it!=save_width.end(); it++) {

       for ( auto ix=(*it).begin();  ix!=(*it).end() ; ix++) {
            cnt++;
            WIFIReceiveUsrat->Myprintf("data:%d\n",*ix);
       }
    }
    WIFIReceiveUsrat->Myprintf("cnt:%d\nsavewidthsize:%d\n",cnt,save_width.size());
//    for (std::deque<uint16_t *>::iterator it=save_width->begin();  it< save_width->end();it++) {
//        for (int i = 0; i < 9; ++i) {
//           WIFIReceiveUsrat->Myprintf("savewidth:%d\r", *it[i]);
//        }
//        WIFIReceiveUsrat->Myprintf("\n");
//    }



}

void WIFIReceive::Deal_width() {


    for ( auto it=save_width.begin();  it!=save_width.end(); it++) {
        int cnt=0;
        for ( auto ix=(*it).begin();  ix!=(*it).end() ; ix++) {
            if (*ix>38000&&*ix<42000){
                this->Tow_to_ten.clear();
            }
            else if (*ix>18000&&*ix<32000){
                cnt++;
                if (*ix>18000&&*ix<22000){
                    Tow_to_ten.push_back(0);
                }
                else if (*ix>28000&&*ix<32000){
                    Tow_to_ten.push_back(1);
                }
                if (cnt==8){
                    this->SaveTow_to_ten.push_back(this->Tow_to_ten);
                }

            }
           // WIFIReceiveUsrat->Myprintf("data:%d\n",*ix);
        }
    }
    TowToTen();
}

void WIFIReceive::TowToTen() {
    final=new uint8_t[this->DealFlag]();
    uint16_t temp;
    index=0;
    uint16_t Weight;
    for ( auto it=SaveTow_to_ten.begin();  it!=SaveTow_to_ten.end(); it++) {
        temp=0;
        Weight=1;
        for ( auto ix=(*it).begin();  ix!=(*it).end() ; ix++) {
            temp+=(*ix)*Weight;
            Weight=Weight*2;
           // WIFIReceiveUsrat->Myprintf("%dtemp:%d\n",index,temp);
        }
       final[index++]=temp;


        //WIFIReceiveUsrat->Myprintf("temp:%d\n",temp);

    }



}





