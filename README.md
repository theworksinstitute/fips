# Frequency Independent Phase Shifter

This library contains two set of codes:
1. files with xi_interpolator: the optimal xi value for a large array of Phi0 and Q was determined numerically, and a table contains these optimal xi values; for any given Phi0 and Q, the best xi is determined via interpolation, and then with these a single stage filter can be defined (and plotted)
2. files with phase_shifter_calculation_threestage: a three stage filter given via predefined equations, the coefficients of which are calculated based on optimilzation performed

All the details for the above calculations are described in a google drive document shared for now with TheWorks team members.

<a href="https://github.com/theworksinstitute/fips/blob/main/xi_interpolator.h">xi_interpolator.h</a>:
c++ version of the tabulated values and the interpolator

<a href="https://github.com/theworksinstitute/fips/blob/main/xi_interpolator.cc">xi_interpolator.cc</a>:
c++ code using the interpolator to calculate parameters for a given Phi0 and Q

<a href="https://github.com/theworksinstitute/fips/blob/main/xi_interpolator_plotter.cc">xi_interpolator_plotter.cc</a>:
plotting Phi(omega) with the calculated central frequencies for any Phi0 and Q, in c++/ROOT

<a href="https://github.com/theworksinstitute/fips/blob/main/xi_interpolator.py">xi_interpolator.py</a>:
tabulated values and interpolator in Python

<a href="https://github.com/theworksinstitute/fips/blob/main/xi_interpolator_plotter.py">xi_interpolator_plotter.py</a>:
Phi(omega) plotter using the calculated central frequencies for any Phi0 and Q, in Python

<a href="https://github.com/theworksinstitute/fips/blob/main/phase_shifter_calculation_threestage.cc">phase_shifter_calculation_threestage.cc</a>:
three stage filter in c++/ROOT

<a href="https://github.com/theworksinstitute/fips/blob/main/phase_shifter_calculation_threestage.py">phase_shifter_calculation_threestage.py</a>:
three stage filter in Python

<a href="https://github.com/theworksinstitute/fips/blob/main/Makefile">Makefile</a>:
used to compile the c++ version of plotter (ROOT also needed for that)

Example output from xi_interpolator_plotter (left: c++/ROOT, right: Python):<br />
<img alt="phasefunc_ave90_Q010 ROOT" src="https://user-images.githubusercontent.com/38218165/212292835-16786a3e-7295-4877-a23a-87a9c098b24e.png" width=300 />
<img alt="phasefunc_Phi090_Q010 Python" src="https://user-images.githubusercontent.com/38218165/212292776-ea20eef9-a560-430b-934c-3dcbc3bb528f.png" width=300 />

Example from phase_shifter_calculation_threestage.cc (three stages, c++/ROOT version):<br />
<img alt="phasefunc_threestage_many" src="https://user-images.githubusercontent.com/38218165/207390031-d4a3d175-0bdf-4643-9915-e90e1704335d.png" width=300 />
<img alt="phasefunc_threestage_many_diff" src="https://user-images.githubusercontent.com/38218165/207390022-7b35021f-eb64-4b73-8322-7aa69893a8d7.png" width=300 /><br />
(note that right plot is in degrees, NOT radians; all others are in radians)

Example from phase_shifter_calculation_threestage.py (three stages, Python version):<br />
<img alt="phase_shifter_threestage_python" src="https://user-images.githubusercontent.com/38218165/209837680-87123765-c4f1-4c96-9bfb-6ad40fb2a566.png" width=300 />
<img alt="phase_shifter_threestage_diff_python" src="https://user-images.githubusercontent.com/38218165/209837682-ca78f4b8-2da0-4d10-9a21-86b185f4fbfa.png" width=300 />

Text files with output parameters:

<a href="https://github.com/theworksinstitute/fips/blob/main/Q_Phi0_table.txt">Q_Phi0_table.txt</a>: Table of xi values for some example Q and Phi0 values for the single stage filter

<a href="https://github.com/theworksinstitute/fips/blob/main/three_stage_example_parameters.txt">three_stage_example_parameters.txt</a>: Parameters of the three stage filter for some example Phi0 values.
