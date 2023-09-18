# STM32：PWM舵机控制

## 一、硬件

### 1、硬件清单

- 180°舵机
- 270°舵机
- 360°舵机
- STM32F103C8T6核心板
- 杜邦线

```
180°/270°舵机：标准舵机（角度舵机或定位舵机），可以精确控制角度位置。
```

```
360°舵机：连续旋转舵机（360°舵机或无限制舵机），可以控制舵机旋转速度和方向。
```

### 2、硬件接线

| 舵机        | STM32F103C8T6 |
| ----------- | ------------- |
| VCC（红色） | 5V            |
| SIG(黄色)   | PB4           |
| GND(褐色)   | GND           |

## 二、标准/连续旋转舵机

PWM舵机的控制原理基于脉宽调制技术

### 1、标准舵机

- **具有固定的角度范围**
- **精确控制角度位置**
- **舵机控制**

```
通过改变PWM信号来控制脉冲的高电平时间，从而来控制舵机旋转的角度
```

### 2、连续旋转舵机

- **控制旋转速度和方向**
- **实现无限制的连续旋转**
- **舵机控制**

```
通过改变PWM信号来控制脉冲的高电平时间，从而来控制舵机的速度和方向
```

## 三、舵机控制思路 

控制信号以固定频率的方波形式发送给舵机；这个方波的周期通常为20ms，即50Hz的频率；

在控制信号中，脉冲的高电平时间决定舵机旋转的角度或旋转速度和方向。

| 舵机（180°） | 高电平脉宽（us） |
| :----------: | :--------------: |
|      0°      |       500        |
|     45°      |       1000       |
|     90°      |       1500       |
|     135°     |       2000       |
|     180°     |       2500       |

| 舵机（270°） | 高电平脉宽（us） |
| :----------: | :--------------: |
|      0°      |       500        |
|     135°     |       1500       |
|     270°     |       2500       |

|     舵机（360°）     | 高电平脉宽（us） |
| :------------------: | :--------------: |
| 顺时针旋转：速度最快 |       500        |
| 顺时针旋转：速度中等 |       1000       |
|       停止旋转       |       1500       |
| 逆时针旋转：速度中等 |       2000       |
| 逆时针旋转：速度最快 |       2500       |

```
表格只列举部分控制情况
```

