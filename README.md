# Frequency Independent Phase Shifter

xi_interpolator.h: contains the tabulated values and the interpolator

xi_interpolator.cc: example code using the interpolator to calculate parameters for a given Phi0 and Q

xi_interpolator_plotter.cc: plotting Phi(omega) with the calculated central frequencies for any Phi0 and Q

phase_shifter_calculation_threestage.cc: three stage filter in c++/ROOT

phase_shifter_calculation_threestage.py: three stage filter in Python

Makefile: used to compile the c++ version of plotter (ROOT also needed for that)

Eexample output from xi_interpolator_plotter.cc (single stage):<br />
<img alt="phasefunc_ave90_Q0 07" src="https://user-images.githubusercontent.com/38218165/207389293-c4c4b65c-80d1-44b3-b2d5-da07d44de7f2.png" width=300 />

Example from phase_shifter_calculation_threestage.cc (three stages, c++/ROOT version):<br />
<img alt="phasefunc_threestage_many" src="https://user-images.githubusercontent.com/38218165/207390031-d4a3d175-0bdf-4643-9915-e90e1704335d.png" width=300 />
<img alt="phasefunc_threestage_many_diff" src="https://user-images.githubusercontent.com/38218165/207390022-7b35021f-eb64-4b73-8322-7aa69893a8d7.png" width=300 /><br />
(note that right plot is in degrees, NOT radians; all others are in radians)

Example from phase_shifter_calculation_threestage.py (three stages, Python version):<br />
<img alt="phase_shifter_threestage_python" src="https://user-images.githubusercontent.com/38218165/209837680-87123765-c4f1-4c96-9bfb-6ad40fb2a566.png" width=300 />
<img alt="phase_shifter_threestage_diff_python" src="https://user-images.githubusercontent.com/38218165/209837682-ca78f4b8-2da0-4d10-9a21-86b185f4fbfa.png" width=300 />
