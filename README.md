# IR-key-receiver

This source is too small to make a big comment. You can use it with Arduino and Digispark/Digistump development boards.
You connect an IR receiver to pin 2 and you should have something that can send NEC-codes.

Basic build block for the codes to send is:

>  0x23000000 + (code << 16) + (mode << 8) + (code ^ mode ^ 0xEC)

"code" is your scancode regarding to USB-HID-spec, and "mode" is what modifier-keys are pressed.

Have Fun! ;)
