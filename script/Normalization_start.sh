#!/bin/bash

make -j8

./bin/Normalization Full EH1 1
./bin/Normalization Full EH1 2
./bin/Normalization Full EH1 3
./bin/Normalization Full EH1 4

./bin/Normalization Full EH2 1
./bin/Normalization Full EH2 2
./bin/Normalization Full EH2 3
./bin/Normalization Full EH2 4

./bin/Normalization Full EH3 1
./bin/Normalization Full EH3 2
./bin/Normalization Full EH3 3
./bin/Normalization Full EH3 4
