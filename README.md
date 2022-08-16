<p><strong><strong>ParamMate使用说明</strong></strong></p>
<p>&nbsp;</p>
<p>目录</p>
<p><a href="#_Toc8129 ">更新说明 </a></p>
<p><a href="#_Toc32398 ">一、 简介 </a></p>
<p><a href="#_Toc6137 ">二、 程序移植 </a></p>
<p><a href="#_Toc7213 ">2.1文件移植 </a></p>
<p><a href="#_Toc2148 ">2.2接口移植 </a></p>
<p><a href="#_Toc23226 ">三、 SDK说明 </a></p>
<p><a href="#_Toc23160 ">3.1宏定义说明 </a></p>
<p><a href="#_Toc1009 ">3.2枚举说明 </a></p>
<p><a href="#_Toc9881 ">3.2.1参数读写类型枚举 </a></p>
<p><a href="#_Toc21976 ">3.2.2数据类型枚举 </a></p>
<p><a href="#_Toc25889 ">3.2.3示波线条类型枚举 </a></p>
<p><a href="#_Toc30758 ">3.2.4图像类型枚举 </a></p>
<p><a href="#_Toc29863 ">3.3结构体说明 </a></p>
<p><a href="#_Toc13797 ">3.3.1参数控件结构体 </a></p>
<p><a href="#_Toc1940 ">3.3.2示波控件结构体 </a></p>
<p><a href="#_Toc25921 ">3.3.2图传控件结构体 </a></p>
<p><a href="#_Toc23362 ">3.4函数说明 </a></p>
<p><a href="#_Toc30360 ">3.4.1复位窗口 </a></p>
<p><a href="#_Toc27964 ">3.4.2复位窗口 </a></p>
<p><a href="#_Toc11595 ">3.4.3创建参数控件 </a></p>
<p><a href="#_Toc18267 ">3.4.4创建参数通道 </a></p>
<p><a href="#_Toc22501 ">3.4.5创建示波控件 </a></p>
<p><a href="#_Toc457 ">3.4.6创建示波通道 </a></p>
<p><a href="#_Toc19079 ">3.4.7创建图传控件 </a></p>
<p><a href="#_Toc21052 ">3.4.8发送参数控件数据 </a></p>
<p><a href="#_Toc13765 ">3.4.9发送示波控件数据 </a></p>
<p><a href="#_Toc31201 ">3.4.10发送图传控件数据 </a></p>
<p><a href="#_Toc1365 ">3.4.11回传数据处理函数 </a></p>
<p><a href="#_Toc12243 ">四、 使用方法 </a></p>
<p><a href="#_Toc3385 ">4.1上位机使用方法 </a></p>
<p><a href="#_Toc21522 ">4.1.1上位机布局介绍 </a></p>
<p><a href="#_Toc16726 ">4.1.2 MainWindow介绍 </a></p>
<p><a href="#_Toc22350 ">4.1.3图传控件介绍 </a></p>
<p><a href="#_Toc21132 ">4.1.4示波控件介绍 </a></p>
<p><a href="#_Toc26124 ">4.1.5参数控件介绍 </a></p>
<p><a href="#_Toc9681 ">4.2下位机使用方法 </a></p>
<p><a href="#_Toc6633 ">4.2.1下位机初始化流程 </a></p>
<p><a href="#_Toc31961 ">4.2.2下位机发送数据流程 </a></p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<h1><a name="_Toc8129"></a><strong>更新说明</strong></h1>
<table>
<tbody>
<tr>
<td width="142">
<p>版本</p>
</td>
<td width="142">
<p>作者</p>
</td>
<td width="142">
<p>时间</p>
</td>
<td width="142">
<p>备注</p>
</td>
</tr>
<tr>
<td width="142">
<p>V1.0.0</p>
</td>
<td width="142">
<p>满心欢喜</p>
</td>
<td width="142">
<p>20220812</p>
</td>
<td width="142">
<p>初始版本</p>
</td>
</tr>
</tbody>
</table>
<p>&nbsp;</p>
<h1><a name="_Toc32398"></a>一、<strong>简介</strong></h1>
<p>ParamMate是一个集调参、示波、图传的多功能调试助手。采取模块化的设计思路将各个功能以控件的形式拼装组合使用，用户可以根据下位机的不同初始化语句来DIY上位机页面组成而无需像传统调试助手一样需要两头配置（配置下位机之后还要再上位机进行相应配置），这样可以大大提升调试效率。</p>
<p>ParamMate采用自定义通信协议，可承载于多种通信方式如：串口、IIC、SPI、UART、USB、CAN、SDIO、WIFI等，这样无需关心具体数据传输是如何实现的只需要将通信数据完整传输到上位机即可。就像计算机网络中应用层无需关心物理层是如何实现传输的。封装好的通信协议栈，用户只需要将数据IO接口配置好，就可以实现调用SDK实现所有功能。</p>
<p>ParamMate最大支持一个32通道调参控件、三个8通道示波控件、两个图传控件。支持读模式、写模式、读写模式调参，支持折线图、样条线图、条形图示波，支持二值化图、灰度图、RGB565彩图等图传。</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<h1><a name="_Toc6137"></a>二、<strong>程序移植</strong></h1>
<h2><a name="_Toc7213"></a><strong>2.1文件移植</strong></h2>
<p>①将ParamMate.lib、PM_CommProt.h、ParamMate.h三个文件放入工程路径下任意位置（若为逐飞驱动库可将其放在Project\CODE文件夹下）。</p>
<p>②打开工程将ParamMate.lib、PM_CommProt.h、ParamMate.h添加到工程当中。</p>
<p>③将PM_CommProt.h、ParamMate.h文件路径添加至工程头文件路径（若为逐飞驱动库放入CODE文件夹下无需此操作）。</p>
<h2><a name="_Toc2148"></a><strong>2.2接口移植</strong></h2>
<p>①打开PM_CommProt.h文件将PM_SendByte(dat)宏定义修改为自己的UART输出数据函数。</p>
<p>&nbsp;</p>
<p>②若需要参数控件下传数据还需适配PM_RevHandle函数，若不需要无需适配。</p>
<p>将PM_RevHandle函数放入串口接收中断中将参数控件结构体指针与接收的数据传入函数即可（若不放在中断服务函数也可以，只要确保每次UART接收数据可以正确传入函数即可）。</p>
<p>&nbsp;</p>
<h1><a name="_Toc23226"></a>三、<strong>SDK说明</strong></h1>
<p>在SDK使用过程中创建的控件结构体为Malloc生成，会占用部分静态区内存，可能会导致Malloc申请失败，请在创建控件之后判断一下控件地址是否为PM_NULL，若为PM_NULL则创建失败。</p>
<p>所有的控件结构体存储着控件的所有信息，创建成功返回的结构体指针建议存储在全局变量，也存在局部变量中，但请注意变量的作用域。</p>
<h2><a name="_Toc23160"></a><strong>3.1宏定义说明</strong></h2>
<table>
<tbody>
<tr>
<td width="189">
<p>名称</p>
</td>
<td width="189">
<p>数值</p>
</td>
<td width="189">
<p>描述</p>
</td>
</tr>
<tr>
<td width="189">
<p>REV_HANDLE</p>
</td>
<td width="189">
<p>1</p>
</td>
<td width="189">
<p>是否开启回传数据</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_MAIN_WINDOW_ID</p>
</td>
<td width="189">
<p>255</p>
</td>
<td width="189">
<p>主窗口ID</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_MAX_NAME_LEN</p>
</td>
<td width="189">
<p>32</p>
</td>
<td width="189">
<p>名称最大字节数</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_MAX_PARAM</p>
</td>
<td width="189">
<p>1</p>
</td>
<td width="189">
<p>最大支持参数控件数</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_MAX_WAVEFORM</p>
</td>
<td width="189">
<p>3</p>
</td>
<td width="189">
<p>最大支持示波控件数</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_MAX_IMAGE</p>
</td>
<td width="189">
<p>2</p>
</td>
<td width="189">
<p>最大支持图传控件数</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_MAX_PARAMCANNELS</p>
</td>
<td width="189">
<p>32</p>
</td>
<td width="189">
<p>参数最大通道数</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_MAX_WAVEFORMCANNELS</p>
</td>
<td width="189">
<p>8</p>
</td>
<td width="189">
<p>示波最大通道数</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_MAX_WIDTH</p>
</td>
<td width="189">
<p>188</p>
</td>
<td width="189">
<p>图像最大宽度</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_MAX_HEIGHT</p>
</td>
<td width="189">
<p>120</p>
</td>
<td width="189">
<p>图像最大高度</p>
</td>
</tr>
</tbody>
</table>
<h2><a name="_Toc1009"></a><strong>3.2枚举说明</strong></h2>
<h3><a name="_Toc9881"></a><strong>3.2.1参数读写类型枚举</strong></h3>
<table>
<tbody>
<tr>
<td colspan="3" width="568">
<p><strong><strong>RWMode_Type</strong></strong></p>
</td>
</tr>
<tr>
<td width="189">
<p>名称</p>
</td>
<td width="189">
<p>数值</p>
</td>
<td width="189">
<p>描述</p>
</td>
</tr>
<tr>
<td width="189">
<p>R_Type</p>
</td>
<td width="189">
<p>1</p>
</td>
<td width="189">
<p>只读类型</p>
</td>
</tr>
<tr>
<td width="189">
<p>W_Type</p>
</td>
<td width="189">
<p>2</p>
</td>
<td width="189">
<p>只写类型</p>
</td>
</tr>
<tr>
<td width="189">
<p>RW_Type</p>
</td>
<td width="189">
<p>3</p>
</td>
<td width="189">
<p>读写类型</p>
</td>
</tr>
</tbody>
</table>
<p>&nbsp;</p>
<h3><a name="_Toc21976"></a><strong>3.2.2数据类型枚举</strong></h3>
<table>
<tbody>
<tr>
<td colspan="3" width="568">
<p><strong><strong>Data_Type</strong></strong></p>
</td>
</tr>
<tr>
<td width="189">
<p>名称</p>
</td>
<td width="189">
<p>数值</p>
</td>
<td width="189">
<p>描述</p>
</td>
</tr>
<tr>
<td width="189">
<p>uint8_Type</p>
</td>
<td width="189">
<p>0</p>
</td>
<td width="189">
<p>uint8型</p>
</td>
</tr>
<tr>
<td width="189">
<p>uint16_Type</p>
</td>
<td width="189">
<p>1</p>
</td>
<td width="189">
<p>uint16型</p>
</td>
</tr>
<tr>
<td width="189">
<p>uint32_Type</p>
</td>
<td width="189">
<p>2</p>
</td>
<td width="189">
<p>uint32型</p>
</td>
</tr>
<tr>
<td width="189">
<p>int8_Type</p>
</td>
<td width="189">
<p>3</p>
</td>
<td width="189">
<p>int8型</p>
</td>
</tr>
<tr>
<td width="189">
<p>int16_Type</p>
</td>
<td width="189">
<p>4</p>
</td>
<td width="189">
<p>int16型</p>
</td>
</tr>
<tr>
<td width="189">
<p>int32_Type</p>
</td>
<td width="189">
<p>5</p>
</td>
<td width="189">
<p>int32型</p>
</td>
</tr>
<tr>
<td width="189">
<p>float_Type</p>
</td>
<td width="189">
<p>6</p>
</td>
<td width="189">
<p>float型</p>
</td>
</tr>
</tbody>
</table>
<h3><a name="_Toc25889"></a><strong>3.2.3示波线条类型枚举</strong></h3>
<table>
<tbody>
<tr>
<td colspan="3" width="568">
<p><strong><strong>Series_Type</strong></strong></p>
</td>
</tr>
<tr>
<td width="189">
<p>名称</p>
</td>
<td width="189">
<p>数值</p>
</td>
<td width="189">
<p>描述</p>
</td>
</tr>
<tr>
<td width="189">
<p>LineSeries_Type</p>
</td>
<td width="189">
<p>0</p>
</td>
<td width="189">
<p>折线图</p>
</td>
</tr>
<tr>
<td width="189">
<p>SplineSeries_Type</p>
</td>
<td width="189">
<p>1</p>
</td>
<td width="189">
<p>样条线图</p>
</td>
</tr>
<tr>
<td width="189">
<p>BarSeries_Type</p>
</td>
<td width="189">
<p>2</p>
</td>
<td width="189">
<p>条形图</p>
</td>
</tr>
</tbody>
</table>
<h3><a name="_Toc30758"></a><strong>3.2.4图像类型枚举</strong></h3>
<table>
<tbody>
<tr>
<td colspan="3" width="568">
<p><strong><strong>Image_Type</strong></strong></p>
</td>
</tr>
<tr>
<td width="189">
<p>名称</p>
</td>
<td width="189">
<p>数值</p>
</td>
<td width="189">
<p>描述</p>
</td>
</tr>
<tr>
<td width="189">
<p>Binarization_Type</p>
</td>
<td width="189">
<p>0</p>
</td>
<td width="189">
<p>二值化图</p>
</td>
</tr>
<tr>
<td width="189">
<p>Grayscale_Type</p>
</td>
<td width="189">
<p>1</p>
</td>
<td width="189">
<p>灰度图</p>
</td>
</tr>
<tr>
<td width="189">
<p>RGB565_Type</p>
</td>
<td width="189">
<p>2</p>
</td>
<td width="189">
<p>RGB565彩图</p>
</td>
</tr>
</tbody>
</table>
<p>&nbsp;</p>
<h2><a name="_Toc29863"></a><strong>3.3结构体说明</strong></h2>
<h3><a name="_Toc13797"></a><strong>3.3.1参数控件结构体</strong></h3>
<table>
<tbody>
<tr>
<td colspan="3" width="568">
<p><strong><strong>PM_Param_t</strong></strong></p>
</td>
</tr>
<tr>
<td width="189">
<p>类型</p>
</td>
<td width="189">
<p>名称</p>
</td>
<td width="189">
<p>描述</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_uint8</p>
</td>
<td width="189">
<p>ID</p>
</td>
<td width="189">
<p>ID</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_uint8</p>
</td>
<td width="189">
<p>Channels</p>
</td>
<td width="189">
<p>参数通道数</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_uint8</p>
</td>
<td width="189">
<p>DataType[PM_MAX_PARAMCANNELS]</p>
</td>
<td width="189">
<p>参数数据类型列表</p>
</td>
</tr>
<tr>
<td width="189">
<p>void*</p>
</td>
<td width="189">
<p>DataAddrList[PM_MAX_PARAMCANNELS]</p>
</td>
<td width="189">
<p>参数数据地址列表</p>
</td>
</tr>
</tbody>
</table>
<h3><a name="_Toc1940"></a><strong>3.3.2示波控件结构体</strong></h3>
<table>
<tbody>
<tr>
<td colspan="3" width="568">
<p><strong><strong>PM_Waveform_t</strong></strong></p>
</td>
</tr>
<tr>
<td width="189">
<p>类型</p>
</td>
<td width="189">
<p>名称</p>
</td>
<td width="189">
<p>描述</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_uint8</p>
</td>
<td width="189">
<p>ID</p>
</td>
<td width="189">
<p>ID</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_uint8</p>
</td>
<td width="189">
<p>DataType</p>
</td>
<td width="189">
<p>数据类型</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_uint8</p>
</td>
<td width="189">
<p>Channels</p>
</td>
<td width="189">
<p>示波通道数</p>
</td>
</tr>
<tr>
<td width="189">
<p>void*</p>
</td>
<td width="189">
<p>DataAddrList[PM_MAX_WAVEFORMCANNELS]</p>
</td>
<td width="189">
<p>示波数据地址列表</p>
</td>
</tr>
</tbody>
</table>
<h3><a name="_Toc25921"></a><strong>3.3.2图传控件结构体</strong></h3>
<table>
<tbody>
<tr>
<td colspan="3" width="568">
<p><strong><strong>PM_Image_t</strong></strong></p>
</td>
</tr>
<tr>
<td width="189">
<p>类型</p>
</td>
<td width="189">
<p>名称</p>
</td>
<td width="189">
<p>描述</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_uint8</p>
</td>
<td width="189">
<p>ID</p>
</td>
<td width="189">
<p>ID</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_uint8</p>
</td>
<td width="189">
<p>ImageType</p>
</td>
<td width="189">
<p>图像类型</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_uint8</p>
</td>
<td width="189">
<p>Height</p>
</td>
<td width="189">
<p>图像高度</p>
</td>
</tr>
<tr>
<td width="189">
<p>PM_uint8</p>
</td>
<td width="189">
<p>Width</p>
</td>
<td width="189">
<p>图像宽度</p>
</td>
</tr>
<tr>
<td width="189">
<p>void*</p>
</td>
<td width="189">
<p>DataAddr</p>
</td>
<td width="189">
<p>图像数据地址</p>
</td>
</tr>
</tbody>
</table>
<p>&nbsp;</p>
<h2><a name="_Toc23362"></a><strong>3.4函数说明</strong></h2>
<h3><a name="_Toc30360"></a><strong>3.4.1复位窗口</strong></h3>
<table>
<tbody>
<tr>
<td colspan="2" width="568">
<p><strong><strong>void PM_ResetWindow(void)</strong></strong></p>
</td>
</tr>
<tr>
<td width="82">
<p>名称</p>
</td>
<td width="485">
<p>PM_ResetWindow</p>
</td>
</tr>
<tr>
<td width="82">
<p>描述</p>
</td>
<td width="485">
<p>复位窗口</p>
</td>
</tr>
<tr>
<td width="82">
<p>参数</p>
</td>
<td width="485">
<p>void</p>
</td>
</tr>
<tr>
<td width="82">
<p>返回值</p>
</td>
<td width="485">
<p>void</p>
</td>
</tr>
<tr>
<td width="82">
<p>示例</p>
</td>
<td width="485">
<p>PM_ResetWindow()</p>
</td>
</tr>
</tbody>
</table>
<h2><a name="_Toc27964"></a><strong>3.4.2复位窗口</strong></h2>
<table>
<tbody>
<tr>
<td colspan="2" width="568">
<p><strong><strong>void PM_InitWindow(void)</strong></strong></p>
</td>
</tr>
<tr>
<td width="82">
<p>名称</p>
</td>
<td width="485">
<p>PM_InitWindow</p>
</td>
</tr>
<tr>
<td width="82">
<p>描述</p>
</td>
<td width="485">
<p>初始化窗口</p>
</td>
</tr>
<tr>
<td width="82">
<p>参数</p>
</td>
<td width="485">
<p>void</p>
</td>
</tr>
<tr>
<td width="82">
<p>返回值</p>
</td>
<td width="485">
<p>void</p>
</td>
</tr>
<tr>
<td width="82">
<p>示例</p>
</td>
<td width="485">
<p>PM_InitWindow()</p>
</td>
</tr>
</tbody>
</table>
<h2><a name="_Toc11595"></a><strong>3.4.3创建参数控件</strong></h2>
<table>
<tbody>
<tr>
<td colspan="2" width="568">
<p><strong><strong>PM_Param_t* PM_CreateParam(PM_uint8 ID, const PM_int8* Name)</strong></strong></p>
</td>
</tr>
<tr>
<td width="82">
<p>名称</p>
</td>
<td width="485">
<p>PM_CreateParam</p>
</td>
</tr>
<tr>
<td width="82">
<p>描述</p>
</td>
<td width="485">
<p>创建参数控件</p>
</td>
</tr>
<tr>
<td width="82">
<p>参数</p>
</td>
<td width="485">
<p>ID 控件ID（保证全局唯一性）</p>
</td>
</tr>
<tr>
<td width="82">
<p>参数</p>
</td>
<td width="485">
<p>Name 控件名称（标题）</p>
</td>
</tr>
<tr>
<td width="82">
<p>返回值</p>
</td>
<td width="485">
<p>参数控件结构体指针</p>
</td>
</tr>
<tr>
<td width="82">
<p>示例</p>
</td>
<td width="485">
<p>PM_CreateParam(0x00, "Test_param")</p>
</td>
</tr>
</tbody>
</table>
<h2><strong><br /><a name="_Toc18267"></a></strong><strong>3.4.4创建参数通道</strong></h2>
<table>
<tbody>
<tr>
<td colspan="2" width="568">
<p><strong><strong>PM_err PM_CreateParamChannels(PM_Param_t* PM_Param, const PM_int8* Name, RWMode_Type ModeType,Data_Type DataType, void* DataAddr)</strong></strong></p>
</td>
</tr>
<tr>
<td width="82">
<p>名称</p>
</td>
<td width="485">
<p>PM_CreateParamChannels</p>
</td>
</tr>
<tr>
<td width="82">
<p>描述</p>
</td>
<td width="485">
<p>创建参数通道</p>
</td>
</tr>
<tr>
<td width="82">
<p>参数</p>
</td>
<td width="485">
<p>PM_Param 参数控件指针</p>
</td>
</tr>
<tr>
<td width="82">
<p>参数</p>
</td>
<td width="485">
<p>Name 数据名称</p>
</td>
</tr>
<tr>
<td width="82">
<p>参数</p>
</td>
<td width="485">
<p>ModeType 读写类型</p>
</td>
</tr>
<tr>
<td width="82">
<p>参数</p>
</td>
<td width="485">
<p>DataType 数据类型</p>
</td>
</tr>
<tr>
<td width="82">
<p>参数</p>
</td>
<td width="485">
<p>DataAddr 数据地址</p>
</td>
</tr>
<tr>
<td width="82">
<p>返回值</p>
</td>
<td width="485">
<p>错误码 &nbsp;PM_EOK为创建成功 &nbsp;PM_EFULL为创建失败</p>
</td>
</tr>
<tr>
<td width="82">
<p>示例</p>
</td>
<td width="485">
<p>PM_CreateParamChannels(PM_Param,"Test1",RW_Type,int8_Type, &amp;test1)</p>
</td>
</tr>
</tbody>
</table>
<h2><a name="_Toc22501"></a><strong>3.4.5创建示波控件</strong></h2>
<table>
<tbody>
<tr>
<td colspan="2" width="568">
<p><strong><strong>PM_Waveform_t* PM_CreateWaveform(PM_uint8 ID, const PM_int8* Name, Series_Type SeriesType, Data_Type DataType)</strong></strong></p>
</td>
</tr>
<tr>
<td width="82">
<p>名称</p>
</td>
<td width="485">
<p>PM_CreateWaveform</p>
</td>
</tr>
<tr>
<td width="82">
<p>描述</p>
</td>
<td width="485">
<p>创建示波控件</p>
</td>
</tr>
<tr>
<td width="82">
<p>参数</p>
</td>
<td width="485">
<p>ID 控件ID（保证全局唯一性）</p>
</td>
</tr>
<tr>
<td width="82">
<p>参数</p>
</td>
<td width="485">
<p>Name 控件名称（标题）</p>
</td>
</tr>
<tr>
<td width="82">
<p>参数</p>
</td>
<td width="485">
<p>SeriesType 控件类型：示波线条类型枚举</p>
</td>
</tr>
<tr>
<td width="82">
<p>参数</p>
</td>
<td width="485">
<p>DataType 数据类型</p>
</td>
</tr>
<tr>
<td width="82">
<p>返回值</p>
</td>
<td width="485">
<p>示波控件结构体指针</p>
</td>
</tr>
<tr>
<td width="82">
<p>示例</p>
</td>
<td width="485">
<p>PM_CreateWaveform(0x00,"Test_Waveform",SplineSeries_Type,uint16_Type)</p>
</td>
</tr>
</tbody>
</table>
<p>&nbsp;</p>
<h2><a name="_Toc457"></a><strong>3.4.6创建示波通道</strong></h2>
<table>
<tbody>
<tr>
<td colspan="2" width="568">
<p><strong><strong>PM_err PM_CreateWaveformChannels(PM_Waveform_t* PM_Waveform, const PM_int8* Name, void* DataAddr)</strong></strong></p>
</td>
</tr>
<tr>
<td width="70">
<p>名称</p>
</td>
<td width="497">
<p>PM_CreateWaveformChannels</p>
</td>
</tr>
<tr>
<td width="70">
<p>描述</p>
</td>
<td width="497">
<p>创建示波通道</p>
</td>
</tr>
<tr>
<td width="70">
<p>参数</p>
</td>
<td width="497">
<p>PM_Waveform 示波控件结构体指针</p>
</td>
</tr>
<tr>
<td width="70">
<p>参数</p>
</td>
<td width="497">
<p>Name 数据名称</p>
</td>
</tr>
<tr>
<td width="70">
<p>参数</p>
</td>
<td width="497">
<p>DataAddr 数据地址</p>
</td>
</tr>
<tr>
<td width="70">
<p>返回值</p>
</td>
<td width="497">
<p>错误码 &nbsp;PM_EOK为创建成功 &nbsp;PM_EFULL为创建失败</p>
</td>
</tr>
<tr>
<td width="70">
<p>示例</p>
</td>
<td width="497">
<p>PM_CreateWaveformChannels(PM_Waveform,"Test", &amp;Test)</p>
</td>
</tr>
</tbody>
</table>
<h2><a name="_Toc19079"></a><strong>3.4.7创建图传控件</strong></h2>
<table>
<tbody>
<tr>
<td colspan="2" width="568">
<p><strong><strong>PM_Image_t* PM_CreateImage(PM_uint8 ID, const PM_int8* Name, Image_Type ImageType, PM_uint8 Height, PM_uint8 Width, void* DataAddr)</strong></strong></p>
</td>
</tr>
<tr>
<td width="70">
<p>名称</p>
</td>
<td width="497">
<p>PM_CreateImage</p>
</td>
</tr>
<tr>
<td width="70">
<p>描述</p>
</td>
<td width="497">
<p>创建图传控件</p>
</td>
</tr>
<tr>
<td width="70">
<p>参数</p>
</td>
<td width="497">
<p>ID 控件ID（保证全局唯一性）</p>
</td>
</tr>
<tr>
<td width="70">
<p>参数</p>
</td>
<td width="497">
<p>Name 控件名称（标题）</p>
</td>
</tr>
<tr>
<td width="70">
<p>参数</p>
</td>
<td width="497">
<p>ImageType 图像类型：详见图像类型枚举</p>
</td>
</tr>
<tr>
<td width="70">
<p>参数</p>
</td>
<td width="497">
<p>Height 图像高度</p>
</td>
</tr>
<tr>
<td width="70">
<p>参数</p>
</td>
<td width="497">
<p>Width 图像宽度</p>
</td>
</tr>
<tr>
<td width="70">
<p>参数</p>
</td>
<td width="497">
<p>DataAddr 图像地址</p>
</td>
</tr>
<tr>
<td width="70">
<p>返回值</p>
</td>
<td width="497">
<p>图传控件结构体指针</p>
</td>
</tr>
<tr>
<td width="70">
<p>示例</p>
</td>
<td width="497">
<p>PM_CreateImage(0x00,"TestImage1",Binarization_Type,60,90,image)</p>
</td>
</tr>
</tbody>
</table>
<p>&nbsp;</p>
<h2><a name="_Toc21052"></a><strong>3.4.8发送参数控件数据</strong></h2>
<table>
<tbody>
<tr>
<td colspan="2" width="568">
<p><strong><strong>void PM_SendParamData(PM_Param_t* PM_Param)</strong></strong></p>
</td>
</tr>
<tr>
<td width="70">
<p>名称</p>
</td>
<td width="497">
<p>PM_SendParamData</p>
</td>
</tr>
<tr>
<td width="70">
<p>描述</p>
</td>
<td width="497">
<p>发送参数控件数据</p>
</td>
</tr>
<tr>
<td width="70">
<p>参数</p>
</td>
<td width="497">
<p>PM_Param 参数控件结构体</p>
</td>
</tr>
<tr>
<td width="70">
<p>返回值</p>
</td>
<td width="497">
<p>void</p>
</td>
</tr>
<tr>
<td width="70">
<p>示例</p>
</td>
<td width="497">
<p>PM_SendParamData(PM_Param)</p>
</td>
</tr>
</tbody>
</table>
<h2><a name="_Toc13765"></a><strong>3.4.9发送示波控件数据</strong></h2>
<table>
<tbody>
<tr>
<td colspan="2" width="568">
<p><strong><strong>void PM_SendWaveformData(PM_Waveform_t* PM_Waveform)</strong></strong></p>
</td>
</tr>
<tr>
<td width="70">
<p>名称</p>
</td>
<td width="497">
<p>PM_SendWaveformData</p>
</td>
</tr>
<tr>
<td width="70">
<p>描述</p>
</td>
<td width="497">
<p>发送示波控件数据</p>
</td>
</tr>
<tr>
<td width="70">
<p>参数</p>
</td>
<td width="497">
<p>PM_Waveform 示波控件结构体</p>
</td>
</tr>
<tr>
<td width="70">
<p>返回值</p>
</td>
<td width="497">
<p>void</p>
</td>
</tr>
<tr>
<td width="70">
<p>示例</p>
</td>
<td width="497">
<p>PM_SendWaveformData(PM_Waveform)</p>
</td>
</tr>
</tbody>
</table>
<h2><a name="_Toc31201"></a><strong>3.4.10发送图传控件数据</strong></h2>
<table>
<tbody>
<tr>
<td colspan="2" width="568">
<p><strong><strong>void PM_SendImageData(PM_Image_t* PM_Image)</strong></strong></p>
</td>
</tr>
<tr>
<td width="70">
<p>名称</p>
</td>
<td width="497">
<p>PM_SendImageData</p>
</td>
</tr>
<tr>
<td width="70">
<p>描述</p>
</td>
<td width="497">
<p>发送图传控件数据</p>
</td>
</tr>
<tr>
<td width="70">
<p>参数</p>
</td>
<td width="497">
<p>PM_Image 图传控件结构体</p>
</td>
</tr>
<tr>
<td width="70">
<p>返回值</p>
</td>
<td width="497">
<p>void</p>
</td>
</tr>
<tr>
<td width="70">
<p>示例</p>
</td>
<td width="497">
<p>PM_SendImageData(PM_Image)</p>
</td>
</tr>
</tbody>
</table>
<p>&nbsp;</p>
<h2><a name="_Toc1365"></a><strong>3.4.11回传数据处理函数</strong></h2>
<table>
<tbody>
<tr>
<td colspan="2" width="568">
<p><strong><strong>void PM_RevHandle(PM_Param_t* Param, PM_uint8 dat)</strong></strong></p>
</td>
</tr>
<tr>
<td width="70">
<p>名称</p>
</td>
<td width="497">
<p>PM_RevHandle</p>
</td>
</tr>
<tr>
<td width="70">
<p>描述</p>
</td>
<td width="497">
<p>回传数据处理函数</p>
</td>
</tr>
<tr>
<td width="70">
<p>参数</p>
</td>
<td width="497">
<p>Param 参数控件结构体指针</p>
</td>
</tr>
<tr>
<td width="70">
<p>参数</p>
</td>
<td width="497">
<p>dat 接收字节</p>
</td>
</tr>
<tr>
<td width="70">
<p>返回值</p>
</td>
<td width="497">
<p>void</p>
</td>
</tr>
<tr>
<td width="70">
<p>示例</p>
</td>
<td width="497">
<p>PM_RevHandle(PM_Param, dat)</p>
</td>
</tr>
</tbody>
</table>
<p>&nbsp;</p>
<h1><a name="_Toc12243"></a>四、<strong>使用方法</strong></h1>
<h1><a name="_Toc3385"></a><strong>4.1上位机使用方法</strong></h1>
<h3><a name="_Toc21522"></a><strong>4.1.1上位机布局介绍</strong></h3>
<p>&nbsp;</p>
<p>①工具栏：主要为与物理层连接的工具，负责传输与下位机通信的数据，初代版本为串口工具。</p>
<p>②Window栏：MainWindow栏各个空间的容器，ID默认为0xFF。</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p>①图传控件、②示波控件、③参数控件</p>
<h3><a name="_Toc16726"></a><strong>4.1.2 MainWindow介绍</strong></h3>
<p>MainWindow为所有控件的母容器，下位机创建的所有的控件均添加到该容器内，默认ID为0xFF。</p>
<p>MainWindow内所有控件均可自由缩放。</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<h3><a name="_Toc22350"></a><strong>4.1.3图传控件介绍</strong></h3>
<p>&nbsp;</p>
<p>①控件ID号：由下位机初始化获得。</p>
<p>②图像类型：由下位机初始化获得。</p>
<p>③图像高度：由下位机初始化获得。</p>
<p>④图像宽度：由下位机初始化获得。</p>
<p>⑤适应窗口：勾选该选项则将图片铺满控件，否则将以原始比例显示。</p>
<p>⑥保存图像：勾选该选项将自动保存所有接收到的图像，<strong><strong>鼠标左键双击图像也可保存图像</strong></strong>。</p>
<p>图像保存路径为以控件名称命名的文件夹下。</p>
<p>⑦图像栅格：将单位像素框选。</p>
<h3><a name="_Toc21132"></a><strong>4.1.4示波控件介绍</strong></h3>
<p>&nbsp;</p>
<p>①控件ID号：由下位机初始化获得。</p>
<p>②通道数：由下位机创建的通道总数。</p>
<p>③控件类型：由下位机初始化获得。</p>
<p>④数据类型：由下位机初始化获得。</p>
<p>⑤Y轴放大：在非自适应模式下Y轴放大。</p>
<p>⑥Y轴缩小：在非自适应模式下Y轴缩小。</p>
<p>⑦Y轴归0：在非自适应模式下Y轴中心归0，<strong><strong>双击控件背景也可Y轴中归0。</strong></strong></p>
<p>⑧X轴放大：X轴坐标放大。</p>
<p>⑨X轴缩小：X轴坐标缩小。</p>
<p>⑩关闭自适应：开关自适应模式按键。</p>
<p><strong><strong>示波控件默认开启自适应模式，该模式会将数据完整的显示在窗口内。</strong></strong></p>
<p><strong><strong>&nbsp;</strong></strong></p>
<h3><a name="_Toc26124"></a><strong>4.1.5参数控件介绍</strong></h3>
<p>&nbsp;</p>
<p>单个参数通道是由通道名称和输入框组成的，若通道为只写模式（W_Type）还会有一个设置按钮。</p>
<p>强烈推荐若无需修改通道数值请设置为&ldquo;<strong><strong>只读模式</strong></strong>&rdquo;，若无需知道通道数值请设置为&ldquo;<strong><strong>只写模式</strong></strong>&rdquo;。因为读写模式是双向传输的在上位机写的时候下位机同时在上传，很有可能会造成修改失败的情况。</p>
<h2><a name="_Toc9681"></a><strong>4.2下位机使用方法</strong></h2>
<h3><a name="_Toc6633"></a><strong>4.2.1下位机初始化流程</strong></h3>
<p>①复位MainWindow控件：调用<strong><strong>PM_ResetWindow</strong></strong>函数，发送窗口复位命令。</p>
<p>②根据需求创建控件并添加通道：</p>
<p>调用<strong><strong>PM_CreateParam</strong></strong>函数，创建示波控件，将其返回的参数控件结构体指针保存到全局变量，判断其是否为PM_NULL，若为PM_NULL则创建失败。其他控件同理。</p>
<p>调用<strong><strong>PM_CreateParamChannels</strong></strong>，创建示波通道判断其返回的错误码是否为PM_EOK，若为PM_EOK则创建成功。其他通道同理。</p>
<p>③初始化MainWindow控件：调用<strong><strong>PM_InitWindow</strong></strong>函数，发送窗口初始化命令。</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p><strong><strong>示例程序：</strong></strong></p>
<p>PM_Param_t* PM_Param;</p>
<p>PM_Waveform_t* PM_Waveform[3];</p>
<p>PM_Image_t* PM_Image[2];</p>
<p>uint16 adc;</p>
<p>int8 test1 = 1;</p>
<p>int16 test2 = 0;</p>
<p>int32 test3 = 0;</p>
<p>uint8 test4 = 0;</p>
<p>uint16 test5 = 0;</p>
<p>uint32 test6 = 0;</p>
<p>float test7 = 0.0;</p>
<p>uint16 Image[50][90] = {0};</p>
<p>&nbsp;</p>
<p>void Window_init(void)</p>
<p>{</p>
<p>/* 复位MainWindow控件 */</p>
<p>PM_ResetWindow();</p>
<p>/* Test_param 控件 */</p>
<p>PM_Param = PM_CreateParam(0x00, "Test_param");</p>
<p>PM_CreateParamChannels(PM_Param, "Test_Param1",R_Type, int8_Type, &amp;test1);</p>
<p>PM_CreateParamChannels(PM_Param, "Test_Param2",W_Type, int16_Type, &amp;test2);</p>
<p>PM_CreateParamChannels(PM_Param, "Test_Param3",RW_Type, int32_Type, &amp;test3);</p>
<p>PM_CreateParamChannels(PM_Param, "Test_Param4",RW_Type, uint8_Type, &amp;test4);</p>
<p>PM_CreateParamChannels(PM_Param, "Test_Param5",RW_Type, uint16_Type, &amp;test5);</p>
<p>PM_CreateParamChannels(PM_Param, "Test_Param6",RW_Type, uint32_Type, &amp;test6);</p>
<p>PM_CreateParamChannels(PM_Param, "Test_Param7",RW_Type, float_Type, &amp;test7);</p>
<p>/* ADC0 控件 */</p>
<p>PM_Waveform[0] = PM_CreateWaveform(0x01, "ADC0", LineSeries_Type, uint16_Type);</p>
<p>PM_CreateWaveformChannels(PM_Waveform[0], "Test", &amp;adc);</p>
<p>/* MPU6050_Gyro 控件 */</p>
<p>PM_Waveform[1] = PM_CreateWaveform(0x02, "MPU6050_Gyro", SplineSeries_Type, int16_Type);</p>
<p>PM_CreateWaveformChannels(PM_Waveform[1], "GyroX", &amp;mpu_gyro_x);</p>
<p>PM_CreateWaveformChannels(PM_Waveform[1], "Gyroy", &amp;mpu_gyro_y);</p>
<p>PM_CreateWaveformChannels(PM_Waveform[1], "GyroZ", &amp;mpu_gyro_z);</p>
<p>/* MPU6050_Acc 控件 */</p>
<p>PM_Waveform[2] = PM_CreateWaveform(0x03, "MPU6050_Acc", BarSeries_Type, int16_Type);</p>
<p>PM_CreateWaveformChannels(PM_Waveform[2], "AccX", &amp;mpu_acc_x);</p>
<p>PM_CreateWaveformChannels(PM_Waveform[2], "AccY", &amp;mpu_acc_y);</p>
<p>PM_CreateWaveformChannels(PM_Waveform[2], "AccZ", &amp;mpu_acc_z);</p>
<p>/* Test_RGB565 控件 */</p>
<p>PM_Image[0] = PM_CreateImage(0x04, "Test_RGB565", RGB565_Type, 50, 90, Image);</p>
<p>/* Test_Grayscale 控件 */</p>
<p>PM_Image[1] = PM_CreateImage(0x05, "Test_Grayscale", Grayscale_Type, 50, 90, Image);</p>
<p>/* 初始化MainWindow */</p>
<p>PM_InitWindow();</p>
<p>}</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<h3><a name="_Toc31961"></a><strong>4.2.2下位机发送数据流程</strong></h3>
<p>①在需要发送数据的地方调用<strong><strong>PM_SendWaveformData</strong></strong>函数，即可将控件数据发送到上位机。其他控件同理。</p>
<p><strong><strong>示例程序：</strong></strong></p>
<p>while(1)</p>
<p>{</p>
<p>gpio_toggle(C0);</p>
<p>/* 更新数据 */</p>
<p>adc = adc_convert(ADC_1, ADC1_CH00_A00);</p>
<p>get_accdata();</p>
<p>get_gyro();</p>
<p>/* 发送数据 */</p>
<p>PM_SendParamData(PM_Param);</p>
<p>PM_SendWaveformData(PM_Waveform[0]);</p>
<p>PM_SendWaveformData(PM_Waveform[1]);</p>
<p>PM_SendWaveformData(PM_Waveform[2]);</p>
<p>PM_SendImageData(PM_Image[0]);</p>
<p>PM_SendImageData(PM_Image[1]);</p>
<p>/* 延时 */</p>
<p>systick_delay_ms(20);</p>
<p>}</p>
<p>&nbsp;</p>
<p>&nbsp;</p>