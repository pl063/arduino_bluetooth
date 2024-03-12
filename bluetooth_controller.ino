
  #include <ArduinoBLE.h>
  #include "smile_matrx.h"


  BLEService ledService("19b10000-e8f2-537e-4f6c-d104768a1214");
  BLECharacteristic switchCharacteristic("19b10001-e8f2-537e-4f6c-d104768a1214", BLERead | BLEWrite | BLENotify | BLEBroadcast, 20);



  const int ledPin = LED_BUILTIN;
  const char* stringArray[4] = {
      "YapplyHoo",
      "Superposition",
      "QuantumLeap",
      "Einsteinium"
  };

  void setup() {
    smile();
    Serial.begin(9600);
    while (!Serial);

    pinMode(ledPin, OUTPUT);

    if (!BLE.begin()) {
      Serial.println("Starting Bluetooth® Low Energy module failed!");
      while (1);
    }

    BLE.setLocalName("LEDCallback");
    BLE.setAdvertisedService(ledService);
    ledService.addCharacteristic(switchCharacteristic);
    BLE.addService(ledService);

    BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
    BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

    switchCharacteristic.setEventHandler(BLEWritten, switchCharacteristicWritten);
    switchCharacteristic.writeValue("Heureka");

    BLE.advertise();

    Serial.println("Bluetooth® device active, waiting for connections...");
  }

  int counter=0;



  void loop() {
    
        
        BLE.poll();
        delay(1000);
        Serial.print("."); // Timer tick
   
  }

  void blePeripheralConnectHandler(BLEDevice central) {
    Serial.print("Connected event, central: ");
    Serial.println(central.address());
  }

  void blePeripheralDisconnectHandler(BLEDevice central) {
    Serial.print("Disconnected event, central: ");
    Serial.println(central.address());
  }

  void switchCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
    Serial.print("Characteristic event, written: ");

    uint8_t characteristicValue[20];
    int bytesRead = characteristic.readValue(characteristicValue, sizeof(characteristicValue));

    Serial.print("Received bytes: ");
    for (int i = 0; i < bytesRead; i++) {
      Serial.print(characteristicValue[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    String receivedString = "";

    for (int i = 0; i < bytesRead; i++) {
      receivedString += (char)characteristicValue[i];
    }

    Serial.println("Value: " + receivedString);
    characteristic.writeValue(stringArray[random(0, 4)]); // set initial value for this characteristic 
  }