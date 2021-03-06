#!/usr/bin/env bash

. $CVTOOL_TESTS_COMMON

cmd_tests_init

$CVTOOL create -w 10 -h 10 -c red > r.pnm 

$CVTOOL tonemap -m schlick94 --brightness 100.0 < r.pnm > /dev/null
$CVTOOL tonemap -m tumblin99 --max-display-luminance=200.0 --display-adaptation-level=100.0 --max-displayable-contrast=70.0 < r.pnm > /dev/null
$CVTOOL tonemap -m reinhard05 --intensity=0.1 --light-adaptation=0.5 --chromatic-adaptation=0.5 < r.pnm > /dev/null
$CVTOOL tonemap -m ashikhmin02 --local-contrast=0.5 < r.pnm > /dev/null
$CVTOOL tonemap -m drago03 --max-display-luminance=200.0 --bias=0.84 < r.pnm > /dev/null
$CVTOOL tonemap -m durand02 --sigma-spatial=0.3 --sigma-luminance=0.4 --base-contrast=3 < r.pnm > /dev/null
$CVTOOL tonemap -m reinhard02 --key-value=0.1 --white=1.0 --sharpness=10.0 --epsilon=0.5 < r.pnm > /dev/null

cmd_tests_cleanup
