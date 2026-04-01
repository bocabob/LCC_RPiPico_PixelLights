# LCC RPi Pico PixelLights

An OpenLCB (LCC) node for the Raspberry Pi Pico that controls up to four NeoPixel LED strings. The node receives LCC events over a CAN bus and translates them into pixel lighting effects, luminosity changes, and group-based on/off scheduling — including time-based scheduling driven by an LCC broadcast fast clock.

**Authors:** Jim Kueneman, Bob Gamble
**Hardware version:** 2.6A — **Software version:** 2.1
**Node ID range:** `05.01.01.01.94.xx` — assigned to Bob Gamble / Southern Piedmont

---

## Features

- Four independent NeoPixel LED strings, up to 20 pixels each
- Per-pixel, per-channel (R/G/B) effect configuration: off, constant, blink, flicker
- Six independently controllable groups with LCC event-based on/off
- Per-group time-based scheduling driven by the LCC broadcast fast clock
- Two global luminosity levels (full / dim) controlled by LCC events
- String-level on/off/toggle and effects on/off/toggle via LCC events
- Per-string dimmer toggle
- Configuration stored in external I2C EEPROM (non-volatile, survives power cycles)
- Configuration accessible and editable via any standard LCC configuration tool (JMRI, etc.)
- OTA firmware update support via LittleFS + PicoOTA
- Serial monitor debug interface for NVM management and diagnostics
- Dual-core RP2040: core 0 runs the LCC/CAN stack, core 1 runs pixel processing

---

## Hardware

### Board

Raspberry Pi Pico (RP2040). Use the **Earl F. Philhower** board library, not the Arduino Mbed one.

### CAN Interface — MCP2517/2518 (SPI)

| Signal | GPIO |
|--------|------|
| CS     | 17   |
| INT    | 20   |
| SCK    | 18   |
| SDI    | 19   |
| SDO    | 16   |
| SPI bus | SPI (default) |

### NeoPixel Output Pins

| String | GPIO |
|--------|------|
| A      | 2    |
| B      | 6    |
| C      | 7    |
| D      | 3    |

Strings use the RP2040 PIO hardware via `NeoPixelBusLg` (`Rp2040x4Pio1Ws2811Method`). For WS2812 LEDs, change the method to `Rp2040x4Pio1Ws2812xMethod` in `NPlights.cpp`.

> **NeoPixel wiring best practices:**
> - Add a 1000 µF capacitor across the strip's + and − supply.
> - Place a 300–500 Ω resistor in series with the data line.
> - Connect ground first, then power, then data — never on a live circuit.
> - Use a logic-level converter on the data line when driving 5 V strips from the 3.3 V Pico.

### I2C EEPROM (Configuration Memory)

| Signal | GPIO |
|--------|------|
| SDA    | 26   |
| SCL    | 27   |
| Address | 0x50 |
| Bus    | Wire1 (`STOR_WIRE`) |

Supported device: 24LC256 (32 KB). Alter `I2C_DEVICESIZE` and `CONFIG_MEM_SIZE` in `BoardSettings.h` to match a different chip.

### Second I2C Bus (I2C2)

| Signal | GPIO |
|--------|------|
| SDA    | 4    |
| SCL    | 5    |

---

## Software Prerequisites

Install the following libraries through the Arduino IDE Library Manager or by manual installation:

