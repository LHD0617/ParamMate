#!/usr/bin/env python
# -*- encoding: utf-8 -*-
"""
@File    :   SerialTool.py    
@Contact :   15663678208
@Modify Time      @Author    @Version    @Desciption
------------      -------    --------    -----------
2022/8/8 12:47   LHD      1.0         None
"""

# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'SerialToolUI.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.

import re
import sys
from MessageClass import MessageClass
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import pyqtSignal, QTimer
from PyQt5.QtWidgets import QGroupBox
from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo


class UiSerialTool(QGroupBox):
    BaudList = ('9600', '14400', '19200', '57600', '115200', '256000', '460800', '2000000')
    DataBitList = ('5', '6', '7', '8')
    CheckBitStrList = ('无校验', '偶校验', '奇校验')
    CheckBitList = (QSerialPort.NoParity, QSerialPort.EvenParity, QSerialPort.OddParity)
    StopBitList = ('1', '2')
    RefreshPortTimer: QTimer()
    LogSignal = pyqtSignal(MessageClass)

    def __init__(self):
        """
        初始化函数
        """
        self.Name = 'SerialTool'
        self.SwitchPortFlag = False
        self.PortList = []
        self.RefreshPortTimer = QTimer()
        self.Ser = QSerialPort()
        super(UiSerialTool, self).__init__()
        self.setupUi(self)
        self.RefreshPortTimer.start(100)

    def setupUi(self, SerialTool):
        """
        UI页面初始化
        :param SerialTool:
        :return:
        """
        SerialTool.setObjectName("SerialTool")
        SerialTool.resize(200, 800)
        self.setMaximumSize(QtCore.QSize(200, 16777215))
        self.ConfigureGboxLayout = QtWidgets.QGridLayout(self)
        self.ConfigureGboxLayout.setVerticalSpacing(20)
        self.ConfigureGboxLayout.setObjectName("ConfigureGboxLayout")
        self.BaudLab = QtWidgets.QLabel()
        self.BaudLab.setObjectName("BaudLab")
        self.ConfigureGboxLayout.addWidget(self.BaudLab, 1, 0, 1, 1)
        self.DatabitLab = QtWidgets.QLabel()
        self.DatabitLab.setObjectName("DatabitLab")
        self.ConfigureGboxLayout.addWidget(self.DatabitLab, 2, 0, 1, 1)
        self.DataBitCbox = QtWidgets.QComboBox()
        self.DataBitCbox.setObjectName("DataBitCbox")
        self.ConfigureGboxLayout.addWidget(self.DataBitCbox, 2, 1, 1, 1)
        self.CheckBitCbox = QtWidgets.QComboBox()
        self.CheckBitCbox.setObjectName("CheckBitCbox")
        self.ConfigureGboxLayout.addWidget(self.CheckBitCbox, 3, 1, 1, 1)
        self.PortLab = QtWidgets.QLabel()
        self.PortLab.setObjectName("PortLab")
        self.ConfigureGboxLayout.addWidget(self.PortLab, 0, 0, 1, 1)
        self.StopBitLab = QtWidgets.QLabel()
        self.StopBitLab.setObjectName("StopBitLab")
        self.ConfigureGboxLayout.addWidget(self.StopBitLab, 4, 0, 1, 1)
        self.CheckBitLab = QtWidgets.QLabel()
        self.CheckBitLab.setObjectName("CheckBitLab")
        self.ConfigureGboxLayout.addWidget(self.CheckBitLab, 3, 0, 1, 1)
        self.PortCbox = QtWidgets.QComboBox()
        self.PortCbox.setObjectName("PortCbox")
        self.ConfigureGboxLayout.addWidget(self.PortCbox, 0, 1, 1, 1)
        self.PortSwitchPbtn = QtWidgets.QPushButton()
        self.PortSwitchPbtn.setObjectName("PortSwitchPbtn")
        self.ConfigureGboxLayout.addWidget(self.PortSwitchPbtn, 5, 0, 1, 2)
        self.BaudCbox = QtWidgets.QComboBox()
        self.BaudCbox.setObjectName("BaudCbox")
        self.ConfigureGboxLayout.addWidget(self.BaudCbox, 1, 1, 1, 1)
        self.StopBitCbox = QtWidgets.QComboBox()
        self.StopBitCbox.setObjectName("StopBitCbox")
        self.ConfigureGboxLayout.addWidget(self.StopBitCbox, 4, 1, 1, 1)
        spacerItem = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.ConfigureGboxLayout.addItem(spacerItem, 6, 0, 1, 2)

        self.retranslateUi(SerialTool)
        self.SetSignalFunction()
        QtCore.QMetaObject.connectSlotsByName(SerialTool)

    def retranslateUi(self, SerialTool):
        """
        文本初始化
        :param SerialTool:
        :return:
        """
        _translate = QtCore.QCoreApplication.translate
        SerialTool.setWindowTitle(_translate("SerialTool", "Form"))
        self.setTitle(_translate("SerialTool", "串口配置"))
        self.BaudLab.setText(_translate("SerialTool", "波特率："))
        self.DatabitLab.setText(_translate("SerialTool", "数据位："))
        self.PortLab.setText(_translate("SerialTool", "端口："))
        self.StopBitLab.setText(_translate("SerialTool", "停止位："))
        self.CheckBitLab.setText(_translate("SerialTool", "校验位："))
        self.PortSwitchPbtn.setText(_translate("SerialTool", "打开串口"))

        self.BaudCbox.addItems(self.BaudList)
        self.BaudCbox.setCurrentIndex(7)
        self.DataBitCbox.addItems(self.DataBitList)
        self.DataBitCbox.setCurrentIndex(3)
        self.CheckBitCbox.addItems(self.CheckBitStrList)
        self.StopBitCbox.addItems(self.StopBitList)

    def SetSignalFunction(self):
        """
        设置信号槽
        :return:
        """
        self.PortSwitchPbtn.clicked.connect(self.SwitchPort)
        self.RefreshPortTimer.timeout.connect(self.RefreshPort)

    def RefreshPort(self):
        """
        刷新串口
        :return:
        """
        if not self.SwitchPortFlag:
            TempPortList = list(QSerialPortInfo.availablePorts())
            TempPortNameList = []
            for TempPort in TempPortList:
                TempPortNameList.append(TempPort.portName())
            if not self.PortList == TempPortNameList:
                self.PortList = TempPortNameList
                self.PortCbox.clear()
                self.PortCbox.addItems(self.PortList)
        else:
            TempPortList = list(QSerialPortInfo.availablePorts())
            TempPortNameList = []
            for TempPort in TempPortList:
                TempPortNameList.append(TempPort.portName())
            if not TempPortNameList.count(self.PortCbox.currentText()):
                self.SwitchPort()

    def SwitchPort(self):
        """
        开关串口
        :return:
        """
        com = self.PortCbox.currentText()
        if not self.SwitchPortFlag:
            if len(com) > 0:
                try:
                    self.Ser.setPortName(com)
                    self.Ser.setBaudRate(int(self.BaudCbox.currentText()))
                    self.Ser.setDataBits(int(self.DataBitCbox.currentText()))
                    self.Ser.setParity(self.CheckBitList[self.CheckBitList[self.CheckBitCbox.currentIndex()]])
                    self.Ser.setStopBits(int(self.StopBitCbox.currentText()))
                    self.Ser.open(QSerialPort.ReadWrite)
                except:
                    self.LogSignal.emit(MessageClass(self.Name, '%s打开失败' % com))
                if self.Ser.isOpen():
                    self.LogSignal.emit(MessageClass(self.Name, '%s打开成功' % com))
                    self.SwitchPortFlag = True
                    self.PortSwitchPbtn.setText('关闭串口')
                    self.PortCbox.setEnabled(False)
                    self.BaudCbox.setEnabled(False)
                    self.DataBitCbox.setEnabled(False)
                    self.CheckBitCbox.setEnabled(False)
                    self.StopBitCbox.setEnabled(False)
                else:
                    self.LogSignal.emit(MessageClass(self.Name, '%s打开失败' % com))
            else:
                self.LogSignal.emit(MessageClass(self.Name, '请选择串口'))
        else:
            self.SwitchPortFlag = False
            self.PortSwitchPbtn.setText('打开串口')
            self.PortCbox.setEnabled(True)
            self.BaudCbox.setEnabled(True)
            self.DataBitCbox.setEnabled(True)
            self.CheckBitCbox.setEnabled(True)
            self.StopBitCbox.setEnabled(True)
            self.Ser.close()
            self.LogSignal.emit(MessageClass(self.Name, '%s已关闭' % com))

    def OutputData(self, dat: bytes):
        """
        输出数据
        :param dat:
        :return:
        """
        print(dat.hex())
        self.Ser.write(dat)


if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    ui = UiSerialTool()
    ui.show()
    sys.exit(app.exec_())
