/*====================================================================================================*/
/*====================================================================================================*/
#include "modules\module_serial.h"
#include "algorithms\algorithm_moveAve.h"

#include "experiment_nrf51.h"
#include "ble_beaconScan.h"

#include <string.h>
#include "softdevice_handler.h"
#include "app_timer.h"

#include <math.h>
/*====================================================================================================*/
/*====================================================================================================*/
#define APP_TIMER_PRESCALER     0
#define APP_TIMER_OP_QUEUE_SIZE 2

APP_TIMER_DEF(m_leds_timer_id);

static void leds_timer_handler( void * p_context )
{
  LED1_Toggle();
}

static void timers_init( void )
{
  uint32_t err_code;

  APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);

  // LED timer
  err_code = app_timer_create(&m_leds_timer_id, APP_TIMER_MODE_REPEATED, leds_timer_handler);
  APP_ERROR_CHECK(err_code);
}

static void timers_start( void )
{
  uint32_t err_code;

  err_code = app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(1000, APP_TIMER_PRESCALER), NULL);
  APP_ERROR_CHECK(err_code);
}
/*====================================================================================================*/
/*====================================================================================================*/
#define MA_FIFO_SIZE  16
#define MA_WINDOW     12
int16_t moveAveFIFO[MA_FIFO_SIZE+1] = {0};

typedef struct {
  int8_t  rssi;
  uint8_t rsp;
  uint8_t type;
  uint8_t dlen;
  uint8_t data[31];
} m_ble_scan_c_t;

double getDistance( int8_t rssi, int8_t tx_power, float n )
{
  return pow(10, (tx_power - rssi) / (10 * n));
}
void position( int8_t rssi )
{
  static uint32_t readTimes = 0;

  int8_t rssi_ma = 0;
  double distance = 0.0;

  readTimes++;

  // simple move ave filter, w = 12
  rssi_ma = (int8_t)MoveAve_SMA(rssi, moveAveFIFO, MA_FIFO_SIZE, MA_WINDOW);

  // get distancem, tx = -61dBm, n = 2.5
  distance = getDistance(rssi_ma, -61, 2.5);

  // print info
  printf("readTimes ------ %d\r\n", readTimes);
  printf("rssi_ma  = %d dBm\r\n", rssi_ma);
  printf("distance = %f m\r\n\r\n", distance);
}
void ble_scan_evt( const ble_evt_t *p_ble_evt )
{
  static int8_t tmp;

  m_ble_scan_c_t m_ble_scan_c;

  m_ble_scan_c.rssi = p_ble_evt->evt.gap_evt.params.adv_report.rssi;
  m_ble_scan_c.rsp  = p_ble_evt->evt.gap_evt.params.adv_report.scan_rsp;
  m_ble_scan_c.type = p_ble_evt->evt.gap_evt.params.adv_report.type;
  m_ble_scan_c.dlen = p_ble_evt->evt.gap_evt.params.adv_report.dlen;
  for(uint8_t i = 0; i < 31; i++)
    m_ble_scan_c.data[i] = p_ble_evt->evt.gap_evt.params.adv_report.data[i];

  LED4_Toggle();

  if((tmp != m_ble_scan_c.rssi) && (m_ble_scan_c.rsp != 1)) {
    tmp = m_ble_scan_c.rssi;

    position(m_ble_scan_c.rssi);

    // print info
//    printf("rsp   - %2X\r\n",  m_ble_scan_c.rsp);
//    printf("type  - %2X\r\n",  m_ble_scan_c.type);
//    printf("dlen  - %2X\r\n",  m_ble_scan_c.dlen);
//    printf("adv_p ----");
//    for(uint8_t i = 0; i < 31; i++)
//      printf("%2X ", m_ble_scan_c.data[i]);
//    printf("\r\n\r\n");

//    printf("uuid     = ");
//    for(uint8_t i = 0; i < 16; i++)
//      printf("%2X ", m_ble_scan_c.data[i+9]);
//    printf("\r\n");
//    printf("major    = %2X, %2x\r\n", m_ble_scan_c.data[25], m_ble_scan_c.data[26]);
//    printf("minor    = %2X, %2x\r\n", m_ble_scan_c.data[27], m_ble_scan_c.data[28]);
//    printf("rssi     = %d dBm\r\n", m_ble_scan_c.rssi);
//    printf("tx power = %d dbm\r\n", (int8_t)m_ble_scan_c.data[29]);
//    printf("\r\n");
  }
}

static void ble_evt_dispatch( ble_evt_t * p_ble_evt )
{
  ble_scan_evt(p_ble_evt);
}

static void ble_stack_init( void )
{
  uint32_t err_code;

  // Initialize the SoftDevice handler module.
  SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM, NULL);

  // Enable BLE stack 
  ble_enable_params_t ble_enable_params;
  memset(&ble_enable_params, 0, sizeof(ble_enable_params));
  ble_enable_params.gatts_enable_params.service_changed = false;
  ble_enable_params.gap_enable_params.role = BLE_GAP_ROLE_CENTRAL;
  err_code = sd_ble_enable(&ble_enable_params);
  APP_ERROR_CHECK(err_code);

  // Register with the SoftDevice handler module for BLE events.
  err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
  APP_ERROR_CHECK(err_code);
}
/*====================================================================================================*/
/*====================================================================================================*/
#define SCAN_INTERVAL   0x0020  // Determines scan interval in units of 0.625 millisecond.
#define SCAN_WINDOW     0x0020  // Determines scan window in units of 0.625 millisecond.

static ble_gap_scan_params_t  m_scan_param;

static void scan_start( void )
{
  uint32_t err_code;

  m_scan_param.active      = 0;             // Active scanning set.
  m_scan_param.selective   = 0;             // Selective scanning not set.
  m_scan_param.interval    = SCAN_INTERVAL; // Scan interval.
  m_scan_param.window      = SCAN_WINDOW;   // Scan window.
  m_scan_param.p_whitelist = NULL;          // No whitelist provided.
  m_scan_param.timeout     = 0x0000;        // No timeout.

  err_code = sd_ble_gap_scan_start(&m_scan_param);
  APP_ERROR_CHECK(err_code);
}
/*====================================================================================================*/
/*====================================================================================================*/
void ble_init( void )
{
  // Initialize
  timers_init();
  ble_stack_init();

  // Start execution
  timers_start();
  scan_start();
}
void ble_power_manage( void )
{
  uint32_t err_code = sd_app_evt_wait();
  APP_ERROR_CHECK(err_code);
}
/*====================================================================================================*/
/*====================================================================================================*/
