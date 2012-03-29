#include "pred.h"


/**
 * Predicts the new phyto value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_phyto(int x, int y)
{
	patches[x][y].phyto = patches[x][y].phyto + patches[x][y].growth_phyto - patches[x][y].herbivore_pred_phyto;

	if (patches[x][y].phyto < 0.001)
	{
		patches[x][y].phyto = 0.001;
	}
}


/**
 * Predicts the new herbivore value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_herbivore(int x, int y)
{
	patches[x][y].herbivore = patches[x][y].herbivore + patches[x][y].herbivore_ingest_phyto + patches[x][y].herbivore_ingest_peri + patches[x][y].herbivore_ingest_waterdecomp 
                              - (patches[x][y].herbivore_respiration + patches[x][y].herbivore_excretion + patches[x][y].herbivore_senescence) - patches[x][y].consum_pred_herbivore;

	if (patches[x][y].herbivore < 0.001)
	{
		patches[x][y].herbivore = 0.001;
	}
}


/**
 * Predicts the new seddecomp value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_seddecomp(int x, int y)
{
	patches[x][y].seddecomp = patches[x][y].seddecomp + patches[x][y].seddecomp_ingest_detritus 
                              - (patches[x][y].seddecomp_respiration + patches[x][y].seddecomp_excretion + patches[x][y].seddecomp_senescence) - patches[x][y].sedconsumer_pred_seddecomp;

	if (patches[x][y].seddecomp < 0.001)
	{
		patches[x][y].seddecomp = 0.001;
	}
}


/**
 * Predicts the new waterdecomp value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_waterdecomp(int x, int y)
{
	patches[x][y].waterdecomp = patches[x][y].waterdecomp + patches[x][y].waterdecomp_ingest_doc + patches[x][y].waterdecomp_ingest_poc 
                                - (patches[x][y].waterdecomp_respiration + patches[x][y].waterdecomp_excretion + patches[x][y].waterdecomp_senescence) - patches[x][y].herbivore_pred_waterdecomp;

	if (patches[x][y].waterdecomp < 0.001)
	{
		patches[x][y].waterdecomp = 0.001;
	}
}


/**
 * Predicts the new sedconsumer value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_sedconsumer(int x, int y)
{
	patches[x][y].sedconsumer = patches[x][y].sedconsumer + patches[x][y].sedconsumer_ingest_peri + patches[x][y].sedconsumer_ingest_seddecomp 
                                - (patches[x][y].sedconsumer_respiration + patches[x][y].sedconsumer_excretion + patches[x][y].sedconsumer_senescence) - patches[x][y].consum_pred_sedconsumer;

	if (patches[x][y].sedconsumer < 0.001)
	{
		patches[x][y].sedconsumer = 0.001;
	}

}


/**
 * Predicts the new detritus value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_detritus(int x, int y)
{
	patches[x][y].detritus_POC_transfer = patches[x][y].detritus * (0.25 * log10(patches[x][y].velocity / 40.0 + 0.01) + 0.5);
	
	patches[x][y].detritus = patches[x][y].detritus + patches[x][y].detritus_growth - patches[x][y].seddecomp_pred_detritus - patches[x][y].detritus_POC_transfer;

	if (patches[x][y].detritus < 0.001)
	{
		patches[x][y].detritus = 0.001;
	}
}


/**
 * Predicts the new DOC value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_DOC(int x, int y)
{
	patches[x][y].DOC = patches[x][y].DOC + patches[x][y].DOC_growth - patches[x][y].waterdecomp_pred_doc - patches[x][y].flocculation;

	if (patches[x][y].DOC < 0.001)
	{
		patches[x][y].DOC = 0.001;
	}
}


/**
 * Predicts the new POC value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_POC(int x, int y)
{
	patches[x][y].POC = patches[x][y].POC + patches[x][y].POC_growth - patches[x][y].waterdecomp_pred_poc - patches[x][y].POC_detritus_transfer;

	if (patches[x][y].POC < 0.001)
	{
		patches[x][y].POC = 0.001;
	}
}


/**
 * Predicts the new consum value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_consum(int x, int y)
{
	patches[x][y].consum = patches[x][y].consum + patches[x][y].consum_ingest_herbivore + patches[x][y].consum_ingest_sedconsumer 
                           - (patches[x][y].consum_respiration + patches[x][y].consum_excretion + patches[x][y].consum_senescence);

	if (patches[x][y].consum < 0.001)
	{
		patches[x][y].consum = 0.001;
	}
}

