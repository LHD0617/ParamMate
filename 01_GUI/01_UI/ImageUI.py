# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ImageUI.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(800, 600)
        self.gridLayout_2 = QtWidgets.QGridLayout(Form)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.groupBox = QtWidgets.QGroupBox(Form)
        self.groupBox.setTitle("")
        self.groupBox.setObjectName("groupBox")
        self.gridLayout = QtWidgets.QGridLayout(self.groupBox)
        self.gridLayout.setObjectName("gridLayout")
        self.ImageLab = QtWidgets.QLabel(self.groupBox)
        self.ImageLab.setEnabled(True)
        self.ImageLab.setMinimumSize(QtCore.QSize(240, 180))
        self.ImageLab.setAlignment(QtCore.Qt.AlignCenter)
        self.ImageLab.setObjectName("ImageLab")
        self.gridLayout.addWidget(self.ImageLab, 1, 0, 1, 5)
        self.ImageGridCbox = QtWidgets.QCheckBox(self.groupBox)
        self.ImageGridCbox.setObjectName("ImageGridCbox")
        self.gridLayout.addWidget(self.ImageGridCbox, 2, 4, 1, 1)
        self.ColorRevCbox = QtWidgets.QCheckBox(self.groupBox)
        self.ColorRevCbox.setObjectName("ColorRevCbox")
        self.gridLayout.addWidget(self.ColorRevCbox, 2, 3, 1, 1)
        self.SaveImageCbox = QtWidgets.QCheckBox(self.groupBox)
        self.SaveImageCbox.setObjectName("SaveImageCbox")
        self.gridLayout.addWidget(self.SaveImageCbox, 2, 2, 1, 1)
        self.IDLab = QtWidgets.QLabel(self.groupBox)
        self.IDLab.setMaximumSize(QtCore.QSize(16777215, 20))
        self.IDLab.setObjectName("IDLab")
        self.gridLayout.addWidget(self.IDLab, 0, 0, 1, 1)
        self.ImageWidthLab = QtWidgets.QLabel(self.groupBox)
        self.ImageWidthLab.setMaximumSize(QtCore.QSize(16777215, 20))
        self.ImageWidthLab.setObjectName("ImageWidthLab")
        self.gridLayout.addWidget(self.ImageWidthLab, 0, 4, 1, 1)
        self.ImageHeightLab = QtWidgets.QLabel(self.groupBox)
        self.ImageHeightLab.setMaximumSize(QtCore.QSize(16777215, 20))
        self.ImageHeightLab.setObjectName("ImageHeightLab")
        self.gridLayout.addWidget(self.ImageHeightLab, 0, 3, 1, 1)
        self.ImageTypeLab = QtWidgets.QLabel(self.groupBox)
        self.ImageTypeLab.setMaximumSize(QtCore.QSize(16777215, 20))
        self.ImageTypeLab.setObjectName("ImageTypeLab")
        self.gridLayout.addWidget(self.ImageTypeLab, 0, 1, 1, 2)
        self.gridLayout_2.addWidget(self.groupBox, 0, 0, 1, 1)

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.ImageLab.setText(_translate("Form", "Image"))
        self.ImageGridCbox.setText(_translate("Form", "图像栅格"))
        self.ColorRevCbox.setText(_translate("Form", "颜色反转"))
        self.SaveImageCbox.setText(_translate("Form", "保存图像"))
        self.IDLab.setText(_translate("Form", "ID："))
        self.ImageWidthLab.setText(_translate("Form", "图像宽度："))
        self.ImageHeightLab.setText(_translate("Form", "图像高度："))
        self.ImageTypeLab.setText(_translate("Form", "图像类型："))
