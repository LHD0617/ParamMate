#!/usr/bin/env python
# -*- encoding: utf-8 -*-
"""
@File    :   Image.py
@Contact :   15663678208
@Modify Time      @Author    @Version    @Desciption
------------      -------    --------    -----------
2022/8/7 15:41   LHD      1.0         None
"""
import sys

from PyQt5 import QtCore, QtWidgets
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtWidgets import QGroupBox

ImageTypeStrList = ('Binarization', 'Grayscale', 'RGB565', 'RGB888')


class MyImage(QGroupBox):
    ID: int  # 控件ID
    ImageType: int  # 控件类型
    ImageHeight: int  # 图像高度
    ImageWidth: int  # 图像宽度

    def __init__(self, ID=0, Name='', ImageType=0, Width=0, Height=0):
        super(MyImage, self).__init__()
        self.ID = ID
        self.ImageType = ImageType
        self.ImageHeight = Height
        self.ImageWidth = Width
        self.setupUi(self)
        self.setTitle(Name)

    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(800, 600)
        self.gridLayout = QtWidgets.QGridLayout(self)
        self.gridLayout.setObjectName("gridLayout")
        self.ImageLab = QtWidgets.QLabel()
        self.ImageLab.setEnabled(True)
        self.ImageLab.setMinimumSize(QtCore.QSize(240, 600))
        self.ImageLab.setAlignment(QtCore.Qt.AlignCenter)
        self.ImageLab.setObjectName("ImageLab")
        self.gridLayout.addWidget(self.ImageLab, 1, 0, 1, 5)
        self.ImageGridCbox = QtWidgets.QCheckBox()
        self.ImageGridCbox.setObjectName("ImageGridCbox")
        self.gridLayout.addWidget(self.ImageGridCbox, 2, 4, 1, 1)
        self.ColorRevCbox = QtWidgets.QCheckBox()
        self.ColorRevCbox.setObjectName("ColorRevCbox")
        self.gridLayout.addWidget(self.ColorRevCbox, 2, 3, 1, 1)
        self.SaveImageCbox = QtWidgets.QCheckBox()
        self.SaveImageCbox.setObjectName("SaveImageCbox")
        self.gridLayout.addWidget(self.SaveImageCbox, 2, 2, 1, 1)
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
        self.ColorRevCbox.setText(_translate("Form", "颜色反转"))
        self.SaveImageCbox.setText(_translate("Form", "保存图像"))
        self.ImageWidthLab.setText(_translate("Form", "图像宽度：%d" % self.ImageWidth))
        self.ImageTypeLab.setText(_translate("Form", "图像类型：%s" % ImageTypeStrList[self.ImageType]))

    def InputData(self, Data: bytes):
        myqimage = QImage(Data, self.ImageWidth, self.ImageHeight, QImage.Format_Grayscale8)
        self.ImageLab.setPixmap(QPixmap.fromImage(myqimage))
        self.ImageLab.setScaledContents(True)

if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    ui = MyImage()
    ui.show()
    sys.exit(app.exec_())



