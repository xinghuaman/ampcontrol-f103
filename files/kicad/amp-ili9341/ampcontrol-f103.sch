EESchema Schematic File Version 4
LIBS:ampcontrol-f103-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GNDD #PWR010
U 1 1 5C043025
P 5900 6450
F 0 "#PWR010" H 5900 6200 50  0001 C CNN
F 1 "GNDD" H 5904 6295 50  0000 C CNN
F 2 "" H 5900 6450 50  0001 C CNN
F 3 "" H 5900 6450 50  0001 C CNN
	1    5900 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 6250 5800 6350
Wire Wire Line
	5800 6350 5900 6350
Wire Wire Line
	6000 6350 6000 6250
Wire Wire Line
	5900 6250 5900 6350
Connection ~ 5900 6350
Wire Wire Line
	5900 6350 6000 6350
Wire Wire Line
	5900 6450 5900 6350
$Comp
L power:+3V3 #PWR09
U 1 1 5C0430F5
P 5800 3050
F 0 "#PWR09" H 5800 2900 50  0001 C CNN
F 1 "+3V3" H 5815 3223 50  0000 C CNN
F 2 "" H 5800 3050 50  0001 C CNN
F 3 "" H 5800 3050 50  0001 C CNN
	1    5800 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 3250 5700 3150
Wire Wire Line
	5700 3150 5800 3150
Wire Wire Line
	5900 3150 5900 3250
Wire Wire Line
	5800 3250 5800 3150
Connection ~ 5800 3150
Wire Wire Line
	5800 3150 5900 3150
Wire Wire Line
	5800 3050 5800 3150
$Comp
L power:+3V3 #PWR02
U 1 1 5C0435B6
P 2800 5600
F 0 "#PWR02" H 2800 5450 50  0001 C CNN
F 1 "+3V3" H 2815 5773 50  0000 C CNN
F 2 "" H 2800 5600 50  0001 C CNN
F 3 "" H 2800 5600 50  0001 C CNN
	1    2800 5600
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR01
U 1 1 5C0435EA
P 2600 5750
F 0 "#PWR01" H 2600 5500 50  0001 C CNN
F 1 "GNDD" H 2604 5595 50  0000 C CNN
F 2 "" H 2600 5750 50  0001 C CNN
F 3 "" H 2600 5750 50  0001 C CNN
	1    2600 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 5650 2600 5650
Wire Wire Line
	2600 5650 2600 5750
Wire Wire Line
	2800 5750 2800 5600
NoConn ~ 3000 5850
Wire Wire Line
	3000 5950 2750 5950
Text Label 2750 5950 0    50   ~ 0
RS
Wire Wire Line
	3000 6050 2750 6050
Wire Wire Line
	2800 5750 3000 5750
Wire Wire Line
	3000 7050 2750 7050
Wire Wire Line
	3000 7150 2750 7150
Wire Wire Line
	3000 7250 2750 7250
Wire Wire Line
	3000 7450 2750 7450
Text Label 2750 6050 0    50   ~ 0
WR
Text Label 2750 6150 0    50   ~ 0
RD
Text Label 2750 7050 0    50   ~ 0
CS
Text Label 2750 7150 0    50   ~ 0
F_CS
Text Label 2750 7250 0    50   ~ 0
NRST
Text Label 2750 7450 0    50   ~ 0
BCKL
NoConn ~ 3000 7550
$Comp
L Connector_Generic:Conn_02x20_Top_Bottom J1
U 1 1 5C047533
P 3200 6550
F 0 "J1" H 3250 7667 50  0000 C CNN
F 1 "Conn_LCD" H 3250 7576 50  0000 C CNN
F 2 "ampcontrol-f103:PinSocket_2x20_P2.54mm_Vertical_Top_Bottom" H 3200 6550 50  0001 C CNN
F 3 "~" H 3200 6550 50  0001 C CNN
	1    3200 6550
	1    0    0    -1  
$EndComp
NoConn ~ 3500 7550
NoConn ~ 3500 7450
NoConn ~ 3500 6750
Wire Wire Line
	3500 5650 3750 5650
Wire Wire Line
	3750 5750 3500 5750
Wire Wire Line
	3500 5850 3750 5850
Wire Wire Line
	3750 5950 3500 5950
Wire Wire Line
	3500 6050 3750 6050
Wire Wire Line
	3750 6150 3500 6150
Wire Wire Line
	3500 6250 3750 6250
Wire Wire Line
	3750 6350 3500 6350
Wire Wire Line
	3500 6450 3750 6450
Wire Wire Line
	3500 6550 3750 6550
Wire Wire Line
	3500 6650 3750 6650
Wire Wire Line
	3500 6850 3750 6850
Wire Wire Line
	3500 6950 3750 6950
Wire Wire Line
	3500 7050 3750 7050
Wire Wire Line
	3500 7150 3750 7150
Wire Wire Line
	3500 7250 3750 7250
Wire Wire Line
	3500 7350 3750 7350
NoConn ~ 3000 7350
Text Label 3750 5650 2    50   ~ 0
DB0
Text Label 3750 5750 2    50   ~ 0
DB1
Text Label 3750 5850 2    50   ~ 0
DB2
Text Label 3750 5950 2    50   ~ 0
DB3
Text Label 3750 6050 2    50   ~ 0
DB4
Text Label 3750 6150 2    50   ~ 0
DB5
Text Label 3750 6250 2    50   ~ 0
DB6
Text Label 3750 6350 2    50   ~ 0
DB7
Text Label 3750 6450 2    50   ~ 0
T_CLK
Text Label 3750 6550 2    50   ~ 0
T_CS
Text Label 3750 6650 2    50   ~ 0
T_DIN
Text Label 3750 6850 2    50   ~ 0
T_DO
Text Label 3750 6950 2    50   ~ 0
T_IRQ
Text Label 3750 7050 2    50   ~ 0
SD_DO
Text Label 3750 7150 2    50   ~ 0
SD_CLK
Text Label 3750 7250 2    50   ~ 0
SD_DIN
Text Label 3750 7350 2    50   ~ 0
SD_CS
$Comp
L MCU_ST_STM32F1:STM32F103CBTx U2
U 1 1 5C050C11
P 5800 4750
F 0 "U2" H 5250 6200 50  0000 C CNN
F 1 "STM32F103CBTx" H 5800 4750 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 5200 3350 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 5800 4750 50  0001 C CNN
	1    5800 4750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5200 4550 4800 4550
