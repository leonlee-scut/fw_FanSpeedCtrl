# Fan Speed Control Firmware

这是一个用于控制直流风机转速的固件，基于STM32G070KBTx微控制器。

## 硬件配置

- STM32G070KBTx微控制器
- 4路ADC用于读取NTC热敏电阻传感器
- 1路PWM输出用于控制风机转速，控制2路风机
- 2路定时器输入用于检测风机转速
- 1路UART用于调试输出
- 1路UART用于与上位机通信

原理图参见 [原理图](./Docs/FAN_PWM_Controller.png)。

## 软件配置

- STM32CubeMX用于生成初始化代码
- 使用CMSIS和HAL库进行开发
- 使用CMSIS-RTOS2和RTX实时操作系统进行任务调度

## 使用说明
