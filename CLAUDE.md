# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

See [../LCC_RPiPico_Common/LCC_NODE_STANDARD.md](../LCC_RPiPico_Common/LCC_NODE_STANDARD.md) for cross-project conventions (toolchain, board versioning, dual-core contract, CDI/EEPROM handling, naming). This file documents only what is specific to this node.

## Build Environment

- **Board family/revision**: Node board family — `LCC_BOARD_NODE_V29` is current (`ProjectConfig.h`); v2.5/v2.6/v2.7/v2.8 supported
- No display driver (this node has no display)
- No project-specific libraries beyond the family standard (`ACAN2517`, `I2C_eeprom`, `NeoPixelBus`, `Wire`)

## Architecture

This is an OpenLCB (LCC) node that controls up to four NeoPixel LED strings (up to 20 pixels each). It translates LCC events received over CAN into per-pixel/per-channel lighting effects, group on/off, luminosity changes, and time-based scheduling driven by the LCC broadcast fast clock.

### Key Module Responsibilities

| File | Role |
|---|---|
| [LCC_RPiPico_PixelLights.ino](LCC_RPiPico_PixelLights.ino) | Entry point, node init, consumer/producer registration, serial CLI |
| [NPlights.cpp](NPlights.cpp) | NeoPixel string/group effects, scheduling, luminosity |
| [callbacks.cpp](callbacks.cpp) | OpenLCB event handlers (consumed/produced), fast clock receive, 100ms timer |
| [config_mem_helper.cpp](config_mem_helper.cpp) | I2C EEPROM config storage, CDI-driven memory map |
| [BoardSettings.h](BoardSettings.h) | All hardware pin and storage definitions |
| [NodeConfig.h](NodeConfig.h) | Functional pin assignment layer (NeoPixel_PinA/B/C/D, button pins) |

### Key Data Flow

1. **Lighting control**: LCC consumed event (string/group on/off/toggle, effect, luminosity) → `callbacks.cpp` → `NPlights.cpp`
2. **Time-based scheduling**: LCC broadcast fast-clock event → `callbacks.cpp` → `NPlights.cpp` group schedule check → on/off per group

### Important Implementation Notes

- Dual-core: Core 0 runs LCC/CAN stack; Core 1 runs NeoPixel pixel processing
- `MAX_STRINGS` (4) and `MAX_LIGHTS` (20) in `BoardSettings.h` are also duplicated in `NPlights.cpp` and the `.ino` — keep all three in sync if changed, and update the event table accordingly
- Node ID range `05.01.01.01.94.xx` (Bob Gamble / Southern Piedmont)
- Implements the protected NVM node identity block described in the standard's §7.1 (`NodeIdentity.h`/`.cpp`, `CONFIG_MEM_SIZE` reduced to `32704`, `'N'`/`'Y'` serial provisioning commands) — now also implemented identically in Turntable, Roundhouse, and Clock_Lights.
- `LCC_BOARD_NODE_V30` (generic v3.0 Node board) is now selectable in `ProjectConfig.h`; the existing `NodeConfig.h` button defines (`BLUE_BUTTON_PIN`/`GOLD_BUTTON_PIN`) are `#ifndef`-guarded since the v3.0 board header defines them directly (gp5/gp28) unlike earlier Node boards.
