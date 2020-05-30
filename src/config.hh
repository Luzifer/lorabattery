// Logic: Below charging voltage deep-sleep is used, above delay as
// battery is provided power
#define BATTERY_LOAD_VOLTAGE  13.5          // 14V SHOULD be supplied during charge
#define BATTERY_SLEEP_US      240 * 1000000 // 240s of deep sleep = 360 wake-ups / day
#define CHARGE_SLEEP_MS       30 * 1000     // 30s delay between measurements during charging

// Debug: Allow to enable / disable LoRa sending / deep sleep
#define DISABLE_SLEEP         false
#define ENABLE_SEND           true

// PIN to which the voltage sensor is connected
#define PIN_VOLTAGE_READ      32

// Adjustments for the measurement to work around unstable measurements
#define CORRECT_DIFF          0.90  // Measurement isn't fully accurate, lets adjust
#define MEAS_COUNT            16    // How many readings to make for each measurement

// LoRaWAN configuration
#define BAND  868E6 // 868MHz = Europe transfer channel

// Defined through environment variable during build, see platformio.ini
const char* devEui = DEVEUI; // TTN Device EUI
const char* appEui = APPEUI; // TTN Application EUI
const char* appKey = APPKEY; // TTN Application Key
