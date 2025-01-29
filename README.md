# I2C Scanner

Should work for all the boards with a arduino r3 pin layout.

On ST nucleo 64 boards, the I2C port is accessible through I2C2. This code sample uses I2C2.

## How to use this sample

### Clone the repo to your workspace

git clone https://github.com/ptournoux/zephyr-sample-i2c-scanner.git

### Build

west build --board=nucleo_wl55jc -p always zephyr-sample-i2c-scanner

