extensions [profiler]


;change repeat statement
globals 
[
;; environmental globals
Q10;temperature dependent coefficient for aquatic plants
theta ; rate of change of photosynthesis based on an increase of 10 degrees celcius
par ; photosynthetic radiation
parvar ; used in SA sets par a % difference  
day ; calculates the number of days based on ticks
temp ; water temperature
tempvar ;;used to SA temp fluctuation impacts around 17 (from orig model)
NaN-trigger ; reports if NaNs are triggered
;; hydrologic variables
discharge ; rate of flow released from the dam at the top of a pool
hydro-group ; different groups designate different ranges of discharges
hydro-changed ; asks if the model switched hydro-groups
patch-length ; sets the length of an indiv. patch
max-area  ; uses patch-length to calculate cell area
compare-max ;  >>>>>
vars ; variables

out-macro; mean macro in export
out-phyto ; mean "" in export
out-herbivore  ; mean "" in export
out-waterdecomp ; mean "" in export
out-seddecomp ; mean "" in export
out-sedconsumer; mean "" in export
out-consum; mean "" in export
out-DOC ; mean "" in export
out-POC ; mean "" in export
out-detritus    ; mean "" in export
;; all biotic variables follow the same naming conventions and are in gwr/unit biomass **need refer
;; ; max- max density; e- excretion->DOC; r- respiration; s- senecence(natural mortality); -egestion ->POC
 ; j - stock 
 ; i - prey stock
 ; Cj =  PIij * THETAj * Xj * Fij * Fjj
; example: set waterdecomp-pred-doc (pref-waterdecomp-doc * max-waterdecomp * waterdecomp
;           * waterdecomp-space-limitation * waterdecomp-doc-prey-limitation)
 
 ;; Ai - prey density threshold max - labeled from consumer to prey
 ;; Gi - prey density threshold min - labeled from consumer to prey
 ;; Aj - space limitation max
 ;; Gj - space limitation min

; k - half saturation constant ?
; this is used in turbidity for hydrological function
;  k-inorganic ***unused

;;  DOC (dissolved organic carbon) variables  ;;

;;  POC (particulate organic carbon) variables  ;;
  k-POC ;used update-patches and 
  
;;  detritus variables  ;;

;;  phytoplankton variables  ;;
  ; k-phyto
  Aj-phyto           Gj-phyto
  
;;  periphyton variables (set as 10% macro per cell -* between eq3,4 source) ;;
  max-peri        e-peri        r-peri        s-peri
  Ai-Peri-DOC                 Gi-Peri-DOC                   pref-Peri-DOC 
  Ai-Peri-POC                 Gi-Peri-POC                   pref-Peri-POC
  peri-phys-loss
  Aj-peri Gj-peri
  
;;  macrophytes variables  ;;
 ; k-macro

;;  herbivores variables  ;;
  max-herbivore   e-herbivore   r-herbivore   s-herbivore   herbivore-egestion
  k-herbivore
  Ai-herbivore-phyto          Gi-herbivore-phyto            pref-herbivore-phyto        
  Ai-herbivore-waterdecomp    Gi-herbivore-waterdecomp      pref-herbivore-waterdecomp 
  Ai-herbivore-peri           Gi-herbivore-peri             pref-herbivore-peri
  Aj-herbivore       Gj-herbivore       

;;  decomposers in the water column variables  ;;
  max-waterdecomp e-waterdecomp r-waterdecomp s-waterdecomp
  Ai-waterdecomp-DOC          Gi-waterdecomp-DOC            pref-waterdecomp-DOC        
  Ai-waterdecomp-POC          Gi-waterdecomp-POC            pref-waterdecomp-POC
  Aj-waterdecomp     Gj-waterdecomp      
  
;;  decomposers in the sediment variables  ;;
  max-seddecomp   e-seddecomp   r-seddecomp   s-seddecomp
  Ai-seddecomp-detritus       Gi-seddecomp-detritus         pref-seddecomp-detritus
  Aj-seddecomp       Gj-seddecomp        
    
;;  consumers in the water column variables  ;;
  max-consum      e-consum      r-consum      s-consum          consum-egestion
  Ai-consum-herbivore         Gi-consum-herbivore           pref-consum-herbivore        
  Ai-consum-sedconsumer       Gi-consum-sedconsumer         pref-consum-sedconsumer 
  Aj-consum          Gj-consum   
  
;;  consumers in the sediments variables  ;;
  max-sedconsumer e-sedconsumer r-sedconsumer  s-sedconsumer 
  sedconsumer-egestion-seddecomp sedconsumer-egestion-detritus
  Ai-sedconsumer-seddecomp    Gi-sedconsumer-seddecomp      pref-sedconsumer-seddecomp  
  Ai-sedconsumer-peri         Gi-sedconsumer-peri           pref-sedconsumer-peri       
  Ai-sedconsumer-detritus     Gi-sedconsumer-detritus       pref-sedconsumer-detritus
  Aj-sedconsumer     Gj-sedconsumer        
        
]


patches-own
[
;;waterdecomp-phys-loss 
;;seddecomp-phys-loss 
;;herbivore-phys-loss 
;;sedconsumer-phys-loss 
;;consum-phys-loss
px-vector ; flow vector in the x-direction for hydraulics
pxv-list ; list of x flow vectors
py-vector; flow vector in the y-direction for hydraulics
pyv-list; list of y flow vectors
max-vector ; largest flow vector
depth ; depth of water in an indiv. cell
depth-list ; list of depths
current-depth ; depth in the previous time-step
velocity ; the rate of flow for hydraulics
v-list ; list of velocities
aqa-point ; biomass estimates of macro from USGS
cell-type ; 


waterdecomp-doc-prey-limitation
waterdecomp-poc-prey-limitation
peri-doc-prey-limitation
peri-poc-prey-limitation
seddecomp-detritus-prey-limitation
herbivore-phyto-prey-limitation
herbivore-waterdecomp-prey-limitation
herbivore-peri-prey-limitation
sedconsumer-seddecomp-prey-limitation
sedconsumer-peri-prey-limitation
sedconsumer-detritus-prey-limitation
consum-herbivore-prey-limitation
consum-sedconsumer-prey-limitation

peri-space-limitation           
waterdecomp-space-limitation    
seddecomp-space-limitation    
herbivore-space-limitation    
sedconsumer-space-limitation   
consum-space-limitation      

assimilation
detritus DOC POC waterdecomp seddecomp macro phyto herbivore sedconsumer peri consum
bottom-light ; par that reaches the bottom of the river
consumer ; consumers in the water column, such as fish
consum-consumption
consum-ingest-herbivore
consum-pred-herbivore
consum-ingest-sedconsumer
consum-pred-sedconsumer
consum-excretion
consum-sda
consum-senescence
consum-respiration
consum-growth
detritus-growth
detritus-POC-transfer ; the amount of carbon that transfers from detritus to POC
seddecomp-pred-detritus
sedconsumer-pred-detritus
direction ; the direction carbon flows
DOC-growth
DOC-pred
egestion
excretion
excretion-phyto
flocculation ; the act of DOC sticking together to create POC
gross-photo
gross-photo-macro ; photosynthesis of macrophytes
gross-photo-phyto ; photosythesis of phytoplankton
growth-herbivore
growth-detritus
;growth-DOC
growth-macro
;growth-POC
growth-sedconsumer
growth-phyto
growth-waterdecomp
herbivore-consumption
herbivore-ingest-peri
herbivore-pred-peri
herbivore-ingest-phyto
herbivore-pred-phyto
herbivore-ingest-waterdecomp
herbivore-pred-waterdecomp
herbivore-excretion
herbivore-sda
herbivore-senescence
herbivore-respiration
herbivore-growth
K ; carrying capacity
large-death ; death of large-sized trophic groups
light 
light-k ; attenuation coefficient of phytoplankon
macro-death
macro-exudation ; amount of photosynthetic material released
micro-death ; amount of dead plant material that becomes DOC
phyto-maximum-growth-rate 
phyto-pred
POC-detritus-transfer ; the amount of carbon that transfers from detritus to POC
POC-growth
POC-pred
phyto-density
peri-ingest-doc
peri-pred-doc
peri-ingest-poc
peri-pred-poc
peri-respiration
peri-excretion
peri-senescence
senescence ; death
scouring ; 
small-death ; amount of dead plant material that becomes POC
respiration
respiration-macro
respiration-phyto
scouring-macro
sedconsumer-ingest-peri
sedconsumer-pred-peri
senescence-macro
senescence-phyto
sedconsumer-consumption
sedconsumer-ingest-detritus
sedconsumer-ingest-seddecomp
sedconsumer-pred-seddecomp
sedconsumer-excretion
sedconsumer-egestion
sedconsumer-senescence
sedconsumer-respiration
sedconsumer-growth
seddecomp-consumption
seddecomp-ingest-detritus
seddecomp-excretion
seddecomp-growth
seddcomp-ingest-peri
seddecomp-pred-peri
seddecomp-respiration
seddecomp-senescence
velpoc; velocity used for poc-to-detritus transfer equation
waterdecomp-consumption
waterdecomp-ingest-doc
waterdecomp-sda
waterdecomp-excretion
waterdecomp-ingest-poc
waterdecomp-pred-doc
waterdecomp-pred-poc
waterdecomp-respiration
waterdecomp-senescence
turbidity ; metric of suspended solids in water column

]

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; BEGIN SETUP FUNCTION
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

to setup
  ; order is important here...
  ca
  import-hydro
  setup-parameters
  setup-environmentals
  setup-stocks
  setup-vars
  setup-plot-stocks
;;  setup-export
;  if import-day90? = true
;   [ import-day90
;     skip-90days ]
end

to profile
                  ;; set up the model
profiler:start         ;; start profiling
repeat 1 [ go ]       ;; run something you want to measure
profiler:stop          ;; stop profiling
print profiler:report  ;; view the results
profiler:reset         ;; clear the data

end

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; BEGIN GO FUNCTION
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
to go


ifelse fixedEnvironmentals? = false 
 [ update-environmentals ] ;;this is flagged to run every 24 ticks in the function
 [ ifelse sin ((ticks - 6) * (360 / 24)) <= 0  ;; this is a sinusoidal wave to fluctuate PAS rom 0 - fixedPAR over 24 hours
    [ set par 0 ]
    [ set par fixedPAR * sin ((ticks - 6) * (360 / 24)) ]]

ask patches with [depth > 0] 
 [
  update-patches 
  go-macro 
  go-phyto 
  go-herbivore  
  go-waterdecomp 
  go-seddecomp 
  go-sedconsumer
  go-consum
  go-DOC 
  go-POC 
  go-detritus 
 
  pred-phyto
  pred-herbivore
  pred-seddecomp
  pred-waterdecomp
  pred-sedconsumer
  pred-detritus
  pred-DOC
  pred-POC
  pred-consum
  check-NaN "In ecology"
 ]



 avg-output
 
 let timestep 0
 repeat 3600 / max-timestep [  
  foreach sort patches with [depth > 0 and velocity > 0] [
    ask ? [flow-carbon]]

    if NaN-trigger = "true" [
   print "NaN triggered"
   stop ]  
]   
 




  tick
  input

  
 set day floor (ticks / 24) ;;runs first since ticks starts at 0
   if (ticks / 24) = int (ticks / 24)
    [ update-plot-stocks] 
    
; if day >= DaystoRun [stop] 

; if (day / 7) = int ( day / 7 )
;  [ export-count ]
  

 if ExportPics? = true [
  if (ticks / 24) = int (ticks / 24)
    [ export-color (day)] 

  if (ticks / 1080) = int ( ticks / 1080 )
    [ export-fs (day) ]]

end


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;; END setup & go ROUTINES
;;;;;;; All called functions follow
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; BEGIN FUNCTIONS in SETUP ROTUTINE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