Wire Wire Line
	5200 4650 4800 4650
Wire Wire Line
	4800 4750 5200 4750
Wire Wire Line
	5200 4850 4800 4850
Wire Wire Line
	5200 4950 4800 4950
Wire Wire Line
	5200 5050 4800 5050
Wire Wire Line
	5200 5150 4800 5150
Wire Wire Line
	5200 5250 4800 5250
Text Label 4800 4550 0    50   ~ 0
DB0
Text Label 4800 4650 0    50   ~ 0
DB1
Text Label 4800 4750 0    50   ~ 0
DB2
Text Label 4800 4850 0    50   ~ 0
DB3
Text Label 4800 4950 0    50   ~ 0
DB4
Text Label 4800 5050 0    50   ~ 0
DB5
Text Label 4800 5150 0    50   ~ 0
DB6
Text Label 4800 5250 0    50   ~ 0
DB7
Wire Wire Line
	5200 6050 4800 6050
Text Label 4800 6050 0    50   ~ 0
HW_RST
Wire Wire Line
	6500 4950 6900 4950
Wire Wire Line
	6500 5050 6900 5050
Text Label 6900 5050 2    50   ~ 0
WR
Wire Wire Line
	6500 5150 6900 5150
Text Label 6900 5150 2    50   ~ 0
RS
Wire Wire Line
	6500 5250 6900 5250
Text Label 6900 5250 2    50   ~ 0
CS
Text Label 6900 4150 2    50   ~ 0
BCKL
NoConn ~ 2750 6250
NoConn ~ 2750 6350
NoConn ~ 2750 6450
NoConn ~ 2750 6550
NoConn ~ 2750 6650
NoConn ~ 2750 6750
NoConn ~ 2750 6850
NoConn ~ 2750 6950
NoConn ~ 2750 7150
NoConn ~ 3750 6450
NoConn ~ 3750 6550
NoConn ~ 3750 6650
NoConn ~ 3750 6850
NoConn ~ 3750 6950
NoConn ~ 3750 7050
NoConn ~ 3750 7150
NoConn ~ 3750 7250
NoConn ~ 3750 7350
$Comp
L Device:Crystal_Small Y2
U 1 1 5C0E4C09
P 7400 3850
F 0 "Y2" H 7450 3700 50  0000 L CNN
F 1 "8MHz" H 7400 3700 50  0000 R CNN
F 2 "Crystal:Crystal_HC49-4H_Vertical" H 7400 3850 50  0001 C CNN
F 3 "~" H 7400 3850 50  0001 C CNN
	1    7400 3850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6500 4150 6900 4150
Wire Wire Line
	6900 5350 6500 5350
Wire Wire Line
	6900 5450 6500 5450
Text Label 6900 5350 2    50   ~ 0
MUTE
Text Label 6900 5450 2    50   ~ 0
STBY
Wire Wire Line
	5200 5350 4800 5350
Text Label 4800 5350 0    50   ~ 0
IR
Wire Wire Line
	5200 5450 4800 5450
Wire Wire Line
	4800 5550 5200 5550
Text Label 4800 5450 0    50   ~ 0
TX
Text Label 4800 5550 0    50   ~ 0
RX
$Comp
L Device:C C6
U 1 1 5C12356D
P 7600 3650
F 0 "C6" H 7485 3604 50  0000 R CNN
F 1 "20p" H 7485 3695 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 7638 3500 50  0001 C CNN
F 3 "~" H 7600 3650 50  0001 C CNN
	1    7600 3650
	-1   0    0    1   
$EndComp
$Comp
L Device:C C5
U 1 1 5C1235AB
P 7200 3650
F 0 "C5" H 7085 3604 50  0000 R CNN
F 1 "20p" H 7085 3695 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 7238 3500 50  0001 C CNN
F 3 "~" H 7200 3650 50  0001 C CNN
	1    7200 3650
	-1   0    0    1   
$EndComp
$Comp
L Device:C C4
U 1 1 5C12CD09
P 7600 4550
F 0 "C4" H 7485 4504 50  0000 R CNN
F 1 "6p2" H 7485 4595 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 7638 4400 50  0001 C CNN
F 3 "~" H 7600 4550 50  0001 C CNN
	1    7600 4550
	-1   0    0    1   
$EndComp
$Comp
L Device:C C3
U 1 1 5C12CD53
P 7200 4550
F 0 "C3" H 7315 4596 50  0000 L CNN
F 1 "6p2" H 7315 4505 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 7238 4400 50  0001 C CNN
F 3 "~" H 7200 4550 50  0001 C CNN
	1    7200 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR014
U 1 1 5C138140
P 7600 4700
F 0 "#PWR014" H 7600 4450 50  0001 C CNN
F 1 "GNDD" H 7604 4545 50  0000 C CNN
F 2 "" H 7600 4700 50  0001 C CNN
F 3 "" H 7600 4700 50  0001 C CNN
	1    7600 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal_Small Y1
U 1 1 5C138248
P 7400 4350
F 0 "Y1" H 7350 4500 50  0000 R CNN
F 1 "32768" H 7400 4500 50  0000 L CNN
F 2 "Crystal:Crystal_C38-LF_D3.0mm_L8.0mm_Vertical" H 7400 4350 50  0001 C CNN
F 3 "~" H 7400 4350 50  0001 C CNN
	1    7400 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 4250 7600 4250
Wire Wire Line
	7500 4350 7600 4350
$Comp
L power:GNDD #PWR012
U 1 1 5C144D0F
P 7200 4700
F 0 "#PWR012" H 7200 4450 50  0001 C CNN
F 1 "GNDD" H 7204 4545 50  0000 C CNN
F 2 "" H 7200 4700 50  0001 C CNN
F 3 "" H 7200 4700 50  0001 C CNN
	1    7200 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR016
