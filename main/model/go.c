#include "go.h"
#include "globals.h"
#include "math.h"

/**
 * This function runs the model
 */
void go()
{
	if (fixed_environmentals == 0)
	{
		update_environmentals();	// This is flagged to run every 24 hours in the function
	}

	else 
	{
		if (sin((hours - 6) * (360 / 24)) <= 0)	// This is a sinusoidal wave to fluctuate PAS rom 0
		{
			photo_radiation = 0;
		}

		else
		{
			photo_radiation = gui_photo_radiation * sin((hours - 6) * (360 / 24));
		}
	}


	// Ask patches HERE
	update_patches(0, 0);
}


/**
 * Updates the environmental variables (Primary macrophyte routine)
 *
 * NOTE: NEED TO IMPLEMENT "UPDATE-HYDRO-MAP" AND "CHOOSE-HYDRO-MAP"
 */
void update_environmentals()
{
	if ((hours % 24) == 0)	// Updates daily
	{
		update_discharge();	// Pulls next discharge from a data array
		//choose_hydro_map();	// Chooses a new hydro map based on the discharge
		if (hydro_changed == 1)
		{
			//update_hydro_map();	// Updates a new hydro map based on the discharge
		}
	}

	if ((hours % 168) == 0)	// Updates weekly
	{
		update_temp();	// Updates to a new water temperature
	}

	update_par();	// Updates hourly to a new photosynthetic radiation value
}


/**
 * Updates the temperature variable
 */
void update_temp()
{
	temperature_index++;
	temperature = temperature_data[temperature_index];
	temperature = temperature - ((temperature - 17) * temp_dif);
}

/**
 * Updates the photosynthetic radiation variable
 */
void update_par()
{
	photo_radiation_index++;
	photo_radiation = photo_radiation_data[photo_radiation_index];
	photo_radiation = photo_radiation - (photo_radiation * par_dif);
}

/**
 * Updates the discharge variable
 */
void update_discharge()
{
	discharge_index++;
	discharge = discharge_data[discharge_index];
} 
