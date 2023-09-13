#!/bin/bash

make -j8

./bin/Normalization P17B EH1 1
./bin/Normalization P17B EH1 2
./bin/Normalization P17B EH1 3
./bin/Normalization P17B EH1 4

./bin/Normalization P17B EH2 1
./bin/Normalization P17B EH2 2
./bin/Normalization P17B EH2 3
./bin/Normalization P17B EH2 4

./bin/Normalization P17B EH3 1
./bin/Normalization P17B EH3 2
./bin/Normalization P17B EH3 3
./bin/Normalization P17B EH3 4
