#include "decoder.h"
#include <string.h>

/**
 * File: decoder.c
 * Author: Hanshi Zuo
 * Implematation with definintions for functions
 * and const variables
 * 
 */


/// below are the codes and corresponding keys
const char * code = "XAfbPDNgK$5m";
const char * key[] = 
{
  "000","001", "010", "011", "100",
  "101", "110", "111", "00", "01","10","11"
};

/// const variables that help with readability
const int charSize = sizeof(char);
const int Byte = 8;

/**
 * Function that takes a bit and returns
 * its interger value in decimal
 * @ parameter is the binary bit string
 * \ return is the integer representation
 */

int byteToDec (const char* binary)
{  
   int sum=0;
   for (int count = 0 ; count < Byte ; count++)
   {  sum *= 2;
      if (*(binary + count) == '1')
	 ++sum;
   }
   return sum;
}


/**
 * Reset the temporary byte so that it is ready
 * for future inputs 
 * @ param bindata is the char * to be reset
 */

void refresher(char * bindata)
{   
    /// moving the extra stuff at the end to the beginning
    memmove(bindata, bindata+Byte, 2*charSize);
    /// seting remain bytes to zero 
    memset(bindata+2,0, Byte*charSize);
}

/**
 * Decode an encoded string into a character stream.
 * @param encoded The input string we are decoding
 * @param decoded The output string we produce
 * @param maxLen The maximum size for decoded
 */

void decoder(const char *encoded, char *decoded, int maxLen)
{  /* counter for characters, temp string and 
      and a place indicator within temp string */

   int charCount = 0;   
   char temp[10] = {0};
   /* note that temp is not a string, just a char array
      since no string functions are used on it and it saves
      space as a max of 10 spaces is needed for overflow instead of 
      11 (7+3 =10)
    */
   int tempPlace = 0;
   
   /*
      maxLen is used here, note that charCount + 1 < maxLen since one space
      for 0 at end
    */

   for (; charCount+1 < maxLen && *(encoded); )
   {   const int threeBitMax = 8;
       /// location in code corresponds to key
       int keyNum = strchr(code ,*(encoded++) ) - code;
      
       if (keyNum < threeBitMax)
       {   /// this case deals with the keys with three bits
           memcpy(temp+tempPlace, key[keyNum] ,3*charSize);
           tempPlace = tempPlace + 3;
       }
       
       else           
       {  /// this is the 2 bit case 
          memcpy(temp+tempPlace, key[keyNum] ,2*charSize);
          tempPlace = tempPlace + 2;
       }
       
       if (tempPlace >= Byte)
       {   /// deals with the need to convert to a char
          
           decoded[charCount++] = (char) byteToDec(temp);
           /// reseting temp and the tempPlace varible
           refresher(temp);
           tempPlace = tempPlace-Byte;
       }

   } 
   decoded[charCount] = 0; /// 0 termination
}


