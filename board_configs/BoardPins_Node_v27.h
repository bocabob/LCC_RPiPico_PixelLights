/*
 * Pin definitions for LCC RPi Pico Node board v2.7
 *
 * Do not include this file directly — it is selected automatically
 * by BoardSettings.h based on the LCC_BOARD_* define in ProjectConfig.h.
 *
 * Key differences from v2.5/v2.6:
 *   - No dedicated NeoPixel pins; gp0-gp7 are general-purpose I/O headers.
 *     Connect NeoPixel strings to I/O header pins and update NeoPixel_Pin*
 *     defines here if needed.
 *   - I2C0 (servo) on natural I2C0 pins gp4/gp5 (I/O-1:Pin7/Pin8)
 *   - I2C1 (storage), CAN, and buttons unchanged from v2.5
 *
 * v2.7 layout:
 *   NeoPixel outputs : none dedicated — use I/O header pins
 *   I2C0 for servo   : gp4 (SDA) / gp5 (SCL)  — I/O-1:Pin7/Pin8
 *   I2C1 for storage : gp26 (SDA) / gp27 (SCL)  — Wire1
 *   CAN (SPI0)       : SDO=gp16, CS=gp17, SCK=gp18, SDI=gp19, INT=gp20
 *   Buttons          : Blue=gp21, Gold=gp22
 */

#ifndef BOARDPINS_NODE_V27_H
#define BOARDPINS_NODE_V27_H

// --------------------------------------------
//  NeoPixel outputs
//  No dedicated pins on v2.7 — assign I/O header pins here if needed.
//  127 = UNUSED_PIN (defined in BoardSettings.h).
// --------------------------------------------
#define NeoPixel_PinA   127  // UNUSED — reassign to an I/O header pin
#define NeoPixel_PinB   127
#define NeoPixel_PinC   127
#define NeoPixel_PinD   127

// --------------------------------------------
//  I2C0 — servo controller (PCA9685)
//  gp4/gp5 = I/O-1:Pin7/Pin8, natural I2C0 pins on RP2040
// --------------------------------------------
#define SERVO_SDA    4
#define SERVO_SCL    5

// --------------------------------------------
//  I2C1 — EEPROM storage (Wire1) — unchanged from v2.5
// --------------------------------------------
#define I2C_SDA     26
#define I2C_SCL     27
#define STOR_WIRE   Wire1

// --------------------------------------------
//  CAN transceiver — MCP2517/18 via SPI0 — unchanged from v2.5
// --------------------------------------------
#define MCP2517_SPI SPI
#define MCP2517_SDO 16
#define MCP2517_CS  17
#define MCP2517_SCK 18
#define MCP2517_SDI 19
#define MCP2517_INT 20

// --------------------------------------------
//  Buttons — unchanged from v2.5
// --------------------------------------------
#define BLUE_BUTTON_PIN  21
#define GOLD_BUTTON_PIN  22

#endif  // BOARDPINS_NODE_V27_H