| Library | Purpose |
|---------|---------|
| [arduino-pico](https://github.com/earlephilhower/arduino-pico) by Earl F. Philhower | RP2040 board support (required — do **not** use the Arduino Mbed board) |
| [NeoPixelBus](https://github.com/Makuna/NeoPixelBus) by Makuna | NeoPixel control with luminance support |
| [LibPrintf](https://github.com/embeddedartistry/arduino-printf) | `printf` support for Arduino |
| [I2C_EEPROM](https://github.com/RobTillaart/I2C_EEPROM) by Rob Tillaart | I2C EEPROM read/write (selected via `USE_TILLAART` in `BoardSettings.h`) |
| PicoOTA | OTA firmware update (bundled with the Philhower board library) |
| LittleFS | Filesystem for OTA image staging (bundled with the Philhower board library) |

The OpenLCB stack is included in the `src/` directory and does not require a separate installation.

---

## Configuration (`BoardSettings.h`)

All hardware settings are in `BoardSettings.h`. Key options:

| Setting | Default | Description |
|---------|---------|-------------|
| `USE_I2C_STORAGE` | enabled | Use external I2C EEPROM for config memory |
| `EXTERNAL_EEPROM` | enabled | EEPROM chip type (vs. `EXTERNAL_FRAM`) |
| `USE_TILLAART` | enabled | Use Rob Tillaart's EEPROM library |
| `CONFIG_MEM_SIZE` | 32768 | Config memory size in bytes (must match or be less than `I2C_DEVICESIZE`) |
| `I2C_DEVICESIZE` | 32768 | EEPROM chip capacity in bytes (24LC256 = 32768) |
| `MAX_STRINGS` | 4 | Maximum number of NeoPixel strings |
| `MAX_LIGHTS` | 20 | Maximum LEDs per string |
| `MAX_LUMINANCE` | 100 | Full-brightness luminance level (0–255) |
| `EEPROM_VERSION` | 8 | Config schema version |

---

## LCC Configuration Memory Layout

Configuration is stored in address space `0xFD` (space 253) starting at address `0x00`. The layout is defined by the CDI XML in `CDI.xml` and maps directly to the `config_mem_t` struct in `config_mem_helper.h`.

| Segment | Address | Contents |
|---------|---------|---------|
| Node ID | 0x00 | Node name (62 bytes) and description (63 bytes) |
| Reset Control | 0x7D | Reset-on-boot flag |
| Attributes | 0x7E | String count, luminosity levels, effect frequency, global luminosity event IDs |
| Controls | 0x92 | 6 groups × (on event, off event, on time HH:MM, off time HH:MM) |
| Strings | 0x10A | 4 strings × (description, head count, 7 event IDs, 20 pixels × 3 leads × 6 fields) |

### Consumed Events (per node, in registration order)

| Index | Event |
|-------|-------|
| 0 | Full luminosity on |
| 1 | Low luminosity on |
| 2–13 | Group 0–5 on/off (pairs) |
| 14–41 | String 0–3 × 7 events (all-on, all-off, all-toggle, effects-on, effects-off, effects-toggle, dimmer-toggle) |

---

## LED Effects

Each LED lead (R, G, or B channel) is independently configured with:

| Field | Description |
|-------|-------------|
| `intensity` | Channel brightness (0–255) |
| `effect` | 0 = off, 1 = constant, 2 = blink, 3 = flicker |
| `cycles_on` | Effect cycles to stay on (blink/flicker) |
| `cycles_off` | Effect cycles to stay off (blink/flicker) |
| `starting_cycle` | Initial state (0 or 1) for blink/flicker |
| `group` | Group number (0–5) that gates this channel |

The effect processing cycle period is set by `effect_cycle_frequency` in the Attributes configuration segment (in milliseconds, default 100 ms).

---

## First Boot / NVM Initialization

On first power-up after a fresh firmware flash, the EEPROM will contain `0xFF` bytes. The sketch detects this and automatically initializes the EEPROM with default values, then registers all consumer event IDs with the LCC stack.

To manually reinitialize NVM, use the serial monitor commands below.

---

## Serial Monitor Debug Interface

Connect at **115200 baud**. The following single-character commands are available:

| Key | Action |
|-----|--------|
| `h` | Print help |
| `c` | Clear all NVM to `0x00` |
| `i` | Write CDI default values to NVM |
| `r` | Reset NVM to `0xFF` (simulates factory-fresh EEPROM) |
| `p` | Toggle LCC message logging (prints CAN frames as GridConnect strings) |
| `m` | Toggle config memory read/write logging |
| `t` | Display current fast clock time |
| `q` | Send a fast clock query on the LCC bus |

---

## Firmware Updates (OTA)

Firmware updates are supported via the LCC Memory Configuration protocol (firmware address space). A configuration tool (e.g., JMRI) can upload a new `.bin` image, which is staged to the Pico's LittleFS filesystem as `bootloader.bin`. On the next reboot, PicoOTA applies the update.

---

## Project Structure

```
LCC_RPiPico_PixelLights/
├── LCC_RPiPico_PixelLights.ino  # Main sketch: setup, loop (LCC), loop1 (pixels)
├── BoardSettings.h              # Hardware pin assignments and compile-time options
├── NPlights.h / .cpp            # NeoPixel state machine and effect processing
├── callbacks.h / .cpp           # LCC event and protocol callbacks
├── config_mem_helper.h / .cpp   # Config memory struct, NVM read/write helpers
├── openlcb_user_config.h / .c   # Node parameters and CDI binary data
├── can_user_config.h            # CAN buffer depth configuration
├── mdebugging.h                 # Conditional debug print macros
├── CDI.xml                      # Human-readable CDI for reference / tooling
├── sketch.yaml                  # Arduino CLI build descriptor
└── src/                         # OpenLCB C library (do not modify)
```

---

## License

BSD 2-Clause. Copyright © 2026 Jim Kueneman & Bob Gamble. See source file headers for full license text.
