#!/usr/bin/env python
# -*- encoding: utf-8 -*-
"""
@File    :   MessageClass.py    
@Contact :   15663678208
@Modify Time      @Author    @Version    @Desciption
------------      -------    --------    -----------
2022/8/11 11:52   LHD      1.0         None
"""
import time


class MessageClass:
    Name: str  # 对象名称
    Message: str  # 消息内容
    Time: str  # 消息时间

    def __init__(self, Name='Unknown Name', Message=''):
        """
        初始化函数
        :param Name:
        :param Message:
        """
        self.Name = Name
        self.Time = time.strftime('%H:%M:%S', time.localtime())
        self.Message = '%s  %32s:%s' % (self.Time, self.Name, Message)