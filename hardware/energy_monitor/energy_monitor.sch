EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:shared
LIBS:energy_monitor-cache
EELAYER 25 0
EELAYER END
$Descr USLedger 17000 11000
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
L ADS131E08 U2
U 1 1 5B12AE1E
P 8300 6050
F 0 "U2" H 7400 7700 60  0000 L CNN
F 1 "ADS131E08" H 8850 4000 60  0000 L CNN
F 2 "" H 8300 6050 60  0001 C CNN
F 3 "" H 8300 6050 60  0001 C CNN
	1    8300 6050
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x03 J1
U 1 1 5B12AE8E
P 1450 1800
F 0 "J1" H 1450 2000 50  0000 C CNN
F 1 "Screw_Terminal_01x03" H 1450 1600 50  0001 C CNN
F 2 "" H 1450 1800 50  0001 C CNN
F 3 "" H 1450 1800 50  0001 C CNN
	1    1450 1800
	-1   0    0    -1  
$EndComp
$Comp
L Fuse F1
U 1 1 5B12B1C8
P 2100 1400
F 0 "F1" V 2180 1400 50  0000 C CNN
F 1 "1A/300V" V 2025 1400 50  0000 C CNN
F 2 "" V 2030 1400 50  0001 C CNN
F 3 "" H 2100 1400 50  0001 C CNN
	1    2100 1400
	0    1    -1   0   
$EndComp
$Comp
L Fuse F2
U 1 1 5B12B24D
P 2100 2200
F 0 "F2" V 2180 2200 50  0000 C CNN
F 1 "1A/300V" V 2025 2200 50  0000 C CNN
F 2 "" V 2030 2200 50  0001 C CNN
F 3 "" H 2100 2200 50  0001 C CNN
	1    2100 2200
	0    1    -1   0   
$EndComp
$Comp
L Varistor RV1
U 1 1 5B12B2F1
P 2450 1600
F 0 "RV1" H 2550 1650 50  0000 L CNN
F 1 "MOV" H 2550 1550 50  0000 L CNN
F 2 "" V 2380 1600 50  0001 C CNN
F 3 "" H 2450 1600 50  0001 C CNN
F 4 "DigiKey" H 2450 1600 60  0001 C CNN "Source"
F 5 "495-6609-ND" H 2450 1600 60  0001 C CNN "Part"
	1    2450 1600
	1    0    0    -1  
$EndComp
Text Label 2750 1400 0    60   ~ 0
L1
Text Label 2750 1800 0    60   ~ 0
N
Text Label 2750 2200 0    60   ~ 0
L2
$Comp
L Varistor RV2
U 1 1 5B12BD44
P 2450 2000
F 0 "RV2" H 2550 2050 50  0000 L CNN
F 1 "MOV" H 2550 1950 50  0000 L CNN
F 2 "" V 2380 2000 50  0001 C CNN
F 3 "" H 2450 2000 50  0001 C CNN
F 4 "DigiKey" H 2450 2000 60  0001 C CNN "Source"
F 5 "495-6609-ND" H 2450 2000 60  0001 C CNN "Part"
	1    2450 2000
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5B12BFB2
P 4550 1600
F 0 "C1" H 4575 1700 50  0000 L CNN
F 1 "0.1u" H 4575 1500 50  0000 L CNN
F 2 "" H 4588 1450 50  0001 C CNN
F 3 "" H 4550 1600 50  0001 C CNN
	1    4550 1600
	1    0    0    -1  
$EndComp
$Comp
L CP C3
U 1 1 5B12C0FF
P 4850 1600
F 0 "C3" H 4875 1700 50  0000 L CNN
F 1 "47u" H 4875 1500 50  0000 L CNN
F 2 "" H 4888 1450 50  0001 C CNN
F 3 "" H 4850 1600 50  0001 C CNN
	1    4850 1600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 5B12C02D
P 5050 1800
F 0 "#PWR3" H 5050 1550 50  0001 C CNN
F 1 "GND" H 5050 1650 50  0000 C CNN
F 2 "" H 5050 1800 50  0001 C CNN
F 3 "" H 5050 1800 50  0001 C CNN
	1    5050 1800
	0    -1   -1   0   
$EndComp
$Comp
L RAC04 U1
U 1 1 5B12CF15
P 3850 1800
F 0 "U1" H 3550 2350 60  0000 L CNN
F 1 "RAC04" H 3550 1250 60  0000 L CNN
F 2 "" H 3850 1800 60  0001 C CNN
F 3 "" H 3850 1800 60  0001 C CNN
F 4 "DigiKey" H 3850 1800 60  0001 C CNN "Source"
F 5 "945-2415-5-ND" H 3850 1800 60  0001 C CNN "Part"
	1    3850 1800
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5B12CF79
P 4550 2000
F 0 "C2" H 4575 2100 50  0000 L CNN
F 1 "0.1u" H 4575 1900 50  0000 L CNN
F 2 "" H 4588 1850 50  0001 C CNN
F 3 "" H 4550 2000 50  0001 C CNN
	1    4550 2000
	1    0    0    -1  
