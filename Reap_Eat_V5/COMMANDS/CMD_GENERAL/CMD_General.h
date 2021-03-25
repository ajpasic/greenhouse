/*
 * CMD_General.h
 *
 *  Created on: Mar 16, 2021
 *      Author: juanleyva
 */

#ifndef COMMANDS_CMD_GENERAL_CMD_GENERAL_H_
#define COMMANDS_CMD_GENERAL_CMD_GENERAL_H_



typedef enum
{
    TEMPERATURE = 0,
    HUMIDITY,
    WATERING,
    LIGHTING,
    SYSTEM,

    SIZE_OF_NOUN_TABLE

} cmd_noun_t;

typedef enum
{
    SET = 0,
    GET,
    ALERT,

    SIZE_OF_VERB_TABLE

} cmd_verb_t;

typedef enum
{
    CRITICAL,
    WARNING,

    AMBIENT_SENSOR_FAILURE,
    TEMPERATURE_CONTROL_TIMEOUT,
    TYPE_2,
    TYPE_3,
    TYPE_4,
    TYPE_5,
    TYPE_6,
    TYPE_7,
    TYPE_8,
    TYPE_9,
    TYPE_10,
    TYPE_11,
    TYPE_12,
    TYPE_13,
    TYPE_14,
    TYPE_15,
    TYPE_16,

    SIZE_OF_ALERT_TABLE

} cmd_alert_type_t;

#endif /* COMMANDS_CMD_GENERAL_CMD_GENERAL_H_ */
