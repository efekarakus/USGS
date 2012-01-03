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

![Figure 1: Map of pool 5 on the Mississippi River](/Users/efekarakus/USGS/images/Figure1.png "Figure 1: Map of pool 5 on the Mississippi River")

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

Table 2:

Stock-specific values for heterotroph formulas, where τ is the maximum rate of consumption by 
predator, where τ is the maximum rate of consumption by the predator stock, P is the innate prey 
preference i of predator j, ηj is carbon lost to excretion, μ is the specific physiological mortality rate, ε 
is the egestion rate, Ajj  is the minimum predator density at which prey capture efficiency is decreased, 
and Gjj is the maximum predator density at which prey capture efficiency is set to 0.

<table>
<tr>
  <td>Stock</td>
  <td>τ</td>
  <td>Ρij</td>
  <td>η</td>
  <td>μ</td>
  <td>ε</td>
  <td>Ajj</td>
  <td>Gjj</td>
</tr>
<tr>
  <td> Herbivore </td>
  <td> 0.04166667 </td>
  <td> 0.003333 </td> 
  <td> 0.016666667 </td>
  <td> 0.000416667 </td>
  <td> 0.2 </td> 
  <td> 2.4 </td>
  <td >108 </td>
</tr>
<tr>
  <td> Water Decomposer </td>
  <td> 0.26083333</td>
  <td>0.025</td>
  <td>0.007208333</td>
  <td>0.002083333</td>
  <td>0</td> 
  <td>1.2</td> 
  <td>20</td>
</tr>
<tr>
  <td>Sediment Decomposer</td>
  <td> 0.26083333 </td> 
  <td>0.025</td>
  <td>0.007208333</td>
  <td>0.002083333</td>
  <td>0</td>
  <td>0.2</td>
  <td>120 </td>
</tr>
<tr>
  <td>Sediment consumer </td>
  <td> 0.02291667 </td> 
  <td>0.003333</td>
  <td>0.000416667</td>
  <td>0.000416667 </td>
  <td>0.35</td>
  <td>2</td>
  <td>20</td>
</tr>
<tr>
  <td> Consumer </td>
  <td>0.005125 </td>
  <td>0.000521</td>
  <td>8.33333E-05</td> 
  <td>8.33333E-05</td>
  <td>0.2</td>
  <td>0.65</td> 
  <td>6.5</td>
</tr>
</table>

<a name="submodels_stocks"/>
### Detritus, Particulate Organic Carbon (POC), and Dissolved Organic Carbon (DOC)

Both the detritus and particulate organic carbon (POC) carbon stocks acquire carbon from dead 
organic matter which is > 1μm in size.  However, POC refers to matter in the water column and detritus 
refers to matter in the sediments.  For this model, senesced material was deemed detritus if particle size 
was > 10μm (Wetzel 2001). The percent of senesced material transferred to the detritus stock varied 
according to its source (Table 3). All egested carbon contributes to detritus (Table 3).  Carbon lost to POC 
from the detritus category is described as: 

9. Transj=  Xj \* (2.5 log ((v / 40.0) + .0001) + 0.5)

where v is equal to the water velocity, and higher velocities result in a greater proportion of organic 
matter in the water column.  Similarly, the transfer of carbon from the POC stock to the detritus stock is 
described as the product of POC biomass and (1 – Transj).  When velocity is equal to zero, 90% of the 
carbon in the POC stock settles out and becomes detritus.

All senesced carbon in the model that is not assigned to the detritus stock is assigned to the POC 
stock, with the exception of a small percentage, which is assigned to the dissolved organic carbon (DOC) 
stock (Table 3). Carbon is also transferred to POC from DOC at a rate of 1% due to flocculation.

The DOC carbon stock acquires carbon from dead or excreted objects that measure < 1 µm in 
size (Wetzel 2001).  In this model, in addition to some senesced carbon, all carbon excreted or released 
as exudates contributes to DOC (Wetzel 1975)(Table 3).

Table 3:

Percent of senesced, excreted and egested carbon assigned to new carbon states.

<table>
<tr>
  <td>Carbon Stock </td> 
  <td>Detritus </td> 
  <td>DOC</td> 
  <td>POC</td>
</tr>
<tr>
  <td> Macrophytes </td> 
  <td>100</td>
  <td>0</td>
  <td>0 </td>
</tr>
<tr>
  <td> Phytoplankton </td> 
  <td>90</td>
  <td>1</td>
  <td> 9 </td>
</tr>
<tr>
  <td> Herbivore </td>
  <td>30</td>
  <td>0</td>
  <td>70 </td>
</tr>
<tr>
  <td>Periphyton</td>
  <td>70</td>
  <td>0</td>
  <td>30</td>
