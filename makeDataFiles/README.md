# makeDataFiles
Low energy event light simulations in SBND.

Code capable of simulating the induced scintillation of low energy events (specifically supernova neutrinos, argon-39 beta decay and radon-222 alpha decay) occuring within the active volume of SBND (200 by 400 by 500 cm) for different configurations of TPB-coated, wavelength-shifting reflector foils.

## Using the code
The code generates .root files which contain both an "event_tree" and a "data_tree", where the former contains information on each event entry (e.g. a supernova event) and the latter essentially contains an entry for each and every DETECTED photon from ALL events simulated (=> data_tree >> event_tree).

* Before you start, you'll need to set up ROOT. Do this by entering "source setupRoot.sh" into the terminal
* Then, compile the code by typing "make -B", to recompile everything.
  * NOTE: You must have the libraries in the directory you are working from, the libraries begin with: Lib154PMTs8inch_... (these are ~300MB each)
  * As many of the configurable parameters are in the 'libraryanalyze_light_histo.h' header file, if you change a parameter in this file, it is best to recompile everything in the project.
* The Makefile generates an executable that can be run with "./libraryanalyze_light_histo" (or whatever you change the name to). If you happen to be missing the data file, a segmentation violation will occur. Before the crash readout, you will find that the requested file could not be found. Change your path, and it should then run fine.

The code creates two root files - where the *event_file.root* should contain the information needed to perform any analysis. The event_tree has data on an event-by-event basis, and data_tree has the information based on DETECTED photons from ALL events.

## IMPORTANT NOTES:
1.  Use the "libraryanalyze_light_histo.h" file to change:
	  - The type of event
	  - The number of events
	  - The position of the events (make sure only one Boolean is true)
	  - The foil configuration (full coverage, cathode-only coverage or no coverage)
	  - The general properties of an event type, e.g. electron scintillation yield (most likely will not need to be changed)

2. All of the main functionailty used to generate the .root files is found in "libraryanalyze_light_histo.cc". This is well commented and I would advise going through it slowly to understand how the trees are created/filled.

3. plotEvents_yz.C contains simple code that will read in the root file, grab the tree's and plot the histograms.

4. utility_functions.cc contains the functions which determine the timing of the photons. Notice that to include the simulation of radon I have added Rn_function which is basically a gaussian centered around the mean radon energy. I have also added functionality to Scintillation_function which now has a third parameter that determines whether it is electron-like / alpha particle scintillation as this will determine the ratio of the fast and slow components. 


## Notes on number of events and memory consumption:
At the time of writing, the memory consumption of the code is rather significant. This is most likely due to the calculation of the transport and scintillation times (for every detected photon) which are determined by the GetVUVTime and GetVisibleTimeOnlyCathode functions in the utilityfunctions.cc/.h files. 

## Other notes:
The variation in detection efficiency based on position is important, making higher statistics samples very useful. If you desire to generate higher statistics to test the detection efficiency, I would recommend running the code without the timing operations (NB in addition to commenting out the timing operations, you'll have to write a for loop to fill the data_tree for every photon (entry)).

Please be aware that running large statistics WITH TIMING OPERATIONS takes a long time.
- The event tree will have an entry for each event you chose to simulate. Therefore, if you set max_events_FE to 100 for example, you would expect to see
100 events in the event tree 
- the data tree has an entry for every single photon which was detected from ALL of the events. To determine which event a photon came from, you'll need
to see the data_event leaf for that entry. 
	  