U 1 1 5C14C7F5
P 7200 3500
F 0 "#PWR016" H 7200 3250 50  0001 C CNN
F 1 "GNDD" H 7204 3345 50  0000 C CNN
F 2 "" H 7200 3500 50  0001 C CNN
F 3 "" H 7200 3500 50  0001 C CNN
	1    7200 3500
	-1   0    0    1   
$EndComp
Wire Wire Line
	6500 4350 7200 4350
Wire Wire Line
	7200 4350 7300 4350
Wire Wire Line
	6900 4550 6500 4550
Wire Wire Line
	6900 4650 6500 4650
Text Label 6900 4550 2    50   ~ 0
SP_L
Text Label 6900 4650 2    50   ~ 0
SP_R
Wire Wire Line
	6500 4750 6900 4750
Text Label 6900 4750 2    50   ~ 0
BOOT1
Wire Wire Line
	6500 3650 6900 3650
Text Label 6900 3650 2    50   ~ 0
BOOT0
Wire Wire Line
	6500 4850 6900 4850
Text Label 6900 4850 2    50   ~ 0
SCK
$Comp
L power:+5V #PWR013
U 1 1 5C166122
P 7200 5150
F 0 "#PWR013" H 7200 5000 50  0001 C CNN
F 1 "+5V" H 7215 5323 50  0000 C CNN
F 2 "" H 7200 5150 50  0001 C CNN
F 3 "" H 7200 5150 50  0001 C CNN
	1    7200 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R18
U 1 1 5C166181
P 7200 5350
F 0 "R18" H 7270 5396 50  0000 L CNN
F 1 "4k7" H 7270 5305 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 7130 5350 50  0001 C CNN
F 3 "~" H 7200 5350 50  0001 C CNN
	1    7200 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 5550 7200 5550
$Comp
L power:+5V #PWR015
U 1 1 5C16F716
P 7600 5150
F 0 "#PWR015" H 7600 5000 50  0001 C CNN
F 1 "+5V" H 7615 5323 50  0000 C CNN
F 2 "" H 7600 5150 50  0001 C CNN
F 3 "" H 7600 5150 50  0001 C CNN
	1    7600 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R19
U 1 1 5C16F733
P 7600 5350
F 0 "R19" H 7670 5396 50  0000 L CNN
F 1 "4k7" H 7670 5305 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 7530 5350 50  0001 C CNN
F 3 "~" H 7600 5350 50  0001 C CNN
	1    7600 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 5500 7200 5550
Wire Wire Line
	7200 5200 7200 5150
Wire Wire Line
	7600 5150 7600 5200
Wire Wire Line
	7600 5500 7600 5650
Wire Wire Line
	7600 5650 6500 5650
Text Label 6900 5550 2    50   ~ 0
SCL
Text Label 6900 5650 2    50   ~ 0
SDA
Text Label 4800 5950 0    50   ~ 0
SWCLK
Text Label 4800 5850 0    50   ~ 0
SWDIO
Wire Wire Line
	6500 5750 6900 5750
Wire Wire Line
	6900 5850 6500 5850
Wire Wire Line
	6500 5950 6900 5950
Wire Wire Line
	6900 6050 6500 6050
Text Label 6900 5750 2    50   ~ 0
SD_CS
Text Label 6900 5850 2    50   ~ 0
SD_CLK
Text Label 6900 5950 2    50   ~ 0
SD_DO
Text Label 6900 6050 2    50   ~ 0
SD_DIN
Wire Wire Line
	5200 5650 4800 5650
Text Label 4800 5650 0    50   ~ 0
USB_DM
Wire Wire Line
	4800 5750 5200 5750
Text Label 4800 5750 0    50   ~ 0
USB_DP
$Comp
L Device:R R16
U 1 1 5C1D0086
P 3750 4750
F 0 "R16" V 3650 4725 50  0000 R CNN
F 1 "1k" V 3650 4775 50  0000 L CNN
F 2 "" V 3680 4750 50  0001 C CNN
F 3 "~" H 3750 4750 50  0001 C CNN
	1    3750 4750
	0    1    1    0   
$EndComp
$Comp
L Device:R R15
U 1 1 5C1D00F4
P 3750 4550
F 0 "R15" V 3650 4525 50  0000 R CNN
F 1 "1k" V 3650 4575 50  0000 L CNN
F 2 "" V 3680 4550 50  0001 C CNN
F 3 "~" H 3750 4550 50  0001 C CNN
	1    3750 4550
	0    1    1    0   
$EndComp
$Comp
L Device:R R12
U 1 1 5C1D01B1
P 3750 3950
F 0 "R12" V 3650 3925 50  0000 R CNN
F 1 "1k" V 3650 3975 50  0000 L CNN
F 2 "" V 3680 3950 50  0001 C CNN
F 3 "~" H 3750 3950 50  0001 C CNN
	1    3750 3950
	0    1    1    0   
$EndComp
$Comp
L Device:R R11
U 1 1 5C1D01B7
P 3750 3750
F 0 "R11" V 3650 3725 50  0000 R CNN
F 1 "1k" V 3650 3775 50  0000 L CNN
F 2 "" V 3680 3750 50  0001 C CNN
F 3 "~" H 3750 3750 50  0001 C CNN
	1    3750 3750
	0    1    1    0   
$EndComp
$Comp
L Device:R R10
U 1 1 5C1D2991
P 3750 3550
F 0 "R10" V 3650 3525 50  0000 R CNN
F 1 "1k" V 3650 3575 50  0000 L CNN
F 2 "" V 3680 3550 50  0001 C CNN
F 3 "~" H 3750 3550 50  0001 C CNN
	1    3750 3550
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 5C1D2997
P 3750 3350
F 0 "R9" V 3650 3325 50  0000 R CNN
F 1 "1k" V 3650 3375 50  0000 L CNN
F 2 "" V 3680 3350 50  0001 C CNN
F 3 "~" H 3750 3350 50  0001 C CNN
	1    3750 3350
	0    1    1    0   
