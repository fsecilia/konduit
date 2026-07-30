// SPDX-License-Identifier: MIT

#include "device_sink.h"

long konduit_device_sink_write(
    const struct konduit_device_sink* sink,
    const void* data,
    size_t size)
{
    if(!sink || !sink->write) return -1;
    return sink->write(sink->context, data, size);
}
