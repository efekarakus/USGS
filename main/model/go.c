#include "go.h"

/**
 * This function runs the model
 */
void go()
{


}


/**
 * Updates the environmental variables (Primary macrophyte routine)
 *
 * NOTE: NEED TO IMPLEMENT "UPDATE-HYDRO-MAP" AND "CHOOSE-HYDRO-MAP"
 */
void update_environmentals()
{
	if (hours % 24 == 0)	// Updates daily
	{
		update_discharge();	// Pulls a new discharge from a text file
		//choose_hydro_map();	// Chooses a new hydro map based on the discharge
		if (hydro_changed == 1)
		{
			//update_hydro_map();	// Updates a new hydro map based on the discharge
		}
	}

	if (hours % 168 == 0)	// Updates weekly
	{
		update_temp();	// Updates to a new water temperature
	}

	update_par()	// Updates hourly to a new photosynthetic radiation value
}


/**
 * Updates the temperature variable
 */
void update_temp()
{
	// Doesn't make sense
}

/**
 * Updates the photosynthetic radiation variable
 */
void update_par()
{
	// Doesn't make sense
}

/**
 * Updates the discharge variable
 */
void update_discharge()
{


}
 */
