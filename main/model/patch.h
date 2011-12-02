#ifndef _PATCH
#define _PATCH

#include "list.h"

void update_patches();

void go_macro();

void go_phyto();

void go_herbivore();

void go_waterdecomp();

void go_seddecomp();

void go_consum();

void go_DOC();

void go_POC();

void go_detritus();

void pred_phyto();

void pred_herbivore();

void pred_seddecomp();

void pred_waterdecomp();

void pred_sedconsumer();

void pred_detritus();

void pred_DOC();

void pred_POC();

void pred_consum();

typedef struct _patch {

	/* Build_in patch variables by netlogo */
	int pxcor;  ///< the x_coordinate for the patch
	int pycor;  ///< the y_coordinate for the patch
	int pcolor; ///< the rgb_value for the patch
	
	/* Extra patch variables that were added by Scientists */
	double px_vector;     ///< flow vector in the x_direction for hydraulics
	List pxv_list;        ///< list of x_flow vectors
	double py_vector;     ///< flow vector in the y_direction for hydraulics
	List pyv_list;        ///< list of y_flow vectors
	double max_vector;    ///< largest flow vector
	double depth;         ///< depth of an individual cell
	List depth_list;      ///< all the depths in the different hydraulic datasets
	double current_depth; ///< depth in the previous time_step
	double velocity;      ///< the rate of flow for hydraulics
	List v_list;          ///< list of velocities
	int aqa_point;        ///< biomass estimates of macro from USGS
	short cell_type;      ///< 0 for "output", 1 for "input"

	double waterdecomp_doc_prey_limitation;       ///< NOT AVAILABLE
	double waterdecomp_poc_prey_limitation;       ///< NOT AVAILABLE
	double peri_doc_prey_limitation;              ///< NOT AVAILABLE
	double peri_poc_prey_limitation;              ///< NOT AVAILABLE
	double seddecomp_detritus_prey_limitation;    ///< NOT AVAILABLE
	double herbivore_phyto_prey_limitation;       ///< NOT AVAILABLE
	double herbivore_waterdecomp_prey_limitation; ///< NOT AVAILABLE
	double herbivore_peri_prey_limitation;        ///< NOT AVAILABLE
	double sedconsumer_seddecomp_prey_limitation; ///< NOT AVAILABLE
	double sedconsumer_peri_prey_limitation;      ///< NOT AVAILABLE
	double sedconsumer_detritus_prey_limitation;  ///< NOT AVAILABLE
	double consum_herbivore_prey_limitation;      ///< NOT AVAILABLE
	double consum_sedconsumer_prey_limitation;    ///< NOT AVAILABLE

	double peri_space_limitation;           ///< NOT AVAILABLE
	double waterdecomp_space_limitation;    ///< NOT AVAILABLE
	double seddecomp_space_limitation;      ///< NOT AVAILABLE
	double herbivore_space_limitation;      ///< NOT AVAILABLE
	double sedconsumer_space_limitation;    ///< NOT AVAILABLE
	double consum_space_limitation;         ///< NOT AVAILABLE

	int assimilation;                       ///< NOT AVAILABLE
	int detritus;                           ///< NOT AVAILABLE
	int DOC;                                ///< NOT AVAILABLE
	int POC;                                ///< NOT AVAILABLE
	int waterdecomp;                        ///< NOT AVAILABLE
	int seddecomp;                          ///< NOT AVAILABLE
	int macro;                              ///< NOT AVAILABLE
	int phyto;                              ///< NOT AVAILABLE
	int herbivore;                          ///< NOT AVAILABLE
	int sedconsumer;                        ///< NOT AVAILABLE
	int peri;                               ///< NOT AVAILABLE
	int consum;                             ///< NOT AVAILABLE
	double bottom_light;                    ///< par that reaches the bottom of the river
	int consumer;                           ///< consumers in the water column, such as fish
	double consum_consumption;              ///< NOT AVAILABLE
	double consum_ingest_herbivore;         ///< NOT AVAILABLE
	double consum_pred_herbivore;           ///< NOT AVAILABLE
	double consum_ingest_sedconsumer;       ///< NOT AVAILABLE
	double consum_pred_sedconsumer;         ///< NOT AVAILABLE
	double consum_excretion;                ///< NOT AVAILABLE
	double consum_sda;                      ///< NOT AVAILABLE
	double consum_senescence;               ///< NOT AVAILABLE
	double consum_respiration;              ///< NOT AVAILABLE
	double consum_growth;                   ///< NOT AVAILABLE
	double detritus_growth;                 ///< NOT AVAILABLE
	double detritus_POC_transfer;           ///< the amount of carbon that transfers from detritus to POC
	double seddecomp_pred_detritus;         ///< NOT AVAILABLE
	double sedconsumer_pred_detritus;       ///< NOT AVAILABLE
	double direction;                       ///< the direction carbon flows
	double DOC_growth;                      ///< NOT AVAILABLE
	double DOC_pred;                        ///< NOT AVAILABLE
	double egestion;                        ///< NOT AVAILABLE
	double excretion;                       ///< NOT AVAILABLE
	double excretion_phyto;                 ///< NOT AVAILABLE
	double flocculation;                    ///< the act of DOC sticking together to create POC
	double gross_photo;                     ///< NOT AVAILABLE
	double gross_photo_macro;               ///< photosynthesis of macrophytes
	double gross_photo_phyto;               ///< photosythesis of phytoplankton
	double growth_herbivore;                ///< NOT AVAILABLE
	double growth_detritus;                 ///< NOT AVAILABLE
	double growth_macro;                    ///< NOT AVAILABLE
	double growth_sedconsumer;              ///< NOT AVAILABLE
	double growth_phyto;                    ///< NOT AVAILABLE
	double growth_waterdecomp;              ///< NOT AVAILABLE
	double herbivore_consumption;           ///< NOT AVAILABLE
	double herbivore_ingest_peri;           ///< NOT AVAILABLE
	double herbivore_pred_peri;             ///< NOT AVAILABLE
	double herbivore_ingest_phyto;          ///< NOT AVAILABLE
	double herbivore_pred_phyto;            ///< NOT AVAILABLE
	double herbivore_ingest_waterdecomp;    ///< NOT AVAILABLE
	double herbivore_pred_waterdecomp;      ///< NOT AVAILABLE
	double herbivore_excretion;             ///< NOT AVAILABLE
	double herbivore_sda;                   ///< NOT AVAILABLE
	double herbivore_senescence;            ///< NOT AVAILABLE
	double herbivore_respiration;           ///< NOT AVAILABLE
	double herbivore_growth;                ///< NOT AVAILABLE
	double K;                               ///< carrying capacity
	double large_death;                     ///< death of large_sized trophic groups
	double light;                           ///< NOT AVAILABLE
	double light_k;                         ///< attenuation coefficient of phytoplankon
	double macro_death;                     ///< NOT AVAILABLE
	double macro_exudation;                 ///< amount of photosynthetic material released
	double micro_death;                     ///< amount of dead plant material that becomes DOC
	double phyto_maximum_growth_rate;       ///< NOT AVAILABLE
	double phyto_pred;                      ///< NOT AVAILABLE
	double POC_detritus_transfer;           ///< the amount of carbon that transfers from detritus to POC
	double POC_growth;                      ///< NOT AVAILABLE
	double POC_pred;                        ///< NOT AVAILABLE
	double phyto_density;                   ///< NOT AVAILABLE
	double peri_ingest_doc;                 ///< NOT AVAILABLE
	double peri_pred_doc;                   ///< NOT AVAILABLE
	double peri_ingest_poc;                 ///< NOT AVAILABLE
	double peri_pred_poc;                   ///< NOT AVAILABLE
	double peri_respiration;                ///< NOT AVAILABLE
	double peri_excretion;                  ///< NOT AVAILABLE
	double peri_senescence;                 ///< NOT AVAILABLE
	double senescence;                      ///< death
	double scouring;                        ///< NOT AVAILABLE
	double small_death;                     ///< amount of dead plant material that becomes POC
	double respiration;                     ///< NOT AVAILABLE
	double respiration_macro;               ///< NOT AVAILABLE
	double respiration_phyto;               ///< NOT AVAILABLE
	double scouring_macro;                  ///< NOT AVAILABLE
	double sedconsumer_ingest_peri;         ///< NOT AVAILABLE
	double sedconsumer_pred_peri;           ///< NOT AVAILABLE
	double senescence_macro;                ///< NOT AVAILABLE
	double senescence_phyto;                ///< NOT AVAILABLE
	double sedconsumer_consumption;         ///< NOT AVAILABLE
	double sedconsumer_ingest_detritus;     ///< NOT AVAILABLE
	double sedconsumer_ingest_seddecomp;    ///< NOT AVAILABLE
	double sedconsumer_pred_seddecomp;      ///< NOT AVAILABLE
	double sedconsumer_excretion;           ///< NOT AVAILABLE
	double sedconsumer_egestion;            ///< NOT AVAILABLE
	double sedconsumer_senescence;          ///< NOT AVAILABLE
	double sedconsumer_respiration;         ///< NOT AVAILABLE
	double sedconsumer_growth;              ///< NOT AVAILABLE
	double seddecomp_consumption;           ///< NOT AVAILABLE
	double seddecomp_ingest_detritus;       ///< NOT AVAILABLE
	double seddecomp_excretion;             ///< NOT AVAILABLE
	double seddecomp_growth;                ///< NOT AVAILABLE
	double seddcomp_ingest_peri;            ///< NOT AVAILABLE
	double seddecomp_pred_peri;             ///< NOT AVAILABLE
	double seddecomp_respiration;           ///< NOT AVAILABLE
	double seddecomp_senescence;            ///< NOT AVAILABLE
	double velpoc;                          ///< velocity used for poc_to_detritus transfer equation
	double waterdecomp_consumption;         ///< NOT AVAILABLE
	double waterdecomp_ingest_doc;          ///< NOT AVAILABLE
	double waterdecomp_sda;                 ///< NOT AVAILABLE
	double waterdecomp_excretion;           ///< NOT AVAILABLE
	double waterdecomp_ingest_poc;          ///< NOT AVAILABLE
	double waterdecomp_pred_doc;            ///< NOT AVAILABLE
	double waterdecomp_pred_poc;            ///< NOT AVAILABLE
	double waterdecomp_respiration;         ///< NOT AVAILABLE
	double waterdecomp_senescence;          ///< NOT AVAILABLE
	double turbidity;                       ///< metric of suspended solids in water column
} patch;

#endif 