$EndComp
$Comp
L CP C4
U 1 1 5B12CFB1
P 4850 2000
F 0 "C4" H 4875 2100 50  0000 L CNN
F 1 "47u" H 4875 1900 50  0000 L CNN
F 2 "" H 4888 1850 50  0001 C CNN
F 3 "" H 4850 2000 50  0001 C CNN
	1    4850 2000
	1    0    0    -1  
$EndComp
Connection ~ 4550 2200
Wire Wire Line
	4850 2150 4850 2250
Wire Wire Line
	4550 2200 4550 2150
Wire Wire Line
	4350 2200 4850 2200
Connection ~ 4550 1400
Wire Wire Line
	4850 1350 4850 1450
Wire Wire Line
	4550 1400 4550 1450
Wire Wire Line
	4350 1400 4850 1400
Connection ~ 4550 1800
Wire Wire Line
	4550 1750 4550 1850
Connection ~ 4850 1800
Wire Wire Line
	4850 1750 4850 1850
Wire Wire Line
	4350 1800 5050 1800
Connection ~ 2450 2200
Connection ~ 2450 1400
Wire Wire Line
	1850 1900 1650 1900
Wire Wire Line
	1850 2200 1850 1900
Wire Wire Line
	1950 2200 1850 2200
Connection ~ 2450 1800
Wire Wire Line
	2250 2200 3050 2200
Wire Wire Line
	2450 2150 2450 2200
Wire Wire Line
	2450 1400 2450 1450
Wire Wire Line
	2250 1400 3350 1400
Wire Wire Line
	1850 1400 1950 1400
Wire Wire Line
	1850 1700 1850 1400
Wire Wire Line
	1650 1700 1850 1700
Wire Wire Line
	2450 1750 2450 1850
Wire Wire Line
	1650 1800 3350 1800
Connection ~ 4850 2200
$Comp
L +5V #PWR1
U 1 1 5B12DF14
P 4850 1350
F 0 "#PWR1" H 4850 1200 50  0001 C CNN
F 1 "+5V" H 4850 1490 50  0000 C CNN
F 2 "" H 4850 1350 50  0001 C CNN
F 3 "" H 4850 1350 50  0001 C CNN
	1    4850 1350
	1    0    0    -1  
$EndComp
Connection ~ 4850 1400
$Comp
L -5V #PWR?
U 1 1 5B132626
P 4850 2250
F 0 "#PWR?" H 4850 2350 50  0001 C CNN
F 1 "-5V" H 4850 2400 50  0000 C CNN
F 2 "" H 4850 2250 50  0001 C CNN
F 3 "" H 4850 2250 50  0001 C CNN
	1    4850 2250
	-1   0    0    1   
$EndComp
$Comp
L TPS723 U?
U 1 1 5B132A80
P 6950 2350
F 0 "U?" H 6650 2600 60  0000 L CNN
F 1 "TPS723" H 7000 2000 60  0000 L CNN
F 2 "" H 6950 2750 60  0001 C CNN
F 3 "" H 6950 2750 60  0001 C CNN
F 4 "DigiKey" H 6950 2350 60  0001 C CNN "Source"
F 5 "296-39479-1-ND" H 6950 2350 60  0001 C CNN "Part"
	1    6950 2350
	1    0    0    -1  
$EndComp
$Comp
L TPS730 U?
U 1 1 5B132DEC
P 6950 1050
F 0 "U?" H 6650 1300 60  0000 L CNN
F 1 "TPS730" H 7000 700 60  0000 L CNN
F 2 "" H 6950 1050 60  0001 C CNN
F 3 "" H 6950 1050 60  0001 C CNN
F 4 "DigiKey" H 6950 1050 60  0001 C CNN "Source"
F 5 "296-17578-1-ND" H 6950 1050 60  0001 C CNN "Part"
	1    6950 1050
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5B1330C2
P 6050 850
F 0 "#PWR?" H 6050 700 50  0001 C CNN
F 1 "+5V" H 6050 990 50  0000 C CNN
F 2 "" H 6050 850 50  0001 C CNN
F 3 "" H 6050 850 50  0001 C CNN
	1    6050 850 
	1    0    0    -1  
