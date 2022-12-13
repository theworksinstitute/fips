# Frequency Independent Phase Shifter

xi_interpolator.h: contains the tabulated values and the interpolator

xi_interpolator.cc: example code using the interpolator to calculate parameters for a given Phi0 and Q

xi_interpolator_plotter.cc: plotting Phi(omega) with the calculated central frequencies for any Phi0 and Q

phase_shifter_calculation_threestage.cc: three stage filter

Makefile: used to compile the plotter (ROOT also needed for that)

Eexample output from xi_interpolator_plotter.cc (single stage):
![phasefunc_ave90_Q0 07](https://user-images.githubusercontent.com/38218165/207389293-c4c4b65c-80d1-44b3-b2d5-da07d44de7f2.png)

Example from phase_shifter_calculation_threestage.cc (three stages):
![phasefunc_threestage_many](https://user-images.githubusercontent.com/38218165/207390031-d4a3d175-0bdf-4643-9915-e90e1704335d.png)
![phasefunc_threestage_many_diff](https://user-images.githubusercontent.com/38218165/207390022-7b35021f-eb64-4b73-8322-7aa69893a8d7.png)
