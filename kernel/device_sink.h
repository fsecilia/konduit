// SPDX-License-Identifier: MIT

#pragma once

#include <stddef.h>

struct konduit_device_sink
{
    void* context;
    long (*write)(void* context, const void* data, size_t size);
};

long konduit_device_sink_write(
    const struct konduit_device_sink* sink,
    const void* data,
    size_t size);
