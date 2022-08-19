#!/usr/bin/env python
# -*- encoding: utf-8 -*-
"""
@File    :   MainWindow.py    
@Contact :   15663678208
@Modify Time      @Author    @Version    @Desciption
------------      -------    --------    -----------
2022/8/6 15:24   LHD      1.0         None
"""

# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ParamMate_Tools_UI.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.
import sys

import qdarkstyle

import Icon_rc
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QMainWindow, QSplitter
from typing import List
from CommProt import CommProtClass, RevDataPackageClass
from Image import MyImage
from Param import MyParam
from SerialTool import UiSerialTool
from Waveform import MyWaveform
from MessageClass import MessageClass

PM_MAIN_WINDOW_ID = 0xFF  # 主窗口ID
PM_MAX_NAME_LEN = 32  # 名称最大字节数
PM_MAX_PARAM = 1  # 最大支持参数控件数
PM_MAX_WAVEFORM = 3  # 最大支持示波控件数
PM_MAX_IMAGE = 2  # 最大支持图传控件数
PM_MAX_PARAMCANNELS = 32  # 参数最大通道数
PM_MAX_WAVEFORMCANNELS = 8  # 示波最大通道数
PM_MAX_WIDTH = 188  # 图像最大宽度
PM_MAX_HEIGHT = 120  # 图像最大高度


