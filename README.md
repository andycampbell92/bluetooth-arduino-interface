# bluetooth-arduino-interface
An Arduino sketch that allows the Arduino pin modes and output to be controlled via the serial interface

Supports setting pin mode to input/output, digital output, analog output

The following commands can be entered in the serial monitor within the Arduino IDE with 

IMPORTANT!! Make sure line endings are set to "Both NL & CR"

Set pin mode
```
pm <PIN NUM> <MODE>

// Example set pin 6 to OUTPUT
pm 6 1```

Digtal Write
```
dw <PIN NUM> <VALUE>
// Example set pin 6 to HIGH```

Analog Write
```
aw <PIN NUM> <VALUE>
// example set pin 6 to 125
aw 6 125```
