#!/usr/bin/env python
# -*- encoding: utf-8 -*-
"""
@File    :   Image.py
@Contact :   15663678208
@Modify Time      @Author    @Version    @Desciption
------------      -------    --------    -----------
2022/8/7 15:41   LHD      1.0         None
"""
import os
import sys
import numpy as np
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtCore import pyqtSignal
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtWidgets import QGroupBox
from MessageClass import MessageClass

ImageTypeStrList = ('Binarization', 'Grayscale', 'RGB565')


class MyImage(QGroupBox):
    ID: int  # 控件ID
    Name: str  # 控件名称
    ImageType: int  # 控件类型
    ImageHeight: int  # 图像高度
    ImageWidth: int  # 图像宽度
    Count: int  # 图像序号
    Image: QImage  # 图像
    LogSignal = pyqtSignal(MessageClass)

    def __init__(self, ID=0, Name='Unknown Name', ImageType=0, Width=0, Height=0):
        super(MyImage, self).__init__()
        self.ID = ID
        self.Name = Name.strip(b'\x00'.decode())
        self.ImageType = ImageType
        self.ImageHeight = Height
        self.ImageWidth = Width
        self.Count = 0
        self.setupUi(self)
        self.setTitle(Name)

    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(800, 600)
        self.gridLayout = QtWidgets.QGridLayout(self)
        self.gridLayout.setObjectName("gridLayout")
        self.ImageLab = QtWidgets.QLabel()
        self.ImageLab.setEnabled(True)
        self.ImageLab.setMinimumSize(QtCore.QSize(0, 0))
        self.ImageLab.setAlignment(QtCore.Qt.AlignCenter)
        self.ImageLab.setObjectName("ImageLab")
        self.ImageLab.mouseDoubleClickEvent = self.SaveImage
        self.gridLayout.addWidget(self.ImageLab, 1, 0, 1, 5)
        self.ImageGridCbox = QtWidgets.QCheckBox()
        self.ImageGridCbox.setObjectName("ImageGridCbox")
        self.gridLayout.addWidget(self.ImageGridCbox, 2, 4, 1, 1)
        self.SaveImageCbox = QtWidgets.QCheckBox()
        self.SaveImageCbox.setObjectName("SaveImageCbox")
        self.gridLayout.addWidget(self.SaveImageCbox, 2, 3, 1, 1)
        self.AdaptCbox = QtWidgets.QCheckBox()
        self.AdaptCbox.setObjectName("AdaptCbox")
        self.gridLayout.addWidget(self.AdaptCbox, 2, 2, 1, 1)
        self.IDLab = QtWidgets.QLabel()
        self.IDLab.setMaximumSize(QtCore.QSize(16777215, 20))
        self.IDLab.setObjectName("IDLab")
        self.gridLayout.addWidget(self.IDLab, 0, 0, 1, 1)
        self.ImageWidthLab = QtWidgets.QLabel()
        self.ImageWidthLab.setMaximumSize(QtCore.QSize(16777215, 20))
        self.ImageWidthLab.setObjectName("ImageWidthLab")
        self.gridLayout.addWidget(self.ImageWidthLab, 0, 4, 1, 1)
        self.ImageHeightLab = QtWidgets.QLabel()
        self.ImageHeightLab.setMaximumSize(QtCore.QSize(16777215, 20))
        self.ImageHeightLab.setObjectName("ImageHeightLab")
        self.gridLayout.addWidget(self.ImageHeightLab, 0, 3, 1, 1)
        self.ImageTypeLab = QtWidgets.QLabel()
        self.ImageTypeLab.setMaximumSize(QtCore.QSize(16777215, 20))
        self.ImageTypeLab.setObjectName("ImageTypeLab")
        self.gridLayout.addWidget(self.ImageTypeLab, 0, 1, 1, 2)

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.ImageHeightLab.setText(_translate("Form", "图像高度：%d" % self.ImageHeight))
        self.IDLab.setText(_translate("Form", "ID：%d" % self.ID))
        self.ImageLab.setText(_translate("Form", "Image"))
        self.ImageGridCbox.setText(_translate("Form", "图像栅格"))
        self.SaveImageCbox.setText(_translate("Form", "保存图像"))
        self.AdaptCbox.setText(_translate("Form", "适应窗口"))
        self.ImageWidthLab.setText(_translate("Form", "图像宽度：%d" % self.ImageWidth))
        self.ImageTypeLab.setText(_translate("Form", "图像类型：%s" % ImageTypeStrList[self.ImageType]))

    def InputData(self, Data: bytes):
        if self.ImageType == 0:
            DataLen = self.ImageHeight * self.ImageWidth // 8
            if self.ImageHeight * self.ImageWidth % 8 > 0:
                DataLen += 1
        else:
            DataLen = self.ImageHeight * self.ImageWidth * self.ImageType
        if len(Data) == DataLen:
            if self.ImageType == 0:     # 二值化图
                image = np.zeros((self.ImageHeight * 5, self.ImageWidth * 5), np.uint8)
                for i in range(self.ImageHeight):
                    for j in range(self.ImageWidth):
                        if Data[(i * self.ImageWidth + j) // 8] & (0b10000000 >> ((i * self.ImageWidth + j) % 8)):
                            image[i * 5:(i + 1) * 5, j * 5:(j + 1) * 5] = 255
                        else:
                            image[i * 5:(i + 1) * 5, j * 5:(j + 1) * 5] = 0
                if self.ImageGridCbox.isChecked():
                    for i in range(5, int(self.ImageHeight) * 5, 5):
                        image[i, 0:int(self.ImageWidth) * 5] = 100
                    for i in range(5, int(self.ImageWidth) * 5, 5):
                        image[0:int(self.ImageHeight) * 5, i] = 100
                self.Image = QImage(image, image.shape[1], image.shape[0], image.shape[1], QImage.Format_Grayscale8)
            if self.ImageType == 1:     # 灰度图
                image = np.zeros((self.ImageHeight * 5, self.ImageWidth * 5), np.uint8)
                for i in range(self.ImageHeight):
                    for j in range(self.ImageWidth):
                        image[i * 5: (i + 1) * 5, j * 5: (j + 1) * 5] = Data[i * self.ImageWidth + j]
                if self.ImageGridCbox.isChecked():
                    for i in range(5, int(self.ImageHeight) * 5, 5):
                        image[i, 0:int(self.ImageWidth) * 5] = 100
                    for i in range(5, int(self.ImageWidth) * 5, 5):
                        image[0:int(self.ImageHeight) * 5, i] = 100
                self.Image = QImage(image, image.shape[1], image.shape[0], image.shape[1], QImage.Format_Grayscale8)
            if self.ImageType == 2:     # RGB565彩图
                image = np.zeros((self.ImageHeight * 5, self.ImageWidth * 5), np.uint16)
                for i in range(self.ImageHeight):
                    for j in range(self.ImageWidth):
                        Uint16Data = int.from_bytes(
                            Data[i * self.ImageWidth * 2 + j * 2: i * self.ImageWidth * 2 + (j * 2) + 1 + 2], 'little')
                        image[i * 5: (i + 1) * 5, j * 5: (j + 1) * 5] = Uint16Data
                if self.ImageGridCbox.isChecked():
                    for i in range(5, int(self.ImageHeight) * 5, 5):
                        image[i, 0:int(self.ImageWidth) * 5] = 100
                    for i in range(5, int(self.ImageWidth) * 5, 5):
                        image[0:int(self.ImageHeight) * 5, i] = 16904
                self.Image = QImage(image, self.ImageWidth * 5, self.ImageHeight * 5, QImage.Format_RGB16)
            self.ImageLab.setPixmap(QPixmap.fromImage(self.Image))
            if self.AdaptCbox.isChecked():
                self.ImageLab.setScaledContents(True)
            else:
                self.ImageLab.setScaledContents(False)
            if self.SaveImageCbox.isChecked():
                self.SaveImage(0)
            self.Count += 1
        else:
            self.LogSignal.emit(MessageClass(self.Name, '数据接收错误'))

    def SaveImage(self, event):
        if not os.path.exists('%s_Save_Images' % self.Name):
            os.mkdir('%s_Save_Images' % self.Name)
        self.Image.save('%s_Save_Images/%d.jpg' % (self.Name, self.Count))
        if not type(event) == int:
            self.LogSignal.emit(MessageClass(self.Name, '%d.jpg保存成功' % self.Count))


if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    ui = MyImage()
    ui.show()
    sys.exit(app.exec_())



