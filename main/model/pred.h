#ifndef _PRED
#define _PRED


/**
 * Predicts the new phyto value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_phyto(int x, int y);


/**
 * Predicts the new herbivore value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_herbivore(int x, int y);


/**
 * Predicts the new seddecomp value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_seddecomp(int x, int y);


/**
 * Predicts the new waterdecomp value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_waterdecomp(int x, int y);


/**
 * Predicts the new sedconsumer of the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_sedconsumer(int x, int y);


/**
 * Predicts the new detritus value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_detritus(int x, int y);


/**
 * Predicts the new DOC value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_DOC(int x, int y);


/**
 * Predicts the new POC value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_POC(int x, int y);


/**
 * Predicts the new consum value in the patch
 * @param x x-coord of the patch
 * @param y y-coord of the patch
 */
void pred_consum(int x, int y);
#endif
