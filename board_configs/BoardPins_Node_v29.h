/*
 * Physical pin topology for LCC RPi Pico Node board v2.9
 *
 * Do not include this file directly — it is selected automatically
 * by BoardSettings.h based on the LCC_BOARD_* define in ProjectConfig.h.
 *
 * This file describes PHYSICAL connector layout only.
 * Functional assignments (NeoPixel_Pin*, buttons, etc.) belong in NodeConfig.h.
 *
 * Connector layout — 10-pin IDC (IO1, IO2):
 *   Pins 1-4  signal | Pin 5 VCC | Pin 6 GND | Pins 7-10 signal
 *
 * IO3 is a 5-pin analog header:
 *   Pin 1-2 signal | Pin 3 AGND | Pin 4 VREF | Pin 5 signal
 *
 * Note: gp26 is shared between IO2_PIN10 and IO3_PIN1.
 *       gp21 and gp22 also serve as Blue/Gold buttons — assign in NodeConfig.h.
 */

#ifndef BOARDPINS_NODE_V29_H
#define BOARDPINS_NODE_V29_H

// --------------------------------------------
//  IO1 — 10-pin IDC connector
// --------------------------------------------
#define IO1_PIN1    8
#define IO1_PIN2    9
#define IO1_PIN3   10
#define IO1_PIN4   11
#define IO1_PIN5   PWR_VCC
#define IO1_PIN6   PWR_GND
#define IO1_PIN7   12
#define IO1_PIN8   13
#define IO1_PIN9   14
#define IO1_PIN10  15

// --------------------------------------------
//  IO2 — 10-pin IDC connector
//  gp21 = Pin8 (also Blue Button)
//  gp22 = Pin9 (also Gold Button)
//  gp26 = Pin10 (shared with IO3_PIN1)
// --------------------------------------------
#define IO2_PIN1   16
#define IO2_PIN2   17
#define IO2_PIN3   18
#define IO2_PIN4   19
#define IO2_PIN5   PWR_VCC
#define IO2_PIN6   PWR_GND
#define IO2_PIN7   20
#define IO2_PIN8   21
#define IO2_PIN9   22
#define IO2_PIN10  26

// --------------------------------------------
//  IO3 — 5-pin analog header
//  Pin 3 = AGND, Pin 4 = VREF (not assignable GPIOs)
//  gp26 = Pin1 (shared with IO2_PIN10)
// --------------------------------------------
#define IO3_PIN1   26
#define IO3_PIN2   27
#define IO3_PIN3   PWR_AGND
#define IO3_PIN4   PWR_VREF
#define IO3_PIN5   28

// --------------------------------------------
//  Standalone header pin
// --------------------------------------------
#define HDR_PIN1    5

// --------------------------------------------
//  I2C1 — EEPROM storage (Wire1, gp6/gp7)
//  Fixed-function traces — not on any connector.
// --------------------------------------------
#define I2C_SDA      6
#define I2C_SCL      7
#define STOR_WIRE    Wire1

// --------------------------------------------
//  CAN transceiver — MCP2517/18 via SPI0 (gp0-gp4)
//  Fixed-function traces — not on any connector.
// --------------------------------------------
#define MCP2517_SPI  SPI
#define MCP2517_SDO   0   // MISO (ACAN_RX_PIN)
#define MCP2517_CS    1
#define MCP2517_SCK   2
#define MCP2517_SDI   3   // MOSI (ACAN_TX_PIN)
#define MCP2517_INT   4

#endif  // BOARDPINS_NODE_V29_H
