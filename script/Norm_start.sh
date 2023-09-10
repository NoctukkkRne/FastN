#!/bin/bash

make -j8

./bin/Normalization EH1 1
./bin/Normalization EH1 2
./bin/Normalization EH1 3
./bin/Normalization EH1 4

./bin/Normalization EH2 1
./bin/Normalization EH2 2
./bin/Normalization EH2 3
./bin/Normalization EH2 4

./bin/Normalization EH3 1
./bin/Normalization EH3 2
./bin/Normalization EH3 3
./bin/Normalization EH3 4
