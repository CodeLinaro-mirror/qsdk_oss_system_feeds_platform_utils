#
# Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
# SPDX-License-Identifier: BSD-3-Clause-Clear
#
# Makefile for dice_bcc_ca
# Used by OpenWrt build system

TARGET := dice_bcc_ca
SRCS := dice_bcc_ca.c

# Compiler flags will be passed by OpenWrt
CFLAGS += $(TARGET_CFLAGS) -Wall -Wextra -O2
LDFLAGS += $(TARGET_LDFLAGS) -lteec

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
