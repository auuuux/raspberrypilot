/*
 * pios_lsm330.h
 *
 * Created: 6/2/2012 3:59:17 PM
 *  Author: zlewko
 */ 

#ifndef PIOS_LSM330_H_
#define PIOS_LSM330_H_

#include <pios.h>
#include <stdbool.h>

// LSM330 I�C Address
// -------------------------------------------------------------------------
#define PIOS_LSM330_I2C_ADAPTER				PIOS_I2C_MAIN_ADAPTER
// 7 Bit LSB follows the SDO_A pin. This address assumes grounded.
#define PIOS_LSM330_A_I2C_ADDR_DATASHEET	0x30 // Add 2 if SDO_A == 1
#define PIOS_LSM330_A_I2C_ADDR				(PIOS_LSM330_A_I2C_ADDR_DATASHEET >> 1)
// 7 Bit LSB follows the SDO_G pin. This address assumes grounded.
#define PIOS_LSM330_G_I2C_ADDR_DATASHEET	0xD4 // Add 2 if SDO_G == 1
#define PIOS_LSM330_G_I2C_ADDR				(PIOS_LSM330_G_I2C_ADDR_DATASHEET >> 1)

/*  In order to read multiple bytes, it is necessary to assert the most significant
 bit of the subaddress field. In other words, SUB(7) must be equal to 1 while SUB(6-0)
 represents the address of first register to be read. The 7 LSb represent the actual
 register address while the MSb enables address auto increment. If the MSb of the SUB
 field is �1�, the SUB (register address) will be automatically increased to allow
 multiple data read/write. */
#define PIOS_LSM330_G_REPEATED				(1 << 7)

// Acceleromter Register Map
// -------------------------------------------------------------------------
#define PIOS_CTRL_REG1_A					0x20
#define PIOS_CTRL_REG2_A					0x21
#define PIOS_CTRL_REG3_A					0x22
#define PIOS_CTRL_REG4_A					0x23
#define PIOS_CTRL_REG5_A					0x24
#define PIOS_CTRL_REG6_A					0x25
#define PIOS_REFERENCE_A					0x26
#define PIOS_STATUS_REG_A					0x27
#define PIOS_OUT_X_L_A						0x28
#define PIOS_OUT_X_H_A						0x29
#define PIOS_OUT_Y_L_A						0x2A
#define PIOS_OUT_Y_H_A						0x2B
#define PIOS_OUT_Z_L_A						0x2C
#define PIOS_OUT_Z_H_A						0x2D
#define PIOS_FIFO_CTRL_REG					0x2E
#define PIOS_FIFO_SRC_REG					0x2F
#define PIOS_INT1_CFG_A						0x30
#define PIOS_INT1_SOURCE_A					0x31
#define PIOS_INT1_THS_A						0x32
#define PIOS_LSM330_INT1_DURATION_A			0x33
#define PIOS_LSM330_INT2_CFG_A				0x34
#define PIOS_LSM330_INT2_SOURCE_A			0x35
#define PIOS_LSM330_INT2_THS_A				0x36
#define PIOS_LSM330_INT2_DURATION_A			0x37
#define PIOS_LSM330_CLICK_CFG_A				0x38
#define PIOS_LSM330_CLICK_SRC_A				0x39
#define PIOS_LSM330_CLICK_THS_A				0x3A
#define PIOS_LSM330_TIME_LIMIT_A			0x3B
#define PIOS_LSM330_TIME_LATENCY_A			0x3C
#define PIOS_LSM330_TIME_WINDOW_A			0x3D
#define PIOS_LSM330_Act_THS					0x3E
#define PIOS_LSM330_Act_DUR					0x3F

// Gyroscope Register Map
// -------------------------------------------------------------------------
#define PIOS_LSM330_WHO_AM_I_G				0x0F // Value should be 0xC4
#define PIOS_LSM330_CTRL_REG1_G				0x20
#define PIOS_LSM330_CTRL_REG2_G				0x21
#define PIOS_LSM330_CTRL_REG3_G				0x22
#define PIOS_LSM330_CTRL_REG4_G				0x23
#define PIOS_LSM330_CTRL_REG5_G				0x24
#define PIOS_LSM330_REFERENCE_G				0x25
#define PIOS_LSM330_OUT_TEMP_G				0x26
#define PIOS_LSM330_STATUS_REG_G			0x27
#define PIOS_LSM330_OUT_X_L_G				0x28
#define PIOS_LSM330_OUT_X_H_G				0x29
#define PIOS_LSM330_OUT_Y_L_G				0x2A
#define PIOS_LSM330_OUT_Y_H_G				0x2B
#define PIOS_LSM330_OUT_Z_L_G				0x2C
#define PIOS_LSM330_OUT_Z_H_G				0x2D
#define PIOS_LSM330_FIFO_CTRL_REG_G			0x2E
#define PIOS_LSM330_FIFO_SRC_REG_G			0x2F
#define PIOS_LSM330_INT1_CFG_G				0x30
#define PIOS_LSM330_INT1_SRC_G				0x31
#define PIOS_LSM330_INT1_TSH_XH_G			0x32
#define PIOS_LSM330_INT1_TSH_XL_G			0x33
#define PIOS_LSM330_INT1_TSH_YH_G			0x34
#define PIOS_LSM330_INT1_TSH_YL_G			0x35
#define PIOS_LSM330_INT1_TSH_ZH_G			0x36
#define PIOS_LSM330_INT1_TSH_ZL_G			0x37
#define PIOS_LSM330_INT1_DURATION_G			0x38