$EndComp
$Comp
L -5V #PWR?
U 1 1 5B133141
P 6050 2150
F 0 "#PWR?" H 6050 2250 50  0001 C CNN
F 1 "-5V" H 6050 2300 50  0000 C CNN
F 2 "" H 6050 2150 50  0001 C CNN
F 3 "" H 6050 2150 50  0001 C CNN
	1    6050 2150
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5B1331DD
P 6050 2550
F 0 "C?" H 6075 2650 50  0000 L CNN
F 1 "0.1u" H 6075 2450 50  0000 L CNN
F 2 "" H 6088 2400 50  0001 C CNN
F 3 "" H 6050 2550 50  0001 C CNN
	1    6050 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 2450 6350 2450
Wire Wire Line
	6350 2450 6350 2250
Wire Wire Line
	6050 2250 6450 2250
$Comp
L GND #PWR?
U 1 1 5B1332C9
P 6050 2900
F 0 "#PWR?" H 6050 2650 50  0001 C CNN
F 1 "GND" H 6050 2750 50  0000 C CNN
F 2 "" H 6050 2900 50  0001 C CNN
F 3 "" H 6050 2900 50  0001 C CNN
	1    6050 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B133352
P 6950 2900
F 0 "#PWR?" H 6950 2650 50  0001 C CNN
F 1 "GND" H 6950 2750 50  0000 C CNN
F 2 "" H 6950 2900 50  0001 C CNN
F 3 "" H 6950 2900 50  0001 C CNN
	1    6950 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 2150 6050 2400
Connection ~ 6350 2250
Wire Wire Line
	6050 2700 6050 2900
Connection ~ 6050 2250
Wire Wire Line
	6950 2850 6950 2900
$Comp
L C C?
U 1 1 5B133844
P 7550 2700
F 0 "C?" H 7575 2800 50  0000 L CNN
F 1 "0.01u" H 7575 2600 50  0000 L CNN
F 2 "" H 7588 2550 50  0001 C CNN
F 3 "" H 7550 2700 50  0001 C CNN
	1    7550 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B1338F2
P 7550 2900
F 0 "#PWR?" H 7550 2650 50  0001 C CNN
F 1 "GND" H 7550 2750 50  0000 C CNN
F 2 "" H 7550 2900 50  0001 C CNN
F 3 "" H 7550 2900 50  0001 C CNN
	1    7550 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 2450 7550 2450
Wire Wire Line
	7550 2450 7550 2550
Wire Wire Line
	7550 2850 7550 2900
$Comp
L GND #PWR?
U 1 1 5B133B82
P 6950 1600
F 0 "#PWR?" H 6950 1350 50  0001 C CNN
F 1 "GND" H 6950 1450 50  0000 C CNN
F 2 "" H 6950 1600 50  0001 C CNN
F 3 "" H 6950 1600 50  0001 C CNN
	1    6950 1600
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5B133BBA
P 6050 1250
F 0 "C?" H 6075 1350 50  0000 L CNN
F 1 "0.1u" H 6075 1150 50  0000 L CNN
F 2 "" H 6088 1100 50  0001 C CNN
F 3 "" H 6050 1250 50  0001 C CNN
	1    6050 1250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B133C14
P 6050 1600
F 0 "#PWR?" H 6050 1350 50  0001 C CNN
F 1 "GND" H 6050 1450 50  0000 C CNN
F 2 "" H 6050 1600 50  0001 C CNN
F 3 "" H 6050 1600 50  0001 C CNN
	1    6050 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 1600 6050 1400
Wire Wire Line
	6050 950  6450 950 
Wire Wire Line
	6050 850  6050 1100
Wire Wire Line
	6450 1150 6350 1150
Wire Wire Line
	6350 1150 6350 950 
Connection ~ 6350 950 
Connection ~ 6050 950 
Wire Wire Line
	6950 1550 6950 1600
$Comp
L C C?
U 1 1 5B133E29
P 7550 1400
F 0 "C?" H 7575 1500 50  0000 L CNN
F 1 "0.01u" H 7575 1300 50  0000 L CNN
F 2 "" H 7588 1250 50  0001 C CNN
F 3 "" H 7550 1400 50  0001 C CNN
	1    7550 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B133E7A
P 7550 1600
F 0 "#PWR?" H 7550 1350 50  0001 C CNN
F 1 "GND" H 7550 1450 50  0000 C CNN
F 2 "" H 7550 1600 50  0001 C CNN
F 3 "" H 7550 1600 50  0001 C CNN
	1    7550 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 1600 7550 1550
Wire Wire Line
	7450 1150 7550 1150
Wire Wire Line
	7550 1150 7550 1250
$Comp
L +2.5V #PWR?
U 1 1 5B134586
P 7850 850
F 0 "#PWR?" H 7850 700 50  0001 C CNN
F 1 "+2.5V" H 7850 990 50  0000 C CNN
F 2 "" H 7850 850 50  0001 C CNN
F 3 "" H 7850 850 50  0001 C CNN
	1    7850 850 
	1    0    0    -1  
