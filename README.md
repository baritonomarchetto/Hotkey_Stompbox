# Hotkey Stompbox
A DIY stompbox to send keystrokes to your software of choice. Hands free!

![](/pics/1000041587_risultato.jpg)

I’ve found myself needing this on more than one occasion over the past few years.

Some time ago, I wanted to send keystrokes to a software looper to start and stop recording my synthesizer output while playing.

Today, I need a device to play and stop a drum loop on my favourite DAW for guitar practice.

Hands-free, is the leitmotiv here!

Whatever your application, if you have ever felt the need for a device that emulates a keyboard to control a software by feet, check this out.

# Supplyes
The PCB I layed down is dimensioned for compatibility with the following components:

- 1x aluminum alloy case (1590B, 112 x 60 x 31 mm)
- 1x panel mount USB type C TPC connector, 4 wires (those used to add a USB charge slot in cars)
- 1X USB type C male connector (those with exposed terminals through a PCB)

The stompbox PCB is populated by the following components:

- 1x RP2040 Zero microcontroller board
- 2x PCB mount footswitch 3PDT 9 pin (latching or non latching)
- 4x PCB mount micro switch 6x6 mm, 20 mm height (tall aren't they? :D)
- 2x 680 ohm resistor
- 6x 10K ohm resistor
- 2x LED, 3mm

![](/pics/IMG_20251024_111900_risultato.jpg)

To work the aluminum alloy case, I suggest you to use:
- Power driller (mandatory)
- Drill bits for metals (mandatory)
- Step drill bits (optional, but highly recommended)
- Auto center puncher (optional)
  
The biggest hole diameter in this project is 12 mm. Nothing scary then!
# Hardware
There's little space inside a 1590B case. Most is already taken by the two footswitches, so only small room is left for any other component.

This is why I opted for the smallest microcontroller board out there: The RP2040 Zero. This thing is in the 4 cm^2 ballpark and equips a powerful (and cheap) microcontroller. A no-brainer.

![](/pics/1000041577_risultato.jpg)

Two classic PCB mount, latching, guitar effect footswitches are used to trigger keystrokes. This makes the device durable and solid feeling.

Four additional (momentary) microswitches are present. These can be used for auxiliary functions like sending other keystrokes, menu diving, operation mode selection, etc.

There are two on-board LEDs. One is directly wired to the 3.3V line and gives information about the existence of the correct tension to feed the microcontroller.

The other one is instead connected to a microcontroller GPIO and can be programmed to return a visual feedback of some action, debugging, etc.

I adopted a panel mount, type-C plug in order to have a sturdy connection. There are not many options for this, honestly, but I think the one adopted is a very good choice.

The Box is directly powered by USB power. USB also sends data from the device to the PC in order to emulate the key presses.
# Software
## Functions
The firmware I wrote performs a single, fundamental, task: emulates PC keyboard keypress at any switch press.

In the moment I am writing keys "SPACE" and "T" are emulated by pressing the footswitch, "i", "j", "k" and "l" by pressing one of the four tactile buttons. User can easily change the keys at software level.

A software debounce routine is implemented to avoid false readings due to switch bounce (and they bounce a lot!).

The board has two LEDs. The one wired to a microcontroller pin is used to give a sign of MCU life on startup: when you first connect the USB cable and the microcontroller turns on, it blinks for some second telling you he is running ok and waiting for switch pressed.
Good to know :)

## Programming
RP2040-based microcontroller boards can be programmed both via circuit Python or Arduino IDE.

I choosed this second way, with the help of [Earl Phil Hower's Pi Pico core](https://github.com/earlephilhower/arduino-pico). To install this core refer to the [Author's notes on his github page](https://github.com/earlephilhower/arduino-pico).

As I said, in my prototype I adopted latching footswitches because easier to source. These, unlike non-latching switches, do not associate the press position to a state and release to another, but toggle the state at every press/release.
The software handles both latching and non-latching switches. I set a definition for the kind of footwitch:

[code]
#define LATCHING
[/code]

Simply comment (//) or delete the line for non latching switches.

# Acknowledgments

A special thanks goes to the nice girls and guys at [JLCPCB](https://jlcpcb.com/IAT) for sponsoring PCBs manufacturing of this project of mine.

![](/pics/1000041588_risultato.jpg)

Without their contribution this project would have never seen the light (I would have stopped at my first prototype: no sharing, only my own personal use... definitely a less noble goal!).

In this run they also sponsored the production of a revision of the [RGB Test Pattern Generator](https://www.instructables.com/DIY-Portable-RGB-CRT-Test-Pattern-Generator/), the previous being affected by an error in the SCART pinout (never trust others footprints!). Now it's fully tested and working.

In this run they also realized for me a prototype of the main circuitry of one of my next project: a multi FX pedal. Let see how it goes!

JLCPCB is a high-tech manufacturer specialized in the production of high-reliable and cost-effective PCBs. They offer a flexible PCB assembly service with a huge library of more than 600.000 components in stock at today.

3D printing is part of their portfolio of services so one could create a full finished product, all in one place!

By registering at JLCPCB site via [THIS LINK](https://jlcpcb.com/IAT) (affiliated link) you will receive a series of coupons for your orders.

You can have your PCB manufactured from $2, stencil from $3 (dropped from $7 recently!). Definitely worth a try, if you ask me ;)