// CTRL_REG1_G (20h)
// [DR1 DR0 BW1 BW0 PD Zen Xen Yen]
// DR<1:0> is used to set ODR selection. BW <1:0> is used to set bandwidth selection.
// 											Value			ODR(Hz)		Cut-Off
// -----------------------------------------------------------------------------
#define PIOS_LSM330_ODR_0_G					(0x00 << 4)	//	95			12.5
#define PIOS_LSM330_ODR_1_G					(0x01 << 4)	//	95			25
#define PIOS_LSM330_ODR_2_G					(0x02 << 4)	//	95			25
#define PIOS_LSM330_ODR_3_G					(0x03 << 4)	//	95			25
#define PIOS_LSM330_ODR_4_G					(0x04 << 4)	//	190			12.5
#define PIOS_LSM330_ODR_5_G					(0x05 << 4)	//	190			25
#define PIOS_LSM330_ODR_6_G					(0x06 << 4)	//	190			50
#define PIOS_LSM330_ODR_7_G					(0x07 << 4)	//	190			70
#define PIOS_LSM330_ODR_8_G					(0x08 << 4)	//	380			20
#define PIOS_LSM330_ODR_9_G					(0x09 << 4)	//	380			25
#define PIOS_LSM330_ODR_A_G					(0x0A << 4)	//	380			50
#define PIOS_LSM330_ODR_B_G					(0x0B << 4)	//	380			100
#define PIOS_LSM330_ODR_C_G					(0x0C << 4)	//	760			30
#define PIOS_LSM330_ODR_D_G					(0x0D << 4)	//	760			35
#define PIOS_LSM330_ODR_E_G					(0x0E << 4)	//	760			50
#define PIOS_LSM330_ODR_F_G					(0x0F << 4)	//	760			100

// PD Power-down mode enable. Default value: 0
// (0: Power-down mode, 1: Normal mode or Sleep mode)
#define PIOS_LSM330_PD_G					(1 << 3)
// Zen Z axis enable. Default value: 1
// (0: Z axis disabled; 1: Z axis enabled)
#define PIOS_LSM330_ZEN_G					(1 << 2)
// Yen Y axis enable. Default value: 1
// (0: Y axis disabled; 1: Y axis enabled)
#define PIOS_LSM330_YEN_G					(1 << 1)
// Xen X axis enable. Default value: 1
// (0: X axis disabled; 1: X axis enabled)
#define PIOS_LSM330_XEN_G					(1 << 0)

// CTRL_REG1_A (20h)
// ODR3-0 Data rate selection. Default value: 0
// (0000: Power-down; Others: Refer to Table 21, �Data rate configuration�)
// ------------------------------------------------------------------------------------------
#define PIOS_LSM330_ODR_0_A					(0 << 4)	//	Power-down mode
#define PIOS_LSM330_ODR_1_A					(1 << 4)	//	Normal / Low power mode (1 Hz)
#define PIOS_LSM330_ODR_2_A					(2 << 4)	//	Normal / Low power mode (10 Hz)
#define PIOS_LSM330_ODR_3_A					(3 << 4)	//	Normal / Low power mode (25 Hz)
#define PIOS_LSM330_ODR_4_A					(4 << 4)	//	Normal / Low power mode (50 Hz)
#define PIOS_LSM330_ODR_5_A					(5 << 4)	//	Normal / Low power mode (100 Hz)
#define PIOS_LSM330_ODR_6_A					(6 << 4)	//	Normal / Low power mode (200 Hz)
#define PIOS_LSM330_ODR_7_A					(7 << 4)	//	Normal / Low power mode (400 Hz)
#define PIOS_LSM330_ODR_8_A					(8 << 4)	//	Low power mode (1.620 kHz)
#define PIOS_LSM330_ODR_9_A					(9 << 4)	//	Normal (1.344 kHz) / Low power mode (5.376 kHz)
// LPen, Low power mode enable. Default value: 0
// (0: Normal mode, 1: Low power mode)
#define PIOS_LSM330_LPEN_A					(1 << 3)
// Zen, Z axis enable. Default value: 1                
// (0: Z axis disabled; 1: Z axis enabled)        
#define PIOS_LSM330_ZEN_A					(1 << 2)
// Yen, Y axis enable. Default value: 1                
// (0: Y axis disabled; 1: Y axis enabled)        
#define PIOS_LSM330_YEN_A					(1 << 1)
// Xen, X axis enable. Default value: 1                
// (0: X axis disabled; 1: X axis enabled)        
#define PIOS_LSM330_XEN_A					(1 << 0)


// Raspberry Pilot LSM330 Gyro Register Settings
// ------------------------------------------------------------------------------------------------
// 380 samples, 50hz bw, all axis enabled - may want to speed this up later.
#define PIOS_LSM330_CTL_REG1_G_SETTING		(PIOS_LSM330_ODR_A_G	| \
											 PIOS_LSM330_PD_G		| \
											 PIOS_LSM330_ZEN_G		| \
											 PIOS_LSM330_YEN_G		| \
											 PIOS_LSM330_XEN_G)
#define PIOS_LSM330_CTL_REG2_G_SETTING		0x00 // default
#define PIOS_LSM330_CTL_REG3_G_SETTING		0x00 // default
#define PIOS_LSM330_CTL_REG4_G_SETTING		0xB0 // block data update between msb and lsb, 2000 deg/s fs
#define PIOS_LSM330_CTL_REG5_G_SETTING		0x00 // default value
#define PIOS_LSM330_G_READ_START			PIOS_LSM330_OUT_X_L_G
#define PIOS_LSM330_G_PER_LSB				(float) 4000.0/65535


// public api
bool PIOS_LSM330_init_gyro(void);
bool PIOS_LSM330_read_gyro(float gyro_vector[3]);

#endif /* PIOS_LSM330_I2C_H_ */
