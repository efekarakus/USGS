A Spatially-Explicit Carbon Cycle Model in Pool 5 of the Mississippi River
==========================================================================

Table of Contents
-----------------
* [Client Profile](#clientprofile)
* [Geological Background](#background)
* [Netlogo](#netlogo)
  * [Introduction](#netlogo_intro)
  * [Geological Objectives](#netlogo_objectives)
* [Original Model](#originalmodel)
  * [Purpose](#originalmodel_purpose)
  * [State Variables and Scales](#originalmodel_state)
  * [Process Overview and Scheduling](#originalmodel_overview)
  * [Initialization](#originalmodel_init)
  * [Input](#originalmodel_input)
* [Submodels](#submodels)
  * [Autotrophic Stocks](#submodels_auto)
  * [Hetotrophic Stocks](#submodels_heto)
  * [Detritus, Particulate Organic Carbon (POC), and Dissolved Organic Carbon (DOC)](#submodels_stocks)
  * [Incorporation of Hydraulic](#submodels_hydro)
* [Reflection of Original Model](#reflection_original)
* [Conclusion of Original Model](#conclusion_original)
* [Other Stakeholders](#other_stakeholders)
* [Solution - NetLogo to C Translations](#translation)
  * [Memory Concerns](#translation_memory)
  * [Transition to Python](#translation_python)
  * [Valgrind](#translation_valgrind)
* [Meetings with USGS](#meetings)
  * [Meeting One](#meetings_one)
  * [Meeting Two](#meetings_two)
  * [Meeting Three](#meetings_three)
  * [Meetings Four](#meetings_four)
  * [Meetings Five](#meetings_five)
  * [Meetings Six](#meetings_six)
  * [Meetings Seven](#meetings_seven)
* [Functional Requirements](#functional_req)
* [Non-Functional Requirements](#nonfunctional_req)
* [Assumptions](#assumptions)
* [Plan](#plan)
* [Team Experience](#experience)
* [Lessons Learned](#lessons)
* [End of Semester Status](#status)
* [Plans for Completion](#completion)

<a name="clientprofile"/>
Client Profile
--------------
Our group will be working with the United States Geological Survey (USGS) this year.  They are a 
scientific agency of the United States government.  The scientists in USGS study the landscape of the
United States, its natural resources, and the natural hazards that threaten it.  The group can be 
decomposed into four different disciplines, namely, biology, geography, geology and hydrology. The 
team we will be working with is concerned with hydraulic applications.  What we are helping USGS do is 
to simulate a spatially-explicit carbon cycle model for the Mississippi River.  We will be working with 
scientists and researchers across the United States.  The organization desires to simulate carbon flow 
because carbon is the most vital element for living beings.  All living organisms are constructed from
their compounds.  The carbon cycle is important in ecosystems because it moves carbon, a lifesustaining element, from the atmosphere and oceans into organisms and back again to the atmosphere 
and oceans.  If the balance between these latter two reservoirs is upset, serious consequences, such as 
global warming and climate disruption may result.  In addition, measuring the carbon in the river helps 
scientists study energy flow and ecological growth.  The goals USGS is trying to accomplish are two-fold.  
First, they want a generalized carbon model for a large river system.  Second, they want to link 
ecological models with hydraulic models.  Both together provide a generalized tool that can be applied 
on any river system, assuming hydraulics is available or can be estimated.  This enables comparative 
studies among the Great Rivers.  Additional applications made possible through this modeling process 
would be tests of when, where and why various river theories apply, an observation of how carbon 
stocks change with respect to management actions, indication whether a pool is a carbon source or sink 
and under what conditions, and indications of how nutrients influence certain patterns. Our group is 
responsible for speeding up their current code to generate these models.  Currently, it takes about 4 
days to simulate the respective data.  We need to get that down to less than an hour.  In addition, we
need to write a more effective graphical user interface to display this information.  As the semesters 
progress, we will also need to be flexible to allow our liaison to assign new functionalities for the model.


<a name="background"/>
Geological Background
---------------------
Understanding sources of productivity is crucial to watershed restoration and management of 
large rivers.  However, large rivers are dynamic ecosystems with complex organic carbon cycles that are 
difficult to understand.  Energy flow is driven not only by biotic and abiotic factors similar to those 
associated with terrestrial ecosystems, but also by hydraulic factors that move carbon within the river 
channel [Doi 2009; Power 2006].  Furthermore, both autotrophs within the river and allochthonous 
materials from outside the river serve as carbon sources [Doi 2009].  As a result, there is some debate as 
to what drives productivity in large rivers [Dettmers et al. 2001; Hoeinghaus et al. 2007; Power 2006; 
Power and Dietrich 2002]

Currently, three theories have been put forth to explain patterns of productivity in large rivers: 
the river continuum concept (RCC), the riverine productivity model (RPM), and the flood-pulse concept 
(FPC) [Dettmers et al. 2001].  The RCC states that the terrestrial input provides allochthonous carbon to 
headwater streams which is assimilated and transferred downstream with water flow [Vannote et al. 
1980].  The RPM claims that river productivity stems mainly from autochthonous carbon sources such as 
phytoplankton and macrophytes [Thorp and Delong 1994].  Finally, the FPC stresses that river 
productivity depends on terrestrial carbon inputs into river ecosystems via floodplain inundation [Junk 
et al. 1989].  Field data have provided support for each of these three theories across different river 
systems and within river systems across seasons [Hoeinghaus et al. 2007; Kohler 1995; Oliver and 
Merrick 2006; Sheldon and Thoms 2006; Henebry and Gorden 1989].  However, no one theory can be
generally applied across time or space, and in many cases, it remains unclear whether autochthonous or 
allochthonouscarbon sources are more important drivers in river productivity.

With so much spatial and temporal variability in energy sources within and between river 
systems, determining the most effective way to conserve or restore riparian populations can be difficult.  
Although more field data is necessary to better describe the mechanisms behind large river productivity, 
many studies are limited in their ability to accurately represent patterns of carbon flow within rivers.  
Field studies of consumer foraging behavior last only a few years and provide “snapshots” or river 
dynamics which may not represent prevailing trends across decades or long-term responses to natural 
and man-made disturbances.  In contrast, long-term monitoring programs may detect trends in 
populations and productivity over time, but the underlying causes of the trends may not be identified.

Spatially explicit modeling of large river ecosystems provides an opportunity for researchers to 
utilize both short- and long-term data in restoration and management plans and can guide future data 
collection.  Explanatory models can be used to determine if trophic linkages identified in short-term 
studies play a role in long-term trends detected by monitoring, and the construction of these models 
efficiently pinpoints gaps in current databases.  However, although modeling is an excellent tool for 
planning and directing long-term river productivity studies, the creation of the model itself can be timeconsuming and expensive.  Furthermore, while numerous studies have used modeling to examine river 
ecosystem dynamics such as productivity [Best and Boyd 2008; Best et al. 2001; Garbey at al. 2006; Herb 
and Stefan 2003; Park et al. 2003], many of these models are limited in their ability to incorporate the 
physical complexities of river ecosystems.  Basic river productivity models that build off of previouslyconstructed models and incorporate both ecological and hydraulic processes may fulfill the same goals 
and save time and money.

The extensive system of locks and dams created on the Mississippi River make it a particularly 
interesting site for the study of river productivity.  Human-induced changes in water depth, flood 
dynamics, and sediment accumulation, among other factors, may greatly influence productivity and 
alter successive patterns in river communities [Tyser et al. 2001].  However, information regarding the 
energy flow and productivity of the Mississippi is still incomplete.  Although the FPC has been shown to 
predict productivity in the Mississippi to some degree, its accuracy is limited to specific conditions 
[Gutreuter et al. 1999; Schramm and Eddleton 2006].  Ultimately, it is unclear whether the RCC, the 
ROM, the FPC, or a combination of the three best describes productivity in the Mississippi [Dettmers et 
al. 2001].  As a result, it is also unclear how human activities affect productivity in the Mississippi and 
which management plans are most appropriate.  In this study, the United States Geological Survey
began the development of an ecological model in NetLogo that can be used to better describe the 
sources of productivity in the Mississippi River ecosystem.

<a name="netlogo"/>
Netlogo
-------

<a name="netlogo_intro"/>
### Introduction

Understanding Netlogo was one of the major hurdles we had to overcome. Our client tasked us 
with translating their Netlogo code into C, which would require an in depth understanding of Netlogo. 
Until now, none of us had any idea what Netlogo was or how it was used. We spent our first few week 
figuring out how the syntax worked and discovered that it is actually built on top of Java. Netlogo is a 
modeling language that was designed for scientists and students who wanted to test their hypothesis 
and create a visual simulation of their data. While this is exactly what our client wanted to create,
Netlogo is not designed to model complex models, which made the running time of our clients model 
last four days.

While looking up the syntax of Netlogo, we discovered that it was actually create at 
Northwestern by Prof. Uri Wilensky. Netlogo is a world made up of Agents and there are four different 
types of Agents. The first type are known as Turtles. Turtles are mobile agents that move around the 
world. Netlogo allows the programmer to create these Turtles and give them instructions, such as how 
to move, what color they are, and how they interact with the world. The next type of Agent is called a 
Patch. Patches represent the grid layout of the Netlogo world. Its best to think of Patches as the floor of 
the world that Turtles can move on. Patches are not mobile like Turtles, but they can interact with any 
Turtle that is currently on it.

The next type of Agent is known as a Link. A Link is an Agent that connects two turtles together, 
essentially an edge in a graph. The idea behind a Link is to allow the programmer to build graphs, 
networks and aggregates. The last Agent that makes up the Netlogo world is called the Observer. The 
observer is not physically located in the Netlogo world, but its main job is to give commands. Its best to 
think of the Observer as the main function. These four Agents are what make up the Netlogo world and 
allows users to create detailed simulations of their experiments. 

<a name="netlogo_objectives"/>
### Geological Objectives

The main objective of this NetLogo model is to integrate river hydrology into an ecological 
model of river productivity.  By uniting ecological and hydraulic processes in the same model, the United 
States Geological Survey hopes to better represent the complexity of the Mississippi River carbon cycle 
and to pinpoint key sources of productivity within it.  If the United States Geological Survey’s model can 
accurately predict productivity in the Mississippi River, it will support the importance of the RPM.  If this 
is not the case, the RCC and/or the FPC may also play important roles and should be included in future 
models.

In designing this model, the United States Geological Survey hopes to provide a simple, widelyaccessible tool for researchers interested in river productivity.  Our goal is to design a model which can 
be easily applied to a variety of river ecosystems simply by swapping hydrology inputs.  Similarly, 
variations on this model may help guide management plans by incorporating changes in hydrology from 
locks and dams and including processes such as sedimentation.

<a name="originalmodel"/>
Original Model
--------------

<a name="originalmodel_purpose"/>
### Purpose

The goal of this model is to simulate carbon flow through Pool 5 of the Upper Mississippi River 
(a 24-km section extending from Navigation Dam No.4 at Alma, Wisconsin downstream to Navigation 
Dam No. 5 near Whitman, Minnesota; Fig. 1) by combining ecological and hydrological processes.  A 
basic carbon cycle is modeled using simple food web interactions while hydrological data from the U.S. 
Army Corps of Engineers is used to incorporate physical characteristics of Pool 5 which describe the 
longitudinal movement of carbon.

<a name="originalmodel_state"/>
### State Variables and Scales

GIS maps of depth, velocity and flow direction in Pool 5 were translated into grayscale and 
divided into patches of 30x30 m, and the carbon cycle was modeled within each patch.  The carbon cycle 
simulates the transfer of labile carbon between trophic levels within each patch and was created based 
mainly upon the theories of the RPM.  It includes eleven basic carbon states: dissolved organic carbon 
(DOC), particulate organic carbon (POC), detritus, phytoplankton, macrophytes, periphyton, herbivores, 
decomposers in the water column, decomposers in the sediment, consumers in the water column, and 
consumers in the sediments.  The abundance of each of these stocks was described in grams of carbon 
per patch throughout the simulation.

Several studies have demonstrated that large river ecosystems are not nutrient limited [Allan 
and Castillo 2007; Francoeur 2001], and this model reflects that.  Primary productivity is based on 
temperature, light, and water velocity, and transfer of carbon from one state to another is based on 
biomass-dependent interactions between states.  The movement of labile carbon units between patches 
is modeled based on the hydrology data contained within each GIS map.  The time step for the model is 
set at one hour, in agreement with many of the measurements reported for river processes in the 
literature and with the hydrology data.

<a name="originalmodel_overview"/>
### Process Overview and Scheduling

Within each patch during each time step, relevant carbon states first consume carbon from 
other states.  Then, relevant carbon states are consumed by other states based on the initial values for 
biomass.  Finally, each state is assigned a new biomass value that takes growth and prediction into 
account, and the hydrologic component moves carbon among patches.  Interactions between states are 
described below.

<a name="Initialization"/>
### Initialization

All carbon stocks small enough to be carried in the current (phytoplankton, water column 
decomposers, DOC, POC) were set at 10 grams of carbon per patch to start the model.  These stocks also 
received influxes of 10 grams of carbon in each of the patches bordering the upstream end of Pool 5 
during each time step.  All other stocks were set at 1 gram of carbon per cell to start the model and 
were not subject to influxes during the simulation.

<a name="originalmodel_input"/>
### Input

This model is based on GIS maps of water depth, velocity, and flow direction in Pool 5 of the 
Mississippi River, which were created from a 2-dimensional hydraulic model developed by the U.S. Army 
Corps of Engineers.  The hydraulic model simulated a range of discharges between 10,000 and 127,000 
cfs.  Hydraulic data was associated with a specific range of discharge values.  Hydraulic data was 
available for 6 different discharge ranges so that an annual hydrograph can be simulated.  Maps of 
depth and velocity were divided into patches and set in gray-scale so that an average depth and velocity 
could be calculated for each patch.  Flow vectors were split into units that move in the x-direction and ydirection.  SUNY-modeled global horizontal photosynthetic active radiation was input into the model at 
an hourly time step.  Daily average surface water temperature was also incorporated into the model 
from data collected by the U.S. Army Corps of Engineers.

<a name="submodels"/>
Submodels
---------

<a name="submodels_auto"/>
### Autotrophic Stocks

The three autotrophs considered for this model are: macrophytes, phytoplankton, and 
periphyton.  However, the United States Geological Survey modeled only macrophytes and 
phytoplankton and set periphyton as 10% of the macrophyte concentration in each patch.  Macrophytes 
were only modeled in patches where water velocity was less than 1ms^-1
since higher velocities result in complete scouring.

We modeled all autotrophic stocks using the general equation:

1. dXj/dt = Prodj - Physj - Predj

where the biomass of stock j equals the difference between primary production and physiological and 
predatory losses.

Primary production for macrophytes is described using the maximum gross photosynthesis 
equation (Kaj Sand-Jensen, Chambers et al. 1991):

2. Prodj = 0.08\*Xj\*(L / (L + 10))\*Q10\*(K – Xj) / K

where Xj is equal to the macrophyte biomass, Q10 is the temperature-dependent coefficient, 
K is the halfsaturation constant, and L is the amount of light that reaches the macrophytes depending on the 
amount of surface light, depth , and total suspended solids.  Primary production for phytoplankton was 
modeled using a similar formula (Huisman and Weissing 1994).

Physiological losses of an autotrophic stock were modeled as:

3. Physj = (µj + ŋj + σj) \* Xj

where µj is the specific physiological mortality rate, ŋj is carbon lost to excretion, and σj is carbon lost to 
respiration (Garbey et al. 2006).  Carbon lost via physiological mortality is transferred to the detritus, 
POC and DOC stocks, and carbon lost via excretion enters the DOC stock.  Carbon lost to respiration by a 
stock is removed from the system.  In this version of the model, the phytoplankton stock, and not the 
macrophyte stock, loses carbon to herbivores.  These losses are described in the equations for 
heterotrophic stocks.

<a name="submodels_heto"/>
### Hetotrophic Stocks

Heterotrophic stocks included herbivores, consumers, and decomposers.  We modeled all of 
these stocks using the general equations developed by Wiegert (1975, 1979).  Biomass of a stock at time 
t + 1 is determined by the formula:

4. dXj/dt = Cj \* (1 – εj) – Physj - Predj

where the biomass of stock j equals the difference between consumption corrected for egestion (εj) and 
physiological and predatory losses.  Egested material enters the detrital food web as POC, much of 
which may be converted to detritus depending on the hydrological conditions of the cell.  Consumption 
by stock j is determined by the summation of consumption of each available prey type (m) of predator j, 
and is given by the following formula:

5. Cj = ∑ (πij \* τj \* Xj \* fij \* fjj (sum from i = 1 to j)

where πij is the preference of stock j for prey stock i, τj is the maximum rate of consumption by predator 
stock j, and Xj is the biomass of predator stock j.  The functional response of predator stocks is 
determined by fij and fjj, represent prey and space limitation functions. Population growth rates 
can be limited by both prey availability and intra-specific interference at high population densities. Both 
fij and fjj produces values between 0 and 1. At high prey densities, predators will not be resource-limited 
and thus feed at the maximum rate (τj); however, below a prey density threshold (Aij), consumption will 
be reduced and will eventually fall to zero when prey densities are below a refuge level (Gij).  For 
simplicity the United States Geological Survey assumesfij decreases linearly between Aij and Gij.  Space 
limitation is determined similarly except values of Ajj and Gjj relate to predator density.

If a predator stock feeds only on one prey type, then πij is set to one.  However when a predator 
stock feeds on multiple stocks πij is a function of innate prey preference (Pij) for specific stocks and the 
biomass of those stocks in the cell.

6. πij = (Pij \* fij)/∑ (Pij \* fij)  (∑ is sum from i =1 to m)

Stock-specific values for Aij, Ajj, Gij, Gjj, and Pij were adapted from Pace et al. (1984) and are 
listed in Tables 1 & 2, however these values are likely to be system-specific and thus should be 
calibrated with independent data from the system to be modeled.

Physiological losses of a heterotrophic stock were modeled as above for autotrophic stocks:

7. Physj = (µj + ηj + σj) \* Xj

Carbon lost to predation is determined by the summation of losses to each predator stock (k).

8. Predj = ∑ (πjk * τk * Xk * fjk * fkk)  (∑ is sum from k=1 to n)

Table1:

Stock-specific values for heterotroph formulas, where πij is the preference of stock j for prey stock i, 
Aij is the maximum prey density threshold below which capture efficiency is decreased, and Gij is the 
prey refuge at which capture efficiency is equal to 0.

<table>
<tr>
  <td> Predator stock </td> 
  <td> Prey stock </td>
  <td> πij </td>
  <td> Aij </td>
  <td> Gij </td>
</tr>
<tr>
  <td> Herbivore </td>
  <td> Phytoplankton </td>
  <td> 0.7 </td>
  <td> 20 </td>
  <td> 0.01 </td>
</tr>
<tr>
  <td> Herbivore </td>
  <td> Water decomposers </td>
  <td> 0.15 </td>
  <td> 3 </td>
  <td> 0.01 </td>
</tr>
<tr>
  <td> Water decomposer </td>
  <td> POC </td>
  <td> 0.5 </td>
  <td> 30 </td>
  <td> 0.05 </td>
</tr>
<tr>
  <td> Water decomposer </td> 
  <td> DOC  </td> 
  <td> 0.05  </td> 
  <td> 30 </td>
  <td> 0.05 </td>
</tr>
<tr>
  <td>Sediment decomposer </td> 
  <td> Detritus  </td>
  <td> 1 </td>
  <td> 0.6 </td>
  <td> 0.005</td>
</tr>
<tr>
  <td> Periphyton </td>
  <td> DOC  </td> 
  <td> 0.5 </td>
  <td> 30 </td>
  <td> 0.05 </td>
</tr>
<tr>
  <td> Periphyton </td> 
  <td> POC </td> 
  <td> 0.5  </td> 
  <td> 30 </td> 
  <td> 0.05 </td>
</tr>
<tr>
  <td> Sediment consumer </td>
  <td> Sediment decomposer </td> 
  <td> 0.5 </td>
  <td>3</td>
  <td>0.02</td>
</tr>
<tr>
  <td>Sediment consumer </td>
  <td>Detritus</td>
  <td>0.1</td>
  <td>3.5</td>
  <td>0.02</td>
</tr>
<tr>
  <td>Sediment consumer </td> 
  <td> Periphyton </td> 
  <td>0.4</td>
  <td>2</td>
  <td>0.02</td>
</tr>
<tr>
  <td> Consumer </td> 
  <td> Herbivore </td> 
  <td> 0.7</td>
  <td>3.5</td>
  <td> 0.025 </td>
</tr>
<tr>
  <td> Consumer </td>
  <td> Sediment consumer </td>
  <td>0.3 </td>
  <td>4</td>
  <td>0.04 </td>
</tr>
</table>


<a name="submodels_hydro"/>
### Incorporation of Hydraulic

<a name="reflection_original"/>
Reflection of Original Model
----------------------------

<a name="conclusion_original"/>
Conclusion of Original Model
----------------------------

<a name="other_stakeholders"/>
Other Stakeholders
------------------

<a name="translation"/>
Solution - NetLogo to C Translations
------------------------------------

<a name="translation_memory"/>
### Memory Concerns

<a name="translation_python"/>
### Transition to Python

<a name="translation_valgrind"/>
### Valgrind

<a name="meetings"/>
Meetings with USGS
------------------

<a name="meetings_one"/>
### Meeting One

<a name="meetings_two"/>
### Meeting Two

<a name="meetings_three"/>
### Meeting Three

<a name="meetings_four"/>
### Meeting Four

<a name="meetings_five"/>
### Meeting Five

<a name="meetings_six"/>
### Meeting Six

<a name="meetings_seven"/>
### Meeting Seven

<a name="functional_req"/>
Functional Requirements
-----------------------

<a name="nonfunctional_req"/>
Non-Functional Requirements
---------------------------

<a name="assumptions"/>
Assumptions
-----------

<a name="plan"/>
Plan
----

<a name="experience"/>
Team Experience
---------------

<a name="lessons"/>
Lessons Learned
---------------

<a name="status"/>
End of Semester Status
----------------------

<a name="completion"/>
Plans for Completion
--------------------
