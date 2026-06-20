/*
 * NodeConfig.h — functional pin assignments for this specific node build.
 *
 * Edit this file to describe what is physically plugged into each connector.
 * Use the IOx_PINy defines from the active board config (via BoardSettings.h).
 * Set any unconnected function to UNUSED_PIN (127).
 *
 * Available signal pins by connector (v2.9):
 *   IO1: IO1_PIN1(gp8)  IO1_PIN2(gp9)  IO1_PIN3(gp10) IO1_PIN4(gp11)
 *        IO1_PIN7(gp12) IO1_PIN8(gp13) IO1_PIN9(gp14) IO1_PIN10(gp15)
 *
 *   IO2: IO2_PIN1(gp16) IO2_PIN2(gp17) IO2_PIN3(gp18) IO2_PIN4(gp19)
 *        IO2_PIN7(gp20) IO2_PIN8(gp21) IO2_PIN9(gp22) IO2_PIN10(gp26)
 *
 *   IO3: IO3_PIN1(gp26) IO3_PIN2(gp27) IO3_PIN5(gp28)  [analog-capable]
 *
 *   HDR: HDR_PIN1(gp5)
 *
 * Note: gp26 is shared between IO2_PIN10 and IO3_PIN1 — assign to only one function.
 */

#ifndef NODE_CONFIG_H
#define NODE_CONFIG_H

// --------------------------------------------
//  NeoPixel strings
//  Assign each active string to a connector signal pin.
// --------------------------------------------
#define NeoPixel_PinA   UNUSED_PIN
#define NeoPixel_PinB   UNUSED_PIN
#define NeoPixel_PinC   UNUSED_PIN
#define NeoPixel_PinD   UNUSED_PIN

// --------------------------------------------
//  Buttons
//  On v2.9 the Blue and Gold buttons share IO2_PIN8/PIN9. On v3.0 the board
//  header itself defines BLUE_BUTTON_PIN/GOLD_BUTTON_PIN (gp5/gp28) — the
//  #ifndef guards below avoid a macro redefinition when v3.0 is selected.
// --------------------------------------------
#ifndef BLUE_BUTTON_PIN
  #define BLUE_BUTTON_PIN   IO2_PIN8   // gp21
#endif
#ifndef GOLD_BUTTON_PIN
  #define GOLD_BUTTON_PIN   IO2_PIN9   // gp22
#endif

#endif  // NODE_CONFIG_H