to import-hydro
  ; this sets all patches' values to -999
  ; so that when we import, patches with imported values of 0 will be used for calculations

  ask patches [set depth-list [0]
               set pxv-list [0]
               set pyv-list [0]
               set v-list [0]
               set aqa-point -999]
  
  
 foreach ["100k" "90k" "80k" "70k" "60k" "50k" "40k" "30k" "20k" "10k"] 
  [ file-open (word ? "-" count-neighbor ".txt")
    let nothing file-read-line
    while [ not file-at-end? ]
     [ let tempx (file-read )
       let tempy (file-read)
       ask patch tempx tempy
       [ set depth-list lput (file-read) depth-list 
         set pxv-list lput (file-read) pxv-list
         set pyv-list lput (file-read) pyv-list
         set v-list lput (file-read) v-list
      ]]
    file-close 
    print (word "Imported " ?)]
  
  file-open "cell-type.txt"
  let nothing file-read-line
    while [ not file-at-end? ]
     [ let tempx (file-read )
       let tempy (file-read)
       ask patch tempx tempy [set cell-type file-read]]
  file-close
  print "Cell-Type Imported"
  
end


to import-day90
file-open "day90.txt"
while [ not file-at-end? ]  [
ask patch file-read file-read [
  set waterdecomp-doc-prey-limitation file-read 
  set waterdecomp-poc-prey-limitation file-read 
  set peri-doc-prey-limitation file-read 
  set peri-poc-prey-limitation file-read 
  set seddecomp-detritus-prey-limitation file-read 
  set herbivore-phyto-prey-limitation file-read 
  set herbivore-waterdecomp-prey-limitation file-read 
  set herbivore-peri-prey-limitation file-read 
  set sedconsumer-seddecomp-prey-limitation file-read 
  set sedconsumer-peri-prey-limitation file-read 
  set sedconsumer-detritus-prey-limitation file-read 
  set consum-herbivore-prey-limitation file-read 
  set consum-sedconsumer-prey-limitation file-read 
  set peri-space-limitation file-read 
  set waterdecomp-space-limitation file-read 
  set seddecomp-space-limitation file-read 
  set herbivore-space-limitation file-read 
  set sedconsumer-space-limitation file-read 
  set consum-space-limitation file-read 
  set assimilation file-read 
  set detritus file-read 
  set doc file-read 
  set poc file-read 
  set waterdecomp file-read 
  set seddecomp file-read 
  set macro file-read 
  set phyto file-read 
  set herbivore file-read 
  set sedconsumer file-read 
  set peri file-read 
  set consum file-read 
  set bottom-light file-read 
  set consumer file-read 
  set consum-consumption file-read 
  set consum-ingest-herbivore file-read 
  set consum-pred-herbivore file-read 
  set consum-ingest-sedconsumer file-read 
  set consum-pred-sedconsumer file-read 
  set consum-excretion file-read 
  set consum-sda file-read 
  set consum-senescence file-read 
  set consum-respiration file-read 
  set consum-growth file-read 
  set detritus-growth file-read 
  set detritus-poc-transfer file-read 
  set seddecomp-pred-detritus file-read 
  set sedconsumer-pred-detritus file-read 
  set direction file-read 
  set doc-growth file-read 
  set doc-pred file-read 
  set egestion file-read 
  set excretion file-read 
  set excretion-phyto file-read 
  set flocculation file-read 
  set gross-photo file-read 
  set gross-photo-macro file-read 
  set gross-photo-phyto file-read 
  set growth-herbivore file-read 
  set growth-detritus file-read 
  set growth-macro file-read 
  set growth-sedconsumer file-read 
  set growth-phyto file-read 
  set growth-waterdecomp file-read 
  set herbivore-consumption file-read 
  set herbivore-ingest-peri file-read 
  set herbivore-pred-peri file-read 
  set herbivore-ingest-phyto file-read 
  set herbivore-pred-phyto file-read 
  set herbivore-ingest-waterdecomp file-read 
  set herbivore-pred-waterdecomp file-read 
  set herbivore-excretion file-read 
  set herbivore-sda file-read 
  set herbivore-senescence file-read 
  set herbivore-respiration file-read 
  set herbivore-growth file-read 
  set k file-read 
  set large-death file-read 
  set light file-read 
  set light-k file-read 
  set macro-death file-read 
  set macro-exudation file-read 
  set micro-death file-read 
  set phyto-maximum-growth-rate file-read 
  set phyto-pred file-read 
  set poc-detritus-transfer file-read 
  set poc-growth file-read 
  set poc-pred file-read 
  set phyto-density file-read 
  set peri-ingest-doc file-read 
  set peri-pred-doc file-read 
  set peri-ingest-poc file-read 
  set peri-pred-poc file-read 
  set peri-respiration file-read 
  set peri-excretion file-read 
  set peri-senescence file-read 
  set senescence file-read 
  set scouring file-read 
  set small-death file-read 
  set respiration file-read 
  set respiration-macro file-read 
  set respiration-phyto file-read 
  set scouring-macro file-read 
  set sedconsumer-ingest-peri file-read 
  set sedconsumer-pred-peri file-read 
  set senescence-macro file-read 
  set senescence-phyto file-read 
  set sedconsumer-consumption file-read 
  set sedconsumer-ingest-detritus file-read 
  set sedconsumer-ingest-seddecomp file-read 
  set sedconsumer-pred-seddecomp file-read 
  set sedconsumer-excretion file-read 
  set sedconsumer-egestion file-read 
  set sedconsumer-senescence file-read 
  set sedconsumer-respiration file-read 
  set sedconsumer-growth file-read 
  set seddecomp-consumption file-read 
  set seddecomp-ingest-detritus file-read 
  set seddecomp-excretion file-read 
  set seddecomp-growth file-read 
  set seddcomp-ingest-peri file-read 
  set seddecomp-pred-peri file-read 
  set seddecomp-respiration file-read 
  set seddecomp-senescence file-read 
  set velpoc file-read 
  set waterdecomp-consumption file-read 
  set waterdecomp-ingest-doc file-read 
  set waterdecomp-sda file-read 
  set waterdecomp-excretion file-read 
  set waterdecomp-ingest-poc file-read 
  set waterdecomp-pred-doc file-read 
  set waterdecomp-pred-poc file-read 
  set waterdecomp-respiration file-read 
  set waterdecomp-senescence file-read 
  set turbidity file-read 
]]
file-close
print "Day-90 variables imported" 

end

to skip-90days

  repeat 89
   [ update-discharge
     update-temp ]
  repeat 2159 
   [ update-par ]
  print "Updated environmentals to day 90"
end

; function - sets initial values of all global variables
;      *need measures - either here or on declaration
; this can be setup as an imported text file to make site changes easier

to setup-parameters
  
set patch-length 30 ; convert ft to m from the SMS to png scaling conversion
set max-area patch-length ^ 2

set max-waterdecomp 6.26 / 24  set e-waterdecomp .173 / 24  set r-waterdecomp .6 / 24    set s-waterdecomp .05 / 24 
set max-seddecomp   6.26 / 24  set e-seddecomp .173 / 24    set r-seddecomp .6 / 24      set s-seddecomp  .05 / 24  
set max-herbivore  1 / 24      set e-herbivore  .4 / 24     set r-herbivore .08 / 24     set s-herbivore .01 / 24     
set herbivore-egestion .2      
set max-sedconsumer .55 / 24   set e-sedconsumer  .01 / 24  set r-sedconsumer .04 / 24   set s-sedconsumer .01 / 24  
set sedconsumer-egestion-seddecomp .35 set sedconsumer-egestion-detritus .9
set max-consum  .125 / 24      set e-consum  .0032 / 24     set r-consum .0125 / 24      set s-consum  .002 / 24      set consum-egestion .2
; max gwr/unit biomass; e- excretion->DOC; r- respiration; s- senecence(natural mortality); -egestion ->POC


set Ai-waterdecomp-DOC  30      set Gi-waterdecomp-DOC   .05         set pref-waterdecomp-DOC .5
set Ai-waterdecomp-POC  30      set Gi-waterdecomp-POC   .05         set pref-waterdecomp-POC .5
set Ai-Peri-DOC       30        set Gi-Peri-DOC     .05              set pref-Peri-DOC .5
set Ai-Peri-POC       30        set Gi-Peri-POC     .05              set pref-Peri-POC .5
set Ai-seddecomp-detritus  .6   set Gi-seddecomp-detritus .005       set pref-seddecomp-detritus 1
set Ai-herbivore-phyto  20       set Gi-herbivore-phyto  .01          set pref-herbivore-phyto .7
set Ai-herbivore-waterdecomp  3 set Gi-herbivore-waterdecomp .01     set pref-herbivore-waterdecomp .15
set Ai-herbivore-peri      3    set Gi-herbivore-peri    .01         set pref-herbivore-peri .15
set Ai-sedconsumer-seddecomp 3  set Gi-sedconsumer-seddecomp  .02    set pref-sedconsumer-seddecomp .5
set Ai-sedconsumer-peri   2     set Gi-sedconsumer-peri     .02      set pref-sedconsumer-peri .4
set Ai-sedconsumer-detritus 3.5 set Gi-sedconsumer-detritus  .02     set pref-sedconsumer-detritus .1
set Ai-consum-herbivore  3.5    set Gi-consum-herbivore   .025       set pref-consum-herbivore .7
set Ai-consum-sedconsumer  4    set Gi-consum-sedconsumer  .04       set pref-consum-sedconsumer .3
; above variables are ripe for sensitivity analysis
; ben will send reference
; prey parameters - Ai and Gi, coded 1 -> 0
   
set Aj-phyto    10       set  Gj-phyto 100
set Aj-waterdecomp 1.2   set  Gj-waterdecomp 20     
  ;peri updated every timestep based on macro density        
set Aj-seddecomp  .2     set  Gj-seddecomp  120     ; need river values 
set Aj-herbivore  2.4    set  Gj-herbivore  108      
set Aj-sedconsumer  2    set  Gj-sedconsumer  20    
set Aj-consum   .65      set  Gj-consum    6.5
;;density dependent crowding effects on linear scale - capped at Aj and Gj - coded 1->0  
 
; set k-macro .4 -> taken from interface
; set k-phyto .4 -> taken from interface
set k-herbivore .2
set k-POC .2
 
  
set theta 1.072
;let base-temp 19.7 ; base temp for nominal growth
;set Q10 theta ^ (temp - base-temp)

end

; function - reads from files the initial discharge (daily) and initial radiation (hourly) values
;  then import the maps based on the discharge value

to setup-environmentals
  set tempvar 0
  set parvar 0
  ifelse fixedEnvironmentals? = true 
  [ set hydro-group fixedHydro
    update-hydro-map
    set par fixedPAR
    set temp fixedTemp ]
  [ file-close-all
    file-open "discharge.txt"
    set discharge file-read
    file-close
    file-open "par.txt"
    set par file-read
    file-close
    file-open "water-temp.txt"
    set temp file-read
    file-close
    set hydro-group 0
    choose-hydro-map
    update-hydro-map ]
end


;
; function - sets initial stocks of species, wich are patch variables
;      *need measures and relations

to setup-stocks
ask patches with [depth > 0]
[
 set macro 1
 set phyto 10
 set waterdecomp 10
 set seddecomp 1
 set herbivore 1
 set sedconsumer 1
 set DOC 10
 set POC 10
 set detritus 1
 set consum .1
]

end

to setup-export 
  
   file-open "export-fs.txt"
   file-print "day,pxcor,pycor,PHYTO,MACRO"
   file-close

end


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; END FUNCTIONS in SETUP ROTUTINE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; BEGIN FUNCTIONS in GO ROTUTINE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; function - this sets the hydro-group varaible from the discharge hydrograph imported 
;       in the setup-environmentals routine

