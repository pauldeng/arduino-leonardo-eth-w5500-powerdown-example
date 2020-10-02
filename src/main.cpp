
/*
  Initialize code for Leonardo ETH, Ethernet module W5500
 */
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "utility/w5100.h"

#define SS 10  //W5500 CS
#define RST 11 //W5500 RST

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
#if defined(WIZ550io_WITH_MACADDRESS) // Use assigned MAC address of WIZ550io
;
#else
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
#endif

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

unsigned int localPort = 8888; // local port to listen for UDP packets

// destination server address
const char serverDomain[] = "dengpeng.de";
//IPAddress serverIp(3, 25, 113, 187);

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

  delay(1000);

  if (Ethernet.begin(mac) == 0)
  {
#endif
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
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

  // initlise the udp
  Udp.begin(localPort);
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(serverDomain, 8888); // send to domain name
  //Udp.beginPacket(serverIp, 8888); // send to ip address
  Udp.print("Start");
  Udp.endPacket();
  Udp.stop();

  delay(10000);
}
void loop()
{
  Serial.println("Power down the W5500");

  W5100.writePHYCFGR_W5500(0b11110111);
  W5100.writePHYCFGR_W5500(0b01110111);

  delay(10000);

  Serial.println("Power back on the W5500 with '10BT Half-duplex, Auto-negotiation disabled'");

  //set to 10Mbit ethernet
  W5100.writePHYCFGR_W5500(0b11000111);
  W5100.writePHYCFGR_W5500(0b01000111);
  W5100.writePHYCFGR_W5500(0b11000000);

  // softreset
  uint16_t count = 0;
  // write to reset bit
  W5100.writeMR(0x80);
  // then wait for soft reset to complete
  do
  {
    uint8_t mr = W5100.readMR();
    if (mr == 0)
      break;
    delay(1);
  } while (++count < 20);

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

  // initlise the udp
  Udp.begin(localPort);
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(serverDomain, 8888); // send to domain name
  //Udp.beginPacket(serverIp, 8888); // send to ip address
  Udp.print("Wake up");
  Udp.endPacket();
  Udp.stop();

  Serial.println();

  delay(10000);
}