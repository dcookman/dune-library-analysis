# mastersProject
Code adapted / written for my masters project: "Detecting supernova neutrinos in liquid argon". The code simulates the response of the light detection system of SBND (a Liquid Argon Time Projection Chamber) for either electron and alpha particle induced scintillation. By analysing the generated root files, cuts to discriminate between these two types of induced scintillation are also explored.

## makeDataFiles 
The *makeDataFiles/* folder includes all of the code necessary to simulate electron-like/alpha particle events that will induce argon scintillation in the active volume of SBND. This folder includes its own *README.md* that instructs the user on how to use the code.

Essentially, the code in this folder is used to create the necessary event files which are analysed using the code in the *analyseDataFiles/* folder. It also contains the *plotEvents_yz.C* file which is a simple script used to plot useful information from the *.root* data files (NB you will need to create a data file in order to run this script)


IMPORTANT NOTE: To run the code, you will need to have the 3 PMT libraries saved locally as they are too large store in the GitHub repositories (~300 MB each). The names of the libraries are as follows: 
* Lib154PMTs8inch_NoCathodeNoFoils.root
* Lib154PMTs8inch_OnlyCathodeTPB.root
* Lib154PMTs8inch_FullFoilsTPB.root

Where the "Lib154PMTs8inch" informs us that its the library for 154, 8 inch (diammeter) photomultiplier tubes and the latter half informs us of the configuration/coverage of the  TPB coated, wavelength-shifting reflector foils. 

ANOTHER IMPORTANT NOTE: The code used to generate the data files has mostly been written by Colton (https://github.com/Colton21/sbnd_scintillation). My contribution involved modifying the code to allow for alpha particle simulation and then writing new code to allow for the analysis of the data files.

## analyseDataFiles
The *analyseDataFiles/* folder contains 3 folders which represent three different types of analysis:
* *LDSanalysis* includes the code used for analysis of SBNDs light detection system (for different configurations of foil coverage)
* *PSDanalysis* includes the code used for the Pulse Shape Discrimination analysis, which was ultimately used to discern between alpha particle and electron-like events.
* *simpleLightCuts* includes the code used to analyse simple cuts which require a minimum number of PMTs to each collect a minimum number of photons per event. NB: all this code is very arcaic / ad hoc as it was written to try and obtain a very specific outcome.