$EndComp
$Comp
L Device:R R14
U 1 1 5C1E191D
P 3750 4350
F 0 "R14" V 3650 4325 50  0000 R CNN
F 1 "1k" V 3650 4375 50  0000 L CNN
F 2 "" V 3680 4350 50  0001 C CNN
F 3 "~" H 3750 4350 50  0001 C CNN
	1    3750 4350
	0    1    1    0   
$EndComp
$Comp
L Device:R R13
U 1 1 5C1E1923
P 3750 4150
F 0 "R13" V 3650 4125 50  0000 R CNN
F 1 "1k" V 3650 4175 50  0000 L CNN
F 2 "" V 3680 4150 50  0001 C CNN
F 3 "~" H 3750 4150 50  0001 C CNN
	1    3750 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	3600 3350 3300 3350
Text Label 3300 3350 0    50   ~ 0
BTN_0
Wire Wire Line
	3300 3550 3600 3550
Text Label 3300 3550 0    50   ~ 0
BTN_1
Wire Wire Line
	3600 3750 3300 3750
Wire Wire Line
	3300 3950 3600 3950
Wire Wire Line
	3300 4150 3600 4150
Wire Wire Line
	3300 4350 3600 4350
Wire Wire Line
	3300 4550 3600 4550
Wire Wire Line
	3300 4750 3600 4750
Text Label 3300 3750 0    50   ~ 0
BTN_2
Text Label 3300 3950 0    50   ~ 0
BTN_3
Text Label 3300 4150 0    50   ~ 0
BTN_4
Text Label 3300 4350 0    50   ~ 0
BTN_5
Text Label 3300 4550 0    50   ~ 0
ENC_A
Text Label 3300 4750 0    50   ~ 0
ENC_B
Wire Wire Line
	3900 3350 4150 3350
Wire Wire Line
	4150 3550 3900 3550
Wire Wire Line
	3900 3750 4150 3750
Wire Wire Line
	4150 3950 3900 3950
Wire Wire Line
	3900 4150 4150 4150
Wire Wire Line
	4150 4350 3900 4350
Wire Wire Line
	3900 4750 4150 4750
Text Label 4150 3350 2    50   ~ 0
DB0
Text Label 4150 3550 2    50   ~ 0
DB1
Text Label 4150 3750 2    50   ~ 0
DB2
Text Label 4150 3950 2    50   ~ 0
DB3
Text Label 4150 4150 2    50   ~ 0
DB4
Text Label 4150 4350 2    50   ~ 0
DB5
Text Label 4150 4750 2    50   ~ 0
DB7
Wire Wire Line
	3900 4550 4150 4550
Text Label 4150 4550 2    50   ~ 0
DB6
$Comp
L Amplifier_Operational:MCP602 U1
U 1 1 5C17DABA
P 2950 1300
F 0 "U1" H 2950 1667 50  0000 C CNN
F 1 "MCP602" H 2950 1576 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 2950 1300 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21314g.pdf" H 2950 1300 50  0001 C CNN
	1    2950 1300
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:MCP602 U1
U 2 1 5C17DBE3
P 2450 2550
F 0 "U1" H 2450 2917 50  0000 C CNN
F 1 "MCP602" H 2450 2826 50  0000 C CNN
F 2 "" H 2450 2550 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21314g.pdf" H 2450 2550 50  0001 C CNN
	2    2450 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R17
U 1 1 5C182671
P 6600 3250
F 0 "R17" H 6670 3296 50  0000 L CNN
F 1 "22k" H 6670 3205 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 6530 3250 50  0001 C CNN
F 3 "~" H 6600 3250 50  0001 C CNN
	1    6600 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5C18283C
P 2500 1600
F 0 "R4" H 2570 1646 50  0000 L CNN
F 1 "22k" H 2570 1555 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2430 1600 50  0001 C CNN
F 3 "~" H 2500 1600 50  0001 C CNN
	1    2500 1600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2650 1200 2500 1200
Connection ~ 2500 1200
$Comp
L Device:R R1
U 1 1 5C18A86C
P 2300 1400
F 0 "R1" H 2370 1446 50  0000 L CNN
F 1 "22k" H 2370 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2230 1400 50  0001 C CNN
F 3 "~" H 2300 1400 50  0001 C CNN
	1    2300 1400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2650 1400 2600 1400
Wire Wire Line
	2500 1200 2500 1450
$Comp
L Device:C C1
U 1 1 5C19B1FC
P 1950 1400
F 0 "C1" H 1835 1354 50  0000 R CNN
F 1 "2.2" H 1835 1445 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 1988 1250 50  0001 C CNN
F 3 "~" H 1950 1400 50  0001 C CNN
	1    1950 1400
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 1400 2100 1400
$Comp
L power:GNDD #PWR06
U 1 1 5C1A388F
P 2500 1800
F 0 "#PWR06" H 2500 1550 50  0001 C CNN
F 1 "GNDD" H 2504 1645 50  0000 C CNN
F 2 "" H 2500 1800 50  0001 C CNN
F 3 "" H 2500 1800 50  0001 C CNN
	1    2500 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1800 2500 1750
$Comp
L power:+3V3 #PWR011
U 1 1 5C1A7BB6
P 6600 3050
F 0 "#PWR011" H 6600 2900 50  0001 C CNN
F 1 "+3V3" H 6615 3223 50  0000 C CNN
F 2 "" H 6600 3050 50  0001 C CNN
F 3 "" H 6600 3050 50  0001 C CNN
	1    6600 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 3050 6600 3100
$Comp
L Device:R R7
U 1 1 5C1B03FD
P 2950 1600
F 0 "R7" H 3020 1646 50  0000 L CNN
F 1 "220k" H 3020 1555 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2880 1600 50  0001 C CNN
F 3 "~" H 2950 1600 50  0001 C CNN
	1    2950 1600
	0    -1   1    0   
$EndComp
Wire Wire Line
	2800 1600 2600 1600
Wire Wire Line
	2600 1600 2600 1400
Connection ~ 2600 1400
Wire Wire Line
	2600 1400 2450 1400
Wire Wire Line
	3100 1600 3300 1600
Wire Wire Line
	3300 1600 3300 1300
Wire Wire Line
	3300 1300 3250 1300
