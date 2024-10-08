#include "squirrel_consumer.h"
#include <stdint.h>

uint16_t consumer_code = 0;

void consumer_activate_consumer_code(uint16_t code) { consumer_code = code; }
void consumer_deactivate_consumer_code(uint16_t code) {
  if (consumer_code == code) {
    consumer_code = 0;
  }
}
uint16_t consumer_get_consumer_code() { return consumer_code; }
