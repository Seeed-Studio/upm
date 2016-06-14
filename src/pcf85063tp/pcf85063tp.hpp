/*
 * Author: Jon Trulson <jtrulson@ics.com>
 * Copyright (c) 2014 Intel Corporation.
 *
 * Adapted from Seeed Studio library:
 * https://github.com/Seeed-Studio/RTC_PCF85063TP
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include <string>
#include <mraa/i2c.hpp>

#define PCF85063TP_I2C_ADDR    0x51
#define REG_CTRL1       0x00
#define REG_CTRL1_STOP  0x20
#define REG_CTRL2       0x01
#define REG_SEC         0x04
#define REG_SEC_OS      0x80
#define REG_MIN         0x05
#define REG_HOUR        0x06
#define REG_DAY         0x07
#define REG_WEEK        0x08
#define REG_MON         0x09
#define REG_YEAR        0x0A

// Days of the week
#define PCF85063TP_DAY_SUN 0
#define PCF85063TP_DAY_MON 1
#define PCF85063TP_DAY_TUE 2
#define PCF85063TP_DAY_WED 3
#define PCF85063TP_DAY_THU 4
#define PCF85063TP_DAY_FRI 5
#define PCF85063TP_DAY_SAT 6


namespace upm {
  /**
   * @brief PCF85063TP Real-Time Clock library
   * @defgroup PCF85063TP libupm-PCF85063TP
   * @ingroup seeed i2c time
   */

  /**
   * @library PCF85063TP
   * @sensor PCF85063TP
   * @comname Grove RTC (Real-Time Clock)
   * @altname PCF85063TP RTC
   * @type time
   * @man seeed
   * @con i2c
   *
   * @brief API for the PCF85063TP Real-Time CLock
   *
   * UPM module for the PCF85063TP-based real-time clock. The clock can provide information
   * about seconds, minutes, hours, day of the week, day of the month,
   * month, and year. It can operate in either a 24-hour or a 12-hour format.
   * This device can also output a square wave at 1Khz, 4Khz, 8Khz, and 32Khz.
   * However, this capability is not implemented in this module.
   *
   * @image html PCF85063TP.jpg
   * @snippet PCF85063TP.cxx Interesting
   */
  class PCF85063TP {
  public:
    /**
     * PCF85063TP constructor
     *
     * @param bus I2C bus to use
     */
    PCF85063TP(int bus);

    /**
     * Loads all the time values
     *
     * @return True if time data loaded successfully
     */
    bool loadTime();

    /**
     * Sets the time. You should call loadTime() beforehand to
     * maintain consistency
     *
     * @return True if time is set successfully
     */
    bool setTime();

    /**
     * Enables an oscillator on the clock.
     *
     * @return 0 (mraa::SUCCESS) if successful; non-zero otherwise
     */
    mraa::Result enableClock();

    /**
     * Disables the oscillator on the clock. This prevents the clock
     * from updating any time/date values
     *
     * @return 0 (mraa::SUCCESS) if successful; non-zero otherwise
     */
    mraa::Result disableClock();

    /**
     * Writes value(s) into registers
     *
     * @param reg Register location to start writing into
     * @param buffer Buffer for data storage
     * @param len Number of bytes to write
     * @return 0 (mraa::SUCCESS) if successful; non-zero otherwise
     */
    mraa::Result writeBytes(uint8_t reg, uint8_t *buffer, int len);

    /**
     * Reads value(s) from registers
     *
     * @param reg Register location to start reading from
     * @param buffer Buffer for data storage
     * @param len Number of bytes to read
     * @return Number of bytes read
     */
    int readBytes(uint8_t reg, uint8_t *buffer, int len);

    /**
     * Converts a BCD value into decimal
     *
     * @param val BCD value to convert
     * @return Converted decimal value
     */
    unsigned int bcdToDec(uint8_t val);

    /**
     * Converts a decimal value into BCD
     *
     * @param val Decimal value to convert
     * @return Converted BCD value
     */
    uint8_t decToBcd(unsigned int val);

    // These variables store the time data loaded with loadTime(), and
    // are the source of data when setTime() is called.  It is a
    // good idea to call loadTime() to set up the current values before
    // calling setTime() to ensure RTC data is consistent

    /**
     * Holds seconds
     */
    unsigned int seconds;
    /**
     * Holds minutes
     */
    unsigned int minutes;
    /**
     * Holds hours; 1-12 in the am/pm format, 0-23 otherwise
     */
    unsigned int hours;
    /**
     * Holds a day of the week; 1-7, where 1 is Sunday
     */
    unsigned int dayOfWeek;
    /**
     * Holds a day of the month, 1-31
     */
    unsigned int dayOfMonth;
    /**
     * Holds a month, 1-12
     */
    unsigned int month;
    /**
     * Holds a year, 0-99
     */
    unsigned int year;
    /**
     * True if the am/pm format is used, false otherwise
     */
    bool amPmMode;
    /**
     * For the am/pm format, it is true if it's pm, false otherwise
     */
    bool pm;

  private:
    mraa::I2c m_i2c;
  };
}
