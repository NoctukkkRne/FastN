<!--
This is a doc for program FastN
-->

# Fast Neutron in DayaBay Experiment

## OWS-tag

### Retw

Remove the Muon veto, and change the high energy cut from 12 MeV to 100 MeV. choose 1500 us as the coincident time.

### Select

The details are below:

| Cut                           | Value     | Effect                                                                 |
|-------------------------------|-----------|------------------------------------------------------------------------|
| Fold                          | =2        | Double coincidence event                                               |
| T2PreOWSMu                    | < 300 ns  | Make sure of the corrlation between the Prompt signal and the OWS Muon |
| T2PrevIWSMu                   | > 1200 us | IWS Muon Veto                                                          |
| T2PrevAdMu                    | > 1200 us | Ad Muon Veto                                                           |
| T2PrevShMu                    | > 1200 us | Shower Muon Veto                                                       |
| T2PrevOWSMu + T2PrevSubEvt[1] | > 15 us   | The Muon decay                                                         |
| DT                            | > 800mm   | The corrlation between the two subevents                               |

<font color = red> Need to check: </font>

1. The T2PrevOWSMu < 300 ns cut.


## IBD-extend

### Retw

Change the high energy cut for prompt signal from 12 MeV to 100 MeV.

### AccSub

Keep the same criteria and procedure as the IBD analysis.

## Normalization:

### Procedure

1. Gain the fast neutron spectrum from the OWS-tag events.
2. Gain the IBD-extend spectrum in high energy range.
3. Normalize the fast neutron spectrum using the IBD-extend spectrum, and get the number of the fast neutron background in IBD candidates.
4. Use the function with the form of $N (\frac{E}{E_0})^{-a - \frac{E}{E_0}}$ to fit the normalized spectrum, and gain the error of the fitting parameters as the statistical uncertainty.
6. Caculate the difference of the integral of the fitting function and the integral of the events number of the normalization fast neutron in high energy range as the systematic uncertainty.
7. Get the mean and the error of the fast neutron background events in IBD candidates.
