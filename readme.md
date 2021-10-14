# Project ESP32 LVGL Demo


```c++
/*
Version:		V1.0
Author:			Vincent
Create Date:	2021/10/14
Note:
	
*/
```


[toc]

# Makerfabs

[Makerfabs home page](https://www.makerfabs.com/)

[Makerfabs Wiki](https://makerfabs.com/wiki/index.php?title=Main_Page)


# Project ESP32 LVGL Demo

## Intruduce

Github Link : [Project_Touch-Camera-ILI9341](https://github.com/Makerfabs/Project_Touch-Camera-ILI9341)

Product Link ：[ESP32 3.2" TFT Touch with Camera](https://www.makerfabs.com/esp32-3.2-inch-tft-touch-with-camera.html) 

Wiki Link :  [Not ESP32 TFT LCD with Camera(3.2'')](https://www.makerfabs.com/wiki/index.php?title=ESP32_TFT_LCD_with_Camera(3.2%27%27)) 

Github Link : [Project_Touch-Screen-Camera](https://github.com/Makerfabs/Project_Touch-Screen-Camera)

Product link ：[ ESP32 Touch Camera(Resistive)](https://www.makerfabs.com/esp32-3.5-inch-tft-touch-resistive-with-camera.html) 

Product link ：[ ESP32 Touch Camera(Capacitive)](https://www.makerfabs.com/esp32-3.5-inch-tft-touch-capacitive-with-camera.html) 



We did a simple LVGL demo using the ESP32 Touch Camera(Capacitive), and the details are still being edited.



## Equipment list

- ESP32 Touch Camera (3.5" TFT with ILI9488 and FT6236)


## Compiler Options

**If you have any questions，such as how to install the development board, how to download the code, how to install the library. Please refer to :[Makerfabs_FAQ](https://github.com/Makerfabs/Makerfabs_FAQ)**

- Open Makerfabs_LVGL_demo.ino.

- Using library lv_arduino at version 3.0.1
- Using library TFT_eSPI at version 2.3.70
- Upload codes, select "ESP32 Wrover Module" and "Huge APP"



This demo depend on TFT_eSPI library. You must set "User_Setup.h".
Set screen type.

```c++
// Only define one driver, the other ones must be commented out
//#define ILI9341_DRIVER
//#define ST7735_DRIVER      // Define additional parameters below for this display
//#define ILI9163_DRIVER     // Define additional parameters below for this display
//#define S6D02A1_DRIVER
//#define RPI_ILI9486_DRIVER // 20MHz maximum SPI
//#define HX8357D_DRIVER
//#define ILI9481_DRIVER
//#define ILI9486_DRIVER
#define ILI9488_DRIVER     // WARNING: Do not connect ILI9488 display SDO to MISO if other devices share the SPI bus (TFT SDO does NOT tristate when CS is high)
//#define ST7789_DRIVER      // Full configuration option, define additional parameters below for this display
//#define ST7789_2_DRIVER    // Minimal configuration option, define additional parameters below for this display
```
And set pins.

```c++
// For 3.5" 9488
// The hardware SPI can be mapped to any pins

#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15  // Chip select control pin
#define TFT_DC    33  // Data Command control pin
#define TFT_RST   26  // Reset pin (could connect to RST pin)
    

```

This demo also need to set lv_arduino library.

You need copy` lv_conf_template.h`  as `lv_conf.h`next to the `lv_arduino` floder.

And set 0 to 1.

```c++
/**
 * @file lv_conf.h
 * Configuration file for LVGL v7.0.2
 */

/*
 * COPY THIS FILE AS `lv_conf.h` NEXT TO the `lvgl` FOLDER
 */

#if 0 /*Set it to "1" to enable content*/

```






## Code Explain
