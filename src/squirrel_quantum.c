#include <stdbool.h>
#include <stdint.h>

#include "squirrel_quantum.h"

#include "squirrel_keys.h"
#include "squirrel_types.h"

bool layers[16] = {true,  false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false};
uint_fast8_t default_layer = 0;

void key_down(struct key *key, uint_fast8_t keycode, uint_fast8_t layer,
              bool *layers[16], uint_fast8_t *default_layer) {
  (void)key;
  (void)layer;
  active_keycodes[keycode] = true; // Mark the keycode as active.
}

void key_up(struct key *key, uint_fast8_t keycode, uint_fast8_t layer,
            bool *layers[16], uint_fast8_t *default_layer) {
  (void)key;
  (void)layer;
  active_keycodes[keycode] = false; // Mark the keycode as inactive.
}

void mod_down(struct key *key, uint_fast8_t modifier_code, uint_fast8_t layer,
              bool *layers[16], uint_fast8_t *default_layer) {
  (void)key;
  (void)layer;
  modifiers |=
      modifier_code; // OR the modifier code into the modifiers variable.
}

void mod_up(struct key *key, uint_fast8_t modifier_code, uint_fast8_t layer,
            bool *layers[16], uint_fast8_t *default_layer) {
  (void)key;

  (void)layer;
  modifiers &= ~modifier_code; // AND the inverse of the modifier code into the
                               // modifiers variable.
}

void pass_through_rising(struct key *key, uint_fast8_t arg, uint_fast8_t layer,
                         bool *layers[16], uint_fast8_t *default_layer) {
  (void)arg;
  for (uint_fast8_t i = layer - 1; i >= *default_layer;
       i--) { // Start at the layer below the current layer, go down until the
              // default layer.
    if (!layers[i]) { // If the layer is not active, skip it.
      continue;
    }
    key->rising[i](key, key->risingargs[i], i, layers,
                   default_layer); // Call the rising function for
                                   // the layer.
  }
}

void pass_through_falling(struct key *key, uint_fast8_t arg, uint_fast8_t layer,
                          bool *layers[16], uint_fast8_t *default_layer) {
  (void)arg;
  for (uint_fast8_t i = layer - 1; i >= *default_layer;
       i--) { // Start at the layer below the current layer, go down until the
              // default layer.
    if (!layers[i]) { // If the layer is not active, skip it.
      continue;
    }
    key->falling[i](key, key->fallingargs[i], i); // Call the falling function
                                                  // for the layer.
  }
}

void momentary_rising(struct key *key, uint_fast8_t target_layer,
                      uint_fast8_t layer, bool *layers[16],
                      uint_fast8_t *default_layer) {
  (void)key;
  (void)layer;
  *layers[target_layer] = true;
}

void momentary_falling(struct key *key, uint_fast8_t target_layer,
                       uint_fast8_t layer, bool *layers[16],
                       uint_fast8_t *default_layer) {
  (void)key;
  (void)layer;
  layers[target_layer] = false;
}

void toggle(struct key *key, uint_fast8_t target_layer, uint_fast8_t layer,
            bool *layers[16], uint_fast8_t *default_layer) {
  (void)key;
  if (layer == target_layer) {
    layer = *default_layer;
  } else {
    layer = target_layer;
  }
}

void turn_on(struct key *key, uint_fast8_t target_layer, uint_fast8_t layer,
             bool *layers[16], uint_fast8_t *default_layer) {
  (void)key;
  (void)layer;
  for (int i = 0; i <= 15; i++) {
    layers[i] = false;
  }
  *layers[*default_layer] = true;
  *layers[target_layer] = true;
}

void default_set(struct key *key, uint_fast8_t target_layer, uint_fast8_t layer,
                 bool *layers[16], uint_fast8_t *default_layer) {
  (void)key;
  (void)layer;
  *default_layer = target_layer;
}
