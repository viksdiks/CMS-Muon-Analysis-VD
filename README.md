# CMS Open Data Analysis: Z Boson & Jet Kinematics

![C++](https://img.shields.io/badge/Language-C++-blue.svg)
![ROOT](https://img.shields.io/badge/Framework-CERN%20ROOT-blue.svg)

## Overview
This repository contains a C++ based analysis of **CMS Open Data** using the **CERN ROOT** framework. The primary goal of this project is to study the weak interaction and related fields by exploring:
- **Z boson recoil**
- **Jet kinematics**


By comparing Monte Carlo (MC) simulated data with real experimental data from the Compact Muon Solenoid (CMS) detector, this analysis highlights the impact of kinematic cuts and the underlying physics of proton-proton collisions.

## Physics Context
- **Z Boson Isolation & Hadronic Activity:** We first focus on isolating the Z boson from the dataset using Monte Carlo simulations and specific event selection criteria (reconstructing it from muon pairs). Once isolated, the analysis shifts to the hadronic part of the event, identifying and analyzing the jets associated with the Z boson production.
- **Kinematic Sculpting:** Observing how applying specific kinematic cuts (e.g., $p_T$ thresholds, pseudorapidity $\eta$ limits) alters the shape of the physical distributions.
- **Data vs. Simulation:** Validating theoretical models by comparing simulated Monte Carlo events with actual CMS experimental runs.

## Repository Structure

| File | Description |
| :--- | :--- |
| `WithoutCutsFA.cc` | Analysis script for **Monte Carlo (MC) simulated data** (no kinematic cuts applied). |
| `RWithoutCuts.cc` | Analysis script for **Real experimental data** (no kinematic cuts applied). *The "R" prefix stands for Real data.* |
| `WithCutsFA.cc` | Analysis script for MC data **with** kinematic cuts applied to demonstrate sculpting effects. |
| `RWithCuts.cc` | Analysis script for Real data **with** kinematic cuts applied. |
| `AnalysisPhysics.h` | Core header file containing the physics calculation functions, lorentz vector definitions, and common utilities used across all scripts. |

## Prerequisites
To run this analysis, you need to have the **CERN ROOT** data analysis framework installed on your system.
* **ROOT 6:** [Installation Guide](https://root.cern/install/)
* A C++ compiler (e.g., GCC or Clang)

## Data Preparation
This analysis requires specific `.root` files from the [CERN Open Data Portal](https://opendata.cern.ch/docs/cms). 
1. Download the required Monte Carlo and experimental `.root` datasets.
2. Place the `.root` data files in the same directory as the analysis scripts (or update the file paths within the `.cc` scripts to point to your data directory).

## How to Run
You can execute the scripts directly via the ROOT command line interface. 

1. Open your terminal in the repository directory.
2. Start the ROOT session and run the Monte Carlo analysis(for example):
   ```bash
   root -l WithoutCutsFA.cc
   root -l RWithoutCuts.cc