to choose-hydro-map
  set hydro-changed 0
  let old-hydro hydro-group
  ifelse discharge <= 20000
    [ set hydro-group 10
     if old-hydro != hydro-group [ set hydro-changed 1]]   
  [ifelse discharge > 20000 and discharge <= 30000
    [ set hydro-group 9
     if old-hydro != hydro-group [ set hydro-changed 1]]   
  [ifelse discharge > 30000 and discharge <= 40000
    [ set hydro-group 8
     if old-hydro != hydro-group [ set hydro-changed 1]]   
  [ifelse discharge > 40000 and discharge <= 50000
    [ set hydro-group 7
     if old-hydro != hydro-group [ set hydro-changed 1]]      
   [ifelse discharge > 50000 and discharge <= 60000
    [ set hydro-group 6
     if old-hydro != hydro-group [ set hydro-changed 1]]
   [ifelse discharge > 60000 and discharge <= 70000
    [ set hydro-group 5
      if old-hydro != hydro-group [ set hydro-changed 1]]
   [ifelse discharge > 70000 and discharge <= 80000
    [ set hydro-group 4 
      if old-hydro != hydro-group [ set hydro-changed 1]]
   [ifelse discharge > 80000 and discharge <= 90000
    [ set hydro-group 3 
      if old-hydro != hydro-group [ set hydro-changed 1]]
   [ifelse discharge > 90000 and discharge <= 100000
    [ set hydro-group 2 
      if old-hydro != hydro-group [ set hydro-changed 1]]
   [if discharge > 100000
    [ set hydro-group 1 
      if old-hydro != hydro-group [ set hydro-changed 1]]]]]]]]]]]
end

to update-hydro-map
      
    ask patches 
     [ ifelse length depth-list > hydro-group 
       [set px-vector item hydro-group pxv-list
         set py-vector item hydro-group pyv-list
         ifelse abs(px-vector) > abs(py-vector) 
            [ set max-vector abs(px-vector) ]
            [ set max-vector abs(py-vector) ]
         set depth item hydro-group depth-list
         set velocity item hydro-group v-list]
       [set px-vector 0
         set py-vector 0
         set depth 0
         set velocity 0]
     if current-depth > 0 and depth = 0
     [ set detritus detritus + DOC + POC + phyto + macro + waterdecomp + seddecomp + herbivore + sedconsumer + consum
       set DOC 0
       set POC 0
       set phyto 0
       set macro 0
       set waterdecomp 0
       set seddecomp 0
       set herbivore 0
       set sedconsumer 0
       set consum 0 ]
     if current-depth = 0 and depth > 0
     [ set detritus detritus * 0.50 ] ;;make everything else go to zero
       set current-depth depth] ; grabs the current depth before the map update in the next time step, so it can be compared to the new depth 
     
  let max-vx max [px-vector] of patches
  let max-vy max [py-vector] of patches
  let min-vx abs(min [px-vector] of patches)
  let min-vy abs(min [py-vector] of patches)
  set compare-max max (list max-vx max-vy min-vx min-vy)
  
  print (word "updated hydro-map to " hydro-group "at day " day)
       
end

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; function - this is the hydrological flow routine, which runs at a different timestep
; *need patch selection - currently random - should this be algorithmic? 

;to wind ; not the correct to function
;;in calc-stress
;set resuspension-k 213.75 + delta-r; derived from rate of resuspension 4.5g/cell/s - 90g/cell/s for sheer stresses of 0.125N/m^2 - 0.525N/m^2 "Hydrodynamics ans water quality: modeling rivers, lakes, and estuaries by Zhen-Gang Ji"
;if u <= 0.1 [set resuspension-rate 0]; (Hakanson and Jansson, 1983)
;if u > 0.1 [set resuspension-rate resuspension-k * sheer-stress - 20]
;if resuspension-rate < 0 [ set resuspension-rate 0]
;;in go-detritus
;set detritus-suspension detritus * resuspension ; the amount of detritus that goes to POC 
;;in pred-detritus
;set detritus detritus + detritus-growth - seddecomp-pred-detritus - detritus-POC-transfer - detritus-suspension ; updated detritus mass from resuspension
;;in go-POC
;set POC-growth flocculation + detritus-POC-transferset + detritus-suspension; updated POC mass from resuspension
;;in update-patches
;set turbidity ( .29587 + TSS) + (k-phyto * (phyto / 900) ) + (k-macro * (macro / 900) ) + (k-POC * (POC / 900) ) ; a measure of how cloudy the water is
;end


to update-patches
; changed v2.1 from Aloah  
;set turbidity ( .29587 + (.023757 * TSS) + (k-macro * macro) + (k-phyto * phyto) + (k-herbivore * herbivore) + (k-POC * POC)) 
set turbidity ( .29587 + TSS) + (k-phyto * (phyto / 900) ) + (k-macro * (macro / 900) )
 if turbidity > 30 [set turbidity 30]
 if turbidity < 0 [set turbidity 0.01] ; turbidity limits between .01 and 30
 if isNaN turbidity [show " NaN"]
set  bottom-light (par * exp ( (- depth) *  turbidity )) ; the amount of light that reaches the bottom of a water column
set Aj-peri macro / 10 ; space limitation max
set Gj-peri macro / 2 ; space limitation min
set Aj-seddecomp detritus / 20 ; space limitation max
set Gj-seddecomp detritus / 5 ; space limitation min
   ; Environmetrics p3 
end

; function - primary macrophyte routine
; *need details on what is going on here - explicitly - in case code changes

to update-environmentals
  if ( ticks / 24 ) = ( int ( ticks / 24 )); (coding means: if ticks/24 is an integer) updates daily 
   [update-discharge ; pulls a new discharge from a text file 
    choose-hydro-map ; chooses a new hydro map based on the discharge
    if hydro-changed = 1 
     [update-hydro-map] ; updates a new hydro map based on the discharge
    ]
   if ( ticks / 168 ) = ( int ( ticks / 168 )); updates weekly
    [update-temp] ; updates to a new water temperature 
  update-par ; updates hourly to a new photosynthetic radiation value
end  



to update-par
  file-open "par.txt"; hourly time-scale
  set par file-read
  set par  par - (par * parvar) ;; parvar is % dif of value
end

to update-discharge
  file-open "discharge.txt"; daily time-scale
  set discharge file-read
end

to update-temp
  file-open "water-temp.txt"; daily time-scale
  set temp file-read
  set temp  temp - ((temp - 17) * tempvar) ;; tempvar is % dif from 17C
end

; function - primary macrophyte routine
; *need details on what is going on here - explicitly - in case code changes

to go-macro
  
;*** prime for SA - run TSS across full range beyond 1 (milligrams/L)
set Q10 theta ^ (temp - macro-base-temp) ; temperature-dependent coefficient

; ref: Current velocity and aquatic plants (chambers, 1991)
; macro-mass-max - the maximum aquatic macro DRY biomass (in grams per m^2)
; macro-vel-max - the maximum velocity that results in no macro presence (m/s)
ifelse velocity < macro-vel-max 
  [set K  max-area * (macro-mass-max - (macro-mass-max / macro-vel-max * velocity))] ; carrying capacity of macrophytes is set by velocity
  [set K 0.01]

;let macro-turbidity ( .29587 + (.023757 * TSS)  + (k-phyto * phyto) + (k-herbivore * herbivore) + (k-POC * POC))
  ; *need reference - if this equation repeats, let's make an explicit function
;let macro-light (par * exp ( (- depth) *  macro-turbidity ))
; changed 2.1 from Aloah
let macro-light (par * exp ( (- depth) *  turbidity ))  ; *same as bottom-light
;set gross-photo-macro (.08 * macro * ( macro-light / (macro-light + 10)) * Q10 * (K - macro) / K )
set gross-photo-macro (gross-macro-coef * macro * ( macro-light / (macro-light + 10)) * Q10 * (K - macro) / K ); photosynthesis by macrophytes derived from Garby el al. 2006
  ; .08 estimated from Kaj Sand-Jensen fig 7
  ;*** prime for SA
set respiration-macro resp-macro-coef / 24 * macro * Q10  ; hourly macrophyte respiration
;set respiration-macro .04 / 24 * macro * Q10
;*** prime for SA
set senescence-macro sen-macro-coef / 24  * macro ; hourly macrophyte death
;set senescence-macro .05 / 24  * macro  
;*** prime for SA
; values range between .05 and 3m a Garby et al 2006

; set scouring-macro scouring * macro
set growth-macro gross-photo-macro - respiration-macro - senescence-macro - scouring-macro ; amount of biomass macro gains
  ; summing above calcs *need to know about scouring discrepency
set macro macro + growth-macro ; updated macrophyte biomass
if macro < .001 [ set macro .001 ] ; minimum biomass based on seed bank


end

; function - primary phyto routine
; *need details on what is going on here - explicitly - in case code changes

to go-phyto
  
if phyto > 900000 [ set phyto 900000 ] ; minimum and maximum caps on biomass
if phyto < .001 [ set phyto 0.001 ]
let base-temp 8 ; base temp for nominal growth  
set Q10 theta ^ (temp - base-temp) ; temperature-dependent coefficient
let km 10  ;half saturation constant  
set light-k .4 ; this is the attenuation coefficient of phytoplank m^2/g of phyto plankton.
set respiration-phyto .1 / 24 * phyto * Q10
let pre-ln (0.01 + par * e ^ ( -1 * phyto * K-phyto * depth ))
let be (km + ( par * e ^ ( -1 * phyto * K-phyto * depth )))
set gross-photo-phyto abs (pre-ln / be) * ( 1 / depth) * (phyto / turbidity) * Q10 ; photosynthesis from phytoplankton derived from Huisman Weissing 1994 
set excretion-phyto .05 / 24 * phyto 
set senescence-phyto .02 / 24  * phyto  ; values range between .05 and 3
set growth-phyto gross-photo-phyto - excretion-phyto - respiration-phyto - senescence-phyto ; amount of biomas phytoplankton gains
  

end


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;all consumption equations are derived from Wiegert 1975
;Consumption = (sum of)[ ((pi)ij * tj * Xj * fij * fjj)]
;(pi)ij = preference for a stock i by predator j ( i.e. pref-herbivore-phyto)
;tj = maximum rate of consumption for stock I by predator j   (i.e. max-herbivore)
;Xj = biomass of predator j
;fij = prey limitation - calculated for each predator/prey combination
;;;; fij = prey biomass / (Ai - Gi)
;fjj = space limitation
;;;; fjj =  1 - ((predator biomass - Aj) / (Gj - Aj))
;; Ai - prey density threshold max 
;; Gi - prey density threshold min 
;; Aj - space limitation max
;; Gj - space limitation min
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

to go-herbivore
set herbivore-phyto-prey-limitation phyto / (ai-herbivore-phyto - gi-herbivore-phyto)
if herbivore-phyto-prey-limitation > 1 [set herbivore-phyto-prey-limitation 1] ; caps set at 100% and 0%
if herbivore-phyto-prey-limitation < 0 [set herbivore-phyto-prey-limitation 0]
set herbivore-peri-prey-limitation  peri / (ai-herbivore-peri - gi-herbivore-peri)
if herbivore-peri-prey-limitation > 1 [set herbivore-peri-prey-limitation 1]
if herbivore-peri-prey-limitation < 0 [set herbivore-peri-prey-limitation 0]
set herbivore-waterdecomp-prey-limitation  waterdecomp / (ai-herbivore-waterdecomp - gi-herbivore-waterdecomp)
if herbivore-waterdecomp-prey-limitation > 1 [set herbivore-waterdecomp-prey-limitation 1]
if herbivore-waterdecomp-prey-limitation < 0 [set herbivore-waterdecomp-prey-limitation 0]
set herbivore-space-limitation 1 - ((herbivore - Aj-herbivore) / (Gj-herbivore - Aj-herbivore))
if herbivore-space-limitation > 1 [set herbivore-space-limitation 1]
if herbivore-space-limitation < 0 [set herbivore-space-limitation 0]
    ; *need references
set herbivore-pred-phyto (pref-herbivore-phyto * max-herbivore * herbivore * herbivore-space-limitation * herbivore-phyto-prey-limitation) ; amount of biomass herbivore "consume" from phyto
    ; *need reference
set herbivore-ingest-phyto herbivore-pred-phyto * (1 - herbivore-egestion) ; biomass "consumed" adjusted for egestion
    ; *need reference
set herbivore-pred-peri (pref-herbivore-peri * max-herbivore * herbivore * herbivore-space-limitation * herbivore-peri-prey-limitation)
    ; *need reference
set herbivore-ingest-peri herbivore-pred-peri * (1 - herbivore-egestion)
    ; *need reference
set herbivore-pred-waterdecomp (pref-herbivore-waterdecomp * max-herbivore * herbivore * herbivore-space-limitation * herbivore-waterdecomp-prey-limitation)
    ; *need reference
set herbivore-ingest-waterdecomp herbivore-pred-waterdecomp * (1 - herbivore-egestion)
    ; *need reference
