## 8031-learning：8031笔记
8031无内部ROM即无存储代码的空间，必需要使用外部并行ROM，典型IC如PQ2864A, AT28C64。8031运行ROM内部代码前必须要用其他方式向ROM内部写入代码数据。这里使用Arduino UNO。代码见EEPROM.ino，时序图按AT28C64的datasheet写即可。硬件配置上由于UNO引脚不够，所以仿照8031运行过程用SN74HC373复用数据/地址。如果有Arduino 2560的话可以不用这么做。还有记得，373锁存器八个输入引脚上全都要挂上拉电阻，好像这样输出才对，不然输出会乱，（目前没有太清楚为什么会这样，因为373的LE拉低之前UNO上八个引脚就已经设成OUTPUT了，应该没有引脚会处于float状态的）。整个电路用好多好多杜邦线（毕竟是并行的芯片）搭在面包板上，不知道为何目前工作还不太稳定，猜测会不会是某个地方接触不良，打算以后拿个洞洞板试着焊出来。

#### 实验一：Blink
以下代码可以让P1.0上的引脚不停翻转
```ORG 0H
LP: CPL P1.0
ACALL DELAY
SJMP LP

DELAY: MOV R0, #0FFH
AGAIN: MOV R1, #0FFH
AGAIN1: DJNZ R1, AGAIN1
DJNZ R0, AGAIN
RET
END
```
烧EEPROM之前可以找个8051的单片机开发板试一下对不对。然后找到.hex文件，用Notepad++打开（注意默认情况下是黑色的数字代表指令码，前面有地址，最后绿色的是校验码，不确定其实也可以用STC的STC-ISP软件打开hex文件）知汇编程序对应的所有指令为：
```
B2 90 11 06 80 FA 78 FF 79 FF D9 FE D8 FA 22
```
这就有了EEPROM.ino代码里面数据数组的值。烧完之后再拿Arduino读一下看下对不对。最后用书上的电路图连好8031的晶振、复位电路、EEPROM等等，然后连个LED和限流电阻就能看到LED在飞快的闪烁了。

### Reference
----
The 8051 microcontroller: a systems approach by MUHAMMAD ALI MAZIDI etc.（深入理解8051单片机系统）

[803151-interfacing-with-external-rom](http://what-when-how.com/8051-microcontroller/803151-interfacing-with-external-rom/)
