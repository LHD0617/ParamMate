# ParamMate

![image](05_Logo/1.png)
## 1.项目简介

**ParamMate** 是一个集调参、示波、图传的多功能调试助手。采取模块化的设计思路将各 个功能以控件的形式拼装组合使用，用户可以根据下位机的不同初始化语句来 DIY 上位机页 面组成而无需像传统调试助手一样需要两头配置（配置下位机之后还要再上位机进行相应配 置），这样可以大大提升调试效率。 

ParamMate 采用自定义通信协议，可承载于多种通信方式如：串口、IIC、SPI、UART、 USB、CAN、SDIO、WIFI 等，这样无需关心具体数据传输是如何实现的只需要将通信数据完 整传输到上位机即可。就像计算机网络中应用层无需关心物理层是如何实现传输的。封装好 的通信协议栈，用户只需要将数据 IO 接口配置好，就可以实现调用 SDK 实现所有功能。

ParamMate最大支持：
- 一个 32 通道调参控件：支持读模式、写模式、读写模式调参。
- 三个 8 通道示波控件：支持折线图、样条线图、条形图示波。
- 两个图传控件：支持二值化图、 灰度图、RGB565 彩图等图传。

### 结构图

![image](04_Document\1.png)

### 预览图

![image](04_Document\2.png)

## 2.项目结构
    ----.\
        |----.git\
        |----01_GUI\                            //GUI上位机
        |----02_MM32SPIN27_Slave\               //MM32SPIN27下位机Demo工程
        |----03_Seekfree_RT1064_Slave\          //RT1064下位机Demo工程
        |----04_Document\                       //文档
        |----05_Logo\                           //LOGO
        |----06_UserFile\                       //用户文件
        |----07_Tools\                          //工具
        |----MakePathLib.py                     //生成目录结构脚本
        |----README.md                          //README.md

    - 具体说明详见各分支下README

## 3.更新说明

* ### V1.0.0

    初始版本

* ### V1.1.0

    将QtSerialPort替换为pyserial，添加串口工具配置文件

* ### V1.1.1

    关闭OpenGL加速卡顿效果好转