</tr>
<tr>  
  <td>Water Column Consumer</td>
  <td>100</td>
  <td>0</td>
  <td>0</td>
</tr>
<tr>
  <td> Sediment Consumer </td>
  <td>100</td>
  <td>0</td>
  <td>0 </td>
</tr>
<tr>
  <td> Water Column Decomposer</td>
  <td>30</td>
  <td>0</td> 
  <td>70</td>
</tr>
<tr>
  <td>Sediment Decomposer</td>
  <td>100</td>
  <td>0</td>
  <td>0</td>
</tr>
<tr>
  <td> Excretion </td>
  <td>0</td>
  <td>100</td>
  <td>0</td>
</tr>
<tr>
  <td> Macrophyte Exudation </td>
  <td>0</td>
  <td>4</td>
  <td>0 </td>
</tr>
<tr>
  <td> Egestion</td>
  <td>100</td>
  <td>0 </td>
  <td>0 </td>
</tr>
</table>

<a name="submodels_hydro"/>
### Incorporation of Hydraulic

Mobile carbon from each cell was modeled to flow at the same velocity as water, and the 
amount of carbon transferred between cells was calculated using functions based on the speed and 
direction of water flow in each cell (Fig. 2).  Since most fish actively move to find food, consumers in the 
water column in this model were not affected by hydraulics.

![Figure 2: Hydrological component of model](/Users/efekarakus/USGS/images/Figure2.png "Figure 2: Hydrological component of model")

<a name="reflection_original"/>
Reflection of Original Model
----------------------------

Despite extensive research, sources of productivity in large rivers have been hard to pinpoint. 
Spatially-explicit ecological modeling offers the opportunity to simulate river food webs and hydraulic 
processes to predict which biotic and abiotic factors play important roles in dictating river productivity. 
The system of dams and levees in the Mississippi River makes it an especially complex system for 
investigating productivity since these human activities have greatly influenced hydrology. 

Using pre-existing models and data, the United States Geological Surveywas able to successfully 
create a spatially-explicit carbon-based model of productivity for Pool 5 of the Upper Mississippi 
River.Our model suggests that the hydrology of the Mississippi River directly affects its food web. 
Because primary producers rely on light for carbon fixation, the effect of depth on light availability was 
important to their success in this simulation. Furthermore, in shallow areas with the lowest velocities 
and highest light availability, phytoplankton appeared to out-compete macrophytes. Since macrophytes 
rely on their root system to anchor them and obtain nutrients, they were also negatively affected by 
higher velocities. Above velocities of 1 m/s, macrophytes were completely scoured, inhibiting their 
survival regardless of light conditions. Therefore, macrophyte distribution in Pool 5 appears to be limited 
by a number of biotic and abiotic factors.

Because consumers rely on producers as a carbon resource, the United States Geological Survey
would expect consumer carbon acquisition to depend heavily on producer carbon acquisition within this 
system.The model validates this expectation since consumers were able to acquire carbon in any 
location in the river that contained producers. Additionally, the model predicts that Pool 5 consumers 
do not run out of prey in throughout the simulation.

Because it capitalizes on hydraulic models that engineers are likely to employ in river 
development and restoration projects as well as previously-collected ecological data, the United States
Geological Survey’s modeling approach is a powerful, cost-effective tool. Model processes are simplified 
to reduce costs and development time, and the number of inputs and outputs are limited to facilitate 
analyses. Details of the model processes can be easily modified depending on the user’s needs since 
freeware like NetLogo runs on any computer and facilitates development and use by a large group of 
users. Also, by using different hydraulic input maps, users can easily shift the system being simulated, 
and simulations can be run for shorter or longer time periods depending on the time step used. Finally, a 
simple model such as this can provide inputs to more complex individual- or population-based models.

Despite the many advantages of a simplified model, some limitations must be considered when 
evaluating this model’s accuracy. For example, in the United States Geological Survey’s simulation of 
carbon flow, the hydraulic model does not account for waves and currents that are generated by outside 
forces such as wind or recreational boats (Bhowmik et al. 1982; Sparks 1984).  Carbon removal from the 
river by external consumers such as bald eagles is not included in the model, nor is the exchange of 
carbon dioxide between the river and the atmosphere. Although the absence of details such as these 
may not dramatically affect the broad patterns simulated by this model, users may wish to include them 
in future versions of the model to improve the simulation of river dynamics.

