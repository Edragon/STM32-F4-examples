本实验将实现如下功能：利用外部中断，实现与实验3类似的效果，即：STM32F407开发板上载有的4个按钮（WK_UP、KEY0、KEY1和KEY2），来控制板上的2个LED（DS0和DS1）和蜂鸣器，其中WK_UP控制蜂鸣器，按一次叫，再按一次停；KEY2控制DS0，按一次亮，再按一次灭；KEY1控制DS1，效果同KEY2；KEY0则同时控制DS0和DS1，按一次，他们的状态就翻转一次。
 
//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com