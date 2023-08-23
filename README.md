[![License](https://img.shields.io/badge/license-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![GitHub release](https://img.shields.io/github/release/as-iotex/w3bstream-client-arduino.svg)](https://github.com/as-iotex/w3bstream-client-arduino/releases)
[![Unit Tests](https://github.com/as-iotex/w3bstream-client-arduino/workflows/Run%20unit%20tests/badge.svg)](https://github.com/as-iotex/w3bstream-client-arduino/actions/workflows/ci.yml)
[![Arduino CI](https://github.com/as-iotex/w3bstream-client-arduino/workflows/Arduino%20CI/badge.svg)](https://github.com/as-iotex/w3bstream-client-arduino/actions/workflows/arduino-ci.yml)
[![Code Formatting](https://github.com/as-iotex/w3bstream-client-arduino/workflows/Code%20formatting/badge.svg)](https://github.com/as-iotex/w3bstream-client-arduino/actions/workflows/code-formatting.yml)
[![Release-please](https://github.com/as-iotex/w3bstream-client-arduino/workflows/release-please/badge.svg)](https://github.com/as-iotex/w3bstream-client-arduino/actions/workflows/release-please.yml)

# W3bstream Client Arduino Library

The W3bstream Client Arduino Library provides an easy-to-use interface for communicating with the W3bstream network using an Arduino board. The library includes functions for establishing a connection, sending and receiving data, and managing the encryption and decryption of data.

## Dependencies

The W3bstreamClient library relies on other Arduino libraries as dependencies. Depending on your application and board, these may be:  

- [PSACrypto](https://github.com/psa-tools/psa-crypto-arduino): A library that provides cryptographic functions for the Arduino platform.  

- [PubSubClient](https://github.com/knolleary/pubsubclient): A library that provides a simple way to publish and subscribe to MQTT messages on an Arduino board.  

Make sure to install these libraries before using the W3bstreamClient library. You can install them using the Arduino IDE or PlatformIO.  

## Installation

### Arduino IDE

To install the W3bstreamClient library using the Arduino IDE, follow these steps:

1. Open the Arduino IDE.
2. Go to **Sketch > Include Library > Manage Libraries**.
3. The Library Manager window will open, showing a list of available libraries.
4. In the search bar, type "W3bstreamClient" and press Enter.
5. Locate the "W3bstreamClient" library in the search results.
6. Click on the library entry to open its details.
7. Click the "Install" button to install the library.
8. Wait for the installation process to complete.
9. After installation, close the Library Manager window.
10. The W3bstreamClient library is now installed and ready to be used.

### Manual Installation

To install the W3bstreamClient library manually, follow these steps:

1. Download the W3bstreamClient library from the [GitHub repository](https://github.com/as-iotex/w3bstream-client-arduino).
2. Extract the downloaded ZIP file.
3. Rename the extracted folder to "W3bstreamClient".
4. Move the "W3bstreamClient" folder to your Arduino libraries directory. The default locations are:
   - **Windows**: `Documents\Arduino\libraries`
   - **Mac**: `Documents/Arduino/libraries`
   - **Linux**: `Arduino/libraries`
5. Restart the Arduino IDE.
6. The W3bstreamClient library should now be available under **Sketch > Include Library** menu.
7. You can now include the library in your Arduino sketches and use its features.

### PlatformIO

To install the W3bstreamClient library using PlatformIO, follow these steps:

1. Create a new PlatformIO project or open an existing one.
2. Open the `platformio.ini` file located in the root of your project.
3. Add the following line to the `[env:<your_board>]` section:

```ini
lib_deps =
    W3bstreamClient
```

Replace <your_board> with the target board/platform for your project (e.g., esp32, arduino_due, etc.).

1. Save the platformio.ini file.
2. PlatformIO will automatically install the W3bstream library and its dependencies when you build/upload your project.

## Usage

### Arduino IDE

1. Open the Arduino IDE.
2. Go to File > Examples > W3bstreamClient to access the example sketches.
3. Select an example sketch to open it.
4. Modify the sketch as needed to fit your requirements.
5. Upload the sketch to your Arduino board.
6. Open the Serial Monitor to view the output.

### PlatformIO

1. Open your PlatformIO project.
2. Navigate to the src folder.
3. Create a new .cpp file or open an existing one.
4. Include the W3bstreamClient library by adding the following line at the top of your file:

```c++
# include <W3bstreamClient.h>
```

For detailed information on using the W3bstreamClient library, including usage examples and API reference, please refer to the [Documentation](https://as-iotex.github.io/w3bstream-client-arduino/index.html).

## Compatible Hardware

The W3bstreamClient library has been tested and is compatible with the following hardware:

- ESP32
- Arduino Nano 33 IoT

Please note that the library may also work with other Arduino-compatible boards, but it has specifically been tested and verified with the above-mentioned hardware.

It's recommended to check the official documentation of your specific board or consult the manufacturer's specifications to ensure compatibility with the W3bstream library.

## Contributing

Contributions are welcome! Please follow the guidelines in [CONTRIBUTING.md](CONTRIBUTING.md) to contribute to this project.

## License

This library is licensed under Apache License 2.0. See the [LICENSE](LICENSE) file for more information.

## Credits

- [IoTeX](https://iotex.io/)
- [MachineFi](https://github.com/machinefi/)
