class Stream;

class Pico_Flysky{
  public :
    void begin(HardwareSerial &serial);
    void test();
    void update();
    int readChannel(uint8_t channelNr);
    int readChannel(uint8_t channelNr, int minValue, int maxValue);
  private : 
    static const byte PROTOCOL_LENGTH = 0x20;
    static const byte PROTOCOL_OVERHEAD = 3; // packet is <len><cmd><data....><chkl><chkh>, overhead=cmd+chk bytes
    static const byte PROTOCOL_TIMEGAP = 3; // Packets are received very ~7ms so use ~half that for the gap
    static const byte PROTOCOL_CHANNELS = 14;
    static const byte PROTOCOL_COMMAND40 = 0x40;        // Command to set servo or motor speed is always 0x40
    static const byte PROTOCOL_COMMAND_DISCOVER = 0x80; // Command discover sensor (lowest 4 bits are sensor)
    static const byte PROTOCOL_COMMAND_TYPE = 0x90;     // Command discover sensor (lowest 4 bits are sensor)
    static const byte PROTOCOL_COMMAND_VALUE = 0xA0;    // Command send sensor data (lowest 4 bits are sensor)
    static const byte SENSORMAX = 10; // Max number of sensors

    HardwareSerial *stream; 
    uint8_t ptr;
    uint8_t len;
    uint8_t buffer[PROTOCOL_LENGTH];
    uint16_t channel[PROTOCOL_CHANNELS]; 
    uint16_t channelLastValue[PROTOCOL_CHANNELS]; 
    uint16_t chksum;                  // checksum calculation
    uint8_t lchksum;                  // checksum lower byte received
    uint32_t last;
};
