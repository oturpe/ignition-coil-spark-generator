#!/usr/bin/perl -w

# Resets Pololu A-Star 32u4 microcontroller through usb interface.
# Implementaiton is based on ard-reset-arduino tool from
# https://github.com/sudar/Arduino-Makefile/.
#
# Usage: ./reset-32u4.pl PORT
#     PORT: Com port of the microcontroller
#
# Example: ./reset-32u4.pl /dev/ttyACM3

use strict;
use warnings;

use Device::SerialPort;
use Time::HiRes qw( usleep );

my $port = shift @ARGV
    || die "Fatal: Port must be given as input.";
my $connection = Device::SerialPort->new($port)
    || die "Could not connect to serial port ${port}.";

$connection->baudrate(1200);
$connection->rts_active(1);
$connection->dtr_active(0);
$connection->close();
