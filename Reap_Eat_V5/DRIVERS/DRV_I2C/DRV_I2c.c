/*
 * DRV_I2c.c
 *
 *  Created on: Mar 8, 2021
 *      Author: juanleyva
 */

#include "DRV_I2c.h"

int8_t DRV_I2c_Read(uint8_t id, uint8_t reg_addr, uint8_t *data, uint32_t len)
{

    I2CMasterSlaveAddrSet(I2C0_BASE, id, false);
    I2CMasterDataPut(I2C0_BASE, reg_addr);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C0_BASE));

    if(I2CMasterErr(I2C0_BASE) != I2C_MASTER_ERR_NONE)
    {
        return -1;
    }

    if (len == 1)
    {
        I2CMasterSlaveAddrSet(I2C0_BASE, id, true);
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
        while(I2CMasterBusy(I2C0_BASE));

        data[0] = I2CMasterDataGet(I2C0_BASE);
    }
    else
    {
        I2CMasterSlaveAddrSet(I2C0_BASE, id, true);
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
        while(I2CMasterBusy(I2C0_BASE));

        data[0] = I2CMasterDataGet(I2C0_BASE);

        uint32_t msg_i;

        for (msg_i = 1; msg_i < len - 1; msg_i++)
        {
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
            while(I2CMasterBusy(I2C0_BASE));

            data[msg_i] = I2CMasterDataGet(I2C0_BASE);
        }

        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
        while(I2CMasterBusy(I2C0_BASE));
        data[msg_i] = I2CMasterDataGet(I2C0_BASE);
    }

    return 0;
}

int8_t DRV_I2c_Write(uint8_t id, uint8_t reg_addr, const uint8_t *data, uint32_t len)
{

    I2CMasterSlaveAddrSet(I2C0_BASE, id, false);
    I2CMasterDataPut(I2C0_BASE, reg_addr);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C0_BASE));

    if(I2CMasterErr(I2C0_BASE) != I2C_MASTER_ERR_NONE)
    {
        return -1;
    }

    if (len == 1)
    {
        I2CMasterDataPut(I2C0_BASE, data[0]);
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
        while(I2CMasterBusy(I2C0_BASE));
    }
    else
    {
        uint32_t msg_i;
        for (msg_i = 0; msg_i < len - 1; msg_i++)
        {
            I2CMasterDataPut(I2C0_BASE, data[msg_i]);
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
            while(I2CMasterBusy(I2C0_BASE));
        }

        I2CMasterDataPut(I2C0_BASE, data[msg_i]);
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
        while(I2CMasterBusy(I2C0_BASE));
    }

    return 0;
}