set herbivore-respiration r-herbivore * herbivore 
    ; *need reference
set herbivore-excretion e-herbivore * herbivore
    ; *need reference
set herbivore-senescence s-herbivore * herbivore
    ; *need reference
;;set herbivore-phys-loss (herbivore-respiration + herbivore-excretion + herbivore-senescence)
    ; *need reference
; let theta 1.072 - temperature dependence...
; let base-temp 8 ; base temp for nominal growth
; set Q10 theta ^ (temp - base-temp)
end

; function - primary water decomposing routine
; *need details on what is going on here - explicitly - in case code changes

to go-waterdecomp
set waterdecomp-doc-prey-limitation  doc / (ai-waterdecomp-doc - gi-waterdecomp-doc)
if isNaN waterdecomp-doc-prey-limitation [ print (word "waterdecomp-doc-prey-limitation, " doc "," ai-waterdecomp-doc "," gi-waterdecomp-doc )]
if waterdecomp-doc-prey-limitation > 1 [set waterdecomp-doc-prey-limitation 1]
if waterdecomp-doc-prey-limitation < 0 [set waterdecomp-doc-prey-limitation 0]
set waterdecomp-poc-prey-limitation  poc / (ai-waterdecomp-poc - gi-waterdecomp-poc)
if waterdecomp-poc-prey-limitation > 1 [set waterdecomp-poc-prey-limitation 1]
if waterdecomp-poc-prey-limitation < 0 [set waterdecomp-poc-prey-limitation 0]
set waterdecomp-space-limitation 1 - ((waterdecomp - Aj-waterdecomp) / (Gj-waterdecomp - Aj-waterdecomp))
if waterdecomp-space-limitation > 1 [set waterdecomp-space-limitation 1]
if waterdecomp-space-limitation < 0 [set waterdecomp-space-limitation 0]
    ; *need references
  ; PIij * THETAj * Xj * Fij * Fjj
set waterdecomp-pred-doc (pref-waterdecomp-doc * max-waterdecomp * waterdecomp * waterdecomp-space-limitation * waterdecomp-doc-prey-limitation)
if isNAN waterdecomp-pred-doc [ print (word "waterdecomp-pred-doc, " pref-waterdecomp-doc ", " max-waterdecomp ", " waterdecomp ", " waterdecomp-space-limitation ", " waterdecomp-doc-prey-limitation)]
set waterdecomp-ingest-doc waterdecomp-pred-doc 
set waterdecomp-pred-poc (pref-waterdecomp-poc * max-waterdecomp * waterdecomp * waterdecomp-space-limitation * waterdecomp-poc-prey-limitation)
set waterdecomp-ingest-poc waterdecomp-pred-poc
    ; *need reference - we look to be redundant in this call
set waterdecomp-respiration r-waterdecomp * waterdecomp 
set waterdecomp-excretion e-waterdecomp * waterdecomp
set waterdecomp-senescence s-waterdecomp  * waterdecomp 
;;set waterdecomp-phys-loss (waterdecomp-respiration + waterdecomp-excretion + waterdecomp-senescence)
    ; sum above variables
end

; function - primary sedentary decomposing routine
; *need details on what is going on here - explicitly - in case code changes

to go-seddecomp
set seddecomp-detritus-prey-limitation  detritus / (ai-seddecomp-detritus - gi-seddecomp-detritus)
if seddecomp-detritus-prey-limitation > 1 [set seddecomp-detritus-prey-limitation 1]
if seddecomp-detritus-prey-limitation < 0 [set seddecomp-detritus-prey-limitation 0]
    ; *need references
ifelse  (Gj-seddecomp - Aj-seddecomp) != 0   
 [set seddecomp-space-limitation 1 - ((seddecomp - Aj-seddecomp) / (Gj-seddecomp - Aj-seddecomp))]
 [set seddecomp-space-limitation 0]
if seddecomp-space-limitation > 1 [set seddecomp-space-limitation 1]
if seddecomp-space-limitation < 0 [set seddecomp-space-limitation 0]
    ; *need references
set seddecomp-pred-detritus (pref-seddecomp-detritus * max-seddecomp * seddecomp * seddecomp-detritus-prey-limitation * seddecomp-space-limitation)
    ; *need references
set seddecomp-ingest-detritus seddecomp-pred-detritus
    ; *need references 
set seddecomp-respiration r-seddecomp * seddecomp
    ; *need references 
set seddecomp-excretion e-seddecomp * seddecomp
    ; *need references
set seddecomp-senescence s-seddecomp * seddecomp 
    ; *need references
;;set seddecomp-phys-loss (seddecomp-respiration + seddecomp-excretion + seddecomp-senescence)
    ; sums up all calculations
end


; function - primary sedentary consuming routine
; *need details on what is going on here - explicitly - in case code changes

to go-sedconsumer
set sedconsumer-seddecomp-prey-limitation  seddecomp / (ai-sedconsumer-seddecomp - gi-sedconsumer-seddecomp)
if sedconsumer-seddecomp-prey-limitation > 1 [set sedconsumer-seddecomp-prey-limitation 1]
if sedconsumer-seddecomp-prey-limitation < 0 [set sedconsumer-seddecomp-prey-limitation 0]
    ; *need references
set sedconsumer-peri-prey-limitation  peri / (ai-sedconsumer-peri - gi-sedconsumer-peri)
if sedconsumer-peri-prey-limitation > 1 [set sedconsumer-peri-prey-limitation 1]
if sedconsumer-peri-prey-limitation < 0 [set sedconsumer-peri-prey-limitation 0]
    ; *need references
set sedconsumer-detritus-prey-limitation  detritus / (ai-sedconsumer-detritus - gi-sedconsumer-detritus)
if sedconsumer-detritus-prey-limitation > 1 [set sedconsumer-detritus-prey-limitation 1]
if sedconsumer-detritus-prey-limitation < 0 [set sedconsumer-detritus-prey-limitation 0]
    ; *need references
set sedconsumer-space-limitation 1 - ((sedconsumer - Aj-sedconsumer) / (Gj-sedconsumer - Aj-sedconsumer))
if sedconsumer-space-limitation > 1 [set sedconsumer-space-limitation 1]
if sedconsumer-space-limitation < 0 [set sedconsumer-space-limitation 0]
    ; *need references
set sedconsumer-pred-peri (pref-sedconsumer-peri * max-sedconsumer * sedconsumer * sedconsumer-space-limitation * sedconsumer-peri-prey-limitation)
    ; *need references
set sedconsumer-ingest-peri sedconsumer-pred-peri * (1 - sedconsumer-egestion-seddecomp)
    ; *need references
set sedconsumer-pred-seddecomp (pref-sedconsumer-seddecomp * max-sedconsumer * sedconsumer * sedconsumer-space-limitation * sedconsumer-seddecomp-prey-limitation)
    ; *need references
set sedconsumer-ingest-seddecomp sedconsumer-pred-seddecomp * (1 - sedconsumer-egestion-seddecomp)
    ; *need references
set sedconsumer-pred-detritus (pref-sedconsumer-detritus * max-sedconsumer * sedconsumer * sedconsumer-space-limitation * sedconsumer-detritus-prey-limitation)
    ; *need references
set sedconsumer-ingest-detritus sedconsumer-pred-detritus * (1 - sedconsumer-egestion-detritus)
    ; *need references
set sedconsumer-respiration r-sedconsumer * sedconsumer
    ; *need references
set sedconsumer-excretion e-sedconsumer * sedconsumer
    ; *need references
set sedconsumer-senescence s-sedconsumer * sedconsumer 
    ; *need references
;;set sedconsumer-phys-loss (sedconsumer-respiration + sedconsumer-excretion + sedconsumer-senescence)
    ; sums up all calculations
end

; function - primary consuming routine
; *need details on what is going on here - explicitly - in case code changes

to go-consum
set consum-sedconsumer-prey-limitation  sedconsumer / (ai-consum-sedconsumer - gi-consum-sedconsumer)
if consum-sedconsumer-prey-limitation > 1 [set consum-sedconsumer-prey-limitation 1]
if consum-sedconsumer-prey-limitation < 0 [set consum-sedconsumer-prey-limitation 0]
    ; *need references
set consum-herbivore-prey-limitation  herbivore / (ai-consum-herbivore - gi-consum-herbivore)
if consum-herbivore-prey-limitation > 1 [set consum-herbivore-prey-limitation 1]
if consum-herbivore-prey-limitation < 0 [set consum-herbivore-prey-limitation 0]
    ; *need references
set consum-space-limitation 1 - ((consum - Aj-consum) / (Gj-consum - Aj-consum))
if consum-space-limitation > 1 [set consum-space-limitation 1]
if consum-space-limitation < 0 [set consum-space-limitation 0]
    ; *need references
set consum-pred-herbivore (pref-consum-herbivore * max-consum * consum * consum-space-limitation * consum-herbivore-prey-limitation)
    ; *need references
set consum-ingest-herbivore consum-pred-herbivore * (1 - consum-egestion)
    ; *need references
set consum-pred-sedconsumer (pref-consum-sedconsumer * max-consum * consum * consum-space-limitation * consum-sedconsumer-prey-limitation)
    ; *need references
set consum-ingest-sedconsumer consum-pred-sedconsumer * (1 - consum-egestion)
    ; *need references
set consum-respiration r-consum * consum 
    ; *need references
set consum-excretion e-consum * consum
    ; *need references
set consum-senescence s-consum  * consum 
    ; *need references
;;set consum-phys-loss (consum-respiration + consum-excretion + consum-senescence)
    ; sums up all calculations
end

; function - dissolved organic carbon routine
; *need details on what is going on here - explicitly - in case code changes

to go-DOC
set macro-exudation .04 * macro ; 4% of photosynthetic gets released into the water column
    ;Wetzel lit.
set micro-death senescence-macro * .01 + senescence-phyto * .01 
    ;Dead objects < 1um are considered DOC in Wetzel book..
set excretion herbivore-excretion + waterdecomp-excretion + seddecomp-excretion + sedconsumer-excretion + consum-excretion + excretion-phyto + peri-excretion; assumed all excreted materials would be < 10um
    ; *need reference
set flocculation .01 * DOC ; DOC sticks together and becomes POC at a small rate
    ; *need reference
set DOC-growth macro-exudation + micro-death + excretion
    ; sums calculations into variable
end

; function - particulate organic carbon routine
; *need details on what is going on here - explicitly - in case code changes

to go-POC
if velocity > 0
  [ set detritus-POC-transfer detritus * (.25 * log (((velocity / 40) + .0001) + 1) 10 )]
     ; exchange between POC and detritus determined by an approximation of Stoke's Law
if detritus-POC-transfer > 1 
  [set detritus-POC-transfer 1] ; cap at 100%
      ; *need reference
set small-death senescence-macro * .09 + senescence-phyto * .09 + scouring-macro * 0.1 + waterdecomp-senescence * .7 + .3 * peri-senescence ;approximations of the percention of dead objects < 10um that will be in water column; Wetzel Limnology textbook.
    ; *need reference
set POC-growth flocculation + detritus-POC-transfer
    ; flocculation, leaching approximation
end 

; function - detritus routine
; *need details on what is going on here - explicitly - in case code changes

to go-detritus
if velocity > 0
  [ set POC-detritus-transfer POC * ( 1 - (.25 * log (((velocity / 40) + .0001) + 1) 10 )) ]
    ; *need reference
if POC-detritus-transfer < 0
  [set POC-detritus-transfer 0]
    ; *need reference
if velocity = 0
  [ set POC-detritus-transfer POC * .9 ] ; almost all material falls to the bottom in stagnant water
    ; *need reference
if gross-photo-macro < 0
 [ set macro-death 0 - gross-photo-macro]
   ; to incorporate scoured macrophytes into detritus
set large-death senescence-macro * .9 + scouring-macro * 0.9 + senescence-phyto * .9 + seddecomp-senescence + waterdecomp-senescence * .3 +
  herbivore-senescence + sedconsumer-senescence + consum-senescence + .07 * peri-senescence
    ; Dead objects > 10um will sink Wetzel book..
set egestion herbivore-egestion + sedconsumer-egestion + consum-egestion



