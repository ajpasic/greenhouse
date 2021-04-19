#ifndef COMMANDS_H_
#define COMMANDS_H_

typedef enum {
  TEMPERATURE = 0,
  HUMIDITY,
  WATERING,
  LIGHTING,
  SYSTEM,
  SIZE_OF_NOUN_TABLE
} cmd_noun_t;

typedef enum {
  SET = 0,
  GET,
  ALERT,
  SIZE_OF_VERB_TABLE
} cmd_verb_t;

typedef enum {
  CRITICAL = 0,
  WARNING,
  AMBIENT_SENSOR_FAILURE,
  TEMPERATURE_CONTROL_TIMEOUT,
  SIZE_OF_ALERT_TABLE
} cmd_alert_t;

#endif