$EndComp
$Comp
L -2.5V #PWR?
U 1 1 5B1345BC
P 7850 2150
F 0 "#PWR?" H 7850 2000 50  0001 C CNN
F 1 "-2.5V" H 7850 2290 50  0000 C CNN
F 2 "" H 7850 2150 50  0001 C CNN
F 3 "" H 7850 2150 50  0001 C CNN
	1    7850 2150
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5B134781
P 7850 1250
F 0 "C?" H 7875 1350 50  0000 L CNN
F 1 "2.2u" H 7875 1150 50  0000 L CNN
F 2 "" H 7888 1100 50  0001 C CNN
F 3 "" H 7850 1250 50  0001 C CNN
	1    7850 1250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B1348A6
P 7850 1600
F 0 "#PWR?" H 7850 1350 50  0001 C CNN
F 1 "GND" H 7850 1450 50  0000 C CNN
F 2 "" H 7850 1600 50  0001 C CNN
F 3 "" H 7850 1600 50  0001 C CNN
	1    7850 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 1600 7850 1400
Wire Wire Line
	7450 950  7850 950 
Wire Wire Line
	7850 850  7850 1100
$Comp
L C C?
U 1 1 5B134ABC
P 7850 2550
F 0 "C?" H 7875 2650 50  0000 L CNN
F 1 "2.2u" H 7875 2450 50  0000 L CNN
F 2 "" H 7888 2400 50  0001 C CNN
F 3 "" H 7850 2550 50  0001 C CNN
	1    7850 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 2250 7850 2250
Wire Wire Line
	7850 2150 7850 2400
$Comp
L GND #PWR?
U 1 1 5B134BC6
P 7850 2900
F 0 "#PWR?" H 7850 2650 50  0001 C CNN
F 1 "GND" H 7850 2750 50  0000 C CNN
F 2 "" H 7850 2900 50  0001 C CNN
F 3 "" H 7850 2900 50  0001 C CNN
	1    7850 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 2900 7850 2700
Connection ~ 7850 2250
Connection ~ 7850 950 
$Comp
L +2.5V #PWR?
U 1 1 5B135465
P 8150 4150
F 0 "#PWR?" H 8150 4000 50  0001 C CNN
F 1 "+2.5V" H 8150 4290 50  0000 C CNN
F 2 "" H 8150 4150 50  0001 C CNN
F 3 "" H 8150 4150 50  0001 C CNN
	1    8150 4150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B1354A9
P 8700 8350
F 0 "#PWR?" H 8700 8100 50  0001 C CNN
F 1 "GND" H 8700 8200 50  0000 C CNN
F 2 "" H 8700 8350 50  0001 C CNN
F 3 "" H 8700 8350 50  0001 C CNN
	1    8700 8350
	1    0    0    -1  
$EndComp
$Comp
L -2.5V #PWR?
U 1 1 5B1354ED
P 8150 8350
F 0 "#PWR?" H 8150 8200 50  0001 C CNN
F 1 "-2.5V" H 8150 8490 50  0000 C CNN
F 2 "" H 8150 8350 50  0001 C CNN
F 3 "" H 8150 8350 50  0001 C CNN
	1    8150 8350
	-1   0    0    1   
$EndComp
Wire Wire Line
	7900 4250 7900 4200
Wire Wire Line
	7900 4200 8400 4200
Wire Wire Line
	8400 4200 8400 4250
Wire Wire Line
	8300 4250 8300 4200
Connection ~ 8300 4200
Wire Wire Line
	8200 4250 8200 4200
Connection ~ 8200 4200
Wire Wire Line
	8100 4250 8100 4200
Connection ~ 8100 4200
Wire Wire Line
	8000 4250 8000 4200
Connection ~ 8000 4200
Wire Wire Line
	8150 4150 8150 4200
Connection ~ 8150 4200
Wire Wire Line
	7900 8250 7900 8300
Wire Wire Line
	7900 8300 8400 8300
Wire Wire Line
	8400 8300 8400 8250
Wire Wire Line
	8150 8350 8150 8300
Connection ~ 8150 8300
Wire Wire Line
	8100 8250 8100 8300
Connection ~ 8100 8300
Wire Wire Line
	8000 8250 8000 8300
Connection ~ 8000 8300
Wire Wire Line
	8200 8250 8200 8300
Connection ~ 8200 8300
Wire Wire Line
	8300 8250 8300 8300
Connection ~ 8300 8300
Wire Wire Line
	8600 8250 8600 8300
Wire Wire Line
	8600 8300 8800 8300
Wire Wire Line
	8800 8300 8800 8250
Wire Wire Line
	8700 8250 8700 8350
