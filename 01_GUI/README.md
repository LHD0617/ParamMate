# GUI
为了兼容Windows7 开发环境选择Python3.6

## 1.安装环境

### Requirements一键安装

**Requirements - 必要条件**

- Python3.6

在 01_GUI 路径下打开cmd（若Python环境为Anaconda虚拟环境请事先激活相应环境）运行：

`pip install -r requirements.txt`

进行环境一键安装


------------


### 单个安装

**若一键安装出现问题也可选择单个安装**

	altgraph==0.17.2
	certifi==2021.5.30
	future==0.18.2
	importlib-metadata==4.8.3
	iso8601==1.0.2
	numpy==1.19.5
	packaging==21.3
	pefile==2022.5.30
	pyinstaller==4.10
	pyinstaller-hooks-contrib==2022.0
	pyparsing==3.0.9
	PyQt5==5.15.6
	PyQt5-Qt5==5.15.2
	PyQt5-sip==12.9.1
	PyQtChart==5.15.5
	PyQtChart-Qt5==5.15.2
	pyserial==3.5
	pywin32-ctypes==0.2.0
	PyYAML==6.0
	QDarkStyle==3.1
	QtPy==2.0.1
	serial==0.0.97
	typing_extensions==4.1.1
	wincertstore==0.2
	zipp==3.6.0

## 2.项目结构

	----.\
		|----01_UI\												//UI文件
		|    |----ImageUI.py
		|    |----ImageUI.ui
		|    |----ParamMate_Tools_UI.py
		|    |----ParamMate_Tools_UI.ui
		|    |----ParamUI.py
		|    |----ParamUI.ui
		|    |----SerialToolUI.py
		|    |----SerialToolUI.ui
		|    |----WaveformWidgetUI.py
		|    |----WaveformWidgetUI.ui
		|----02_Icon\											//图标文件
		|    |----1.ico
		|    |----1.png
		|    |----2.ico
		|    |----2.png
		|    |----MakeIcon.qrc
		|----CommProt.py									    //协议栈驱动
		|----Icon_rc.py											//图标素材文件
		|----Image.py											//图传控件
		|----MainWindow.py								        //主窗口
		|----MakePathLib.py								        //生成路径结构脚本
		|----MessageClass.py							        //消息类
		|----Param.py										    //参数控件
		|----pyinstaller.txt								    //cmd打包命令
		|----requirements.txt							        //环境依赖
		|----SerialTool.py									    //串口接收工具
		|----SerialToolConfigure.ini				            //串口接收工具配置文件
		|----Waveform.py								        //示波控件





