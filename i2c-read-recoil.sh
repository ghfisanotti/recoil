#!/bin/bash
# Function: invoke Python program to request CSV from the Arduino,
#           saves the output to a file using the time of day as filename
# Author: Gerardo Fisanotti - 1-may-2020
sudo python i2c-read-recoil.py > $(date "+%H%M%S").csv
