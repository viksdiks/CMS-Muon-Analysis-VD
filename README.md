# CMS Open Data Analysis

C++ ROOT analysis of CMS Open Data exploring Z boson recoil, jet kinematics, and kinematic sculpting effects.

## Overview
Working with CMS Open Data to study the weak interaction and related fields using ROOT. 

## Files
* `WithoutCutsFA.cc` - Analysis script for Monte Carlo data.
* `RWithoutCuts.cc` - Analysis script for experimental data.
*  The same files with the cuts. The "R" before the name stands for Real(experimental) data.
* `AnalysisPhysics.h` - Header file containing physics calculation functions.

## How to run
1. Ensure you have CERN ROOT installed.(https://root.cern/install/)
2. Place the required `.root` data files in the same directory.
3. Run the scripts using:
   ```bash
   root -l WithoutCutsFA.cc
   root -l RWithoutCuts.cc
