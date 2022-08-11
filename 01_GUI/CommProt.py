#!/usr/bin/env python
# -*- encoding: utf-8 -*-
"""
@File    :   CommProt.py
@Contact :   15663678208
@Modify Time      @Author    @Version    @Desciption
------------      -------    --------    -----------
2022/8/6 22:23   LHD      1.0         None
"""

from PyQt5.QtCore import pyqtSignal, QObject


class RevDataPackageClass:
    RevEnd: bool  # 停止状态
    TranFlag: bool  # 转义标志位
    Head: int  # 消息帧头
    Type: int  # 消息类型
    ID: int  # ID
    Length: int  # 消息长度
    Data: bytes  # 消息数据
    RevLen: int  # 接收数据长度

    def __init__(self):
        self.ResetPackage()

    def ResetPackage(self):
        self.RevEnd = False
        self.TranFlag = False
        self.Head = 0
        self.Type = 0
        self.ID = 0
        self.Length = 0
        self.Data = bytes()
        self.RevLen = 0


class CommProtClass(QObject):
    RevDataPackage = RevDataPackageClass()
    RevFinishSignal = pyqtSignal(RevDataPackageClass)

    def InputByte(self, Byte):
        if not self.RevDataPackage.RevEnd:
            if type(Byte) == bytes:
                Byte = int.from_bytes(Byte, byteorder='big')
            # 帧头
            if Byte == 0x7a:
                self.RevDataPackage.ResetPackage()
                self.RevDataPackage.Head = 0x7a
                self.RevDataPackage.RevLen += 1
            # 转义
            elif Byte == 0x7b:
                self.RevDataPackage.TranFlag = True
            else:
                if self.RevDataPackage.TranFlag:
                    self.RevDataPackage.TranFlag = False
                    if Byte == 0x00 or Byte == 0x01:
                        if self.RevDataPackage.Head == 0x7a:
                            self.RevDataPackage.RevLen += 1
                            # 帧类型
                            if self.RevDataPackage.RevLen == 2:
                                self.RevDataPackage.Type = 0x7a + Byte
                            # ID
                            elif self.RevDataPackage.RevLen == 3:
                                self.RevDataPackage.ID = (0x7a + Byte)
                            # 帧长度低八位
                            elif self.RevDataPackage.RevLen == 4:
                                self.RevDataPackage.Length += (0x7a + Byte)
                            # 帧长度高八位
                            elif self.RevDataPackage.RevLen == 5:
                                self.RevDataPackage.Length += (0x7a + Byte) << 8
                            # 数据区
                            else:
                                # 数区超出包长度
                                self.RevDataPackage.Data += (0x7a + Byte).to_bytes(1, 'big')
                                if self.RevDataPackage.RevLen >= self.RevDataPackage.Length + 5:
                                    self.RevDataPackage.RevEnd = True
                                    self.RevFinishSignal.emit(self.RevDataPackage)
                                    self.RevDataPackage.ResetPackage()
                    # 转义出现错误
                    else:
                        self.RevDataPackage.ResetPackage()
                else:
                    if self.RevDataPackage.Head == 0x7a:
                        self.RevDataPackage.RevLen += 1
                        if self.RevDataPackage.RevLen == 2:
                            self.RevDataPackage.Type = Byte
                        elif self.RevDataPackage.RevLen == 3:
                            self.RevDataPackage.ID = Byte
                        elif self.RevDataPackage.RevLen == 4:
                            self.RevDataPackage.Length += Byte
                        elif self.RevDataPackage.RevLen == 5:
                            self.RevDataPackage.Length += Byte << 8
                        else:
                            self.RevDataPackage.Data += Byte.to_bytes(1, byteorder='big')
                            if self.RevDataPackage.RevLen >= self.RevDataPackage.Length + 5:
                                self.RevDataPackage.RevEnd = True
                                self.RevFinishSignal.emit(self.RevDataPackage)
                                self.RevDataPackage.ResetPackage()


# if __name__ == '__main__':
#     with open('CreateWaveformData.txt', mode='r') as Fp:
#         DataList = Fp.readlines()
#     for data in DataList:
#         BytesData += bytes.fromhex(data[0:-1].replace(' ', ''))
#     CommProt = CommProtClass()
#     for byte in BytesData:
#         CommProt.InputByte(byte)
#         CommProt.RevDataPackage.RevEnd = False
#
#
