#!/bin/bash
make

./prog > data.csv

python viewSimulation.py