Improved, validated versions of the United States Geological Survey’s spatially-explicit river 
productivity model may be useful for predicting impacts of major natural and man-made disturbances 
and alterations, including floods, droughts, levees, and dams. Such information could be crucial in 
preparing for, and perhaps mitigating, the effects of such disturbances. Impacts of restoration measures 
such as reconnection of rivers and their floodplains or naturalization of water regimes could also be 
evaluated using these types of models, so that choices could be made among alternative restoration 
measures. Results may also help environmental agencies justify more detailed modeling or data-gathering
prior to river development.  The flexibility of the United States Geological Survey’s modeling 
approach allows application to a wide variety of systems and questions.

<a name="conclusion_original"/>
Conclusion of Original Model
----------------------------

Mechanisms behind productivity in large river ecosystems are difficult to pinpoint due to the 
large degree of spatial and temporal variability involved. Although three theories explaining productivity 
in large rivers are commonly discussed, none provides a generalized mechanism that can be used across 
all rivers and all seasons. Using NetLogo, the United States Geological Surveyhas developed a spatiallyexplicit carbon model that aims to simulate patterns of productivity in Pool 5 of the Mississippi River by 
incorporating both ecological and hydraulic components of the river. After further development and 
validation, the model will be a simple and effective tool for exploring river productivity for researchers 
with a variety of backgrounds, studying a variety of ecosystems.It is the United States Geological 
Survey’s hope that this and future versions of spatially-explicit river productivity models can become 
easily accessible to those studying river productivity and can improve research and management of 
large river ecosystems.

<a name="other_stakeholders"/>
Other Stakeholders
------------------

Aside from our clients currently employed by the USGS, the other member of our group 
invested in the project is Keven Freeney, a PH.D biology student writing his research paper on the results 
of our model. His studies will reflect the information displayed on the finished model as well as 
modifications to any equations present in the code.

<a name="translation"/>
Solution - NetLogo to C Translations
------------------------------------

<a name="translation_memory"/>
### Memory Concerns

Before we began the process of translating the code for the carbon model into a new language, 
we wanted to pinpoint exactly what was going eating up so much time in the code itself. As stated 
earlier, the Netlogo language is built around Java and, as a result, slows down via garbage collection 
whenever large amounts of memory are allocated and referenced. This problem was immediately 
evident upon looking at the source code. Around the ballpark of one hundred variables are declared 
inside a patch structure at the top of the code. We initially tried reducing this memory footprint 
assigning types to each of the variables that would closely bind the possible range of values. After all, 
typing is done dynamically in Netlogo, so each variable used a great deal more memory storing these 
values than what was necessary. For example, say a variable was used as a Boolean in one of the 
patches, taking on values of either zero or one.  Since Netlogo dynamically types variables, this would be 
initially set to an integer which is represented with thirty-two bits or four bytes on a modern thirty-two 
bit architecture. It would only take a single bit, zero or one, to represent this value, resulting in thirtyone unused bits of memory for every patch. Booleans are not defined in C, but this can be implemented 
as a character to use the same amount of memory.

At first, this may seem like a trivial amount. After all, memory is one of the cheapest parts of a 
computer nowadays, making a few dozen bits seem almost microscopic in scale. It is easy to see, 
however, how this problem builds up into something more serious when we take a look at the big 
picture. Thirty-one bits is insignificant for a single patch, but this number begins to grow once we 
consider that one patch takes up only a single pixel worth of data. The size of the image is dependent on 
the hydraulic data given as input, but these pictures tend to be around the order of four hundred by
twelve hundred pixels. Roughly yielding half a million patches, this means that the simple change of 
declaring an integer as a character saves around two megabytes of memory allocated and managed by a 
garbage collector at run time. 

Furthermore, this results from changing a single variable. There are around one hundred 
variables within a single patch all with types that well exceed their possible range of values. 
Unfortunately, a great deal of documentation is currently missing from the Netlogo code detailing the 
possible range of values for many of the variables. It is our hope that we will receive further 
documentation from our USGS liaison precisely defining these values in order to minimize the memory 
used by each patch.

<a name="translation_python"/>
### Transition to Python

This topic is noteworthy as it helps introduce the main reasons behind why our group decided to 
translate Netlogo into two languages instead of one. One of the first ideas to pop up in our discussion 
was that the entire code could be translated very quickly into Python and thus allowed us to focus on 
algorithmic instead of system level optimizations, which likely have greater potential for speedup.  
Nevertheless, Netlogo’s similarity to Python is one of the reasons this holds true. Both languages use 
dynamic typing, meaning that those megabytes of wasted memory would still be lost in a translation 
from Netlogo to Python. Furthermore, both languages have garbage collection running in the 
background, so this extra memory would slow down the runtime by periodically performing unnecessary 
memory checks.

