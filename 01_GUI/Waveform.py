#!/usr/bin/env python
# -*- encoding: utf-8 -*-
"""
@File    :   Waveform.py
@Contact :   15663678208
@Modify Time      @Author    @Version    @Desciption
------------      -------    --------    -----------
2022/8/6 22:23   LHD      1.0         None
"""
import sys

from PyQt5 import QtCore, QtWidgets
from PyQt5.QtChart import QLineSeries, QChartView, QChart, QSplineSeries, QBarSeries, QPieSeries, QValueAxis, QBarSet
from PyQt5.QtCore import Qt, QTimer
from PyQt5.QtWidgets import QGroupBox

SeriesTypeStrList = ('折线图', '样条线图', '条形图', '饼图')
DataTypeStrList = ('uint8', 'uint16', 'uint32', 'uint64', 'int8', 'int16', 'int32', 'int64', 'float', 'double')

MaxDataLen = 800  # 最大数据量当数据长度大于该数值将会清空数据

MinXAxisRange = 50  # X轴范围最小值
MaxXAxisRange = 800  # X轴范围最大值
MinYAxisRange = 1  # Y轴范围最小值
MaxYAxisRange = 1073741824  # Y轴范围最大值


class MyWaveform(QGroupBox):
    ID: int  # 控件ID
    SeriesType: int  # 控件类型
    DataType: int  # 数据类型
    Channels: int  # 通道数
    SeriesList: list  # 通道列表
    BarSetList: list  # 柱状图数据列表
    SwitchAdaptiveFlag: bool  # 自适应开关状态
    SwitchFollowFlag: bool  # 自动跟踪开关状态
    AxisX: QValueAxis  # X轴
    AxisY: QValueAxis  # Y轴
    SysDataCount: int  # 系统获取数据次数
    MaxValue = -sys.maxsize - 1  # 最大值
    MinValue = sys.maxsize  # 最小值
    XAxisRange: int  # X轴显示范围
    YAxisRange: int  # Y轴显示范围
    YAxisOffset: int  # Y轴坐标偏移量

    def __init__(self, ID=0, Name='', SeriesType=0, DataType=0):
        super(MyWaveform, self).__init__()
        self.ID = ID
        self.SeriesType = SeriesType
        self.DataType = DataType
        self.Channels = 0
        self.SeriesList = []
        self.SwitchAdaptiveFlag = False
        if SeriesType == 0 or SeriesType == 1:
            self.AxisX = QValueAxis()
            self.AxisX.setLabelFormat('%d')
            self.AxisX.setTickCount(10)
            self.AxisX.setRange(0, 300)
        if SeriesType == 2:
            self.BarSetList = []
            self.BarSeries = QBarSeries()
        self.AxisY = QValueAxis()
        self.AxisY.setTickCount(10)
        self.AxisY.setRange(0, 1)
        self.SysDataCount = 0
        self.XAxisRange = 300
        self.YAxisRange = 1
        self.YAxisOffset = 0
        self.Chart = QChart()
        self.Chart.setTitle(Name)
        self.setupUi(self)
        self.SwitchAdaptive()
        self.graphicsView = QChartView(self.Chart)
        self.graphicsView.setObjectName("graphicsView")
        self.setTitle(Name)
        self.gridLayout.addWidget(self.graphicsView, 1, 0, 1, 6)
        if DataType & 0x08:
            self.UnitChannelSize = 4 + DataType & 0x01 * 4
            self.AxisY.setLabelFormat('%f')
        else:
            self.UnitChannelSize = 0x01 << (DataType & 0x03)
            self.AxisY.setLabelFormat('%d')

    def setupUi(self, From):
        From.setObjectName("From")
        From.resize(800, 600)
        self.gridLayout = QtWidgets.QGridLayout(self)
        self.gridLayout.setObjectName("gridLayout")
        self.XaxisZoomPbtn = QtWidgets.QPushButton()
        self.XaxisZoomPbtn.setObjectName("XaxisZoomPbtn")
        self.gridLayout.addWidget(self.XaxisZoomPbtn, 2, 3, 1, 1)
        self.SwitchAdaptivePbtn = QtWidgets.QPushButton()
        self.SwitchAdaptivePbtn.setObjectName("SwitchAdaptivePbtn")
        self.gridLayout.addWidget(self.SwitchAdaptivePbtn, 2, 5, 1, 1)
        self.graphicsView = QChartView()
        self.graphicsView.setObjectName("graphicsView")
        self.gridLayout.addWidget(self.graphicsView, 1, 0, 1, 6)
        self.IDLab = QtWidgets.QLabel()
        self.IDLab.setObjectName("IDLab")
        self.gridLayout.addWidget(self.IDLab, 0, 0, 1, 1)
        self.YaxisZoomPbtn = QtWidgets.QPushButton()
        self.YaxisZoomPbtn.setObjectName("YaxisZoomPbtn")
        self.gridLayout.addWidget(self.YaxisZoomPbtn, 2, 0, 1, 1)
        self.XaxisShrinkPbtn = QtWidgets.QPushButton()
        self.XaxisShrinkPbtn.setObjectName("XaxisShrinkPbtn")
        self.gridLayout.addWidget(self.XaxisShrinkPbtn, 2, 4, 1, 1)
        self.YaxisShrinkPbtn = QtWidgets.QPushButton()
        self.YaxisShrinkPbtn.setObjectName("YaxisShrinkPbtn")
        self.gridLayout.addWidget(self.YaxisShrinkPbtn, 2, 1, 1, 1)
        self.YaxisZeroPbtn = QtWidgets.QPushButton()
        self.YaxisZeroPbtn.setObjectName("YaxisZeroPbtn")
        self.gridLayout.addWidget(self.YaxisZeroPbtn, 2, 2, 1, 1)
        self.ChannelsLab = QtWidgets.QLabel()
        self.ChannelsLab.setObjectName("ChannelsLab")
        self.gridLayout.addWidget(self.ChannelsLab, 0, 1, 1, 1)
        self.DataTypeLab = QtWidgets.QLabel()
        self.DataTypeLab.setObjectName("DataTypeLab")
        self.gridLayout.addWidget(self.DataTypeLab, 0, 4, 1, 2)
        self.SeriesTypeLab = QtWidgets.QLabel()
        self.SeriesTypeLab.setObjectName("SeriesTypeLab")
        self.gridLayout.addWidget(self.SeriesTypeLab, 0, 2, 1, 2)

        if self.SeriesType == 2 or self.SeriesType == 3:
            self.XaxisZoomPbtn.setEnabled(False)
            self.XaxisShrinkPbtn.setEnabled(False)

        self.retranslateUi(From)
        QtCore.QMetaObject.connectSlotsByName(From)

        self.SetSignalFunction()

    def retranslateUi(self, From):
        _translate = QtCore.QCoreApplication.translate
        From.setWindowTitle(_translate("From", "Form"))
        self.XaxisZoomPbtn.setText(_translate("From", "X轴放大"))
        self.YaxisZoomPbtn.setText(_translate("From", "Y轴放大"))
        self.SeriesTypeLab.setText(_translate("From", "控件类型：%s" % SeriesTypeStrList[self.SeriesType]))
        self.DataTypeLab.setText(_translate("From", "数据类型：%s" % DataTypeStrList[self.DataType]))
        self.ChannelsLab.setText(_translate("From", "通道数："))
        self.SwitchAdaptivePbtn.setText(_translate("From", "开启自适应"))
        self.YaxisZeroPbtn.setText(_translate("From", "Y轴归0"))
        self.YaxisShrinkPbtn.setText(_translate("From", "Y轴缩小"))
        self.XaxisShrinkPbtn.setText(_translate("From", "X轴缩小"))
        self.IDLab.setText(_translate("From", "ID：%d" % self.ID))

    def SetSignalFunction(self):
        # 按键类
        self.SwitchAdaptivePbtn.clicked.connect(self.SwitchAdaptive)
        self.XaxisZoomPbtn.clicked.connect(self.XAxisZoom)
        self.XaxisShrinkPbtn.clicked.connect(self.XAxisShrink)
        self.YaxisZoomPbtn.clicked.connect(self.YAxisZoom)
        self.YaxisShrinkPbtn.clicked.connect(self.YAxisShrink)
        self.YaxisZeroPbtn.clicked.connect(self.YAxisResetZero)

        # QChart事件
        self.Chart.mousePressEvent = self.MousePressEvent
        self.Chart.mouseMoveEvent = self.MouseMoveEvent
        self.Chart.mouseDoubleClickEvent = self.YAxisResetZero
        self.Chart.wheelEvent = self.WheelEvent

    def SwitchAdaptive(self):
        if self.SwitchAdaptiveFlag:
            self.SwitchAdaptiveFlag = False
            self.YaxisShrinkPbtn.setEnabled(True)
            self.YaxisZoomPbtn.setEnabled(True)
            self.YaxisZeroPbtn.setEnabled(True)
            self.SwitchAdaptivePbtn.setText("开启自适应")
        else:
            self.SwitchAdaptiveFlag = True
            self.YaxisShrinkPbtn.setEnabled(False)
            self.YaxisZoomPbtn.setEnabled(False)
            self.YaxisZeroPbtn.setEnabled(False)
            self.SwitchAdaptivePbtn.setText("关闭自适应")

    def MousePressEvent(self, event):
        self.MouseYPos = event.pos().y()
        self.LastYAxisOffset = self.YAxisOffset

    def MouseMoveEvent(self, event):
        if not self.SwitchAdaptiveFlag:
            self.YAxisOffset = self.LastYAxisOffset + self.MouseYPos - event.pos().y()
            self.SetYAxisRange()

    def WheelEvent(self, event):
        if not self.SwitchAdaptiveFlag:
            if event.delta() == 120:
                self.YAxisZoom()
            else:
                self.YAxisShrink()

    def XAxisZoom(self):
        if self.XAxisRange - 50 >= MinXAxisRange:
            self.XAxisRange -= 50
            self.SetXAxisRange()

    def XAxisShrink(self):
        if self.XAxisRange + 50 <= MaxXAxisRange:
            self.XAxisRange += 50
            self.SetXAxisRange()

    def YAxisZoom(self):
        if self.YAxisRange >> 1 >= MinYAxisRange:
            self.YAxisRange >>= 1
            self.SetYAxisRange()

    def YAxisShrink(self):
        if self.YAxisRange << 1 <= MaxYAxisRange:
            self.YAxisRange <<= 1
            self.SetYAxisRange()

    def YAxisResetZero(self, event):
        self.YAxisOffset = 0

    def SetXAxisRange(self):
        if self.SysDataCount < self.XAxisRange:
            self.AxisX.setRange(0, self.XAxisRange)
        else:
            self.AxisX.setRange(self.SysDataCount - self.XAxisRange, self.SysDataCount)

    def SetYAxisRange(self):
        if self.SwitchAdaptiveFlag:
            self.AxisY.setMax(self.MaxValue)
            self.AxisY.setMin(self.MinValue)
        else:
            Offset = self.YAxisOffset / 400
            Offset *= self.YAxisRange
            self.AxisY.setRange(-self.YAxisRange - Offset, self.YAxisRange - Offset)

    def AddChannels(self, Name=''):
        if self.SeriesType == 0x00:  # 折线图
            LineSeries = QLineSeries()
            LineSeries.setUseOpenGL(True)
            LineSeries.setName(Name)
            self.Chart.addSeries(LineSeries)
            self.Chart.addAxis(self.AxisX, Qt.AlignBottom)
            self.Chart.addAxis(self.AxisY, Qt.AlignLeft)
            LineSeries.attachAxis(self.AxisX)
            LineSeries.attachAxis(self.AxisY)
            self.SeriesList.append(LineSeries)
        if self.SeriesType == 0x01:  # 样条线图
            SplineSeries = QSplineSeries()
            SplineSeries.setUseOpenGL(True)
            SplineSeries.setName(Name)
            self.Chart.addSeries(SplineSeries)
            self.Chart.addAxis(self.AxisX, Qt.AlignBottom)
            self.Chart.addAxis(self.AxisY, Qt.AlignLeft)
            SplineSeries.attachAxis(self.AxisX)
            SplineSeries.attachAxis(self.AxisY)
            self.SeriesList.append(SplineSeries)
        if self.SeriesType == 0x02:  # 条形图
            BarSet = QBarSet(Name)
            BarSet.append(0)
            self.BarSeries.append(BarSet)
            self.SeriesList.append(BarSet)
            self.Chart.addSeries(self.BarSeries)
            self.Chart.addAxis(self.AxisY, Qt.AlignLeft)
            self.BarSeries.attachAxis(self.AxisY)
            self.Chart.legend().setVisible(True)
            self.Chart.legend().setAlignment(Qt.AlignBottom)
        if self.SeriesType == 0x03:  # 饼图
            PieSeries = QPieSeries()
            PieSeries.setName(Name)
            self.Chart.addSeries(PieSeries)
            self.SeriesList.append(PieSeries)
        self.Channels = len(self.SeriesList)
        self.ChannelsLab.setText("通道数：%d" % len(self.SeriesList))

    def InputData(self, Data: bytes):
        if len(Data) == self.Channels * self.UnitChannelSize:
            # 获取数据并添加到各个通道
            for i in range(self.Channels):
                ChannelData = Data[i * self.UnitChannelSize: (i + 1) * self.UnitChannelSize]
                if self.DataType < 4:  # 无符号整数
                    ChannelData = int.from_bytes(ChannelData, 'little', signed=False)
                elif self.DataType < 8:  # 有符号整数
                    ChannelData = int.from_bytes(ChannelData, 'little', signed=True)
                else:  # 浮点数
                    pass
                # 记录最值
                if ChannelData > self.MaxValue:
                    self.MaxValue = ChannelData
                if ChannelData < self.MinValue:
                    self.MinValue = ChannelData
                # 将数据添加到通道
                if self.SeriesType == 0 or self.SeriesType == 1:
                    self.SeriesList[i].append(self.SysDataCount, ChannelData)
                if self.SeriesType == 2:
                    self.SeriesList[i].replace(0, ChannelData)
                # 达到最大数据量清除缓存
                if self.SysDataCount % MaxDataLen == 0 and self.SysDataCount > MaxDataLen:
                    self.SeriesList[i].removePoints(0, MaxDataLen)
            # X轴显示范围设置
            if self.SeriesType == 0 or self.SeriesType == 1:
                self.SetXAxisRange()
            # Y轴显示范围
            self.SetYAxisRange()
            # 计数+1
            self.SysDataCount += 1
        else:
            print(len(Data), self.Channels * self.UnitChannelSize)


if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    ui = MyWaveform(Name='Test')
    ui.AddChannels(Name='test1')
    ui.show()
    sys.exit(app.exec_())
