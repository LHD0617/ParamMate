import re
import sys
import serial
from PyQt5 import QtCore, QtGui, QtWidgets
import serial.tools.list_ports
from PyQt5.QtCore import QTimer

class Ui_MainWindow(object):
    port_status = False
    port_list = []
    baud_list = ['9600', '115200']
    ser = serial.Serial()
    timer = QTimer()
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(800, 600)
        MainWindow.setFixedSize(800, 600)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.port_configuration_gbox = QtWidgets.QGroupBox(self.centralwidget)
        self.port_configuration_gbox.setGeometry(QtCore.QRect(10, 10, 191, 251))
        self.port_configuration_gbox.setObjectName("port_configuration_gbox")
        self.port_lab = QtWidgets.QLabel(self.port_configuration_gbox)
        self.port_lab.setGeometry(QtCore.QRect(10, 30, 71, 21))
        self.port_lab.setObjectName("port_lab")
        self.port_cbox = QtWidgets.QComboBox(self.port_configuration_gbox)
        self.port_cbox.setGeometry(QtCore.QRect(100, 30, 81, 21))
        self.port_cbox.setObjectName("port_cbox")
        self.baud_lab = QtWidgets.QLabel(self.port_configuration_gbox)
        self.baud_lab.setGeometry(QtCore.QRect(10, 70, 71, 21))
        self.baud_lab.setObjectName("baud_lab")
        self.baud_cbox = QtWidgets.QComboBox(self.port_configuration_gbox)
        self.baud_cbox.setGeometry(QtCore.QRect(100, 70, 81, 21))
        self.baud_cbox.setObjectName("baud_cbox")
        self.baud_cbox.addItems(self.baud_list)
        self.baud_cbox.setCurrentIndex(1)
        self.refresh_port_pbtn = QtWidgets.QPushButton(self.port_configuration_gbox)
        self.refresh_port_pbtn.setGeometry(QtCore.QRect(50, 120, 91, 31))
        self.refresh_port_pbtn.setObjectName("refresh_port_pbtn")
        self.open_port_pbtn = QtWidgets.QPushButton(self.port_configuration_gbox)
        self.open_port_pbtn.setGeometry(QtCore.QRect(50, 170, 91, 31))
        self.open_port_pbtn.setObjectName("open_port_pbtn")
        self.raw_data_gbox = QtWidgets.QGroupBox(self.centralwidget)
        self.raw_data_gbox.setGeometry(QtCore.QRect(220, 10, 561, 251))
        self.raw_data_gbox.setObjectName("raw_data_gbox")
        self.raw_data_textEdit = QtWidgets.QTextEdit(self.raw_data_gbox)
        self.raw_data_textEdit.setGeometry(QtCore.QRect(10, 20, 541, 221))
        self.raw_data_textEdit.setObjectName("raw_data_textEdit")
        self.information_gbox = QtWidgets.QGroupBox(self.centralwidget)
        self.information_gbox.setGeometry(QtCore.QRect(10, 270, 771, 291))
        self.information_gbox.setObjectName("information_gbox")
        self.information_time_lab = QtWidgets.QLabel(self.information_gbox)
        self.information_time_lab.setGeometry(QtCore.QRect(30, 40, 111, 41))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.information_time_lab.setFont(font)
        self.information_time_lab.setStyleSheet("color: rgb(170, 0, 0);")
        self.information_time_lab.setTextFormat(QtCore.Qt.AutoText)
        self.information_time_lab.setAlignment(QtCore.Qt.AlignCenter)
        self.information_time_lab.setObjectName("information_time_lab")
        self.information_post_lab = QtWidgets.QLabel(self.information_gbox)
        self.information_post_lab.setGeometry(QtCore.QRect(230, 40, 111, 41))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.information_post_lab.setFont(font)
        self.information_post_lab.setStyleSheet("color: rgb(170, 0, 0);")
        self.information_post_lab.setTextFormat(QtCore.Qt.AutoText)
        self.information_post_lab.setAlignment(QtCore.Qt.AlignCenter)
        self.information_post_lab.setObjectName("information_post_lab")
        self.information_general_category_lab = QtWidgets.QLabel(self.information_gbox)
        self.information_general_category_lab.setGeometry(QtCore.QRect(430, 40, 111, 41))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.information_general_category_lab.setFont(font)
        self.information_general_category_lab.setStyleSheet("color: rgb(170, 0, 0);")
        self.information_general_category_lab.setTextFormat(QtCore.Qt.AutoText)
        self.information_general_category_lab.setAlignment(QtCore.Qt.AlignCenter)
        self.information_general_category_lab.setObjectName("information_general_category_lab")
        self.information_subclass_lab = QtWidgets.QLabel(self.information_gbox)
        self.information_subclass_lab.setGeometry(QtCore.QRect(630, 40, 111, 41))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.information_subclass_lab.setFont(font)
        self.information_subclass_lab.setStyleSheet("color: rgb(170, 0, 0);")
        self.information_subclass_lab.setTextFormat(QtCore.Qt.AutoText)
        self.information_subclass_lab.setAlignment(QtCore.Qt.AlignCenter)
        self.information_subclass_lab.setObjectName("information_subclass_lab")
        self.general_category_lab = QtWidgets.QLabel(self.information_gbox)
        self.general_category_lab.setGeometry(QtCore.QRect(430, 170, 151, 41))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.general_category_lab.setFont(font)
        self.general_category_lab.setStyleSheet("color: rgb(0, 170, 0);")
        self.general_category_lab.setTextFormat(QtCore.Qt.AutoText)
        self.general_category_lab.setAlignment(QtCore.Qt.AlignCenter)
        self.general_category_lab.setObjectName("general_category_lab")
        self.subclass_lab = QtWidgets.QLabel(self.information_gbox)
        self.subclass_lab.setGeometry(QtCore.QRect(630, 170, 151, 41))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.subclass_lab.setFont(font)
        self.subclass_lab.setStyleSheet("color: rgb(0, 170, 0);")
        self.subclass_lab.setTextFormat(QtCore.Qt.AutoText)
        self.subclass_lab.setAlignment(QtCore.Qt.AlignCenter)
        self.subclass_lab.setObjectName("subclass_lab")
        self.time_lab = QtWidgets.QLabel(self.information_gbox)
        self.time_lab.setGeometry(QtCore.QRect(30, 170, 151, 41))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.time_lab.setFont(font)
        self.time_lab.setStyleSheet("color: rgb(0, 170, 0);")
        self.time_lab.setTextFormat(QtCore.Qt.AutoText)
        self.time_lab.setAlignment(QtCore.Qt.AlignCenter)
        self.time_lab.setObjectName("time_lab")
        self.post_lab = QtWidgets.QLabel(self.information_gbox)
        self.post_lab.setGeometry(QtCore.QRect(230, 170, 151, 41))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.post_lab.setFont(font)
        self.post_lab.setStyleSheet("color: rgb(0, 170, 0);")
        self.post_lab.setTextFormat(QtCore.Qt.AutoText)
        self.post_lab.setAlignment(QtCore.Qt.AlignCenter)
        self.post_lab.setObjectName("post_lab")
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

        self.refresh_port_pbtn.clicked.connect(self.Refresh_serial_port)
        self.open_port_pbtn.clicked.connect(self.Open_serial_port)
        self.timer.timeout.connect(self.Receive_data)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "17届全国大学生智能汽车竞赛智能视觉组裁判系统"))
        self.port_configuration_gbox.setTitle(_translate("MainWindow", "串口配置"))
        self.port_lab.setText(_translate("MainWindow", "端口："))
        self.baud_lab.setText(_translate("MainWindow", "波特率"))
        self.refresh_port_pbtn.setText(_translate("MainWindow", "刷新串口"))
        self.open_port_pbtn.setText(_translate("MainWindow", "打开串口"))
        self.raw_data_gbox.setTitle(_translate("MainWindow", "原始数据"))
        self.information_gbox.setTitle(_translate("MainWindow", "信息"))
        self.information_time_lab.setText(_translate("MainWindow", "时间"))
        self.information_post_lab.setText(_translate("MainWindow", "坐标"))
        self.information_general_category_lab.setText(_translate("MainWindow", "大类"))
        self.information_subclass_lab.setText(_translate("MainWindow", "小类"))
        self.general_category_lab.setText(_translate("MainWindow", "None"))
        self.subclass_lab.setText(_translate("MainWindow", "None"))
        self.time_lab.setText(_translate("MainWindow", "None"))
        self.post_lab.setText(_translate("MainWindow", "None"))

    def Refresh_serial_port(self):
        com = list(serial.tools.list_ports.comports())
        self.port_list = []
        if len(com) <= 0:
            self.statusbar.showMessage('没有发现串口')
        else:
            self.statusbar.showMessage('发现%d个串口' % len(com))
            for i in range(0, len(com)):
                self.port_list.append(re.search('\(([^)]+)', str(com[i])).group(1))
        self.port_cbox.clear()
        self.port_cbox.addItems(self.port_list)

    def Open_serial_port(self):
        com = self.port_cbox.currentText()
        baud = int(self.baud_cbox.currentText())
        if not self.port_status:
            if com == '':
                self.statusbar.showMessage('请选择串口')
            else:
                try:
                    self.ser = serial.Serial(com, baud, timeout=0.015)
                except:
                    self.statusbar.showMessage('%s打开失败' % com)
                if self.ser.is_open:
                    self.statusbar.showMessage('%s打开成功' % com)
                    self.port_status = True
                    self.open_port_pbtn.setText('关闭串口')
                    self.refresh_port_pbtn.setEnabled(False)
                    self.port_cbox.setEnabled(False)
                    self.baud_cbox.setEnabled(False)
                    self.raw_data_textEdit.clear()
                    self.ser.flushInput()
                    self.timer.start(1)
                else:
                    self.statusbar.showMessage('%s打开失败' % com)
        else:
            self.port_status = False
            self.open_port_pbtn.setText('打开串口')
            self.refresh_port_pbtn.setEnabled(True)
            self.port_cbox.setEnabled(True)
            self.baud_cbox.setEnabled(True)
            self.statusbar.showMessage('%s已关闭' % com)
            self.ser.close()
            self.timer.stop()
            self.general_category_lab.setText("None")
            self.subclass_lab.setText("None")
            self.time_lab.setText("None")
            self.post_lab.setText("None")

    def Receive_data(self):
        try:
            data = str(self.ser.read(18).decode())
            if len(data) == 18:
                self.raw_data_textEdit.append(data)
                self.time_lab.setText(data[0:7])
                self.post_lab.setText('(%02d,%02d)' % (int(data[8:10]), int(data[11:13])))
                if data[-4] == '0':
                    self.general_category_lab.setText('没有目标')
                elif data[-4] == '1':
                    self.general_category_lab.setText('动物')
                    if data[-2] == '1':
                        self.subclass_lab.setText('狗')
                    elif data[-2] == '2':
                        self.subclass_lab.setText('马')
                    elif data[-2] == '3':
                        self.subclass_lab.setText('猫')
                    elif data[-2] == '4':
                        self.subclass_lab.setText('牛')
                    elif data[-2] == '5':
                        self.subclass_lab.setText('猪')
                    else:
                        self.subclass_lab.setText('错误！')
                elif data[-4] == '2':
                    self.general_category_lab.setText('水果')
                    if data[-2] == '1':
                        self.subclass_lab.setText('橙子')
                    elif data[-2] == '2':
                        self.subclass_lab.setText('苹果')
                    elif data[-2] == '3':
                        self.subclass_lab.setText('榴莲')
                    elif data[-2] == '4':
                        self.subclass_lab.setText('葡萄')
                    elif data[-2] == '5':
                        self.subclass_lab.setText('香蕉')
                    else:
                        self.subclass_lab.setText('错误！')
                elif data[-4] == '3':
                    self.general_category_lab.setText('交通工具')
                    if data[-2] == '1':
                        self.subclass_lab.setText('火车')
                    elif data[-2] == '2':
                        self.subclass_lab.setText('轮船')
                    elif data[-2] == '3':
                        self.subclass_lab.setText('飞机')
                    elif data[-2] == '4':
                        self.subclass_lab.setText('小轿车')
                    elif data[-2] == '5':
                        self.subclass_lab.setText('大客车')
                    else:
                        self.subclass_lab.setText('错误！')
                elif data[-4] == '9':
                    self.general_category_lab.setText('正在搬运')
                else:
                    self.general_category_lab.setText('错误！')
        except:
            self.port_status = False
            self.port_cbox.clear()
            self.ser.close()
            self.open_port_pbtn.setText('打开串口')
            self.refresh_port_pbtn.setEnabled(True)
            self.port_cbox.setEnabled(True)
            self.baud_cbox.setEnabled(True)
            self.statusbar.showMessage('严重错误！')
            self.timer.stop()
            self.general_category_lab.setText("None")
            self.subclass_lab.setText("None")
            self.time_lab.setText("None")
            self.post_lab.setText("None")


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())


# pyinstaller -F -w main.py -n 17届全国大学生智能汽车竞赛