$Comp
L Device:R R5
U 1 1 5C1CAA35
P 2000 2250
F 0 "R5" H 2070 2296 50  0000 L CNN
F 1 "22k" H 2070 2205 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1930 2250 50  0001 C CNN
F 3 "~" H 2000 2250 50  0001 C CNN
	1    2000 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5C1CAA3C
P 2000 2850
F 0 "R6" H 2070 2896 50  0000 L CNN
F 1 "22k" H 2070 2805 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1930 2850 50  0001 C CNN
F 3 "~" H 2000 2850 50  0001 C CNN
	1    2000 2850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2150 2450 2000 2450
Connection ~ 2000 2450
Wire Wire Line
	2000 2450 2000 2400
$Comp
L Device:R R2
U 1 1 5C1CAA46
P 1800 2650
F 0 "R2" H 1870 2696 50  0000 L CNN
F 1 "22k" H 1870 2605 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1730 2650 50  0001 C CNN
F 3 "~" H 1800 2650 50  0001 C CNN
	1    1800 2650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2150 2650 2100 2650
Wire Wire Line
	2000 2450 2000 2700
$Comp
L Device:C C2
U 1 1 5C1CAA4F
P 1450 2650
F 0 "C2" H 1335 2604 50  0000 R CNN
F 1 "2.2" H 1335 2695 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 1488 2500 50  0001 C CNN
F 3 "~" H 1450 2650 50  0001 C CNN
	1    1450 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	1650 2650 1600 2650
$Comp
L power:GNDD #PWR08
U 1 1 5C1CAA57
P 2000 3050
F 0 "#PWR08" H 2000 2800 50  0001 C CNN
F 1 "GNDD" H 2004 2895 50  0000 C CNN
F 2 "" H 2000 3050 50  0001 C CNN
F 3 "" H 2000 3050 50  0001 C CNN
	1    2000 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 3050 2000 3000
$Comp
L power:+3V3 #PWR07
U 1 1 5C1CAA5E
P 2000 2050
F 0 "#PWR07" H 2000 1900 50  0001 C CNN
F 1 "+3V3" H 2015 2223 50  0000 C CNN
F 2 "" H 2000 2050 50  0001 C CNN
F 3 "" H 2000 2050 50  0001 C CNN
	1    2000 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2050 2000 2100
$Comp
L Device:R R8
U 1 1 5C1CAA65
P 2450 2850
F 0 "R8" H 2520 2896 50  0000 L CNN
F 1 "220k" H 2520 2805 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2380 2850 50  0001 C CNN
F 3 "~" H 2450 2850 50  0001 C CNN
	1    2450 2850
	0    -1   1    0   
$EndComp
Wire Wire Line
	2300 2850 2100 2850
Wire Wire Line
	2100 2850 2100 2650
Connection ~ 2100 2650
Wire Wire Line
	2100 2650 1950 2650
Wire Wire Line
	2600 2850 2800 2850
Wire Wire Line
	2800 2850 2800 2550
Wire Wire Line
	2800 2550 2750 2550
Text Label 3500 1300 2    50   ~ 0
SP_L
Text Label 3000 2550 2    50   ~ 0
SP_R
Connection ~ 3300 1300
Connection ~ 2800 2550
Wire Wire Line
	2800 2550 3000 2550
Wire Wire Line
	3300 1300 3350 1300
Text Label 900  1150 0    50   ~ 0
IN_L
Text Label 900  1350 0    50   ~ 0
IN_R
$Comp
L Device:R_POT RV1
U 1 1 5C232615
P 1600 1400
F 0 "RV1" H 1530 1446 50  0000 R CNN
F 1 "22k" H 1530 1355 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Piher_PT-6-V_Vertical" H 1600 1400 50  0001 C CNN
F 3 "~" H 1600 1400 50  0001 C CNN
	1    1600 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 1400 1750 1400
$Comp
L power:GNDD #PWR03
U 1 1 5C23F573
P 1600 1650
F 0 "#PWR03" H 1600 1400 50  0001 C CNN
F 1 "GNDD" H 1604 1495 50  0000 C CNN
F 2 "" H 1600 1650 50  0001 C CNN
F 3 "" H 1600 1650 50  0001 C CNN
	1    1600 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 1650 1600 1550
Wire Wire Line
	1600 1150 1600 1250
$Comp
L Device:R_POT RV2
U 1 1 5C260260
P 1100 2650
F 0 "RV2" H 1030 2696 50  0000 R CNN
F 1 "22k" H 1030 2605 50  0000 R CNN
F 2 "" H 1100 2650 50  0001 C CNN
F 3 "~" H 1100 2650 50  0001 C CNN
	1    1100 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 2650 1250 2650
$Comp
L power:GNDD #PWR04
U 1 1 5C260268
P 1100 2900
F 0 "#PWR04" H 1100 2650 50  0001 C CNN
F 1 "GNDD" H 1104 2745 50  0000 C CNN
F 2 "" H 1100 2900 50  0001 C CNN
F 3 "" H 1100 2900 50  0001 C CNN
	1    1100 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 2900 1100 2800
Wire Wire Line
	6600 3400 6600 3450
Wire Wire Line
	6600 3450 6500 3450
$Comp
L Device:R R3
U 1 1 5C19A62C
P 2500 950
F 0 "R3" H 2570 996 50  0000 L CNN
F 1 "22k" H 2570 905 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2430 950 50  0001 C CNN
F 3 "~" H 2500 950 50  0001 C CNN
	1    2500 950 
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR05
U 1 1 5C19A634
P 2500 750
F 0 "#PWR05" H 2500 600 50  0001 C CNN
F 1 "+3V3" H 2515 923 50  0000 C CNN
F 2 "" H 2500 750 50  0001 C CNN
F 3 "" H 2500 750 50  0001 C CNN
	1    2500 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 750  2500 800 
Wire Wire Line
	2500 1100 2500 1200
Text Label 6900 3450 2    50   ~ 0
NRST
$Comp
L Device:R R20
U 1 1 5C373CA2
P 2250 5850
F 0 "R20" H 2320 5896 50  0000 L CNN
F 1 "22k" H 2320 5805 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2180 5850 50  0001 C CNN
F 3 "~" H 2250 5850 50  0001 C CNN
	1    2250 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 6150 2250 6000
