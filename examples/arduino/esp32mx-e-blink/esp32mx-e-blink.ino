/*
Very simple examples that blinks the LED on the esp32MX-E.
It also sends a message via the serial port if the button is pressed.

IMPORTANT! This example only works with esp32MX-E boards with the latest STM32F030 firmware.
See "Details" sectioin below

When Ethernet is not used, GPIO 0 should be used for controlling the LED. If Ethernet
is enabled, GPIO 5 should be used. This is due to the Ethernet PHY reset, and clock detection
circuitry on the esp32MX-E. But, when using GPIO 5, the LED will never completly turn off, and
will toggle between low and high bright levels.

## Details ##
This example only works with esp32MX-E boards with the latest STM32F030 firmware.
When Ethernet is enabled, the 50MHz clock pulse will be outputted on GPIO0. The STM32F030
has code that monitors GPIO0, and after detecting 2000 clock pulses, will enable the Ethernet
PHY chip(LAN8720). On the old STM32F030 firmware, it enabled the PHY after detecting 2000 pulses.
On the new STM32F030 firmware, these 2000 pulses have to occur within 2ms. This means that GPIO0 can NOT
be used to control the LED on boards with old STM32F030 firmware, seeing that after 2000 pulses, it will
stop working. On these boards, GPIO5 should be used, see the "esp32mx-e-blink-old" example.
  
*/

// LED is controlled via GPIO 0 when Ethernet is not used
static const uint8_t LED = 0;

// Button on the esp32MX-E board
static const uint8_t USER_BTN = 34;

// the setup function runs once when you press reset or power the board
void setup() {
  // Initialize LED pin as ouput.
  pinMode(LED, OUTPUT);

  // Initialize user Button pin as input
  pinMode(USER_BTN, INPUT);

  // initialize serial communication
  Serial.begin(115200);

  Serial.println("Hello from the esp32MX-E");
}

// the loop function runs over and over again forever
void loop() {
  
  // Blink the LED
  digitalWrite(LED, HIGH);    // Turn the LED on (HIGH is the voltage level)
  delay(250);                 // Wait for a second
  digitalWrite(LED, LOW);     // Turn the LED off by making the voltage LOW
  delay(250);                 // Wait for a second

  // Print message if button is pressed
  if (digitalRead(USER_BTN) == 1) {
      Serial.println("User button pressed");
  }
}