set detritus-growth large-death + POC-detritus-transfer + egestion + macro-death 


set detritus-growth large-death + POC-detritus-transfer + egestion + macro-death
    ; *need reference
;show detritus-growth   
end

; function - detritus routine
; *need details on what is going on here - explicitly - in case code changes

to pred-phyto
  set phyto phyto + growth-phyto - herbivore-pred-phyto
  if phyto < .001 [ set phyto .001 ]
end


; function - detritus routine
; *need details on what is going on here - explicitly - in case code changes

to pred-herbivore
  set herbivore herbivore + herbivore-ingest-phyto + herbivore-ingest-peri + herbivore-ingest-waterdecomp - (herbivore-respiration + herbivore-excretion + herbivore-senescence) - consum-pred-herbivore
  if herbivore < .001 [ set herbivore 0.001 ]
end

; function - detritus routine
; *need details on what is going on here - explicitly - in case code changes

to pred-seddecomp
  set seddecomp seddecomp + seddecomp-ingest-detritus - (seddecomp-respiration + seddecomp-excretion + seddecomp-senescence) - sedconsumer-pred-seddecomp
  if seddecomp < .001 [ set seddecomp .001 ]
end

; function - detritus routine
; *need details on what is going on here - explicitly - in case code changes

to pred-waterdecomp
  set waterdecomp waterdecomp + waterdecomp-ingest-doc + waterdecomp-ingest-poc - (waterdecomp-respiration + waterdecomp-excretion + waterdecomp-senescence) - herbivore-pred-waterdecomp
  if waterdecomp < .001 [ set waterdecomp .001 ]
end


; function - detritus routine
; *need details on what is going on here - explicitly - in case code changes

to pred-sedconsumer

  set sedconsumer sedconsumer + sedconsumer-ingest-peri + sedconsumer-ingest-seddecomp - (sedconsumer-respiration + sedconsumer-excretion + sedconsumer-senescence) - consum-pred-sedconsumer
  if sedconsumer < .001 [set sedconsumer .001 ]
end


; function - detritus routine
; *need details on what is going on here - explicitly - in case code changes

to pred-detritus
   set detritus-POC-transfer detritus * ((.25 * log ((velocity / 40) + .01) 10) + .5) 
  set detritus detritus + detritus-growth - seddecomp-pred-detritus - detritus-POC-transfer ; - detritus-suspension - added to new model
  if detritus < .001 [ set detritus .001 ]
end


; function - detritus routine
; *need details on what is going on here - explicitly - in case code changes

to pred-DOC 
  set DOC DOC + DOC-growth - waterdecomp-pred-doc - flocculation
  if DOC < .001 [ set DOC .001 ]
end



; function - detritus routine
; *need details on what is going on here - explicitly - in case code changes

to pred-POC
  set POC POC + POC-growth - waterdecomp-pred-poc - POC-detritus-transfer
  if POC < .001 [ set POC .001 ]
end


; function - detritus routine
; *need details on what is going on here - explicitly - in case code changes

to pred-consum 
 set consum consum + consum-ingest-herbivore + consum-ingest-sedconsumer -  (consum-respiration + consum-excretion + consum-senescence) 
 if consum < .001 [set consum .001]
end

to debug-NaN

foreach vars [
  if isNaN runresult ? 
     [ show ? 
       set NaN-trigger "true" ]]

end

to setup-vars
set vars [  
"waterdecomp-doc-prey-limitation"
"waterdecomp-poc-prey-limitation"
"peri-doc-prey-limitation"
"peri-poc-prey-limitation"
"seddecomp-detritus-prey-limitation"
"herbivore-phyto-prey-limitation"
"herbivore-waterdecomp-prey-limitation"
"herbivore-peri-prey-limitation"
"sedconsumer-seddecomp-prey-limitation"
"sedconsumer-peri-prey-limitation"
"sedconsumer-detritus-prey-limitation"
"consum-herbivore-prey-limitation"
"consum-sedconsumer-prey-limitation"
"peri-space-limitation"           
"waterdecomp-space-limitation"    
"seddecomp-space-limitation"    
"herbivore-space-limitation"    
"sedconsumer-space-limitation"   
"consum-space-limitation"      
"assimilation"
"detritus"
"DOC" 
"POC" 
"waterdecomp" 
"seddecomp" 
"macro" 
"phyto" 
"herbivore" 
"sedconsumer" 
"peri" 
"consum"
"bottom-light"
"consumer"
"consum-consumption"
"consum-ingest-herbivore"
"consum-pred-herbivore"
"consum-ingest-sedconsumer"
"consum-pred-sedconsumer"
"consum-excretion"
"consum-sda"
"consum-senescence"
"consum-respiration"
"consum-growth"
"detritus-growth"
"detritus-POC-transfer"
"seddecomp-pred-detritus"
"sedconsumer-pred-detritus"
"direction"
"DOC-growth"
"DOC-pred"
"egestion"
"excretion"
"excretion-phyto"
"flocculation"
"gross-photo"
"gross-photo-macro"
"gross-photo-phyto"
"growth-herbivore"
"growth-detritus"
"growth-macro"
"growth-sedconsumer"
"growth-phyto"
"growth-waterdecomp"
"herbivore-consumption"
"herbivore-ingest-peri"
"herbivore-pred-peri"
"herbivore-ingest-phyto"
"herbivore-pred-phyto"
"herbivore-ingest-waterdecomp"
"herbivore-pred-waterdecomp"
"herbivore-excretion"
"herbivore-sda"
"herbivore-senescence"
"herbivore-respiration"
"herbivore-growth"
"K"
"large-death"
"light"
"light-k"
"macro-death"
"macro-exudation"
"micro-death"
"phyto-maximum-growth-rate" 
"phyto-pred"
"POC-detritus-transfer"
"POC-growth"
"POC-pred"
"phyto-density"
"peri-ingest-doc"
"peri-pred-doc"
"peri-ingest-poc"
"peri-pred-poc"
"peri-respiration"
"peri-excretion"
"peri-senescence"
"senescence"
"scouring"
"small-death"
"respiration"
"respiration-macro"
"respiration-phyto"
"scouring-macro"
"sedconsumer-ingest-peri"
"sedconsumer-pred-peri"
"senescence-macro"
"senescence-phyto"
"sedconsumer-consumption"
"sedconsumer-ingest-detritus"
"sedconsumer-ingest-seddecomp"
"sedconsumer-pred-seddecomp"
"sedconsumer-excretion"
"sedconsumer-egestion"
"sedconsumer-senescence"
"sedconsumer-respiration"
"sedconsumer-growth"
"seddecomp-consumption"
"seddecomp-ingest-detritus"
"seddecomp-excretion"
"seddecomp-growth"
"seddcomp-ingest-peri"
"seddecomp-pred-peri"
"seddecomp-respiration"
"seddecomp-senescence"
"velpoc"
"waterdecomp-consumption"
"waterdecomp-ingest-doc"
"waterdecomp-sda"
"waterdecomp-excretion"
"waterdecomp-ingest-poc"
"waterdecomp-pred-doc"
"waterdecomp-pred-poc"
"waterdecomp-respiration"
"waterdecomp-senescence"
"turbidity" ]  
  
end

to check-NaN [msg]
  
   if isNaN detritus [show (word "detritus-" ticks "-" detritus "-" msg)]
   if isNaN DOC [show (word "DOC " DOC "-" msg)
     show ( word  DOC-growth "-" waterdecomp-pred-doc "-" flocculation)]
   if isNaN POC [show (word "POC-" ticks "-" POC "-" msg)]
   if isNaN waterdecomp [show (word "waterdecomp-" ticks "-" waterdecomp "-" msg)]
   if isNaN seddecomp [show (word "seddecomp-" ticks "-" seddecomp "-" msg)]
   if isNaN macro [show (word "macro-" ticks "-" macro "-" msg)]
   if isNaN phyto [show (word "phyto-" ticks "-" phyto "-" msg)]
   if isNaN herbivore [show (word "herbivore-" ticks "-" herbivore "-" msg)]
   if isNaN sedconsumer [show (word "sedconsumer-" ticks "-" sedconsumer "-" msg)]
   if isNaN peri [show (word "peri-" ticks "-" peri "-" msg)]
   if isNaN consum [show (word "consum-" ticks "-" consum "-" msg)]
   
end



to-report isNaN [x]
  report not ( x > 0 or x < 0 or x = 0 )
end 

to avg-output
  set out-macro mean [macro] of patches with [cell-type = "output"]
  set out-phyto mean [phyto] of patches with [cell-type = "output"]
  set out-herbivore  mean [herbivore] of patches with [cell-type = "output"]
  set out-waterdecomp mean [waterdecomp] of patches with [cell-type = "output"]
  set out-seddecomp mean [seddecomp] of patches with [cell-type = "output"]
  set out-sedconsumer mean [sedconsumer] of patches with [cell-type = "output"]
  set out-consum mean [consum] of patches with [cell-type = "output"]
  set out-DOC mean [DOC] of patches with [cell-type = "output"]
  set out-POC mean [POC] of patches with [cell-type = "output"]
  set out-detritus mean [detritus] of patches with [cell-type = "output"]
  ; show (word out-macro " " out-phyto " " out-herbivore " " out-waterdecomp " " out-seddecomp " " out-sedconsumer " " out-consum " " out-DOC " " out-POC " " out-detritus )  
end

to loop-output
  set macro out-macro
  set phyto out-phyto
  set herbivore out-herbivore
  set waterdecomp out-waterdecomp
  set seddecomp out-seddecomp
  set sedconsumer out-sedconsumer
  set consum out-consum
  set DOC out-DOC
  set POC out-POC
  set detritus out-detritus
  ; show (word "Looped output at " ticks)
end

to flow-carbon ;[timestep]

;;; Since we are using caresian corrdinates, we use the absolutes of the x and y vectors to equate the fraction of 
;;; the carbon to be moved - we have a top/bottom patch, corner patch, right/left patch
      
     ;; removed timestep from equation
      let cornerpatch abs( py-vector * px-vector ) / max-area 
      let tbpatch abs( py-vector * ( patch-length - abs(px-vector) ) ) / max-area
      let rlpatch abs( px-vector * ( patch-length - abs(py-vector) ) ) / max-area

;;; Using patch-at, we only need to know which direction the carbon flows and our choices are polarized
;;; either, -1/0/1, since we just assume some direction, we only test for +/- and move towards 3 patches
;;; if the vector is zero, nothing bad happens, we just spun our wheels a little
      
      if Loop-Output? [
         if cell-type = "input" 
            [loop-output]] 
      ;; This is where the looping of output to the input cell occurs, setting all stocks to averaged output
      
      let origDOC DOC ; need to carry the carbon of the original patch to figure the result in the neighboring patches
      let origPOC POC
      let origPHYTO PHYTO
      let origWATERDECOMP WATERDECOMP
      let tbMvd 0 ; if a neighbor patch is dry, the carbon doesn't move  in that direction 
      let cMvd 0  ; this idea can be revisited to see if we want to move more to other patches
      let rlMvd 0
      
      let px 0  ; this checks the polarity of the vector to allow us to select the correct 'patch-at'
      let py 0
      ifelse  px-vector >= 0 [set px 1] [set px -1]
      ifelse py-vector >= 0 [set py 1] [set py -1]
 
      ; since we had to process our own vector data, we do not have to worry about non-existent patches
      ; plus I turned wrapping back on - there are not any patches that touch across the world borders
      
         ask patch-at 0 py [
           if depth > 0 [
           if isNaN (DOC + origDOC * tbpatch) [show (word "0 py " DOC ", " origDOC ", " tbpatch)
             set NaN-trigger "true" ]  
           set DOC (DOC + origDOC * tbpatch)
           set POC (POC + origPOC * tbpatch)
           set PHYTO (PHYTO + origPHYTO * tbpatch)
           set WATERDECOMP (WATERDECOMP + origWATERDECOMP * tbpatch)
           set tbMvd 1]]

         ask  patch-at px py [
           if depth > 0 [
            if isNaN (DOC + origDOC * cornerpatch) [show (word "px py " DOC ", " origDOC ", " cornerpatch)
              set NaN-trigger "true" ]  
            set DOC (DOC + origDOC * cornerpatch)
            set POC (POC + origPOC * cornerpatch)
            set PHYTO (PHYTO + origPHYTO * cornerpatch)
            set WATERDECOMP (WATERDECOMP + origWATERDECOMP * cornerpatch)            
            set cMvd 1]]

         ask  patch-at px 0 [
           if depth > 0 [
            if isNaN (DOC + origDOC * rlpatch) [show (word "px 0 " DOC ", " origDOC ", " rlpatch)
              set NaN-trigger "true" ]  
            set DOC (DOC + origDOC * rlpatch)
            set POC (POC + origPOC * rlpatch)
            set PHYTO (PHYTO + origPHYTO * rlpatch)
            set WATERDECOMP (WATERDECOMP + origWATERDECOMP * rlpatch)            
            set rlMvd 1]]
      

      ; if a patch was dry and the carbon didn't move, we zero out the loss in the original patch
      let patch-loss (tbpatch * tbMvd + cornerpatch * cMvd + rlpatch * rlMvd)  
      if isNaN (DOC - DOC * patch-loss) [show (word "patch-loss " DOC ", " patch-loss)]
      set DOC (DOC - DOC * patch-loss)
      set POC (POC - POC * patch-loss)
      set PHYTO (PHYTO - PHYTO * patch-loss)
      set WATERDECOMP (WATERDECOMP - WATERDECOMP * patch-loss)
      
