/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "experiment_nrf51.h"
#include "ble_beaconScan.h"
#include "module_rs232.h"

#include "softdevice_handler.h"
#include "app_timer.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define APP_TIMER_PRESCALER       0   // Value of the RTC1 PRESCALER register.
#define APP_TIMER_MAX_TIMERS      4   // Maximum number of simultaneously created timers.
#define APP_TIMER_OP_QUEUE_SIZE   4   // Size of timer operation queues.

typedef struct {
  int8_t  rssi;
  uint8_t rsp;
  uint8_t type;
  uint8_t dlen ;
  uint8_t data[31];
} m_ble_scan_c_t;

//m_ble_scan_c_t m_ble_scan_c;
static ble_gap_scan_params_t  m_scan_param;
static app_timer_id_t m_leds_timer_id;
/*====================================================================================================*/
/*====================================================================================================*/
static void led_timer_handler( void * p_context )
{
  nrf_gpio_pin_toggle(LED_1);
}

static void timers_init( void )
{
  uint32_t err_code;

  APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_MAX_TIMERS, APP_TIMER_OP_QUEUE_SIZE, false);

  err_code = app_timer_create(&m_leds_timer_id, APP_TIMER_MODE_REPEATED, led_timer_handler);
  APP_ERROR_CHECK(err_code);
}

#define PRINT_ALL_DATA 0
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

  nrf_gpio_pin_toggle(LED_4);

  if((tmp != p_ble_evt->evt.gap_evt.params.adv_report.rssi) && (m_ble_scan_c.rsp != 1)) {
    tmp = m_ble_scan_c.rssi;

//    RS232_SendStr((int8_t*)"rsp  :"); RS232_SendNum(Type_H, 2, m_ble_scan_c.rsp);   RS232_SendStr((int8_t*)"\r\n");
//    RS232_SendStr((int8_t*)"type :"); RS232_SendNum(Type_H, 2, m_ble_scan_c.type);  RS232_SendStr((int8_t*)"\r\n");
//    RS232_SendStr((int8_t*)"dlen :"); RS232_SendNum(Type_H, 2, m_ble_scan_c.dlen);  RS232_SendStr((int8_t*)"\r\n");

#if PRINT_ALL_DATA
    RS232_SendStr((int8_t*)"rssi = ");  RS232_SendNum(Type_I, 3, m_ble_scan_c.rssi);  RS232_SendStr((int8_t*)"dbm\r\n");
    RS232_SendStr((int8_t*)"adv_packet :\r\n");
    for(uint8_t i = 0; i < 31; i++) {
      RS232_SendNum(Type_H, 2, m_ble_scan_c.data[i]);
      RS232_SendStr((int8_t*)" ");
    }
    RS232_SendStr((int8_t*)"\r\n");

#else
//    RS232_SendStr((int8_t*)"uuid  = ");
//    for(uint8_t i = 0; i < 16; i++) {
//      RS232_SendNum(Type_H, 2, m_ble_scan_c.data[i+9]);
//      RS232_SendStr((int8_t*)" ");
//    }
//    RS232_SendStr((int8_t*)"\r\n");
    RS232_SendStr((int8_t*)"major = ");
    RS232_SendNum(Type_H, 2, m_ble_scan_c.data[25]);  RS232_SendStr((int8_t*)" ");
    RS232_SendNum(Type_H, 2, m_ble_scan_c.data[26]);  RS232_SendStr((int8_t*)"\r\n");
    RS232_SendStr((int8_t*)"minor = ");
    RS232_SendNum(Type_H, 2, m_ble_scan_c.data[27]);  RS232_SendStr((int8_t*)" ");
    RS232_SendNum(Type_H, 2, m_ble_scan_c.data[28]);  RS232_SendStr((int8_t*)"\r\n");
    RS232_SendStr((int8_t*)"rssi  = ");
    RS232_SendNum(Type_I, 3, m_ble_scan_c.rssi);  RS232_SendStr((int8_t*)"dbm\r\n");
    RS232_SendStr((int8_t*)"tx power = ");
    RS232_SendNum(Type_I, 3, (int8_t)m_ble_scan_c.data[29]);  RS232_SendStr((int8_t*)"dbm\r\n");
#endif

    RS232_SendStr((int8_t*)"\r\n");
  }
}

static void ble_evt_dispatch( ble_evt_t * p_ble_evt )
{
  ble_scan_evt(p_ble_evt);
}

static void ble_stack_init( void )
{
  uint32_t err_code;

  SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM, false);

  // Register with the SoftDevice handler module for BLE events.
  err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
  APP_ERROR_CHECK(err_code);
}

static void timer_start( void )
{
  uint32_t err_code;

  err_code = app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(1000, APP_TIMER_PRESCALER), NULL);
  APP_ERROR_CHECK(err_code);
}

#define SCAN_INTERVAL   0x0020  // Determines scan interval in units of 0.625 millisecond.
#define SCAN_WINDOW     0x0020  // Determines scan window in units of 0.625 millisecond.
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

void ble_init( void )
{
  timers_init();
  ble_stack_init();

  timer_start();
  scan_start();
}

void ble_power_manage( void )
{
  uint32_t err_code = sd_app_evt_wait();
  APP_ERROR_CHECK(err_code);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