class UiParamMateUI(QMainWindow):
    Name: str  # 主窗口名称
    ID: int  # 主窗口ID
    CommProt: CommProtClass  # 通信协议对象
    ParamList: List[MyParam]  # 参数控件列表
    WaveformList: List[MyWaveform]  # 示波控件列表
    ImageList: List[MyImage]  # 图传控件列表

    def __init__(self):
        super(UiParamMateUI, self).__init__()
        self.Name = 'MainWindow'
        self.ID = PM_MAIN_WINDOW_ID
        self.CommProt = CommProtClass()
        self.ParamList = []
        self.WaveformList = []
        self.ImageList = []
        self.setupUi(self)
        self.SetSignalFunction()

    def setupUi(self, ParamMateUI):
        """
        UI页面初始化
        :param ParamMateUI:
        :return:
        """
        ParamMateUI.setObjectName("ParamMateUI")
        ParamMateUI.resize(1000, 800)
        ParamMateUI.setWindowIcon(QIcon(':/1.ico'))
        self.centralwidget = QtWidgets.QWidget(ParamMateUI)
        self.centralwidget.setObjectName("centralwidget")
        self.MainLayout = QtWidgets.QGridLayout(self.centralwidget)
        self.MainLayout.setObjectName("MainLayout")
        self.groupBox = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox.setObjectName("groupBox")
        self.SubWidgetLayout = QtWidgets.QGridLayout(self.groupBox)
        self.SubWidgetLayout.setObjectName("SubWidgetLayout")

        # 后期修改只需要将这里的串口控件修改为其他控件，再将接收数据槽函数与通信接口适配即可
        self.SerialTool = UiSerialTool()
        self.MainLayout.addWidget(self.SerialTool, 0, 0, 1, 1)

        self.MainLayout.addWidget(self.groupBox, 0, 1, 1, 1)
        ParamMateUI.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(ParamMateUI)
        self.statusbar.setObjectName("statusbar")
        ParamMateUI.setStatusBar(self.statusbar)

        self.retranslateUi(ParamMateUI)
        QtCore.QMetaObject.connectSlotsByName(ParamMateUI)

    def retranslateUi(self, ParamMateUI):
        """
        UI文字初始化
        :param ParamMateUI:
        :return:
        """
        _translate = QtCore.QCoreApplication.translate
        ParamMateUI.setWindowTitle(_translate("ParamMateUI", "ParamMate_Tools"))
        self.groupBox.setTitle(_translate("ParamMateUI", "Window"))

    def SetSignalFunction(self):
        """
        设置信号槽
        :return:
        """
        self.SerialTool.readyRead.connect(self.ReceiveData)
        self.SerialTool.LogSignal.connect(self.ShowMessage)
        self.CommProt.RevFinishSignal.connect(self.CommandParsing)
        self.CommProt.LogSignal.connect(self.ShowMessage)

    def CommandParsing(self, DataPackage: RevDataPackageClass):
        """
        命令解析函数
        :param DataPackage:
        :return:
        """
        DataPackage.RevEnd = False  # 置位接收数据结束标志位
        if DataPackage.Type == 0xa0:  # 窗口复位命令
            self.ShowMessage(MessageClass(self.Name, '主窗口复位'))
            if DataPackage.ID == PM_MAIN_WINDOW_ID:
                if DataPackage.Data[0] == 0x01:
                    self.WaveformList.clear()
                    self.ImageList.clear()
                    self.ParamList.clear()
                    for i in range(self.SubWidgetLayout.count()):
                        self.SubWidgetLayout.itemAt(i).widget().deleteLater()
        if DataPackage.Type == 0xa1:  # 窗口初始化命令
            self.ShowMessage(MessageClass(self.Name, '主窗口初始化'))
            if DataPackage.ID == PM_MAIN_WINDOW_ID:
                if DataPackage.Data[0] == 0x01:
                    # 获取控件个数
                    ParamNum = len(self.ParamList)
                    WaveformNum = len(self.WaveformList)
                    ImageNum = len(self.ImageList)
                    SubSplitter = QSplitter(Qt.Vertical)
                    ImageSplitter = QSplitter(Qt.Horizontal)
                    # 添加控件到窗口中并将其信号连接到主窗口
                    for i in range(ImageNum):
                        ImageSplitter.addWidget(self.ImageList[i])
                        self.ImageList[i].LogSignal.connect(self.ShowMessage)
                    WaveformSplitter = QSplitter(Qt.Horizontal)
                    for i in range(WaveformNum):
                        WaveformSplitter.addWidget(self.WaveformList[i])
                        self.WaveformList[i].LogSignal.connect(self.ShowMessage)
                    ParamSplitter = QSplitter(Qt.Horizontal)
                    for i in range(ParamNum):
                        ParamSplitter.addWidget(self.ParamList[i])
                        self.ParamList[i].LogSignal.connect(self.ShowMessage)
                        self.ParamList[i].SendDataSignal.connect(self.SendData)
                    SubSplitter.addWidget(ImageSplitter)
                    SubSplitter.addWidget(WaveformSplitter)
                    SubSplitter.addWidget(ParamSplitter)
                    self.SubWidgetLayout.addWidget(SubSplitter, 0, 0, 1, 1)

        if DataPackage.Type == 0x10:  # 创建参数控件命令
            # 判断是否超出控件最大数量
            ParamNum = len(self.ParamList)
            if ParamNum < PM_MAX_PARAM:
                Name = DataPackage.Data.decode()
                NewParam = MyParam(ID=DataPackage.ID, Name=Name)
                self.ParamList.append(NewParam)
        if DataPackage.Type == 0x11:  # 创建示波控件命令
            # 判断是否超出控件最大数量
            WaveformNum = len(self.WaveformList)
            if WaveformNum < PM_MAX_WAVEFORM:
                SeriesType = DataPackage.Data[0]
                DataType = DataPackage.Data[1]
                Name = DataPackage.Data[2: PM_MAX_NAME_LEN + 2].decode()
                NewWaveform = MyWaveform(ID=DataPackage.ID, Name=Name, SeriesType=SeriesType, DataType=DataType)
                self.WaveformList.append(NewWaveform)
        if DataPackage.Type == 0x12:  # 创建图传控件命令
            ImageNum = len(self.ImageList)
            if ImageNum < PM_MAX_IMAGE:
                ImageType = DataPackage.Data[0]
                Height = DataPackage.Data[1]
                Width = DataPackage.Data[2]
                Name = DataPackage.Data[3: PM_MAX_NAME_LEN + 3].decode()
                NewImage = MyImage(ID=DataPackage.ID, Name=Name, ImageType=ImageType, Height=Height, Width=Width)
                self.ImageList.append(NewImage)
        if DataPackage.Type == 0x20:  # 创建参数通道
            DataType = DataPackage.Data[0]
            ModeType = DataPackage.Data[1]
            Name = DataPackage.Data[2: PM_MAX_NAME_LEN + 2].decode()
            for Param in self.ParamList:
                if Param.ID == DataPackage.ID:
                    Param.AddChannels(Name=Name, DataType=DataType, ModeType=ModeType)
                    break
            else:
                self.ShowMessage(MessageClass(self.Name, '创建参数通道%s时未找到ID为%d的控件' % (Name, DataPackage.ID)))
        if DataPackage.Type == 0x21:  # 创建示波通道
            Name = DataPackage.Data.decode()
            for Waveform in self.WaveformList:
                if Waveform.ID == DataPackage.ID:
                    Waveform.AddChannels(Name=Name)
                    break
            else:
                self.ShowMessage(MessageClass(self.Name, '创建参数通道%s时未找到ID为%d的控件' % (Name, DataPackage.ID)))
        if DataPackage.Type == 0x30:  # 上传参数数据命令
            for Param in self.ParamList:
                if Param.ID == DataPackage.ID:
                    Param.InputData(DataPackage.Data)
                    break
            else:
                self.ShowMessage(MessageClass(self.Name, '接收到来自ID为%d的控件数据未找到其相应控件' % DataPackage.ID))
        if DataPackage.Type == 0x31:  # 上传示波数据命令
            for Waveform in self.WaveformList:
                if Waveform.ID == DataPackage.ID:
                    Waveform.InputData(DataPackage.Data)
                    break
            else:
                self.ShowMessage(MessageClass(self.Name, '接收到来自ID为%d的控件数据未找到其相应控件' % DataPackage.ID))
        if DataPackage.Type == 0x32:  # 上传图传数据命令
            for Image in self.ImageList:
                if Image.ID == DataPackage.ID:
                    Image.InputData(DataPackage.Data)
                    break
            else:
                self.ShowMessage(MessageClass(self.Name, '接收到来自ID为%d的控件数据未找到其相应控件' % DataPackage.ID))

    def ShowMessage(self, Message: MessageClass):
        """
        显示LOG信息函数
        :param Message:
        :return:
        """
        self.statusbar.showMessage(Message.Message, 2000)

    def ReceiveData(self, ByteList: bytes):
        """
        接收数据函数
        :return:
        """
        for Byte in ByteList:
            self.CommProt.InputByte(Byte)

    def SendData(self, Type: int, ID: int, dat: bytes):
        """
        数据发送函数
        :param Type:
        :param ID:
        :param dat:
        :return:
        """
        self.SerialTool.OutputData(self.CommProt.OutputByte(Type, ID, dat))


if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    # app.setStyleSheet(qdarkstyle.load_stylesheet())
    ui = UiParamMateUI()
    ui.show()
    sys.exit(app.exec_())
