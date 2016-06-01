/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf5x_system.h"

#include "nrf51dk_ble.h"

#include "softdevice_handler.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define CENTRAL_LINK_COUNT        0   /**< Number of central links used by the application. When changing this number remember to adjust the RAM settings*/
#define PERIPHERAL_LINK_COUNT     0   /**< Number of peripheral links used by the application. When changing this number remember to adjust the RAM settings*/

#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_XTAL,            \
                                 .rc_ctiv       = 0,                                \
                                 .rc_temp_ctiv  = 0,                                \
                                 .xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM}

void NRF51_BLE_StackInit( void )
{
  uint32_t err_code;

  nrf_clock_lf_cfg_t clock_lf_cfg = NRF_CLOCK_LFCLKSRC;

  // Initialize the SoftDevice handler module.
  SOFTDEVICE_HANDLER_INIT(&clock_lf_cfg, NULL);

  ble_enable_params_t ble_enable_params;
  err_code = softdevice_enable_get_default_config(CENTRAL_LINK_COUNT, PERIPHERAL_LINK_COUNT, &ble_enable_params);
  APP_ERROR_CHECK(err_code);

  //Check the ram settings against the used number of links
  CHECK_RAM_START_ADDR(CENTRAL_LINK_COUNT,PERIPHERAL_LINK_COUNT);

  // Enable BLE stack.
  err_code = softdevice_enable(&ble_enable_params);
  APP_ERROR_CHECK(err_code);
}
/*====================================================================================================*/
/*====================================================================================================*/