Connection ~ 8700 8300
$Comp
L +3.3V #PWR?
U 1 1 5B13611C
P 8850 1550
F 0 "#PWR?" H 8850 1400 50  0001 C CNN
F 1 "+3.3V" H 8850 1690 50  0000 C CNN
F 2 "" H 8850 1550 50  0001 C CNN
F 3 "" H 8850 1550 50  0001 C CNN
	1    8850 1550
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 5B136167
P 8650 4150
F 0 "#PWR?" H 8650 4000 50  0001 C CNN
F 1 "+3.3V" H 8650 4290 50  0000 C CNN
F 2 "" H 8650 4150 50  0001 C CNN
F 3 "" H 8650 4150 50  0001 C CNN
	1    8650 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 4250 8600 4200
Wire Wire Line
	8600 4200 8700 4200
Wire Wire Line
	8700 4200 8700 4250
Wire Wire Line
	8650 4150 8650 4200
Connection ~ 8650 4200
$Comp
L C C?
U 1 1 5B136680
P 9700 7900
F 0 "C?" H 9725 8000 50  0000 L CNN
F 1 "1u" H 9725 7800 50  0000 L CNN
F 2 "" H 9738 7750 50  0001 C CNN
F 3 "" H 9700 7900 50  0001 C CNN
	1    9700 7900
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5B136833
P 9950 7900
F 0 "C?" H 9975 8000 50  0000 L CNN
F 1 "1u" H 9975 7800 50  0000 L CNN
F 2 "" H 9988 7750 50  0001 C CNN
F 3 "" H 9950 7900 50  0001 C CNN
	1    9950 7900
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5B13689A
P 10200 7900
F 0 "C?" H 10225 8000 50  0000 L CNN
F 1 "0.1u" H 10225 7800 50  0000 L CNN
F 2 "" H 10238 7750 50  0001 C CNN
F 3 "" H 10200 7900 50  0001 C CNN
	1    10200 7900
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5B1368F4
P 10450 7900
F 0 "C?" H 10475 8000 50  0000 L CNN
F 1 "1u" H 10475 7800 50  0000 L CNN
F 2 "" H 10488 7750 50  0001 C CNN
F 3 "" H 10450 7900 50  0001 C CNN
	1    10450 7900
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5B136951
P 10700 7900
F 0 "C?" H 10725 8000 50  0000 L CNN
F 1 "22u" H 10725 7800 50  0000 L CNN
F 2 "" H 10738 7750 50  0001 C CNN
F 3 "" H 10700 7900 50  0001 C CNN
	1    10700 7900
	1    0    0    -1  
$EndComp
$Comp
L -2.5V #PWR?
U 1 1 5B136E8A
P 10200 8150
F 0 "#PWR?" H 10200 8000 50  0001 C CNN
F 1 "-2.5V" H 10200 8290 50  0000 C CNN
F 2 "" H 10200 8150 50  0001 C CNN
F 3 "" H 10200 8150 50  0001 C CNN
	1    10200 8150
	-1   0    0    1   
$EndComp
Wire Wire Line
	9400 7650 9700 7650
Wire Wire Line
	9700 7650 9700 7750
Wire Wire Line
	9400 7550 10200 7550
Wire Wire Line
	9950 7550 9950 7750
Wire Wire Line
	10200 7550 10200 7750
Connection ~ 9950 7550
Wire Wire Line
	9400 7450 10450 7450
Wire Wire Line
	10450 7450 10450 7750
Wire Wire Line
	9400 7350 10700 7350
Wire Wire Line
	10700 7350 10700 7750
Wire Wire Line
	9700 8050 9700 8100
Wire Wire Line
	9700 8100 10700 8100
Wire Wire Line
	10700 8100 10700 8050
Wire Wire Line
	10450 8050 10450 8100
Connection ~ 10450 8100
Wire Wire Line
	10200 8050 10200 8150
Connection ~ 10200 8100
Wire Wire Line
	9950 8050 9950 8100
Connection ~ 9950 8100
$Comp
L C C?
U 1 1 5B1376CC
P 9050 9250
F 0 "C?" H 9075 9350 50  0000 L CNN
F 1 "1u" H 9075 9150 50  0000 L CNN
F 2 "" H 9088 9100 50  0001 C CNN
F 3 "" H 9050 9250 50  0001 C CNN
	1    9050 9250
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5B13773D
P 9350 9250
F 0 "C?" H 9375 9350 50  0000 L CNN
F 1 "0.1u" H 9375 9150 50  0000 L CNN
F 2 "" H 9388 9100 50  0001 C CNN
F 3 "" H 9350 9250 50  0001 C CNN
	1    9350 9250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B137923
P 9200 9500
F 0 "#PWR?" H 9200 9250 50  0001 C CNN
F 1 "GND" H 9200 9350 50  0000 C CNN
F 2 "" H 9200 9500 50  0001 C CNN
F 3 "" H 9200 9500 50  0001 C CNN
	1    9200 9500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 9400 9050 9450
