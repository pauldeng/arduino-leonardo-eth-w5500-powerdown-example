/*
  Initialize code for Leonardo ETH, Ethernet module W5500
 */
#include <SPI.h>
#include <Ethernet3.h>
#include <EthernetUdp3.h>
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

  Ethernet.phyMode(POWER_DOWN);
  // or direct write the register value
  //w5500.setPHYCFGR(0b11110111);
  //w5500.setPHYCFGR(0b01110111);

  delay(10000);

  Serial.println("Power back on the W5500 with '10BT Half-duplex, Auto-negotiation disabled'");

  Ethernet.phyMode(HALF_DUPLEX_10);
  Ethernet.softreset();
  // or direct write the register value
  //w5500.setPHYCFGR(0b11000000);
  //w5500.setPHYCFGR(0b01000000);
  //w5500.setPHYCFGR(0b11000000);
  //w5500.softReset();

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

  Serial.print("Ethernet speed: ");
  Serial.print(Ethernet.speed());
  Serial.println();
  Serial.println();

  delay(10000);
}