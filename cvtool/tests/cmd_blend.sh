#!/usr/bin/env bash

. $CVTOOL_TESTS_COMMON

cmd_tests_init

$CVTOOL create -f lum   -t uint8 -w 100 -h 100 -c 0xffffff > ff.pgm
$CVTOOL create -f lum   -t uint8 -w 100 -h 100 -c 0x000000 > 00.pgm
$CVTOOL create -f lum   -t uint8 -w 100 -h 100 -c 0x808080 > 80.pgm

$CVTOOL create -f color -t uint8 -w 100 -h 100 -c 0xff0000 > r.pnm
$CVTOOL create -f color -t uint8 -w 100 -h 100 -c 0x00ff00 > g.pnm
$CVTOOL create -f color -t uint8 -w 100 -h 100 -c 0x807f00 > rg.pnm

$CVTOOL blend -s g.pnm -a ff.pgm -S   < r.pnm > xr.pnm
cmp r.pnm xr.pnm
$CVTOOL blend -s g.pnm -a 00.pgm -x 0 < r.pnm > xg.pnm
cmp g.pnm xg.pnm
$CVTOOL blend -s g.pnm -a 80.pgm -y 0 < r.pnm > xrg.pnm
cmp rg.pnm xrg.pnm

cmd_tests_cleanup