Wire Wire Line
	2250 6150 3000 6150
$Comp
L power:+3V3 #PWR018
U 1 1 5C38284E
P 2250 5600
F 0 "#PWR018" H 2250 5450 50  0001 C CNN
F 1 "+3V3" H 2265 5773 50  0000 C CNN
F 2 "" H 2250 5600 50  0001 C CNN
F 3 "" H 2250 5600 50  0001 C CNN
	1    2250 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 5600 2250 5700
Wire Wire Line
	2750 6250 3000 6250
Wire Wire Line
	2750 6350 3000 6350
Wire Wire Line
	3000 6450 2750 6450
Wire Wire Line
	2750 6550 3000 6550
Wire Wire Line
	2750 6650 3000 6650
Wire Wire Line
	2750 6750 3000 6750
Wire Wire Line
	2750 6850 3000 6850
Wire Wire Line
	2750 6950 3000 6950
Text Label 2750 6250 0    50   ~ 0
DB8
Text Label 2750 6350 0    50   ~ 0
DB9
Text Label 2750 6450 0    50   ~ 0
DB10
Text Label 2750 6550 0    50   ~ 0
DB11
Text Label 2750 6650 0    50   ~ 0
DB12
Text Label 2750 6750 0    50   ~ 0
DB13
Text Label 2750 6850 0    50   ~ 0
DB14
Text Label 2750 6950 0    50   ~ 0
DB15
$Comp
L Device:R R24
U 1 1 5C398138
P 7350 2250
F 0 "R24" H 7420 2296 50  0000 L CNN
F 1 "100k" H 7420 2205 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 7280 2250 50  0001 C CNN
F 3 "~" H 7350 2250 50  0001 C CNN
	1    7350 2250
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J5
U 1 1 5C39890C
P 7800 2250
F 0 "J5" H 7850 2567 50  0000 C CNN
F 1 "Conn_BOOT" H 7850 2476 50  0000 C CNN
F 2 "" H 7800 2250 50  0001 C CNN
F 3 "~" H 7800 2250 50  0001 C CNN
	1    7800 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 2250 7600 2250
$Comp
L Device:R R25
U 1 1 5C3A1C50
P 8300 2250
F 0 "R25" H 8370 2296 50  0000 L CNN
F 1 "100k" H 8370 2205 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 8230 2250 50  0001 C CNN
F 3 "~" H 8300 2250 50  0001 C CNN
	1    8300 2250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8150 2250 8100 2250
$Comp
L power:+3V3 #PWR027
U 1 1 5C3AA90B
P 7550 1950
F 0 "#PWR027" H 7550 1800 50  0001 C CNN
F 1 "+3V3" H 7565 2123 50  0000 C CNN
F 2 "" H 7550 1950 50  0001 C CNN
F 3 "" H 7550 1950 50  0001 C CNN
	1    7550 1950
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR029
U 1 1 5C3AA960
P 8150 1950
F 0 "#PWR029" H 8150 1800 50  0001 C CNN
F 1 "+3V3" H 8165 2123 50  0000 C CNN
F 2 "" H 8150 1950 50  0001 C CNN
F 3 "" H 8150 1950 50  0001 C CNN
	1    8150 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 1950 7550 2150
Wire Wire Line
	7550 2150 7600 2150
Wire Wire Line
	8150 1950 8150 2150
$Comp
L power:GNDD #PWR028
U 1 1 5C3BC82C
P 7550 2450
F 0 "#PWR028" H 7550 2200 50  0001 C CNN
F 1 "GNDD" H 7554 2295 50  0000 C CNN
F 2 "" H 7550 2450 50  0001 C CNN
F 3 "" H 7550 2450 50  0001 C CNN
	1    7550 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 2350 7550 2350
Wire Wire Line
	7550 2350 7550 2450
$Comp
L power:GNDD #PWR030
U 1 1 5C3EA38D
P 8150 2450
F 0 "#PWR030" H 8150 2200 50  0001 C CNN
F 1 "GNDD" H 8154 2295 50  0000 C CNN
F 2 "" H 8150 2450 50  0001 C CNN
F 3 "" H 8150 2450 50  0001 C CNN
	1    8150 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 2350 8150 2350
Wire Wire Line
	8150 2350 8150 2450
Wire Wire Line
	7200 2250 6950 2250
Text Label 6950 2250 0    50   ~ 0
BOOT0
Wire Wire Line
	8450 2250 8750 2250
Text Label 8750 2250 2    50   ~ 0
BOOT1
Wire Wire Line
	8100 2150 8150 2150
Connection ~ 7200 4350
Connection ~ 7600 4350
Wire Wire Line
	7600 4250 7600 4350
Wire Wire Line
	7200 4350 7200 4400
Wire Wire Line
	7600 4400 7600 4350
Wire Wire Line
	4800 5850 5200 5850
Wire Wire Line
	5200 5950 4800 5950
Wire Wire Line
	900  5550 1200 5550
Text Label 1200 5550 2    50   ~ 0
SWCLK
Wire Wire Line
	900  5450 1200 5450
Text Label 1200 5450 2    50   ~ 0
SWDIO
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 5C4E2EC5
P 700 5450
F 0 "J4" H 620 5767 50  0000 C CNN
F 1 "Conn_SWD" H 620 5676 50  0000 C CNN
F 2 "" H 700 5450 50  0001 C CNN
F 3 "~" H 700 5450 50  0001 C CNN
	1    700  5450
	-1   0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR023
U 1 1 5C51402E
P 1100 5700
F 0 "#PWR023" H 1100 5450 50  0001 C CNN
F 1 "GNDD" H 1104 5545 50  0000 C CNN
F 2 "" H 1100 5700 50  0001 C CNN
F 3 "" H 1100 5700 50  0001 C CNN
	1    1100 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 5700 1100 5650
Wire Wire Line
	1100 5650 900  5650
