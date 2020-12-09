#include <ld3320.h>

VoiceRecognition Voice;                         //声明一个语音识别对象
int Led[5]={8,3,5,6,7};                         //定义灯的数组（有5排灯，引脚为8、3、5、6、7）

void setup() 
{
    for(int i=0;i<5;i++)
    {
      pinMode(Led[i],OUTPUT);                   //初始化LED引脚为输出模式
      digitalWrite(Led[i],LOW);                 //LED引脚低电平
    }
    Serial.begin(9600);                        //配置串口监视器频道9600
    Serial.print("Uart start!");                
    Voice.init();                               //初始化VoiceRecognition模块   
    Voice.noiseTime(0x10);                      //定义读取模式
    Voice.micVol(0x30);
    Voice.voiceMaxLength(0x14);
    Voice.addCommand("kai deng",0);             //添加指令“开灯”
    Voice.addCommand("guan deng",1);            //添加指令“关灯”
    Voice.addCommand("hu xi",2);                //添加指令“呼吸”
    Voice.addCommand("bo lang",3);              //添加指令“波浪”
    Voice.addCommand("ni hao",4);               //添加一些垃圾词汇
    Voice.addCommand("wei wei",5);              
    Voice.addCommand("wu wu",6);
    Voice.addCommand("shu shu",7);
    Voice.start();                              //开始识别
}

void loop() {
  switch(Voice.read())                          //判断识别
  {
    case 0:                                     //若是指令“kai deng”
        for(int i=0;i<5;i++)
        {
          digitalWrite(Led[i],1);               //点亮LED
        }  
        Serial.println("LED ON");
        break;
    case 1:                                     //若是指令“guan deng”
        for(int i=0;i<5;i++)
        {
          digitalWrite(Led[i],0);               //熄灭LED
        }                                               
        Serial.println("LED OFF");
        break;    
    case 2:                                     //若是指令“hu xi”
        Serial.println("hu xi");               
        for(int i=0;i<10;i++)
         { for (int value = 0 ; value <= 255; value=value+3)
          {  
            for(int i=0;i<5;i++)                                //定义变量value，取值在0~255之间逐渐改变
            {analogWrite(Led[i], value);
             delay(5);} 
          }
          for (int value = 255; value >=0; value=value-3)
          {  
            for(int i=0;i<5;i++)
            {analogWrite(Led[i], value);
             delay(5);} 
           }
          }
        break;  
    case 3:                                            //若是指令“bo lang”
        Serial.println("bo lang");
        for(int i=0;i<10;i++)
        {for(int j=0;j<5;j++)
        { digitalWrite(Led[j],1); 
          delay(300);                                  //逐个亮灭以达到波浪形效果
          digitalWrite(Led[j],0);}}
        break;
    case 4:
        Serial.println("ni hao");                     //垃圾词汇没有执行的命令
        break;   
    case 5:
        Serial.println("wei wei");
        break; 
    case 6:
        Serial.println("wu wu");
        break;
    case 7:
        Serial.println("shu shu");
        break;
    default:
        break;
  }
}