;;; have not added diffusion back into the model...      
;  let DOC-diffusion .001 * DOC
;  let POC-diffusion .001 * POC
;  let PHYTO-diffusion .001 * PHYTO
;  let WATERDECOMP-diffusion .001 * WATERDECOMP
;  
;  ask neighbors with [depth > 0] [
;    set DOC DOC + DOC-diffusion
;    set POC POC + POC-diffusion
;    set PHYTO PHYTO + PHYTO-diffusion
;    set WATERDECOMP WATERDECOMP + WATERDECOMP-diffusion
;    ]
;    
;  set DOC DOC - DOC-diffusion * count neighbors with [depth > 0]
;  set POC POC - POC-diffusion * count neighbors with [depth > 0]
;  set PHYTO PHYTO - PHYTO-diffusion * count neighbors with [depth > 0]
;  set WATERDECOMP WATERDECOMP - WATERDECOMP-diffusion * count neighbors with [depth > 0]
                
end

to export-count
  
   file-open "export-count1.txt"
   file-print (word "day number: " day)
   file-close

end
to export-fs [i]
  
   file-open (word "-km" k-macro "-kp" k-phyto "-tss" tss "-day" i ".txt")
   file-print "pxcor pycor PHYTO MACRO"
     foreach sort patches with [depth > 0] [
       ask ? 
       [ file-write pxcor file-write pycor file-write PHYTO file-write MACRO]]
   file-close
   print (word "export-fs-" i ".txt has been saved.")

end
; function - detritus routine
; *need details on what is going on here - explicitly - in case code changes

to update-color
if which-stock? = "macro"
;[ let min-macro-mass min [macro] of patches with [depth > 0]
;  let max-macro-mass max [macro] of patches with [depth > 0]
  [ask patches [ set pcolor scale-color green macro 600000 0]]
if which-stock? = "phyto"
 [ask patches  [set pcolor scale-color green phyto 75000 0]]
if which-stock? = "waterdecomp"
 [ask patches [set pcolor scale-color green waterdecomp 30 0 ]]
if which-stock? = "seddecomp"
 [ask patches [set pcolor 99.9 - seddecomp * .09]]
if which-stock? = "herbivore"
[ ask patches [set pcolor 119.9 - herbivore * 0.3]]
if which-stock? = "consum"
[ ask patches [set pcolor 29.9 - consum * 15]]
if which-stock? = "DOC"
[ ask patches [set pcolor  49.9 - DOC * .03 ]]
if which-stock? = "POC" 
[ ask patches [set pcolor scale-color blue POC 10 0]]
if which-stock? = "detritus"
 [ask patches [set pcolor scale-color brown detritus 400 0]]
if which-stock? = "sedconsumer"
 [ask patches [set pcolor scale-color yellow sedconsumer 15 0] ]
end

to export-color [cnt]
  
  foreach ["macro" "phyto"]; "waterdecomp" "seddecomp" "herbivore" "consum" "DOC" "POC" "detritus" "sedconsumer"]
  [set which-stock? ?
    update-color
    export-view (word "results/" ? "-" cnt ".png")]
    
end




to-report max-timestep
  ;; this sets the max-timestep based on the greatest x-y vector
  report floor (patch-length / compare-max)
end



to input
 ask patches with [pycor = 601 and pxcor >= 63 and pxcor <= 80]
 ; will change in bigger map
  [set DOC 10
   set POC 10
   set phyto 10
   set waterdecomp 10]
end


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; END FUNCTIONS in SETUP ROTUTINE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; FUNCTIONS in Interface
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 
 to add-DOC
  ask patch 107 168 [set DOC DOC + 500000]
 end
 

 
;;; unused functions;;;
to go-peri
 set peri-doc-prey-limitation  doc / (ai-peri-doc - gi-peri-doc)
 if peri-doc-prey-limitation > 1 [set peri-doc-prey-limitation 1]
 if peri-doc-prey-limitation < 0 [set peri-doc-prey-limitation 0]
  set peri-poc-prey-limitation  poc / (ai-peri-poc - gi-peri-poc)
 if peri-poc-prey-limitation > 1 [set peri-poc-prey-limitation 1]
 if peri-poc-prey-limitation < 0 [set peri-poc-prey-limitation 0]

 
  set peri-space-limitation 1 - ((peri - Aj-peri) / (Gj-peri - Aj-peri))
  if peri-space-limitation > 1 [set peri-space-limitation 1]
  if peri-space-limitation < 0 [set peri-space-limitation 0]

 set peri-pred-doc (pref-peri-doc * max-peri * peri * peri-space-limitation * peri-doc-prey-limitation)
 set peri-ingest-doc peri-pred-doc 
 set peri-pred-poc (pref-peri-poc * max-peri * peri * peri-space-limitation * peri-poc-prey-limitation)
 set peri-ingest-poc peri-pred-poc 
 set peri-respiration r-peri * peri 
 set peri-excretion e-peri * peri
 set peri-senescence s-peri  * peri 
 set peri-phys-loss (peri-respiration + peri-excretion + peri-senescence)

end

to pred-peri
  set peri peri + peri-ingest-doc + peri-ingest-poc - peri-phys-loss - herbivore-pred-peri - sedconsumer-pred-peri
  if peri < 0 [ set peri .001 ]
end


to validate-fs
  file-open "validate.txt"
  ask patches with [aqa-point > -1]
    [file-print (
         word aqa-point ","
         macro ","
         mean [macro] of patches in-radius 1 ","
         mean [macro] of patches in-radius 2 "," 
         mean [macro] of patches in-radius 3 "," 
         mean [macro] of patches in-radius 5  ","
         mean [macro] of patches in-radius 7 ","
         mean [macro] of patches in-radius 10 ","
         mean [macro] of patches in-radius 12 "," 
         mean [macro] of patches in-radius 15  ","
         max [macro] of patches in-radius 1 "," 
         max [macro] of patches in-radius 2  ","  
         max [macro] of patches in-radius 3 ","
         max [macro] of patches in-radius 5 ","
         max [macro] of patches in-radius 7 ","
         max [macro] of patches in-radius 10   ","  
         max [macro] of patches in-radius 12  ","
         max [macro] of patches in-radius 15 ","
         min [macro] of patches in-radius 1  ","
         min [macro] of patches in-radius 2  ","
         min [macro] of patches in-radius 3 ","
         min [macro] of patches in-radius 5  ","
         min [macro] of patches in-radius 7","   
         min [macro] of patches in-radius 10  ","  
         min [macro] of patches in-radius 12 ","
         min [macro] of patches in-radius 15 )
         file-print ""]
  file-close
  print "Validation export complete"
end

to export-day90
file-open "day90.txt"
ask patches with [depth > 0]  [
  file-write pxcor
  file-write pycor
  file-write waterdecomp-doc-prey-limitation  
  file-write waterdecomp-poc-prey-limitation  
  file-write peri-doc-prey-limitation  
  file-write peri-poc-prey-limitation  
  file-write seddecomp-detritus-prey-limitation  
  file-write herbivore-phyto-prey-limitation  
  file-write herbivore-waterdecomp-prey-limitation  
  file-write herbivore-peri-prey-limitation  
  file-write sedconsumer-seddecomp-prey-limitation  
  file-write sedconsumer-peri-prey-limitation  
  file-write sedconsumer-detritus-prey-limitation  
  file-write consum-herbivore-prey-limitation  
  file-write consum-sedconsumer-prey-limitation  
  file-write peri-space-limitation  
  file-write waterdecomp-space-limitation  
  file-write seddecomp-space-limitation  
  file-write herbivore-space-limitation  
  file-write sedconsumer-space-limitation  
  file-write consum-space-limitation  
  file-write assimilation  
  file-write detritus  
  file-write doc  
  file-write poc  
  file-write waterdecomp  
  file-write seddecomp  
  file-write macro  
  file-write phyto  
  file-write herbivore  
  file-write sedconsumer  
  file-write peri  
  file-write consum  
  file-write bottom-light  
  file-write consumer  
  file-write consum-consumption  
  file-write consum-ingest-herbivore  
  file-write consum-pred-herbivore  
  file-write consum-ingest-sedconsumer  
  file-write consum-pred-sedconsumer  
  file-write consum-excretion  
  file-write consum-sda  
  file-write consum-senescence  
  file-write consum-respiration  
  file-write consum-growth  
  file-write detritus-growth  
  file-write detritus-poc-transfer  
  file-write seddecomp-pred-detritus  
  file-write sedconsumer-pred-detritus  
  file-write direction  
  file-write doc-growth  
  file-write doc-pred  
  file-write egestion  
  file-write excretion  
  file-write excretion-phyto  
  file-write flocculation  
  file-write gross-photo  
  file-write gross-photo-macro  
  file-write gross-photo-phyto  
  file-write growth-herbivore  
  file-write growth-detritus  
  file-write growth-macro  
  file-write growth-sedconsumer  
  file-write growth-phyto  
  file-write growth-waterdecomp  
  file-write herbivore-consumption  
  file-write herbivore-ingest-peri  
  file-write herbivore-pred-peri  
  file-write herbivore-ingest-phyto  
  file-write herbivore-pred-phyto  
  file-write herbivore-ingest-waterdecomp  
  file-write herbivore-pred-waterdecomp  
  file-write herbivore-excretion  
  file-write herbivore-sda  
  file-write herbivore-senescence  
  file-write herbivore-respiration  
  file-write herbivore-growth  
  file-write k  
  file-write large-death  
  file-write light  
  file-write light-k  
  file-write macro-death  
  file-write macro-exudation  
  file-write micro-death  
  file-write phyto-maximum-growth-rate  
  file-write phyto-pred  
  file-write poc-detritus-transfer  
  file-write poc-growth  
  file-write poc-pred  
  file-write phyto-density  
  file-write peri-ingest-doc  
  file-write peri-pred-doc  
  file-write peri-ingest-poc  
  file-write peri-pred-poc  
  file-write peri-respiration  
  file-write peri-excretion  
  file-write peri-senescence  
  file-write senescence  
  file-write scouring  
  file-write small-death  
  file-write respiration  
  file-write respiration-macro  
  file-write respiration-phyto  
  file-write scouring-macro  
  file-write sedconsumer-ingest-peri  
  file-write sedconsumer-pred-peri  
  file-write senescence-macro  
  file-write senescence-phyto  
  file-write sedconsumer-consumption  
  file-write sedconsumer-ingest-detritus  
  file-write sedconsumer-ingest-seddecomp  
  file-write sedconsumer-pred-seddecomp  
  file-write sedconsumer-excretion  
  file-write sedconsumer-egestion  
  file-write sedconsumer-senescence  
  file-write sedconsumer-respiration  
  file-write sedconsumer-growth  
  file-write seddecomp-consumption  
  file-write seddecomp-ingest-detritus  
  file-write seddecomp-excretion  
  file-write seddecomp-growth  
  file-write seddcomp-ingest-peri  
  file-write seddecomp-pred-peri  
  file-write seddecomp-respiration  
  file-write seddecomp-senescence  
  file-write velpoc  
  file-write waterdecomp-consumption  
  file-write waterdecomp-ingest-doc  
  file-write waterdecomp-sda  
  file-write waterdecomp-excretion  
  file-write waterdecomp-ingest-poc  
  file-write waterdecomp-pred-doc  
  file-write waterdecomp-pred-poc  
  file-write waterdecomp-respiration  
  file-write waterdecomp-senescence  
  file-write turbidity  
]
file-close
print "Day-90 variables exported" 