Despite these undesirable characteristics, Python is not altogether useless for our purposes. As 
mentioned before, the main appealing aspect of the Python language is the speed at which an 
application can be developed. This means that the ease in which code is written will allow us to quickly
make changes to an application despite any unforeseen complexities.  In fact, we anticipate with high 
confidence that a great deal of changes will be needed in terms of the program’s GUI over the course of 
next semester. The Netlogo GUI itself contains several sliders and switches for many of the variables 
involved with sensitivity analysis for the carbon flow model. Yet deciding on what variables are present 
within the GUI is no simple task. In fact, one of our liaisons, Kevin Freeney, is writing his P.H.D research 
paper about the topic concerning which variables would have the greatest impact on our current model. 
This effort is ongoing, and thus it is unclear as to what information will need to be present on the 
screen. Therefore, Python excels in this task by allowing us to change the GUI as needed.

Unfortunately, we ran into a great deal of trouble in the initial stages of our development 
process. In order to call a compiled C binary from python, the main.h file has to include Python.h. This 
file is not included in the standard download for Python, but is instead packaged with the Python 
development libraries. When we tried downloading these libraries on a Windows and Linux 
environment, we would continuously receive errors stating that header files were missing for Python.h. 
We tried consulting an administrator for the Senior Project class to help us with this problem, but 
eventually had to give up and try a new approach after several weeks of frustrated effort. Eventually, we 
tried to set up these development libraries on a Macintosh operating system and had success right 
away. To this day, we still have no idea why we could not find a complete package download for the 
Python.h development libraries for Windows and Linux. but can still develop the program with the 
Macintosh environment. Although the target operating system for this program is Windows, which is 
the main operating system for government computers, we will be writing the code without using any 
operating system dependent functionality.

To obtain the optimization mentioned earlier, however, we chose to rewrite the model section 
of our MVC formatted code in C. MVC (Model View Controller) is a style or writing code that splits a 
program into three sections. The view is responsible for displaying the GUI while the controller handles 
actions performed by the GUI, and the model takes care of any computation that goes on in the 
background. As the view and controller would have to change frequently, we chose to rewrite those 
sections in Python. It was obvious then to use C for the model as this is the section of the code that 
holds the most potential for system level optimizations. This separation of the code into modular parts is 
worth mentioning as the original Netlogo code was all written in a single file where the code for the GUI 
was maintained in the background.

In C, the types of variables must be declared at compile time. Additionally, there is no garbage 
collector running in the background. These two characteristics make it so less memory is used and 
instructions can execute faster, but at the risk of leaking memory. A memory leak occurs whenever a 
program allocates memory but does not free this memory at the end of the program’s execution. This is 
a more significant problem for programs that operate over long periods of time such as a game or web 
application as this leaked memory will eventually slow down an application’s performance. Our model is 
less susceptible to this problem as it will be run a set amount of times to help geological managers for 
the Mississippi River predict changes from the river for a given data set. It is possible that these 
conditions would require the code to be ran multiple times over the course of a day, but it is more likely 
that it will be ran once and then forgotten about while its results are being interpreted. Nevertheless, 
leaking memory is an unacceptable flaw and our group has taken it upon ourselves to ensure memory is 
allocated properly. Otherwise, the system level advantages offered by C would unwind into a 
complicated mess of poorly functional code. 

<a name="translation_valgrind"/>
### Valgrind

To ensure that leaks are not present in the final product, we will be using a program called 
Valgrind. This program works by running in the background as our code runs. Similar to a garbage 
collector, it will keep track of when memory is allocated and check if every byte is freed at the end of 
execution. In the case where leaks are found, however, Valgrind will inform us of the line where the 
memory was allocated to help us pinpoint the leak. Additionally, it will also keep track of any errors that 
occur at runtime. Mistakes such as using uninitialized values and using memory past a specified 
allocation limit will be detected by Valgrind, and thus help us spot any bugs that have arisen during 
development.

Yet it is worth noting that using Valgrind for our program has a minor complication. The way the 
code is currently executing is by compiling our C code into an executable binary and then calling that 
binary with our python code. In other words, we are not calling the binary directly from the command 
line. Thus, to use Valgrind to test our code, we will have to make a dummy main function that is not a 
part the total application. This will allow us to compile and run the code as an independent C program, 
and thus ensure that the model is working as intended.

Before moving on to discuss the interface for our application in greater detail, it is important to 
note how the translation of Netlogo to C ties in with our overall goals. After all, the main goal of this 
effort is to speed up the carbon model so that it will complete in less than an hour instead of four days. 
Extensive optimizations have already been applied to the code to reach this goal through Netlogo itself, 
so it become evident that a more modern language was needed. By translating the model to C, we are 
able to take advantage of several low level optimizations. Since the input data for this carbon model is 
so large, perhaps the greatest boost in memory and performance comes from assigning specific types to 
each of the variables. As discussed earlier, this is a result of limiting the size of the hundreds variables to 
a specific range in each of the approximately million patches. Furthermore, any behind-the-scenes 
computation is eliminated through manual garbage collection. To ensure that our final product is leak 
free, we will use Valgrind to check for unfreed memory and errors. it will not be possible to apply 
Valgrind directly to the code as it stands now, so we will substitute in a dummy main function that 
mimics the real function used by the python code. This will allow Valgrind to run properly while ensuring 
that the dummy function tested runs the exact same code as the real main function called from the 
Python code.

