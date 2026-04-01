/*
 *  This is the configuration file for the Raspberry Pi Pico node hardware.
 */

#ifndef DEFINES_H
#define DEFINES_H

#define ARDUINO_COMPATIBLE

// --------------------------------------------
// Select ONE of these for Non-volitile Memory Storage
// --------------------------------------------
// #define USE_INTERNAL_FLASH_STORAGE
#define USE_I2C_STORAGE

// if using external NVM storage, select ONE of these supported types, otherwise use none
#define EXTERNAL_EEPROM     // if uncommented uses external eeprom, using Adafruit library
// #define EXTERNAL_FRAM         // if uncommented uses externalFRAM, using Adafruit library

// if using external NVM, use either Tillaart library or default to Adafruit library
#define USE_TILLAART       // if uncommented then uses Rob Tillaart EEPROM and/or FRAM library

// --------------------------------------------

// -------------------------------------------
// Select ONE of these for Configuration Memory Size
// --------------------------------------------
// #define CONFIG_MEM_SIZE      65536
#define CONFIG_MEM_SIZE      32768
// #define CONFIG_MEM_SIZE      16384
//#define CONFIG_MEM_SIZE      8192
//#define CONFIG_MEM_SIZE      4096
//#define CONFIG_MEM_SIZE      2048
//#define CONFIG_MEM_SIZE      1024
//#define CONFIG_MEM_SIZE      512
//#define CONFIG_MEM_SIZE      256
//#define CONFIG_MEM_SIZE      128
// --------------------------------------------

// Define the size of the EEPROM chip or use 4096 if using emulated internal flash storage
// #define I2C_DEVICESIZE      65536  // 24LC512
#define I2C_DEVICESIZE      32768  // 24LC256
// #define I2C_DEVICESIZE      16384  // 24LC128
// #define I2C_DEVICESIZE       8192  // 24LC64
// #define I2C_DEVICESIZE       4096  // 24LC32    // this is the size to use for internal FLASH EEPROM emulation
// #define I2C_DEVICESIZE       2048  // 24LC16
// #define I2C_DEVICESIZE       1024  // 24LC08
// #define I2C_DEVICESIZE        512  // 24LC04
// #define I2C_DEVICESIZE        256  // 24LC02
// #define I2C_DEVICESIZE        128  // 24LC01

/////////////////////////////////////////////////////////////////////////////////////
//  Define a valid (and free) I2C address, 0x60 is the default.
// 
// #define I2C_ADDRESS 0x60 
// #define KEYPAD_ADDRESS 0x20
// #define DISPLAY_ADDRESS 0x3C
#define SERVO_ADDRESS 0x40
// #define EEPROM_ADDRESS 0x50
#define STORAGE_ADDR 0x50  // 0x50 is the default address!
#define STOR_WIRE Wire1     // make Wire1 or Wire

#define I2C_SDA  26           // pin to use
#define I2C_SCL  27           // pin to use
#define I2C2_SDA  4           // pin to use
#define I2C2_SCL  5           // pin to use
#define NeoPixel_PinA 2           // pin to use for the board interface
#define NeoPixel_PinB 6           // pin to use for the board interface
#define NeoPixel_PinC 7           // pin to use for the board interface
#define NeoPixel_PinD 3           // pin to use for the board interface


/////////////////////////////////////////////////////////////////////////////////////
//  Define the LED blink rates for fast and slow blinking in milliseconds.
// 
//  The LED will alternative on/off for these durations.
#define FREQUENCY 100

#define UNUSED_PIN 127

// Define current version of EEPROM configuration
#define EEPROM_VERSION 8

//  Enable debug outputs if required during troubleshooting.
#define NODE_DEBUG true  // uncomment for debug

//——————————————————————————————————————————————————————————————————————————————
//  MCP2517 connections: adapt theses settings to your design
//  As hardware SPI is used, you should select pins that support SPI functions.
//  This code is designed to use SPI
//  If standard SPI, SPI2 pins are not used then define them
//    SCK input of MCP2517 is connected to pin #32
//    SDI input of MCP2517 is connected to pin #0
//    SDO output of MCP2517 is connected to pin #1
//  CS input of MCP2517 should be connected to a digital output port
//  INT output of MCP2517 should be connected to a digital input port, with interrupt capability

#define MCP2517_SPI  SPI   // SPI port to use for MCP2517/8

#define MCP2517_CS  17   // CS input of MCP2517/8
#define MCP2517_INT 20  // INT output of MCP2517/8
#define MCP2517_SCK 18  // SCK input of MCP2517/8
#define MCP2517_SDI 19  // SI input of MCP2517/8
#define MCP2517_SDO 16  // SO output of MCP2517/8

// NeoPixel defines

#define MAX_STRINGS 4 // also defined in NPlights.cpp and program .ino files and need to update event table
#define MAX_LIGHTS 20 // also defined in NPlights.cpp and program .ino files

#define brightnesss 90
#define MAX_LUMINANCE 100

#endif