Wire Wire Line
	9050 9450 9350 9450
Wire Wire Line
	9350 9450 9350 9400
Wire Wire Line
	9200 9500 9200 9450
Connection ~ 9200 9450
$Comp
L -2.5V #PWR?
U 1 1 5B137DB9
P 9200 9000
F 0 "#PWR?" H 9200 8850 50  0001 C CNN
F 1 "-2.5V" H 9200 9140 50  0000 C CNN
F 2 "" H 9200 9000 50  0001 C CNN
F 3 "" H 9200 9000 50  0001 C CNN
	1    9200 9000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 9100 9050 9050
Wire Wire Line
	9050 9050 9350 9050
Wire Wire Line
	9350 9050 9350 9100
Wire Wire Line
	9200 9000 9200 9050
Connection ~ 9200 9050
$Comp
L C C?
U 1 1 5B1383E1
P 8450 9250
F 0 "C?" H 8475 9350 50  0000 L CNN
F 1 "1u" H 8475 9150 50  0000 L CNN
F 2 "" H 8488 9100 50  0001 C CNN
F 3 "" H 8450 9250 50  0001 C CNN
	1    8450 9250
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5B138479
P 8750 9250
F 0 "C?" H 8775 9350 50  0000 L CNN
F 1 "0.1u" H 8775 9150 50  0000 L CNN
F 2 "" H 8788 9100 50  0001 C CNN
F 3 "" H 8750 9250 50  0001 C CNN
	1    8750 9250
	1    0    0    -1  
$EndComp
$Comp
L +2.5V #PWR?
U 1 1 5B138629
P 8600 9000
F 0 "#PWR?" H 8600 8850 50  0001 C CNN
F 1 "+2.5V" H 8600 9140 50  0000 C CNN
F 2 "" H 8600 9000 50  0001 C CNN
F 3 "" H 8600 9000 50  0001 C CNN
	1    8600 9000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 9100 8450 9050
Wire Wire Line
	8450 9050 8750 9050
Wire Wire Line
	8750 9050 8750 9100
Wire Wire Line
	8600 9000 8600 9050
Connection ~ 8600 9050
$Comp
L GND #PWR?
U 1 1 5B13884F
P 8600 9500
F 0 "#PWR?" H 8600 9250 50  0001 C CNN
F 1 "GND" H 8600 9350 50  0000 C CNN
F 2 "" H 8600 9500 50  0001 C CNN
F 3 "" H 8600 9500 50  0001 C CNN
	1    8600 9500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 9400 8450 9450
Wire Wire Line
	8450 9450 8750 9450
Wire Wire Line
	8750 9450 8750 9400
Wire Wire Line
	8600 9500 8600 9450
Connection ~ 8600 9450
$Comp
L +3.3V #PWR?
U 1 1 5B138E2F
P 9800 9000
F 0 "#PWR?" H 9800 8850 50  0001 C CNN
F 1 "+3.3V" H 9800 9140 50  0000 C CNN
F 2 "" H 9800 9000 50  0001 C CNN
F 3 "" H 9800 9000 50  0001 C CNN
	1    9800 9000
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5B138F8A
P 9650 9250
F 0 "C?" H 9675 9350 50  0000 L CNN
F 1 "1u" H 9675 9150 50  0000 L CNN
F 2 "" H 9688 9100 50  0001 C CNN
F 3 "" H 9650 9250 50  0001 C CNN
	1    9650 9250
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5B139005
P 9950 9250
F 0 "C?" H 9975 9350 50  0000 L CNN
F 1 "0.1u" H 9975 9150 50  0000 L CNN
F 2 "" H 9988 9100 50  0001 C CNN
F 3 "" H 9950 9250 50  0001 C CNN
	1    9950 9250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 9100 9650 9050
Wire Wire Line
	9650 9050 9950 9050
Wire Wire Line
	9950 9050 9950 9100
Wire Wire Line
	9800 9000 9800 9050
Connection ~ 9800 9050
$Comp
L GND #PWR?
U 1 1 5B13923A
P 9800 9500
F 0 "#PWR?" H 9800 9250 50  0001 C CNN
F 1 "GND" H 9800 9350 50  0000 C CNN
F 2 "" H 9800 9500 50  0001 C CNN
F 3 "" H 9800 9500 50  0001 C CNN
	1    9800 9500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 9400 9650 9450
Wire Wire Line
	9650 9450 9950 9450
Wire Wire Line
	9950 9450 9950 9400
Wire Wire Line
	9800 9500 9800 9450
