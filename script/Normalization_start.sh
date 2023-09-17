#!/bin/bash

dataset=P17B
syst_uncertainty=10

make -j8

./bin/Normalization $dataset EH1 1 $syst_uncertainty
./bin/Normalization $dataset EH1 2 $syst_uncertainty
./bin/Normalization $dataset EH1 3 $syst_uncertainty
./bin/Normalization $dataset EH1 4 $syst_uncertainty

./bin/Normalization $dataset EH2 1 $syst_uncertainty
./bin/Normalization $dataset EH2 2 $syst_uncertainty
./bin/Normalization $dataset EH2 3 $syst_uncertainty
./bin/Normalization $dataset EH2 4 $syst_uncertainty

./bin/Normalization $dataset EH3 1 $syst_uncertainty
./bin/Normalization $dataset EH3 2 $syst_uncertainty
./bin/Normalization $dataset EH3 3 $syst_uncertainty
./bin/Normalization $dataset EH3 4 $syst_uncertainty
