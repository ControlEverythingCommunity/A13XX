// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADC121C_A13XX
// This code is designed to work with the ADC121C_A13XX_I2CS_A1304ELHLX-05-T I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Hall-Effect?sku=ADC121C_A13XX_I2CS_A1304ELHLX-05-T#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, ADC121C_A13XX I2C address is 0x50(80)
	ioctl(file, I2C_SLAVE, 0x50);

	// Read 2 bytes of data
	// raw_adc msb, raw_adc lsb
	char data[2] = {0};
	if(read(file, data, 2) != 2)
	{
		printf("Erorr : Input/output Erorr \n");
	}
	else
	{
		// Convert the data to 12-bits
		int raw_adc = ((data[0] & 0x0F) * 256 + data[1]);
		double angle = (raw_adc / 4096.0) * 360;

		// Output data to screen
		printf("Magnetic Angle : %.2f \n", angle);
	}
}