<a name="meetings"/>
Meetings with USGS
------------------

The following is a detailed report of the notes taken at each of the meetings with the members 
of USGS throughout the course of the project.

<a name="meetings_one"/>
### Meeting One

Administrative Updates: We confirmed that most of the technical questions should be directed toward Bart Rossman 
since neither Kevin nor Bruce have a deep understanding of the code.

Technical Updates: The graphical user interface should be split into two different views: Managerial and 
scientific.  This is to allow a different perspective of the data for the potential user.  Both options 
should be available to use.  Consider having a tab at the top of the GUI.

Managerial View: A more summarized version of the GUI.  It will contain less interactive 
components (variables) for the user to change.  It will be designed for managers or individuals 
without a deep understanding of the scientific reasoning behind the model.  It should be 
designed to allow a quick decision making process, yet still provide sufficient detail of the 
model.  (Details of this view will follow in further meetings.  Kevin and Bill need to discuss which 
components are important.)

Scientific View: A more detailed version of the GUI (drilled down).  It will contain more 
interactive components (variables) for the user to change.  It will be designed for scientists and 
field researchers with a deep understanding of the scientific reasoning behind the model. 
(Although the current model reflects a prototype of the scientific model, further details of this 
view will follow.  Perhaps we can eliminate some variables.  Kevin and Bill need to discuss which 
components are important.)

<a name="meetings_two"/>
### Meeting Two

We met with Aloah and Bart to answer selected questions about their NetLogo code.
We walked through the code to better understand how to break up the code and test it.
We clarified NetLogo terminology( Turtles and Patches).

Aloah and Bart were the people who wrote the USGS NetLogo code used to model the carbon flow in 
the Mississippi river. Aloah and Bart moved to Arizona during the summer so we had to set up a remote 
conference with them. Unfortunately, Bart was unavailable for the meeting so we had Aloah walk us 
through the parts of the code she wrote.
A majority of the meeting was having Aloah walk us through the code she wrote and as we went along 
we had a few questions that she answered.

First Question: In the NetLogo code, you mentioned that the variable ticks represents an emulated 
second within the running model of the carbon flow. Does this mean the user would be interested in the 
model as it is being built or just the end result of the simulation?

Answer: Just the end result - NetLogo is built around an observer, so that is
why ticks is used as it is, but for this model NetLogo is actually a
poor fit (hence our desire to have it rewritten). But on tick is not
one second, it is one hour (I believe, I don't have the model here at
work). Within that main routine, we loop through moving the carbon
stocks from cell to cell 3600 times (60 seconds \* 60 minutes), but
then try to speed it up two ways:

1.max-timestep figures the max vector velocity of all cells and
determines how many seconds we can aggregate and compute in one loop
step. So if a cell is 30m on a side and the max vector speed (x or y)
is 6 m/s, then we can process 5 seconds per step versus 1 second per
step without 'pushing carbon' beyond the neighboring cell. You lose a
little precision with this, but it seems negligible in the tests we
performed.

2.The second method that we tried when we increase the number of
cells, we calculate the max-vector of each cell and then compare that
to max-timestep to see if a particular cell can skip more steps...cell
that reside in the main channel of the river may have a velocity of 20
m/s when there is a lot of water, but the shallow areas remain slow,
under 2 m/s. So we 'push carbon' on the shallow cells every 4th
timestep, instead of every single timestep...another loss of
precision.

Second Question: We notice that a majority of the functions use something called ask patches with 
[depth > 0]. What exactly is a patch and what is this call doing?

Answer:Patches are part of the NetLogoworld, that is think of them as the tiles in the display that change 
color. Each patch will have a set a variables that will be used to calculate the color it should 
display on the grid. The ask patches function will go through each patch and select each one 
with depth that is greater than zero. (So each patch is like treated like an object that represents 
a pixel color)

Third Question: While going through your code, we noticed that there was no use of Turtles, why is 
that?

Answer:They had no need for turtles since they only needed to represent the carbon flow using patches. 
As he said before, NetLogo was a poor choice for this project.

Fourth Question: Since the code is broken up into several functions, we would like to test our C code 
and compare it to the NetLogo output, is there any way you could create a data set that can be tested 
without having to run for four days?

