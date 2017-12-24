# sbnd_scintillation
Low energy light simulations

Before you start, you'll need to set up ROOT. Do this by entering "source setupRoot.sh" into the terminal

As the code stands, it can be compiled simply by typing "make -B", to recompile everything. This only takes a few seconds.
As many of the configurable parameters are in 'libraryanalyze_light_histo.h', when you change a parameter in the .h file,
I prefer to recompile everything in the project.

NOTE: You must have the libraries in the directory you are working from, the libraries begin with: Lib154PMTs8inch_...

The Makefile genrates and executable that can be run with "./libraryanalyze_light_histo", or whatever you change the name to.
If you happen to be missing the data file, a segmentation violation will occur. Before the crash readout, you will find
that the requested file could not be found. Change your path, and it should then run fine.

At the moment the code creates two root files - where the event_file.root should contain the information needed to perform any
analysis. The event_tree has data on an event-by-event basis, and data_tree has the information based on detected photons.

Notes on number of events and memory consumption:

At the time of writing, the memory consumption of the code is rather significant. A suspicion has to do with how the timing 
parameterisation distributions are rather finely sampled, but this is untested. Efforts have been made already to attempt
to reduce overall memory consumption, but it is possible that a more efficient method could be developed.

The variation in detection efficiency based on position is important, making higher statistics samples very useful.

Please be aware that running large statistics takes a long time. I would recommend you try and set the event numbers to of order 100 
(do this in libraryanalyse_light_histo.h) and try to create a few files. Once the files are created try to understand what each tree is telling you.
Remember:
- The event tree will have an entry for each event you chose to simulate. Therefore, if you set max_events_FE to 100 for example, you would expect to see
100 events in the event tree 
- the data tree has an entry for every single photon which was detected from ALL of the events. To determine which event a photon came from, you'll need
to see the data_event leaf for that entry. 
