本实验将实现如下功能：本章我们在UCOSII里面创建6个任务：开始任务、LED任务、触摸屏任务、蜂鸣器任务、按键扫描任务和主任务，开始任务用于创建信号量、创建邮箱、初始化统计任务以及其他任务的创建，之后挂起；LED任务用于DS0控制，提示程序运行状况；蜂鸣器任务用于测试信号量，是请求信号量函数，每得到一个信号量，蜂鸣器就叫一次；触摸屏任务用于在屏幕上画图，可以用于测试CPU使用率；按键扫描任务用于按键扫描，优先级最高，将得到的键值通过消息邮箱发送出去；主任务则通过查询消息邮箱获得键值，并根据键值执行DS1控制、信号量发送（蜂鸣器控制）、触摸区域清屏和触摸屏校准等控制。 

    通过按KEY0，可以控制DS1的亮灭；
    通过按KEY1则可以控制蜂鸣器的发声（连续按下多次后，可以看到蜂鸣每隔1秒叫一次），同时，可以在LCD上面看到信号量的当前值；
    通过按KEY2，可以清除触摸屏的输入；
    通过按KEY_UP可以进入校准程序，进行触摸屏校准（注意，电容触摸屏不需要校准，所以如果是电容屏，按KEY_UP，就相当于清屏一次的效果，不会进行校准）


注意：
1，本实验改自触摸屏实验。
2，本实验使用ucosii版本为V2.91。

//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com
