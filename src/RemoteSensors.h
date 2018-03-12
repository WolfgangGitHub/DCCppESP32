/**********************************************************************
DCC++ BASE STATION FOR ESP32

COPYRIGHT (c) 2018 Mike Dunston
COPYRIGHT (c) 2018 Dan Worth

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see http://www.gnu.org/licenses
**********************************************************************/

#ifndef _DETECTORS_H_
#define _DETECTORS_H_

#include <ArduinoJson.h>
#include "DCCppProtocol.h"
#include "Sensors.h"

class RemoteSensor : public Sensor {
public:
  RemoteSensor(uint16_t, uint16_t=0);
  const uint16_t getRawID() {
    return _rawID;
  }
  const uint16_t getSensorValue() {
    return _value;
  }
  void setSensorValue(const uint16_t value) {
    _value = value;
    _lastUpdate = millis();
    set(_value != 0);
  }
  virtual void check();
  void showSensor();
private:
  uint16_t _rawID;
  uint16_t _value;
  unsigned long _lastUpdate = 0;
};

class RemoteSensorManager {
public:
  static void init();
  static void show();
  static void createOrUpdate(const uint16_t, const uint16_t);
  static bool remove(const uint16_t);
  static void getState(JsonArray &);
};

class RemoteSensorsCommandAdapter : public DCCPPProtocolCommand {
public:
  void process(const std::vector<String>);
  String getID() {
    return "RS";
  }
};

#endif