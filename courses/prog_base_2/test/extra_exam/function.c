#include <stdlib.h>


int findWordsInString(const char * string){
    if(string == NULL)return 0;
    int wordsCount = 0, stringSize, inWord = 0;
    stringSize = strlen(string);
    for(int n = 0; n < stringSize; n++){
        if(isalpha(string[n])){
            inWord = 1;
        }else{
            if(inWord == 1)wordsCount++;
            inWord = 0;
        }
    }
    if(inWord == 1)wordsCount++;
    return wordsCount;
}
