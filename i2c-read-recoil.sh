#!/bin/bash
sudo python i2c-read-recoil.py > $(date "+%H%M%S").csv
