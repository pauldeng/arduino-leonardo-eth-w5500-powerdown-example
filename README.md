# Arduino W5500 Ethernet Controller Power Saving Example

This repo contains WIZnet W5500 power saving example code.  
It demonstrates:

- Power down W5500
- Power saving by setting the W5500 to low speed (10Mbps)

## Hardware

Any Arduino board/Shield with WIZnet W5500 Ethernet controller. I tested it on:

- [RobotDyn Leonardo ETH v2](https://robotdyn.com/leonardo-eth-v2-with-atmega32u4-ethernet-w5500-arduino-compatible-board.html)
- [DFRobot W5500 Ethernet with POE IoT Board (Arduino Compatible) V2](https://www.dfrobot.com/product-1286.html)

## Software Library

This branch uses Arduino [Ethernet3 library](https://github.com/sstaub/Ethernet3).  
If you use Arduino standard [Ethernet library](https://github.com/arduino-libraries/Ethernet), you can switch to branch [arduino-default-ether-lib](https://github.com/pauldeng/arduino-leonardo-eth-w5500-powerdown-example/tree/arduino-default-ether-lib).

## Usage

1. Clone this project
2. Choose the branch
3. Load this project to PlatformIO
4. Compile and load to target hardware
5. Measure the power consumption change

## Power Consumption

A simple [USB power meter](https://www.amazon.com/Eversame-Multimeter-Chargers-Capacity-Banks-Black/dp/B01D9Y6ZFW) is used to measure the whole board power consumption (including the MCU). At 5.20V, I observed the RobotDyn Leonardo ETH v2:

- W5500 All capable, Auto-negotiation enabled: ~170mA
- W5500 10BT Half-duplex, Auto-negotiation disabled: ~120mA
- W5500 Power Down mode: ~80mA

## References

- [WIZnet W5500 Datasheet](http://wizwiki.net/wiki/lib/exe/fetch.php/products:w5500:w5500_ds_v109e.pdf)
- [Ethernet3 PHY Configuration](http://wizwiki.net/wiki/lib/exe/fetch.php/products:w5500:w5500_ds_v109e.pdf)
- https://github.com/RobotDyn/Leonardo-ETH-V2

## License

[MIT](https://choosealicense.com/licenses/mit/)
