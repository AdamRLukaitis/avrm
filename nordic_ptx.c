/* Here in lies a concerted and complete effort to get my Nordic
 * nRF24L01+ working. I've had this thing collecting dust for
 * about a year, and it's time to buckle down and figure it out.
 */

#include <avr/io.h>
#include <util/delay.h>
#include "lib/avr.h"
#include "lib/nRF24L01p.h"

int main(void)
{
  // Setup the UART, necessary for stdio actions.
  uart_init();

  // Wait for the nRF24L01p to be ready.
  _delay_us(nRF24L01p_TIMING_INITIAL_US);

  // Initialize the nRF24L01p.
  // TODO: Actual info for arguments.
  nRF24L01p_init(0, 0);

  // Enable pipe 0.
  nRF24L01p_enable_pipe(nRF24L01p_PIPE_0, 0xA6A6A6A6A6, 32);
  nRF24L01p_enable_pipe(nRF24L01p_PIPE_1, 0xD4D4D4D4D4, 32);

  // Set TX mode.
  nRF24L01p_config_transceiver_mode(nRF24L01p_VALUE_CONFIG_PRIM_TX);

  int count = 0;
  while (1)
  {
    char str[50];
    snprintf(str, 50, "%d - is transmission %d.", count, count);
    nRF24L01p_write((byte *) str, 50, nRF24L01p_PIPE_0);
    count++;
    delay_ms(1000);
  }

  return 0;
}
