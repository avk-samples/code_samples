# Visualization of a spiking neural network simulation

A project description can be found [here](http://anettevonkapri.org/projects/2011-2/neural-network-in-vr/). This project was realized at the Virtual Reality Group in Aachen using the [ViSTA platform](https://www.itc.rwth-aachen.de/cms/IT-Center/Forschung-Projekte/Virtuelle-Realitaet/Infrastruktur/~fgmo/ViSTA-Virtual-Reality-Toolkit/?lidx=1) which allows setup of visualizations with Virtual Reality hardware. 

The purpose of this project was to visualize a time-based simulation of the neuron network activity in the brain. The simulation files were given as spiking behavior of inhibitory and excitatory cells in different layers. Each cell has a list of spiking times during the simulation. The fire rate of a cell decays over time unless a new spike occurs. The visualization drew cells at different scale factors based on the firing rate. 

The three files represent the implementation for the cells. The [Cell class](Cell.h) implements the spiking behavior and how to update firing rate, the derived classes [ExcCell](ExcCell.h) and [InhCell](InhCell.h) implement the drawing behavior.

