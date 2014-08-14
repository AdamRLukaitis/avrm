/* Tests for the nrf24l01p lib. */

#include <avr/io.h>
#include <util/delay.h>
#include "lib/avr.h"
#include "lib/nRF24L01p.h"

// Forward declarations.
void assert(const char *name, bool test);

int main(void)
{
  // Setup the UART, necessary for stdio actions.
  uart_init();

  // Wait for the nRF24L01p to be ready.
  _delay_us(nRF24L01p_TIMING_INITIAL_US);

  // Initialize the nRF24L01p.
  nRF24L01p_init();

  // Common storage for register values.
  byte reg;
  long long unsigned int reg40;

  printf("\nRunning Tests\n");

  // Transceiver mode test.
  nRF24L01p_config_transceiver_mode(nRF24L01p_VALUE_CONFIG_PRIM_RX);
  reg = nRF24L01p_get_register8(nRF24L01p_REGISTER_CONFIG);
  assert("config_transceiver_mode_rx", (reg & nRF24L01p_MASK_CONFIG_PRIM_RX)
                                       == nRF24L01p_VALUE_CONFIG_PRIM_RX);

  nRF24L01p_config_transceiver_mode(nRF24L01p_VALUE_CONFIG_PRIM_TX);
  reg = nRF24L01p_get_register8(nRF24L01p_REGISTER_CONFIG);
  assert("config_transceiver_mode_tx", (reg & nRF24L01p_MASK_CONFIG_PRIM_RX)
                                       == nRF24L01p_VALUE_CONFIG_PRIM_TX);

  // Configure address width test.
  nRF24L01p_config_address_width(nRF24L01p_VALUE_SETUP_AW_AW_3);
  reg = nRF24L01p_get_register8(nRF24L01p_REGISTER_SETUP_AW);
  assert("config_address_width_3", (reg & nRF24L01p_MASK_SETUP_AW_AW)
                                   == nRF24L01p_VALUE_SETUP_AW_AW_3);

  nRF24L01p_config_address_width(nRF24L01p_VALUE_SETUP_AW_AW_5);
  reg = nRF24L01p_get_register8(nRF24L01p_REGISTER_SETUP_AW);
  assert("config_address_width_5", (reg & nRF24L01p_MASK_SETUP_AW_AW)
                                   == nRF24L01p_VALUE_SETUP_AW_AW_5);

  // Configure address test.
  nRF24L01p_config_address(nRF24L01p_REGISTER_TX_ADDR, 0x374DFE620B);
  reg40 = nRF24L01p_get_register40(nRF24L01p_REGISTER_TX_ADDR);
  assert("config_address_tx", reg40 == 0x374DFE620B);

  nRF24L01p_config_address(nRF24L01p_REGISTER_RX_ADDR_P0, 0x374DFE620B);
  reg40 = nRF24L01p_get_register40(nRF24L01p_REGISTER_RX_ADDR_P0);
  assert("config_address_rx_p0", reg40 == 0x374DFE620B);

  // Configure payload width test.
  nRF24L01p_config_payload_width(nRF24L01p_REGISTER_RX_PW_P0, 17);
  reg = nRF24L01p_get_register8(nRF24L01p_REGISTER_RX_PW_P0);
  assert("config_payload_width", (reg & nRF24L01p_MASK_RX_PW) == 17);

  // Configure air data rate test.
  nRF24L01p_config_air_data_rate(nRF24L01p_VALUE_RF_SETUP_RF_DR_1Mbps);
  reg = nRF24L01p_get_register8(nRF24L01p_REGISTER_RF_SETUP);
  assert("config_air_data_rate_1Mbps", (reg & nRF24L01p_MASK_RF_SETUP_RF_DR)
                                       == nRF24L01p_VALUE_RF_SETUP_RF_DR_1Mbps);

  nRF24L01p_config_air_data_rate(nRF24L01p_VALUE_RF_SETUP_RF_DR_2Mbps);
  reg = nRF24L01p_get_register8(nRF24L01p_REGISTER_RF_SETUP);
  assert("config_air_data_rate_2Mbps", (reg & nRF24L01p_MASK_RF_SETUP_RF_DR)
                                       == nRF24L01p_VALUE_RF_SETUP_RF_DR_2Mbps);

  // Configure output power test.
  nRF24L01p_config_output_power(nRF24L01p_VALUE_RF_SETUP_RF_PWR_NEG_12dBm);
  reg = nRF24L01p_get_register8(nRF24L01p_REGISTER_RF_SETUP);
  assert("config_output_power_-12dBm", (reg & nRF24L01p_MASK_RF_SETUP_RF_PWR)
                                       == nRF24L01p_VALUE_RF_SETUP_RF_PWR_NEG_12dBm);

  nRF24L01p_config_output_power(nRF24L01p_VALUE_RF_SETUP_RF_PWR_0dBm);
  reg = nRF24L01p_get_register8(nRF24L01p_REGISTER_RF_SETUP);
  assert("config_output_power_0dBm", (reg & nRF24L01p_MASK_RF_SETUP_RF_PWR)
                                     == nRF24L01p_VALUE_RF_SETUP_RF_PWR_0dBm);

  // Power up test.
  nRF24L01p_power_up();
  reg = nRF24L01p_get_register8(nRF24L01p_REGISTER_CONFIG);
  assert("power_up", (reg & nRF24L01p_MASK_CONFIG_PWR_UP)
                     == nRF24L01p_VALUE_CONFIG_PWR_UP);

  nRF24L01p_power_down();
  reg = nRF24L01p_get_register8(nRF24L01p_REGISTER_CONFIG);
  assert("power_down", (reg & nRF24L01p_MASK_CONFIG_PWR_UP)
                       == nRF24L01p_VALUE_CONFIG_PWR_DOWN);

  return 0;
}


//
// assert implementation.
//
void assert(const char *name, bool test)
{
  if (test)
    printf("%s PASS\n", name);
  else
    printf("%s FAIL\n", name);
}