Answer:They weren't sure how to break up the data so it would run on NetLogo in order for it to be 
completed, but they said they would look into it

Fifth Question: Any editor that we can use to for NetLogo in order to highlight syntax?

Answer: When they wrote the program, they used Microsoft word as an editor, which were hoping is not 
the case.

<a name="meetings_three"/>
### Meeting Three

During this meeting, Kevin and Bruce were both present and we showed them the current code 
breakdown of their NetLogo program. This was the first meeting after we talked to Aloah, one of 
the writers of the NetLogo code. We explained to them our plan for tackling this problem.

C for translating the program: After reviewing the NetLogo code with Aloah, we explained to Bruce and 
Kevin that C would work since the NetLogo code wasn't very complicated as its mostly loops and if 
statements, but it has many computations for each patch, which means it will run slow in NetLogo.
cython for the GUI: We explained that in order to provide a presentable user interface, we would use 
cython that would run C executables.
We then had some questions for Kevin and Bruce:

Question: The current NetLogo code updates every single patch and displays on the GUI. Bart told us 
that this was not necessary, only the last output is important. What do you think we should do for the 
GUI? Should we update every pixel or display only the last result?

Answer: Instead of displaying every days output on the screen, we will display the output every month 
so that the users will still be able to see the effects overtime without the overhead of displaying it every 
day.

Question: USGS managers from Wisconsin will be coming on campus, when is that going to happen and 
should we meet with them?

Answer: The managers are going to come early November, and we will meet with them to have a better 
understanding of the Manager side of the GUI.

1.The GUI needs to have two different perspectives: one of them will be for managers (which 
won't have as many calibration tools as the scientists), the other will be for scientists (requires 
all the tools provided in the current NetLogo GUI)
2.Question: What are the parameters that the managers want us to display on the GUI?

Update: Later on, once we are done with the implementation of the necessary features for the GUI. 
Bruce introduced us with another parameter that might be needed for the scientists:
The calibration idea: measurable biological data, biologists have a data map of different 
microphytes. For each cell that is on the data map we need to figure out how many there are,
and color the different pixels according to the number of microphytes available in that region. 
We will need to ask calibration details to Kevin once the time comes.

Display: We showed the confluence webpage that we created, current code layout that is on GitHub 
and future progress on the timeline.

<a name="meetings_four"/>
### Meeting Four

During this meeting, we explained to Kevin that we were preparing presentations that we 
needed to give during class and we decided to post them online in case anyone wanted to view 
them.

We also moved our information onto EfeKarakus's webpage so that Bruce, Bart, and Aloah would have 
access to it. We also told Kevin that almost none of the NetLogo codes functions had any explanation of what the 
method did. He then told us he would go through the code and provide an explanation for each function 
in order to help us understand what was going on. We then decided to meet every other week.

<a name="meetings_five"/>
### Meeting Five

Showed the code that was uploaded on GitHub -- Python GUI and small execution of it. Also 
discussed the upcoming managerial meeting.

Which buttons on the GUI are necessary and in which formats do you want us to have it?
Are the values that are currently listed in the UI too small or too large? do you want more freedom? 
What is necessary to have in the Scientific View and what is necessary to have in the Managerial View?
We know that the managerial view needs to be more restrictive, i.e not to include all the sliders in that 
view. In that situation what should be the values of the other sliders provided?

1. TSS a slider? or input between 0 and 20?
2. macro-base-temp seems arbitrary with the values that is taking from 11.7 to 27.7 but only increasing a tick by 1. Do you want more freedom?
3. gross-macro-coef? slider or input? - Kevin would most likely want to use input for more control
4. macro-mass-max should be fine
5. What does the button Update Picture do? In our situation as we do not display a picture overtime is this necessary

On Wed, November 2nd, USGS Managers will be visiting and we will be attending dinner with them in 
order to learn about their needs.

AIM: Mid Dec develop the UI for Kevin and managers to test out.
Kevin will need to tell us what parameters he needs in the future in order to perform sensitivity analysis. 
While managers might just want to use the scientific average.

Bruce explained the need for Maps:
Velocities and directions determined by maps. Take periods of time when the river is steady and there 
will be a map for that. Another period of time when its flowing quickly and another map for that. These 
are big geographic files that tell you what the velocities are. These files should be specified for the 
managers sequence of hydros specified: Jan- 10k map- should run for that month only. Feb- 20k map- should run for only for this month and so on...

<a name="meetings_six"/>
### Meeting Six

We met with Dr. Ken Lubinski and Richard Sparks, Ph.D. They are both members of USGS and 
wanted to meet with us to discuss options and help us understand their needs. Ken Lubinski provided insight on the manager’s perspective and what it needs to do for them.

