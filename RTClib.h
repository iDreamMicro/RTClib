// Code by JeeLabs http://news.jeelabs.org/code/
// Released to the public domain! Enjoy!

// Simple general-purpose date/time class (no TZ / DST / leap second handling!)
class DateTime {
public:
    DateTime (uint32_t t =0);
    DateTime (uint16_t year, uint8_t month, uint8_t day,
                uint8_t hour =0, uint8_t min =0, uint8_t sec =0);
    DateTime (const char* date, const char* time);
    uint16_t year() const       { return 2000 + yOff; }
    uint8_t month() const       { return m; }
    uint8_t day() const         { return d; }
    uint8_t hour() const        { return hh; }
    uint8_t minute() const      { return mm; }
    uint8_t second() const      { return ss; }
    uint8_t dayOfWeek() const;
    
    void setYear(uint16_t year)     { yOff = year - 2000; }
    void setMonth(uint8_t month)    { m = month; }
    void setDay(uint8_t day)        { d = day; }
    void setHour(uint8_t hour)      { hh = hour; }
    void setMinute(uint8_t minute)  { mm = minute; }
    void setSecond(uint8_t second)  { ss = second; }

    // 32-bit times as seconds since 1/1/2000
    long secondstime() const;   
    // 32-bit times as seconds since 1/1/1970
    uint32_t unixtime(void) const;

protected:
    uint8_t yOff, m, d, hh, mm, ss;
};

// RTC based on the DS1307 chip connected via I2C and the Wire library
class RTC_DS1307 {
public:

    // SQW/OUT frequencies.
    typedef enum Frequencies
    {
        Frequency_1Hz,
        Frequency_4096Hz,
        Frequency_8192Hz,
        Frequency_32768Hz
    } Frequency_t;
    
    static uint8_t begin(void);
    static void adjust(const DateTime& dt);
    uint8_t isrunning(void);
    static DateTime now();
    
    // SQW/OUT methods.
    static void setSqwOutLevel(uint8_t level);
    static void setSqwOutSignal(Frequencies frequency);
    
    // RAM registers read/write methods. Address locations 08h to 3Fh.
    // Max length = 56 bytes.
    static uint8_t readByteInRam(uint8_t address);
    static void readBytesInRam(uint8_t address, uint8_t length, uint8_t* p_data);
    static void writeByteInRam(uint8_t address, uint8_t data);
    static void writeBytesInRam(uint8_t address, uint8_t length, uint8_t* p_data);
};

// RTC using the internal millis() clock, has to be initialized before use
// NOTE: this clock won't be correct once the millis() timer rolls over (>49d?)
class RTC_Millis {
public:
    static void begin(const DateTime& dt) { adjust(dt); }
    static void adjust(const DateTime& dt);
    static DateTime now();

protected:
    static long offset;
};
