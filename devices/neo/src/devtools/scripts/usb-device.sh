#!/bin/sh

if [ -f /sys/class/i2c-adapter/i2c-0/0-0073/neo1973-pm-host.0/hostmode ]; then
  echo 0 > /sys/class/i2c-adapter/i2c-0/0-0073/neo1973-pm-host.0/hostmode
fi
if [ -f /sys/devices/platform/s3c-ohci/usb_mode ]; then
  echo device > /sys/devices/platform/s3c-ohci/usb_mode
fi