Code must be sufficiently documented. All equations must be cited. 
Every function / equation must be paired with a rationale to explain why we chose to go a particular route.
Model should run on a manager's laptop / desktop. Output should be the maps. We need to graph variables to determine how a variable changes over time.
Application should be tailored for the Windows OS. If we can draw a bounding area around certain areas on the map, we should see the change of 
variables over time within that area.  These variables should be plotted on one graph to show 
differences and trends. Once the depth is less than 0, we need to run a terrestrial map instead of a water map.
Numbers will have a maximum of 3 significant digits and 1 integer exponent value. Need to make managers understand the importance of food sources and show habitat diversity.
Reduce the complexities for managers. Ability to run the program to simulate 20-30 years. Managers can input different flows, 10k-30k, for different time intervals.
Managers need to have output in at most 30 minutes. We no longer need two different views. Managers and scientists will use the same UI. 
Require daily map updates on the GUI. To save memory: Run the model for the entire map.  Then the user selects a 
subset.  Run the model again for the subset, graphing changes over time.  However, 
everything else will just use the final result (don't need to store previous values for the 
rest of the map).

As we talked, it seemed that the initial input would be changing overtime depending on what they deem 
is necessary for scientists and managers to control. This is our liaison's job to go through and figure out 
what variables he needs to control. We also discussed that in order to reduce the complexities for the managers, we would have to set up 
default variables that are averaged by the scientists. This would reduce the complexity of setting all the 
variables and understanding them before running.

Richard also suggested the importance of outputting a graph for different rates so managers and 
scientists could have a better understanding. This might be hard to do with the amount of memory each 
patch will contain.

We were also mistaken in thinking that they were only interested in a final result. Ken confirmed with 
Bruce that he would like to have overtime updates appear on screen, but they don't have to be every 
hour like it is in the NetLogo code.

Ken also stated that selecting areas of interest would be an important tool for managers. While this 
would be a nice feature, we are still debating the possibility of this task and we think it can be done, but 
it might increase the run time. This is something we will address once we get the main mapping working.
Ken would also like to be able to control the flow used for different time intervals. As of now, the 
NetLogo code does not take this into account so this is something that we will have to put into the code.

Ken Lubinski’s Requirements and Notes

1. We understand that first and foremost, the computer programming students need to help speed up 
the existing model.  This means re-writing the code to make it run faster.  We discussed the importance 
of being able to see model results in a matter of minutes rather than days.  We also seemed to agree 
that perhaps desktop computer memory might not be a limiting factor, but that remains to be seen.

2.  We also need to assure that we and others have access to the equations the model uses to quantify 
cause and effect relationships and transport processes.

3.  We discussed adding more flexibility to the model inputs and outputs.  Desired inputs include 
selecting initial conditions for the stocks, and user-determined hydrographs.  Desired outputs included 
graphs of selected variables over time, as well as graphs that compared the relationships between 
different selected variables.  came away thinking that these changes were doable for the programmers with the possible exception 
of the user-determined hydrographs.  After thinking about this again, it seems to me that requesting the 
ability to enter user-determined hydrographs, while very valuable to us biologists, might be beyond 
what the contract calls for.  I mentioned last week that I had no intention of being a contract manager 
on this, and so I and Rip simply want to hear back from Efe and others if they think this is too much to 
ask for. If so, then it is something we'll have to postpone for the next version of the model.

4.  We also asked for the ability to link years together, such that conditions on Day 1 of Year 2, for 
example, link back conditions on Day 365 of Year 1.  This is especially important if we focus on 
macrophytes as a primary stock of interest, because macrophyte responses will probably play out over a 
number of years.  But again, it seems like we might have overstepped what could be done or even 
requested given the contract.  We need to hear back from the programmers on this.

General:

If our requests for "variable hydrographs" and "multiple year runs" are beyond the capacity or 
responsibility of the programmers, then Kevin we need to ask whether you'll be able to help add these 
functions to the model during your time at U of I.  Do you intend to make changes to the model once the 
model in its sped-u state to explore different scenarios and ecological questions.  Brian Ickes indicated 
that in its current forms, he knew the model would be insufficient to explore different flood pulse 
relationships.  But he does think there are other, more academic questions that the existing model could 
shed some light on, especially the applicability of different ecological theories (ie. The River Continuum 
Theory, the River Productivity Theory, etc.)to what happens in Pool 8 during a single year.
(Note: Brian is currently waiting on a report from Aloah that will discuss her model verification and 
validation efforts.)

<a name="meetings_seven"/>
### Meeting Seven

We met with Bart Rossman  viaGchat and walked through the main loop of the Netlogo code.

