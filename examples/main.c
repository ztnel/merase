/**
 * @file main.c
 * @author Christian Sargusingh (christian@leapsystems.online)
 * @brief Example for merase usage
 * @version 0.1
 * @date 2022-02
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */
#include <merase.h>

#ifndef LOG_LEVEL
#define LOG_LEVEL 0
#endif

int main(int argc, char **argv) {
  // load in log level from a build preset
  merase_set_level(LOG_LEVEL);
  critical("Merase logging level set to %d", LOG_LEVEL);
  error("Hello from Merase: A simple C logger.");
  warning("Merase is derived from polymerase, an enzyme for building DNA/RNA sequences");
  info("Contributions are welcome.");
  trace("Please contact me at christian@leapsystems.online if you have any questions.");
}