$Comp
L power:+3V3 #PWR022
U 1 1 5C51E187
P 1100 5300
F 0 "#PWR022" H 1100 5150 50  0001 C CNN
F 1 "+3V3" H 1115 5473 50  0000 C CNN
F 2 "" H 1100 5300 50  0001 C CNN
F 3 "" H 1100 5300 50  0001 C CNN
	1    1100 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  5350 1100 5350
Wire Wire Line
	1100 5350 1100 5300
$Comp
L Device:C C8
U 1 1 5C5521B6
P 1400 5500
F 0 "C8" H 1515 5546 50  0000 L CNN
F 1 "0.22" H 1515 5455 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 1438 5350 50  0001 C CNN
F 3 "~" H 1400 5500 50  0001 C CNN
	1    1400 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 5350 1100 5350
Connection ~ 1100 5350
Wire Wire Line
	1400 5650 1100 5650
Connection ~ 1100 5650
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 5C57CFAA
P 700 4200
F 0 "J3" H 620 4517 50  0000 C CNN
F 1 "Conn_USB" H 620 4426 50  0000 C CNN
F 2 "" H 700 4200 50  0001 C CNN
F 3 "~" H 700 4200 50  0001 C CNN
	1    700  4200
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR020
U 1 1 5C57D0A8
P 1050 3900
F 0 "#PWR020" H 1050 3750 50  0001 C CNN
F 1 "+5V" H 1065 4073 50  0000 C CNN
F 2 "" H 1050 3900 50  0001 C CNN
F 3 "" H 1050 3900 50  0001 C CNN
	1    1050 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R21
U 1 1 5C57D103
P 1300 4200
F 0 "R21" H 1370 4246 50  0000 L CNN
F 1 "22" H 1370 4155 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1230 4200 50  0001 C CNN
F 3 "~" H 1300 4200 50  0001 C CNN
	1    1300 4200
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R22
U 1 1 5C57D246
P 1300 4300
F 0 "R22" H 1370 4346 50  0000 L CNN
F 1 "22" H 1370 4255 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1230 4300 50  0001 C CNN
F 3 "~" H 1300 4300 50  0001 C CNN
	1    1300 4300
	0    -1   1    0   
$EndComp
Wire Wire Line
	1050 3900 1050 4100
Wire Wire Line
	1050 4100 900  4100
$Comp
L power:GNDD #PWR021
U 1 1 5C5E01D7
P 1050 4500
F 0 "#PWR021" H 1050 4250 50  0001 C CNN
F 1 "GNDD" H 1054 4345 50  0000 C CNN
F 2 "" H 1050 4500 50  0001 C CNN
F 3 "" H 1050 4500 50  0001 C CNN
	1    1050 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 4500 1050 4400
Wire Wire Line
	1050 4400 900  4400
Wire Wire Line
	1450 4200 1800 4200
Text Label 1800 4200 2    50   ~ 0
USB_DM
Text Label 1800 4300 2    50   ~ 0
USB_DP
$Comp
L power:+5V #PWR025
U 1 1 5C603292
P 1950 3900
F 0 "#PWR025" H 1950 3750 50  0001 C CNN
F 1 "+5V" H 1965 4073 50  0000 C CNN
F 2 "" H 1950 3900 50  0001 C CNN
F 3 "" H 1950 3900 50  0001 C CNN
	1    1950 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R23
U 1 1 5C61B09F
P 1950 4100
F 0 "R23" H 2020 4146 50  0000 L CNN
F 1 "1.5k" H 2020 4055 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1880 4100 50  0001 C CNN
F 3 "~" H 1950 4100 50  0001 C CNN
	1    1950 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 3900 1950 3950
Wire Wire Line
	1950 4300 1950 4250
Wire Wire Line
	1450 4300 1950 4300
Wire Wire Line
	900  4200 1150 4200
Wire Wire Line
	900  4300 1150 4300
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5C700489
P 700 1250
F 0 "J2" H 620 1567 50  0000 C CNN
F 1 "Conn_AUDIO" H 620 1476 50  0000 C CNN
F 2 "" H 700 1250 50  0001 C CNN
F 3 "~" H 700 1250 50  0001 C CNN
	1    700  1250
	-1   0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR024
U 1 1 5C7949EA
P 1250 1450
F 0 "#PWR024" H 1250 1200 50  0001 C CNN
F 1 "GNDD" H 1254 1295 50  0000 C CNN
F 2 "" H 1250 1450 50  0001 C CNN
F 3 "" H 1250 1450 50  0001 C CNN
	1    1250 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 1450 1250 1250
Wire Wire Line
	1250 1250 900  1250
Wire Wire Line
	900  1150 1600 1150
Wire Wire Line
	900  1350 1100 1350
Wire Wire Line
	1100 1350 1100 2500
$Comp
L Regulator_Linear:AMS1117-3.3 U3
U 1 1 5C8506C1
P 9400 900
F 0 "U3" H 9400 1142 50  0000 C CNN
F 1 "AMS1117-3.3" H 9400 1051 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 9400 1100 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 9500 650 50  0001 C CNN
	1    9400 900 
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR033
U 1 1 5C850B17
P 9900 750
F 0 "#PWR033" H 9900 600 50  0001 C CNN
F 1 "+3V3" H 9915 923 50  0000 C CNN
F 2 "" H 9900 750 50  0001 C CNN
F 3 "" H 9900 750 50  0001 C CNN
	1    9900 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 750  9900 900 
$Comp
L power:+5V #PWR031
U 1 1 5C85D485
P 8900 750
F 0 "#PWR031" H 8900 600 50  0001 C CNN
F 1 "+5V" H 8915 923 50  0000 C CNN
F 2 "" H 8900 750 50  0001 C CNN
F 3 "" H 8900 750 50  0001 C CNN
	1    8900 750 
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR032
U 1 1 5C86A11A
P 9400 1350
F 0 "#PWR032" H 9400 1100 50  0001 C CNN
F 1 "GNDD" H 9404 1195 50  0000 C CNN
F 2 "" H 9400 1350 50  0001 C CNN
F 3 "" H 9400 1350 50  0001 C CNN
	1    9400 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 1350 9400 1300