end


to import-fs 
   file-open user-file
   let header 0
   set header file-read-line
   while [ not file-at-end? ]  [
     ask patch file-read file-read [
       set phyto file-read 
       set macro file-read
     ]]
   file-close
   print "File imported"
end

to setup-plot-stocks
  set-current-plot "stocks"
end

to update-plot-stocks
  set-current-plot-pen "doc-min"
  plot min [doc] of patches
  set-current-plot-pen "doc-max"
  plot max [doc] of patches 
  set-current-plot-pen "poc-min"
  plot min [poc] of patches
  set-current-plot-pen "poc-max"
  plot max [poc] of patches  
end   


to import-validation
  ask patches [set aqa-point -999]
  let map-x-min 635312.51 ;; file input min -> 635312.51
  let map-y-min 4825678 ;; file input min -> 4825678
  let x-scaler 30
  let y-scaler 30
;  let vList []

  file-open "Pool8.txt"
  while [ not file-at-end? ]
    ;ifelse patch ((item 0 vList - map-x-min) / x-scaler) ((item 1 vList - map-y-min) / y-scaler) != nobody
    [ask patch ((file-read - map-x-min) / x-scaler) ((file-read - map-y-min) / y-scaler)
    [ set aqa-point file-read]]
  file-close
  print (word "Imported Pool8" )

end
  
@#$#@#$#@
GRAPHICS-WINDOW
175
10
520
1240
-1
-1
1.0
1
10
1
1
1
0
0
0
1
-1
333
-1
1197
0
0
1
ticks

BUTTON
19
16
82
49
NIL
setup
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL

BUTTON
92
16
155
49
NIL
go
T
1
T
OBSERVER
NIL
NIL
NIL
NIL

CHOOSER
603
100
741
145
which-stock?
which-stock?
"macro" "phyto" "waterdecomp" "seddecomp" "herbivore" "consum" "DOC" "POC" "detritus" "sedconsumer"
1

SLIDER
15
241
159
274
TSS
TSS
0
20
10
1
1
NIL
HORIZONTAL

MONITOR
604
10
662
55
NIL
day
17
1
11

BUTTON
686
62
769
96
NIL
add-DOC
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL

BUTTON
604
62
676
95
NIL
profile
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL

INPUTBOX
16
163
158
223
DaysToRun
365
1
0
Number

BUTTON
604
151
725
184
Update Picture
update-color
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL

SLIDER
15
280
162
313
macro-base-temp
macro-base-temp
11.7
27.7
19.7
1
1
NIL
HORIZONTAL

SLIDER
14
322
164
355
gross-macro-coef
gross-macro-coef
0
1
0.08
.01
1
NIL
HORIZONTAL

SLIDER
13
364
165
397
resp-macro-coef
resp-macro-coef
0
1
0.04
.01
1
NIL
HORIZONTAL

SLIDER
11
407
165
440
sen-macro-coef
sen-macro-coef
0
1
0.08
0.01
1
NIL
HORIZONTAL

SWITCH
16
63
157
96
Import-Day90?
Import-Day90?
1
1
-1000

SWITCH
603
193
758
226
exportPics?
exportPics?
1
1
-1000

CHOOSER
604
331
742
376
fixedHydro
fixedHydro
1 2 3 4 5 6 7 8 9 10
4

SWITCH
604
293
793
326
fixedEnvironmentals?
fixedEnvironmentals?
1
1
-1000

SLIDER
604
383
776
416
fixedTemp
fixedTemp
0
30
20
1
1
NIL
HORIZONTAL

SLIDER
604
422
776
455
fixedPAR
fixedPAR
0
2000
2000
100
1
NIL
HORIZONTAL

