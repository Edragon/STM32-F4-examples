实验47_1 DSP BasicMath测试 实验功能简介：测试STM32F4的DSP库基础数学函数：arm_cos_f32和arm_sin_f32和标准库基础数学函数：cosf和sinf的速度差别，并在LCD屏幕上面显示两者计算所用时间，DS0用于提示程序正在运行。

实验47_2 DSP FFT测试 实验功能简介：测试STM32F4的DSP 库的FFT函数，程序运行后，自动生成1024点测试序列，然后，每当KEY0按下后，调用DSP库的FFT算法（基4法）执行FFT运算，在LCD屏幕上面显示运算时间，同时将FFT结果输出到串口，DS0用于提示程序正在运行。


 


//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com