Connection ~ 9800 9450
$Comp
L C C?
U 1 1 5B139A8C
P 6600 7250
F 0 "C?" H 6625 7350 50  0000 L CNN
F 1 "0.1u" H 6625 7150 50  0000 L CNN
F 2 "" H 6638 7100 50  0001 C CNN
F 3 "" H 6600 7250 50  0001 C CNN
	1    6600 7250
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5B139B0B
P 6300 7250
F 0 "C?" H 6325 7350 50  0000 L CNN
F 1 "10u" H 6325 7150 50  0000 L CNN
F 2 "" H 6338 7100 50  0001 C CNN
F 3 "" H 6300 7250 50  0001 C CNN
	1    6300 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 7050 6300 7100
Wire Wire Line
	6300 7400 6300 7500
Wire Wire Line
	6300 7450 6850 7450
Wire Wire Line
	6850 7450 6850 7150
Wire Wire Line
	6600 7100 6600 7050
Connection ~ 6600 7050
Wire Wire Line
	6600 7400 6600 7450
Connection ~ 6600 7450
$Comp
L -2.5V #PWR?
U 1 1 5B13A17B
P 6300 7500
F 0 "#PWR?" H 6300 7350 50  0001 C CNN
F 1 "-2.5V" H 6300 7640 50  0000 C CNN
F 2 "" H 6300 7500 50  0001 C CNN
F 3 "" H 6300 7500 50  0001 C CNN
	1    6300 7500
	-1   0    0    1   
$EndComp
Connection ~ 6300 7450
$Comp
L GND #PWR?
U 1 1 5B13A3B6
P 9500 7950
F 0 "#PWR?" H 9500 7700 50  0001 C CNN
F 1 "GND" H 9500 7800 50  0000 C CNN
F 2 "" H 9500 7950 50  0001 C CNN
F 3 "" H 9500 7950 50  0001 C CNN
	1    9500 7950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 7850 9500 7850
Wire Wire Line
	9500 7850 9500 7950
Wire Wire Line
	6850 7150 7200 7150
Wire Wire Line
	6300 7050 7200 7050
$Comp
L R R?
U 1 1 5B13C258
P 1850 3450
F 0 "R?" V 1930 3450 50  0000 C CNN
F 1 "R" V 1850 3450 50  0000 C CNN
F 2 "" V 1780 3450 50  0001 C CNN
F 3 "" H 1850 3450 50  0001 C CNN
	1    1850 3450
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 5B13C330
P 2200 3450
F 0 "R?" V 2280 3450 50  0000 C CNN
F 1 "R" V 2200 3450 50  0000 C CNN
F 2 "" V 2130 3450 50  0001 C CNN
F 3 "" H 2200 3450 50  0001 C CNN
	1    2200 3450
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 5B13C3B0
P 2550 3450
F 0 "R?" V 2630 3450 50  0000 C CNN
F 1 "R" V 2550 3450 50  0000 C CNN
F 2 "" V 2480 3450 50  0001 C CNN
F 3 "" H 2550 3450 50  0001 C CNN
	1    2550 3450
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 5B13C42F
P 2800 3800
F 0 "R?" V 2880 3800 50  0000 C CNN
F 1 "R" V 2800 3800 50  0000 C CNN
F 2 "" V 2730 3800 50  0001 C CNN
F 3 "" H 2800 3800 50  0001 C CNN
	1    2800 3800
	1    0    0    -1  
$EndComp
Text Label 1500 3450 0    60   ~ 0
L1
Text Label 1150 5550 0    60   ~ 0
L2
$Comp
L ESP-WROOM-32D U?
U 1 1 5B13C8D1
P 13150 4550
F 0 "U?" H 12700 5750 60  0000 C CNN
F 1 "ESP-WROOM-32D" H 13050 3350 60  0000 C CNN
F 2 "" H 12000 5300 60  0001 C CNN
F 3 "" H 12000 5300 60  0001 C CNN
	1    13150 4550
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5B13CF1C
P 2450 5800
F 0 "R?" V 2530 5800 50  0000 C CNN
F 1 "R" V 2450 5800 50  0000 C CNN
F 2 "" V 2380 5800 50  0001 C CNN
F 3 "" H 2450 5800 50  0001 C CNN
	1    2450 5800
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5B13D020
P 2200 5550
F 0 "R?" V 2280 5550 50  0000 C CNN
F 1 "R" V 2200 5550 50  0000 C CNN
F 2 "" V 2130 5550 50  0001 C CNN
F 3 "" H 2200 5550 50  0001 C CNN
	1    2200 5550
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 5B13D0EC
P 1850 5550
F 0 "R?" V 1930 5550 50  0000 C CNN
F 1 "R" V 1850 5550 50  0000 C CNN
F 2 "" V 1780 5550 50  0001 C CNN
F 3 "" H 1850 5550 50  0001 C CNN
	1    1850 5550
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 5B13D17C
P 1500 5550
F 0 "R?" V 1580 5550 50  0000 C CNN
F 1 "R" V 1500 5550 50  0000 C CNN
F 2 "" V 1430 5550 50  0001 C CNN
F 3 "" H 1500 5550 50  0001 C CNN
	1    1500 5550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1100 5550 1350 5550
