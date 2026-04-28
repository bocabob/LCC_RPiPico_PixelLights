/*
 * ProjectConfig.h — THE single file to edit when switching hardware targets.
 *
 * Uncomment exactly ONE board line.  Everything else (pin assignments,
 * I2C buses, CAN SPI pins) is derived automatically from this choice.
 *
 *  LCC_BOARD_NODE_V25  →  v2.5 board  (NeoPixel gp2/3/6/7, CAN gp16-20, I2C1 gp26/27)
 *  LCC_BOARD_NODE_V26  →  v2.6 board  (identical pin assignments to v2.5)
 *  LCC_BOARD_NODE_V27  →  v2.7 board  (all I/O headers, no dedicated NeoPixel, CAN gp16-20)
 *  LCC_BOARD_NODE_V28  →  v2.8 board  (CAN gp0-4, I2C1 gp6/7, I2C0 gp16/17)
 */

// #define LCC_BOARD_NODE_V25    // v2.5 board
//#define LCC_BOARD_NODE_V26  // v2.6 board (identical pins to v2.5)
//#define LCC_BOARD_NODE_V27  // v2.7 board (no dedicated NeoPixel pins)
#define LCC_BOARD_NODE_V28  // v2.8 board (CAN/I2C layout changed)
