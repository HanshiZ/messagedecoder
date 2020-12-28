#ifndef _DECODER_H
#define _DECODER_H

/*
 * Header file with the prototypes for decoder main
 * Author : Hanshi Zuo
 */

int byteToDec (const char* binary);

void refresher(char * bindata);

void decoder(const char *encoded, char *decoded, int maxLen);

#endif