Wire Wire Line
	1450 3450 1700 3450
Wire Wire Line
	2000 3450 2050 3450
Wire Wire Line
	2350 3450 2400 3450
Wire Wire Line
	2700 3450 2900 3450
Wire Wire Line
	2800 3450 2800 3650
Wire Wire Line
	1650 5550 1700 5550
Wire Wire Line
	2000 5550 2050 5550
$Comp
L GND #PWR?
U 1 1 5B13E390
P 2800 4550
F 0 "#PWR?" H 2800 4300 50  0001 C CNN
F 1 "GND" H 2800 4400 50  0000 C CNN
F 2 "" H 2800 4550 50  0001 C CNN
F 3 "" H 2800 4550 50  0001 C CNN
	1    2800 4550
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5B13E8CA
P 3050 3450
F 0 "R?" V 3130 3450 50  0000 C CNN
F 1 "R" V 3050 3450 50  0000 C CNN
F 2 "" V 2980 3450 50  0001 C CNN
F 3 "" H 3050 3450 50  0001 C CNN
	1    3050 3450
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 5B13E946
P 3300 3650
F 0 "C?" H 3325 3750 50  0000 L CNN
F 1 "C" H 3325 3550 50  0000 L CNN
F 2 "" H 3338 3500 50  0001 C CNN
F 3 "" H 3300 3650 50  0001 C CNN
	1    3300 3650
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5B13F075
P 3050 4150
F 0 "R?" V 3130 4150 50  0000 C CNN
F 1 "R" V 3050 4150 50  0000 C CNN
F 2 "" V 2980 4150 50  0001 C CNN
F 3 "" H 3050 4150 50  0001 C CNN
	1    3050 4150
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 5B13F656
P 3300 4350
F 0 "C?" H 3325 4450 50  0000 L CNN
F 1 "C" H 3325 4250 50  0000 L CNN
F 2 "" H 3338 4200 50  0001 C CNN
F 3 "" H 3300 4350 50  0001 C CNN
	1    3300 4350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B13F754
P 3250 1900
F 0 "#PWR?" H 3250 1650 50  0001 C CNN
F 1 "GND" H 3250 1750 50  0000 C CNN
F 2 "" H 3250 1900 50  0001 C CNN
F 3 "" H 3250 1900 50  0001 C CNN
	1    3250 1900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B13F7E6
P 3300 4550
F 0 "#PWR?" H 3300 4300 50  0001 C CNN
F 1 "GND" H 3300 4400 50  0000 C CNN
F 2 "" H 3300 4550 50  0001 C CNN
F 3 "" H 3300 4550 50  0001 C CNN
	1    3300 4550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B13F8A5
P 3300 3850
F 0 "#PWR?" H 3300 3600 50  0001 C CNN
F 1 "GND" H 3300 3700 50  0000 C CNN
F 2 "" H 3300 3850 50  0001 C CNN
F 3 "" H 3300 3850 50  0001 C CNN
	1    3300 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 4150 2800 4150
Wire Wire Line
	2800 3950 2800 4550
Connection ~ 2800 3450
Connection ~ 2800 4150
Wire Wire Line
	3200 4150 4000 4150
Wire Wire Line
	3300 4150 3300 4200
Wire Wire Line
	3300 4500 3300 4550
Wire Wire Line
	3200 3450 4000 3450
Wire Wire Line
	3300 3450 3300 3500
Wire Wire Line
	3300 3800 3300 3850
$Comp
L C C?
U 1 1 5B140113
P 3600 3800
F 0 "C?" H 3625 3900 50  0000 L CNN
F 1 "C" H 3625 3700 50  0000 L CNN
F 2 "" H 3638 3650 50  0001 C CNN
F 3 "" H 3600 3800 50  0001 C CNN
	1    3600 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 4150 3600 3950
Connection ~ 3300 4150
Wire Wire Line
	3600 3450 3600 3650
Connection ~ 3300 3450
Text Label 6800 4650 0    60   ~ 0
L1_P
Text Label 6800 4750 0    60   ~ 0
L1_N
Wire Wire Line
	6750 4750 7200 4750
Wire Wire Line
	6750 4650 7200 4650
Text Label 3700 3450 0    60   ~ 0
L1_P
Text Label 3700 4150 0    60   ~ 0
L1_N
Connection ~ 3600 3450
Connection ~ 3600 4150
Wire Wire Line
	3250 1900 3250 1800
Connection ~ 3250 1800
$EndSCHEMATC
