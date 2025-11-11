# MiniConsole ROADMAP

Structure and descriptions of new features for the main menu.

## 1. Settings

### Description
Global device configuration menu to customize console behavior, accessibility, and appearance.

### Recommended Settings List
- **Screen Brightness**: Manual brightness value 0-255 for OLED
- **Button Mapping**: Swap button functions or invert directions
- **Save Settings**: Persist configuration in SPIFFS
- **Reset to Defaults**: Restore factory settings

---

## 2. Clock

### Description
Clock system with timer and stopwatch. Shows device uptime or can sync via NTP if Wi-Fi is added.

### Suggested Features
- **Clock**: Display uptime in HH:MM:SS format
- **Timer**: Configurable countdown (minutes/seconds)
- **Stopwatch**: Start/Stop/Reset with real-time display
- **Format**: Support 24/12 hour mode (configurable in Settings)
- **Alert**: LED blinks when timer reaches zero

---

## 3. Leaderboards Viewer

### Description
Interactive leaderboard viewer. Allows navigation, visualization, and management of saved high scores.

### Suggested Features
- **List Top Scores**: Display top 10-20 high scores
- **Details**: Player name, score, date, game type
- **Delete Entry**: Remove specific score entry
- **Clear Leaderboard**: Wipe all entries (with confirmation)
- **Pagination**: Navigate through pages of 4 lines (OLED limit)

---

## 4. Export Leaderboards via Bluetooth

### Description
Export leaderboard data via Bluetooth Low Energy (BLE). Enables sending scores to a smartphone or PC with BLE capability.

### Suggested Features
- **BLE Pairing**: Device acts as GATT server
- **GATT Service**: Expose characteristic with leaderboard as text
- **Manual Export**: Option in `leaderboardMenu()` to start export
- **Protocol**: Send CSV or JSON in fragments (ESP32 BLE MTU: 20-256 bytes)
- **Status Feedback**: Show transfer progress on OLED

---

## 5. Quick Utilities

### Description
Collection of small practical tools: generators, converters, diagnostic tools, and component tests.

### Suggested Utilities
- **Random Number Generator**: Generate random number in configurable range (0-100, 0-1000, etc.)
- **Binary/Decimal Converter**: Interactive conversion between formats
- **LED Strobe Generator**: Create LED blink patterns (configurable speed)
- **Light Level Reader**: Show LDR value in real-time with min/max
- **Simple Calculator**: Basic 4-operation calculator (+, -, *, /)
- **Text Composer**: Write small texts and save to SPIFFS
- **Checksum Calculator**: Calculate byte sum of a file

---

## 6. About

### Description
Information screen showing project details including version, author, license, and main dependencies. Ideal for credits and references.

### Suggested Content
- **Project Name**: "MiniConsole"
- **Version**: (e.g. v1.0.0)
- **Build Date**: Automatic or manual compilation timestamp
- **Author**: "Brickle-Pickle"
- **License**: License type and reference
- **Hardware**: List of components (ESP32, OLED, buttons, etc.)
- **Dependencies**: Main libraries (SSD1306, SPIFFS, etc.)
- **Links**: GitHub repository (if applicable)