BUTTON
606
466
718
499
Export Results
export-fs (\"base\")\n
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL

TEXTBOX
739
467
822
621
fixedHydro\n1 - 100k\n2 - 90k\n3 - 80k\n4 - 70k\n5 - 60k\n6 - 50k\n7 - 40k\n8 - 30k\n9 - 20k\n10 - 10k
11
0.0
1

SLIDER
10
447
165
480
macro-mass-max
macro-mass-max
500
1500
1000
25
1
NIL
HORIZONTAL

SLIDER
10
482
166
515
macro-vel-max
macro-vel-max
.2
1.6
1
.1
1
NIL
HORIZONTAL

SLIDER
9
537
166
570
k-phyto
k-phyto
0
1
0.01
.1
1
NIL
HORIZONTAL

BUTTON
606
504
719
537
Import Results
import-fs
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL

SLIDER
9
575
167
608
k-macro
k-macro
0
1
0.01
.01
1
NIL
HORIZONTAL

SWITCH
18
106
158
139
Loop-Output?
Loop-Output?
0
1
-1000

INPUTBOX
603
227
758
287
count-neighbor
5
1
0
Number

PLOT
837
19
1271
424
stocks
day
stock
0.0
10.0
0.0
10.0
true
true
PENS
"doc-max" 1.0 0 -13345367 true
"poc-max" 1.0 0 -10899396 true
"doc-min" 1.0 0 -8630108 true
"poc-min" 1.0 0 -13840069 true

BUTTON
611
555
735
588
NIL
import-validation
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL

BUTTON
611
607
701
640
NIL
validate-fs
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL

@#$#@#$#@
CHANGE LOG
-----------

VERS 1.1
-----------
Consolidated all flow routines in flow-carbon, this removes many comparisons that are redundant (just to gain speed). Moved comparison condition to the outside of the INPUT function.

result: this optimization improved speed 2x for 10 minutes

VERS 1.2
-----------
Removing variables set in go- routines that are just used for calculations, so we go to 2-3 'set' commands instead of 8-10 per routine (just to gain speed)

VERS 1.3
-----------
Did random stuff...please review and update 


VERS 1.4
-----------
Added temperature dependence to primary producers, need to run with temperature profile

VERS 1.5
-----------
Added Aloah's hydrograph and par import, depth scaling based on discharge from hydrograph. Removed all the output boxes that didn't really tell us anything on the left side. Another note - we took the data from CERL and needed to scale the Cartesian coordinates and the size to our map - here is the code for that since it was run as a separate procedure (see vector-convert model). The x and y lengths per patch are in feet below, resulting in a patch area size of 9524 ft^2

let x-scaler 97.57544757 ft
let y-scaler 97.61135362 ft

VERS 1.6
-----------
Big update - new flow-carbon code, finalized map import, model adjusts to discharge rates (only when it changes in range). Still need to actually use PAR, it's just being imported right now. Need to incorporate water temp import from 2004. 

VERS 1.7
-----------
Removed output function, edited input function to match new map size, removed plotting areas. Added daystorun selector and button to update picture.

VERS 1.8
-----------
BUGS: Fixed input coordinates from new maps. Rewrote import procedures since the last routines were triggering spatial oddities. Calculating max-timestep baed on max x.y vectors

VERS 1.9
-----------
Whole bunch of changes - interface set up for SA. Added sliders to tinker with scouring variables in g-macro. Set k-phyto slider. BUG FIX - had addition instead of multiplication in two equations for turbidity. Allowing an import of 90day run, allowing export of phyto & macro to text file, allowing export of all picture files every week during a run (only with GUI, not headless). Fixed the day routing, which set it at hour 12 instead of 24.

VERS 2.0
-----------
Rolled in step optimization - so we will skip slow cells and only push carbon every 4th or 8th step.
@#$#@#$#@
default
true
0
Polygon -7500403 true true 150 5 40 250 150 205 260 250

airplane
true
0
Polygon -7500403 true true 150 0 135 15 120 60 120 105 15 165 15 195 120 180 135 240 105 270 120 285 150 270 180 285 210 270 165 240 180 180 285 195 285 165 180 105 180 60 165 15

arrow
true
0
Polygon -7500403 true true 150 0 0 150 105 150 105 293 195 293 195 150 300 150

box
false
0
Polygon -7500403 true true 150 285 285 225 285 75 150 135
Polygon -7500403 true true 150 135 15 75 150 15 285 75
Polygon -7500403 true true 15 75 15 225 150 285 150 135
Line -16777216 false 150 285 150 135
Line -16777216 false 150 135 15 75
Line -16777216 false 150 135 285 75

bug
true
0
Circle -7500403 true true 96 182 108
Circle -7500403 true true 110 127 80
Circle -7500403 true true 110 75 80
Line -7500403 true 150 100 80 30
Line -7500403 true 150 100 220 30

butterfly
true
0
Polygon -7500403 true true 150 165 209 199 225 225 225 255 195 270 165 255 150 240
Polygon -7500403 true true 150 165 89 198 75 225 75 255 105 270 135 255 150 240
Polygon -7500403 true true 139 148 100 105 55 90 25 90 10 105 10 135 25 180 40 195 85 194 139 163
Polygon -7500403 true true 162 150 200 105 245 90 275 90 290 105 290 135 275 180 260 195 215 195 162 165
Polygon -16777216 true false 150 255 135 225 120 150 135 120 150 105 165 120 180 150 165 225
Circle -16777216 true false 135 90 30
Line -16777216 false 150 105 195 60
Line -16777216 false 150 105 105 60

car
false
0
Polygon -7500403 true true 300 180 279 164 261 144 240 135 226 132 213 106 203 84 185 63 159 50 135 50 75 60 0 150 0 165 0 225 300 225 300 180
Circle -16777216 true false 180 180 90
Circle -16777216 true false 30 180 90
Polygon -16777216 true false 162 80 132 78 134 135 209 135 194 105 189 96 180 89
Circle -7500403 true true 47 195 58
Circle -7500403 true true 195 195 58

circle
false
0
Circle -7500403 true true 0 0 300

circle 2
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240

cow
false
0
Polygon -7500403 true true 200 193 197 249 179 249 177 196 166 187 140 189 93 191 78 179 72 211 49 209 48 181 37 149 25 120 25 89 45 72 103 84 179 75 198 76 252 64 272 81 293 103 285 121 255 121 242 118 224 167
Polygon -7500403 true true 73 210 86 251 62 249 48 208
Polygon -7500403 true true 25 114 16 195 9 204 23 213 25 200 39 123

cylinder
false
0
Circle -7500403 true true 0 0 300

dot
false
0
Circle -7500403 true true 90 90 120

face happy
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 255 90 239 62 213 47 191 67 179 90 203 109 218 150 225 192 218 210 203 227 181 251 194 236 217 212 240

face neutral
false
0
Circle -7500403 true true 8 7 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Rectangle -16777216 true false 60 195 240 225

face sad
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 168 90 184 62 210 47 232 67 244 90 220 109 205 150 198 192 205 210 220 227 242 251 229 236 206 212 183

fish
false
0
Polygon -1 true false 44 131 21 87 15 86 0 120 15 150 0 180 13 214 20 212 45 166
Polygon -1 true false 135 195 119 235 95 218 76 210 46 204 60 165
Polygon -1 true false 75 45 83 77 71 103 86 114 166 78 135 60
Polygon -7500403 true true 30 136 151 77 226 81 280 119 292 146 292 160 287 170 270 195 195 210 151 212 30 166
Circle -16777216 true false 215 106 30

flag
false
0
Rectangle -7500403 true true 60 15 75 300
Polygon -7500403 true true 90 150 270 90 90 30
Line -7500403 true 75 135 90 135
Line -7500403 true 75 45 90 45

flower
false
0
Polygon -10899396 true false 135 120 165 165 180 210 180 240 150 300 165 300 195 240 195 195 165 135
Circle -7500403 true true 85 132 38
Circle -7500403 true true 130 147 38
Circle -7500403 true true 192 85 38
Circle -7500403 true true 85 40 38
Circle -7500403 true true 177 40 38
Circle -7500403 true true 177 132 38
Circle -7500403 true true 70 85 38
Circle -7500403 true true 130 25 38
Circle -7500403 true true 96 51 108
Circle -16777216 true false 113 68 74
Polygon -10899396 true false 189 233 219 188 249 173 279 188 234 218
Polygon -10899396 true false 180 255 150 210 105 210 75 240 135 240

house
false
0
Rectangle -7500403 true true 45 120 255 285
Rectangle -16777216 true false 120 210 180 285
Polygon -7500403 true true 15 120 150 15 285 120
Line -16777216 false 30 120 270 120

leaf
false
0
Polygon -7500403 true true 150 210 135 195 120 210 60 210 30 195 60 180 60 165 15 135 30 120 15 105 40 104 45 90 60 90 90 105 105 120 120 120 105 60 120 60 135 30 150 15 165 30 180 60 195 60 180 120 195 120 210 105 240 90 255 90 263 104 285 105 270 120 285 135 240 165 240 180 270 195 240 210 180 210 165 195
Polygon -7500403 true true 135 195 135 240 120 255 105 255 105 285 135 285 165 240 165 195

line
true
0
Line -7500403 true 150 0 150 300

line half
true
0
Line -7500403 true 150 0 150 150

pentagon
false
0
Polygon -7500403 true true 150 15 15 120 60 285 240 285 285 120

person
false
0
Circle -7500403 true true 110 5 80
Polygon -7500403 true true 105 90 120 195 90 285 105 300 135 300 150 225 165 300 195 300 210 285 180 195 195 90
Rectangle -7500403 true true 127 79 172 94
Polygon -7500403 true true 195 90 240 150 225 180 165 105
Polygon -7500403 true true 105 90 60 150 75 180 135 105

plant
false
0
Rectangle -7500403 true true 135 90 165 300
Polygon -7500403 true true 135 255 90 210 45 195 75 255 135 285
Polygon -7500403 true true 165 255 210 210 255 195 225 255 165 285
Polygon -7500403 true true 135 180 90 135 45 120 75 180 135 210
Polygon -7500403 true true 165 180 165 210 225 180 255 120 210 135
Polygon -7500403 true true 135 105 90 60 45 45 75 105 135 135
Polygon -7500403 true true 165 105 165 135 225 105 255 45 210 60
Polygon -7500403 true true 135 90 120 45 150 15 180 45 165 90

square
false
0
Rectangle -7500403 true true 30 30 270 270

square 2
false
0
Rectangle -7500403 true true 30 30 270 270
Rectangle -16777216 true false 60 60 240 240

star
false
0
Polygon -7500403 true true 151 1 185 108 298 108 207 175 242 282 151 216 59 282 94 175 3 108 116 108

target
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240
Circle -7500403 true true 60 60 180
Circle -16777216 true false 90 90 120
Circle -7500403 true true 120 120 60

tree
false
0
Circle -7500403 true true 118 3 94
Rectangle -6459832 true false 120 195 180 300
Circle -7500403 true true 65 21 108
Circle -7500403 true true 116 41 127
Circle -7500403 true true 45 90 120
Circle -7500403 true true 104 74 152

triangle
false
0
Polygon -7500403 true true 150 30 15 255 285 255

triangle 2
false
0
Polygon -7500403 true true 150 30 15 255 285 255
Polygon -16777216 true false 151 99 225 223 75 224

truck
false
0
Rectangle -7500403 true true 4 45 195 187
Polygon -7500403 true true 296 193 296 150 259 134 244 104 208 104 207 194
Rectangle -1 true false 195 60 195 105
Polygon -16777216 true false 238 112 252 141 219 141 218 112
Circle -16777216 true false 234 174 42
Rectangle -7500403 true true 181 185 214 194
Circle -16777216 true false 144 174 42
Circle -16777216 true false 24 174 42
Circle -7500403 false true 24 174 42
Circle -7500403 false true 144 174 42
Circle -7500403 false true 234 174 42

turtle
true
0
Polygon -10899396 true false 215 204 240 233 246 254 228 266 215 252 193 210
Polygon -10899396 true false 195 90 225 75 245 75 260 89 269 108 261 124 240 105 225 105 210 105
Polygon -10899396 true false 105 90 75 75 55 75 40 89 31 108 39 124 60 105 75 105 90 105
Polygon -10899396 true false 132 85 134 64 107 51 108 17 150 2 192 18 192 52 169 65 172 87
Polygon -10899396 true false 85 204 60 233 54 254 72 266 85 252 107 210
Polygon -7500403 true true 119 75 179 75 209 101 224 135 220 225 175 261 128 261 81 224 74 135 88 99

wheel
false
0
Circle -7500403 true true 3 3 294
Circle -16777216 true false 30 30 240
Line -7500403 true 150 285 150 15
Line -7500403 true 15 150 285 150
Circle -7500403 true true 120 120 60
Line -7500403 true 216 40 79 269
Line -7500403 true 40 84 269 221
Line -7500403 true 40 216 269 79
Line -7500403 true 84 40 221 269

x
false
0
Polygon -7500403 true true 270 75 225 30 30 225 75 270
Polygon -7500403 true true 30 75 75 30 270 225 225 270

@#$#@#$#@
NetLogo 4.1.2
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
<experiments>
  <experiment name="kphyto-01" repetitions="1" runMetricsEveryStep="false">
    <setup>setup</setup>
    <go>go</go>
    <final>export-fs day
export-color day</final>
    <exitCondition>day &gt;= DaysToRun</exitCondition>
    <enumeratedValueSet variable="fixedTemp">
      <value value="20"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedPAR">
      <value value="2000"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="which-stock?">
      <value value="&quot;macro&quot;"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="exportPics?">
      <value value="false"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="k-macro">
      <value value="0.01"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="sen-macro-coef">
      <value value="0.08"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="TSS">
      <value value="0.24"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="DaysToRun">
      <value value="90"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="Import-Day90?">
      <value value="false"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedEnvironmentals?">
      <value value="true"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedHydro">
      <value value="1"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-mass-max">
      <value value="1000"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-base-temp">
      <value value="19.7"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="k-phyto">
      <value value="0.01"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="gross-macro-coef">
      <value value="0.08"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-vel-max">
      <value value="1"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="resp-macro-coef">
      <value value="0.04"/>
    </enumeratedValueSet>
  </experiment>
  <experiment name="kphyto-001" repetitions="1" runMetricsEveryStep="false">
    <setup>setup</setup>
    <go>go</go>
    <final>export-fs day
export-color day</final>
    <exitCondition>day &gt;= DaysToRun</exitCondition>
    <enumeratedValueSet variable="fixedTemp">
      <value value="20"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedPAR">
      <value value="2000"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="which-stock?">
      <value value="&quot;macro&quot;"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="exportPics?">
      <value value="false"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="k-macro">
      <value value="0.01"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="sen-macro-coef">
      <value value="0.08"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="TSS">
      <value value="0.24"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="DaysToRun">
      <value value="90"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="Import-Day90?">
      <value value="false"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedEnvironmentals?">
      <value value="true"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedHydro">
      <value value="1"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-mass-max">
      <value value="1000"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-base-temp">
      <value value="19.7"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="k-phyto">
      <value value="0.0010"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="gross-macro-coef">
      <value value="0.08"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-vel-max">
      <value value="1"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="resp-macro-coef">
      <value value="0.04"/>
    </enumeratedValueSet>
  </experiment>
  <experiment name="kphyto-0001" repetitions="1" runMetricsEveryStep="false">
    <setup>setup</setup>
    <go>go</go>
    <final>export-fs day
export-color day</final>
    <exitCondition>day &gt;= DaysToRun</exitCondition>
    <enumeratedValueSet variable="fixedTemp">
      <value value="20"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedPAR">
      <value value="2000"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="which-stock?">
      <value value="&quot;macro&quot;"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="exportPics?">
      <value value="false"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="k-macro">
      <value value="0.01"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="sen-macro-coef">
      <value value="0.08"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="TSS">
      <value value="0.24"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="DaysToRun">
      <value value="90"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="Import-Day90?">
      <value value="false"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedEnvironmentals?">
      <value value="true"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedHydro">
      <value value="1"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-mass-max">
      <value value="1000"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-base-temp">
      <value value="19.7"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="k-phyto">
      <value value="1.0E-4"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="gross-macro-coef">
      <value value="0.08"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-vel-max">
      <value value="1"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="resp-macro-coef">
      <value value="0.04"/>
    </enumeratedValueSet>
  </experiment>
  <experiment name="kmacro-01" repetitions="1" runMetricsEveryStep="false">
    <setup>setup</setup>
    <go>go</go>
    <final>export-fs day
export-color day</final>
    <exitCondition>day &gt;= DaysToRun</exitCondition>
    <enumeratedValueSet variable="fixedTemp">
      <value value="20"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedPAR">
      <value value="2000"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="which-stock?">
      <value value="&quot;macro&quot;"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="exportPics?">
      <value value="false"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="k-macro">
      <value value="0.01"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="sen-macro-coef">
      <value value="0.08"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="TSS">
      <value value="0.24"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="DaysToRun">
      <value value="90"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="Import-Day90?">
      <value value="false"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedEnvironmentals?">
      <value value="true"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedHydro">
      <value value="1"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-mass-max">
      <value value="1000"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-base-temp">
      <value value="19.7"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="k-phyto">
      <value value="0.01"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="gross-macro-coef">
      <value value="0.08"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-vel-max">
      <value value="1"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="resp-macro-coef">
      <value value="0.04"/>
    </enumeratedValueSet>
  </experiment>
  <experiment name="kmacro-001" repetitions="1" runMetricsEveryStep="false">
    <setup>setup</setup>
    <go>go</go>
    <final>export-fs day
export-color day</final>
    <exitCondition>day &gt;= DaysToRun</exitCondition>
    <enumeratedValueSet variable="fixedTemp">
      <value value="20"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedPAR">
      <value value="2000"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="which-stock?">
      <value value="&quot;macro&quot;"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="exportPics?">
      <value value="false"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="k-macro">
      <value value="0.0010"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="sen-macro-coef">
      <value value="0.08"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="TSS">
      <value value="0.24"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="DaysToRun">
      <value value="90"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="Import-Day90?">
      <value value="false"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedEnvironmentals?">
      <value value="true"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedHydro">
      <value value="1"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-mass-max">
      <value value="1000"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-base-temp">
      <value value="19.7"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="k-phyto">
      <value value="0.01"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="gross-macro-coef">
      <value value="0.08"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-vel-max">
      <value value="1"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="resp-macro-coef">
      <value value="0.04"/>
    </enumeratedValueSet>
  </experiment>
  <experiment name="kmacro-0001" repetitions="1" runMetricsEveryStep="false">
    <setup>setup</setup>
    <go>go</go>
    <final>export-fs day
export-color day</final>
    <exitCondition>day &gt;= DaysToRun</exitCondition>
    <enumeratedValueSet variable="fixedTemp">
      <value value="20"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedPAR">
      <value value="2000"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="which-stock?">
      <value value="&quot;macro&quot;"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="exportPics?">
      <value value="false"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="k-macro">
      <value value="1.0E-4"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="sen-macro-coef">
      <value value="0.08"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="TSS">
      <value value="0.24"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="DaysToRun">
      <value value="90"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="Import-Day90?">
      <value value="false"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedEnvironmentals?">
      <value value="true"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="fixedHydro">
      <value value="1"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-mass-max">
      <value value="1000"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-base-temp">
      <value value="19.7"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="k-phyto">
      <value value="0.01"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="gross-macro-coef">
      <value value="0.08"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="macro-vel-max">
      <value value="1"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="resp-macro-coef">
      <value value="0.04"/>
    </enumeratedValueSet>
  </experiment>
</experiments>
@#$#@#$#@
@#$#@#$#@
default
0.0
-0.2 0 0.0 1.0
0.0 1 1.0 0.0
0.2 0 0.0 1.0
link direction
true
0
Line -7500403 true 150 150 90 180
Line -7500403 true 150 150 210 180

@#$#@#$#@
0
@#$#@#$#@
