#include <zephyr/device.h>
#include <zephyr/kernel.h>

#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>

#define CONFIG_I2C_SCAN_ADDR_START 8
#define CONFIG_I2C_SCAN_ADDR_STOP 127


int main(void)
{
	const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c2));
	if (!device_is_ready(i2c_dev)) {
		printk("%s: device not ready.", i2c_dev->name);
		return 0;
	}

	printk("\n    | 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x0a 0x0b 0x0c 0x0d 0x0e 0x0f |\n");
	printk(  "----|---------------------------------------------------------------------------------");

	uint8_t error = 0u;
	uint8_t dst;
	uint8_t i2c_dev_cnt = 0;
	struct i2c_msg msgs[1];
	msgs[0].buf = &dst;
	msgs[0].len = 1U;
	msgs[0].flags = I2C_MSG_WRITE | I2C_MSG_STOP;

	/* Use the full range of I2C address for display purpose */	
	for (uint16_t x = 0; x <= 0x7f; x++) {
		/* New line every 0x10 address */
		if (x % 0x10 == 0) {
			printk("|\n0x%02x| ",x);	
		}
		/* Range the test with the start and stop value configured in the kconfig */
		if (x >= CONFIG_I2C_SCAN_ADDR_START && x <= CONFIG_I2C_SCAN_ADDR_STOP)	{	
			/* Send the address to read from */
			error = i2c_transfer(i2c_dev, &msgs[0], 1, x);
				/* I2C device found on current address */
				if (error == 0) {
					printk("0x%02x ",x);
					i2c_dev_cnt++;
				}
				else {
					printk(" --  ");
				}
		} else {
			/* Scan value out of range, not scanned */
			printk("     ");
		}
	}
	printk("|\n");
	printk("\nI2C device(s) found on the bus: %d\nScanning done.\n\n", i2c_dev_cnt);
	printk("Find the registered I2C address on: https://i2cdevices.org/addresses\n\n");

}