To ensure that our understanding of the current Netlogo translation was on par with reality, we 
stepped through the main loop of the code with Bart. In particular, our  focus centered on the update 
and flow-carbon functions. Through this, we were able to find several system level optimizations for our 
translation of the code into C. 

First, instead of running the update functions within the main loop, we can simply run them 
once during the call to setup. The update functions are currently implemented by reading one line from 
a file every loop iteration and storing that value to a variable. This is a problem because it introduces 
overhead for reading from a file every loop iteration. Instead, we plan on reading these values into an 
array all at once at the beginning. The previous implementation results in slow performance because 
reading from a file is a system level operation, meaning that the system kernel is accessed to perform 
I/O. As it is with most kernel operations, this process is slow and must generate overhead every time a 
file is read. To reduce this, we simply read all of the files at once within the setup functions and store 
their values within an array. That way, only the index must be updated at every main loop iteration to 
access the correct value.

We also discussed some of the code within the flow-carbon method that was difficult to read. At 
first we thought this had to do with complexities within the carbon model, but later found that it was a 
hack to get around a problem with Netlogo.  In Netlogo, the keyword ‘ask patches’ is equivalent to a 
double for loop that iterates over the x and y coordinates of a 2D array of patches. This syntax, however, 
does not provide functionality for easily referencing adjacent patches. Therefore, this was accomplished 
by using the X and Y vector of the carbon flow within each patch to calculate which patch would have 
carbon pushed into it. When this is translated into C, we can simply use plus or minus one to the X and Y 
coordinates to reference adjacent cells.

<a name="functional_req"/>
Functional Requirements
-----------------------

By summarizing the meetings listed above, we know that the overall functionality of this model 
will be to aid scientists and mangers of the Mississippi River in predicting drastic changes with the river 
that could adversely affect its ecosystem. To do this, they will need to focus in on important parts of the 
river that undergo drastic changes over a long period of time. One example of this might be a shore that
spends several months without water and thus loses the ecosystem that once inhabited it. To effectively 
accomplish this goal, our program will need to be able to:

1. Select specific groups of pixels to be observed via graphs as the model runs
2. Produce an image updated every hour that passes from the model’s perspective

<a name="nonfunctional_req"/>
Non-Functional Requirements
---------------------------

Our model will also need to be easily accessible by new users who are unfamiliar with its use 
and layout. They will need to be able to easily input new stock files and understand any sensitivity 
variables displayed in the graphic interface. To accomplish this, we will document the program’s 
functionality as clearly as possible and provide examples of correctly formatted input files.

<a name="assumptions"/>
Assumptions
-----------

Furthermore, it should be stated that we will tackle this problem under the assumption that the 
current model implemented in Netlogo is working as intended. Thus, our first prototype will be based 
off its functionality and any new features will be added on top of that specific code base.

<a name="plan"/>
Plan
----

We plan to first translate the Netlogo code into C and Python to get a better idea of the speedup 
our solution will achieve. From there, we can then decide whether or not our focus should be directed 
toward new features or optimizations with the current model.

<a name="experience"/>
Team Experience
---------------

When working together, we broke down the Netlogo model into several sections, including 
setup, patches, and go functionality under the MVC format for the GUI. All four team members worked 
on sections of the code that translated Netlogo into C. Efe performed a notable chunk of the work 
regarding setting up the view and controller, but we all contributed to the GUI’s overall functionality and 
display. In total, our team worked well together in communicating problems found and combining code 
at the end using github.

<a name="lessons"/>
Lessons Learned
---------------

If anything, this project has reinforced concepts with modularization, team work, and 
communication that we have already encountered in previous assignments. The best way to work within 
a group is to tear a large problem down piece by piece and then complete each of the combining parts 
one at a time. Through the MVC model, splitting code into multiple files, and working together regularly, 
our group was able to accomplish our goals in a timely matter.

<a name="status"/>
End of Semester Status
----------------------

Currently, our code completes a 365 day model within roughly 10 hours. We believe further 
optimizations can be achieved by changing how we handle memory and approximating flow carbon to 
push a minute or hours with of carbon per iteration instead of a second’s worth. Other than that, the 
core functionality has been implemented in both Python and C, giving us a strong starting point for next 
semester.

<a name="completion"/>
Plans for Completion
--------------------

Our plan is to speed up the current translation of the code to reach the stated requirements. 
Currently, our code completes a 365 day model within roughly twelve hours. We believe further 
optimizations can be achieved by changing how we handle memory and approximating flow carbon to 
push a minute or hours with of carbon per iteration instead of a second’s worth. From there, we can 
make judgment calls on what extra features can be implemented and how best to maximize the clarity 
of its user interface.

