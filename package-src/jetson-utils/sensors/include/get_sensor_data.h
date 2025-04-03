/*
 * Copyright (C) 2023 Spacemit Limited
 * All Rights Reserved.
 */

#ifndef __GET_SENSOR_DATA_H__
#define __GET_SENSOR_DATA_H__

#include <stddef.h>
#include <stdint.h>
#include <pthread.h>
#include "cam_module_interface.h"


#ifdef __cplusplus
extern "C"
{
#endif /* extern "C" */

// public to use
typedef struct _USER_INFO_T
{
    PIXEL_FORMAT_E format;
    void *dataBufferAddr;
    uint32_t width;
    uint32_t height;
    uint32_t bufferIndex;
} USER_INFO_T;

void get_sensor_data_init(void);
void get_sensor_data_deinit(void);

USER_INFO_T * get_sensor_buffer(void);
void release_sensor_buffer(uint32_t bufferIndex);

// private
int get_sensor_write_RawData(const IMAGE_BUFFER_S* imgBuf);
int get_sensor_write_YUVData(const IMAGE_BUFFER_S* imgBuf);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __GET_SENSOR_DATA_H__ */
