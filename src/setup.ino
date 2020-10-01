/*
  Initialize code for Leonardo ETH, Ethernet module W5500
 */
#include <SPI.h>
#include <Ethernet3.h>
#include "utility/w5500.h"

#define SS 10  //W5500 CS
#define RST 11 //W5500 RST

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
#if defined(WIZ550io_WITH_MACADDRESS) // Use assigned MAC address of WIZ550io
;
#else
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
#endif

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

boolean state = true;
void setup()
{
  pinMode(SS, OUTPUT);
  pinMode(RST, OUTPUT);

  digitalWrite(SS, LOW);

  /* If you want to control Reset function of W5500 Ethernet controller */
  digitalWrite(RST, HIGH);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // this check is only needed on the Leonardo:
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Start!");

// start the Ethernet connection:
#if defined(WIZ550io_WITH_MACADDRESS) // Use assigned MAC address of WIZ550io
  if (Ethernet.begin() == 0)
  {
#else
  Ethernet.phyMode(HALF_DUPLEX_10);

  Ethernet.softreset();

  delay(1000);

  if (Ethernet.begin(mac) == 0)
  {
#endif
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }

  Serial.print("Ethernet speed: ");
  Serial.print(Ethernet.speed());
  Serial.println();

  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++)
  {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();

  digitalWrite(SS, HIGH);

  delay(10000);
}
void loop()
{
  Serial.println("Power down the W5500");

  Ethernet.phyMode(POWER_DOWN);
  // or direct write the register value
  //w5500.setPHYCFGR(0b11110111);
  //w5500.setPHYCFGR(0b01110111);

  delay(10000);

  Serial.println("Power back on the W5500 with '10BT Half-duplex, Auto-negotiation disabled'");
  Ethernet.phyMode(HALF_DUPLEX_10);

  Ethernet.softreset();

  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
  }

  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++)
  {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();
  digitalWrite(SS, HIGH);

  Serial.print("Ethernet speed: ");
  Serial.print(Ethernet.speed());
  Serial.println();
  Serial.println();

  delay(10000);
}