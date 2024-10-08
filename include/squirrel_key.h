#ifndef SQUIRREL_KEY_H
#define SQUIRREL_KEY_H
#include <stdbool.h>
#include <stdint.h>

struct key {
  enum squirrel_error (*pressed)(struct key *, uint8_t layer, uint8_t key_index,
                                 int arg_count,
                                 void **args); // called when the key is pressed
  void **pressed_arguments;                    // arguments to pass to pressed
  int pressed_argument_count; // the amount of arguments in pressed_arguments
  enum squirrel_error (*released)(
      struct key *, uint8_t layer, uint8_t key_index, int arg_count,
      void **args);            // called when the key is released
  void **released_arguments;   // arguments to pass to released
  int released_argument_count; // the amount of arguments in released_arguments
};

extern int key_count; // number of keys on the keyboard

void copy_key(
    struct key *source,
    struct key *destination); // Copy the values from one key to another.
enum squirrel_error press_key(
    uint8_t key_index); // Press the key at the index in the appropriate layer.
enum squirrel_error
release_key(uint8_t key_index); // Release the key at the index in the
                                // appropriate layer.

// key_states is an array of booleans that represent the state of each key. Used
// by check_key to determine if a key is pressed or released.
extern bool *key_states;

// check_key compares the state of the key at the index to the key_states array
// to determine if the key is pressed or released, and calls the appropriate
// function.
enum squirrel_error check_key(uint8_t key_index,
                              bool is_pressed); // Check if the key at the
                                                // index is pressed or
                                                // released.
#endif