$Comp
L Switch:SW_Push SW1
U 1 1 5C883FC9
P 1350 7100
F 0 "SW1" V 1304 7248 50  0000 L CNN
F 1 "Reset" V 1395 7248 50  0000 L CNN
F 2 "" H 1350 7300 50  0001 C CNN
F 3 "" H 1350 7300 50  0001 C CNN
	1    1350 7100
	0    1    1    0   
$EndComp
$Comp
L power:GNDD #PWR019
U 1 1 5C89123D
P 1150 7400
F 0 "#PWR019" H 1150 7150 50  0001 C CNN
F 1 "GNDD" H 1154 7245 50  0000 C CNN
F 2 "" H 1150 7400 50  0001 C CNN
F 3 "" H 1150 7400 50  0001 C CNN
	1    1150 7400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5C89E0D9
P 1000 7100
F 0 "C7" H 885 7054 50  0000 R CNN
F 1 "1.0" H 885 7145 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 1038 6950 50  0001 C CNN
F 3 "~" H 1000 7100 50  0001 C CNN
	1    1000 7100
	-1   0    0    1   
$EndComp
Connection ~ 6600 3450
Wire Wire Line
	6600 3450 6950 3450
Wire Wire Line
	1350 7300 1350 7350
Wire Wire Line
	1350 7350 1150 7350
Wire Wire Line
	1000 7350 1000 7250
Wire Wire Line
	1150 7400 1150 7350
Connection ~ 1150 7350
Wire Wire Line
	1150 7350 1000 7350
Wire Wire Line
	1350 6900 1350 6850
Wire Wire Line
	1350 6850 1000 6850
Wire Wire Line
	1000 6850 1000 6950
Text Label 1300 6850 2    50   ~ 0
NRST
$Comp
L Device:C C10
U 1 1 5C99887D
P 8900 1100
F 0 "C10" H 8785 1054 50  0000 R CNN
F 1 "20p" H 8785 1145 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 8938 950 50  0001 C CNN
F 3 "~" H 8900 1100 50  0001 C CNN
	1    8900 1100
	-1   0    0    1   
$EndComp
$Comp
L Device:CP C9
U 1 1 5C9A678D
P 8500 1100
F 0 "C9" H 8618 1146 50  0000 L CNN
F 1 "CP" H 8618 1055 50  0000 L CNN
F 2 "" H 8538 950 50  0001 C CNN
F 3 "~" H 8500 1100 50  0001 C CNN
	1    8500 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 5C9A6853
P 9900 1100
F 0 "C11" H 9785 1054 50  0000 R CNN
F 1 "20p" H 9785 1145 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 9938 950 50  0001 C CNN
F 3 "~" H 9900 1100 50  0001 C CNN
	1    9900 1100
	-1   0    0    1   
$EndComp
$Comp
L Device:CP C12
U 1 1 5C9A68FF
P 10300 1100
F 0 "C12" H 10418 1146 50  0000 L CNN
F 1 "CP" H 10418 1055 50  0000 L CNN
F 2 "" H 10338 950 50  0001 C CNN
F 3 "~" H 10300 1100 50  0001 C CNN
	1    10300 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 900  8500 950 
Wire Wire Line
	8900 950  8900 900 
Connection ~ 8900 900 
Wire Wire Line
	8900 900  8500 900 
Wire Wire Line
	8900 900  9100 900 
Wire Wire Line
	8900 750  8900 900 
Wire Wire Line
	8500 1250 8500 1300
Wire Wire Line
	8500 1300 8900 1300
Wire Wire Line
	8900 1300 8900 1250
Wire Wire Line
	8900 1300 9400 1300
Connection ~ 8900 1300
Connection ~ 9400 1300
Wire Wire Line
	9400 1300 9400 1200
Wire Wire Line
	9700 900  9900 900 
Wire Wire Line
	9900 950  9900 900 
Connection ~ 9900 900 
Wire Wire Line
	9900 900  10300 900 
Wire Wire Line
	10300 900  10300 950 
Wire Wire Line
	9900 1250 9900 1300
Wire Wire Line
	9900 1300 9400 1300
Wire Wire Line
	10300 1250 10300 1300
Wire Wire Line
	10300 1300 9900 1300
Connection ~ 9900 1300
$Comp
L Device:Battery_Cell BT1
U 1 1 5CB11A02
P 5000 2850
F 0 "BT1" H 5118 2946 50  0000 L CNN
F 1 "3.3V" H 5118 2855 50  0000 L CNN
F 2 "" V 5000 2910 50  0001 C CNN
F 3 "~" V 5000 2910 50  0001 C CNN
	1    5000 2850
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR026
U 1 1 5CB11D08
P 5000 3050
F 0 "#PWR026" H 5000 2800 50  0001 C CNN
F 1 "GNDD" H 5004 2895 50  0000 C CNN
F 2 "" H 5000 3050 50  0001 C CNN
F 3 "" H 5000 3050 50  0001 C CNN
	1    5000 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3050 5000 2950
Wire Wire Line
	6000 3250 6000 2550
Wire Wire Line
	6000 2550 5000 2550
Wire Wire Line
	5000 2550 5000 2650
$Comp
L power:GNDD #PWR?
U 1 1 5CBBB67D
P 7600 3500
F 0 "#PWR?" H 7600 3250 50  0001 C CNN
F 1 "GNDD" H 7604 3345 50  0000 C CNN
F 2 "" H 7600 3500 50  0001 C CNN
F 3 "" H 7600 3500 50  0001 C CNN
	1    7600 3500
	-1   0    0    1   
$EndComp
Wire Wire Line
	7600 3800 7600 3850
Wire Wire Line
	6500 3850 7200 3850
Wire Wire Line
	7200 3850 7200 3800
Wire Wire Line
	7300 3850 7200 3850
Connection ~ 7200 3850
Wire Wire Line
	7500 3850 7600 3850
Connection ~ 7600 3850
Wire Wire Line
	7600 3850 7600 3950
Wire Wire Line
	6500 3950 7600 3950
Wire Wire Line
	5700 6250 5700 6350
Wire Wire Line
	5700 6350 5800 6350
Connection ~ 5800 6350
$EndSCHEMATC
