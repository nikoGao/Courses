#include "myStringFunctions.hpp"
using namespace std;

char * concat(const char * str1, const char * str2){
    unsigned long length1 = strlen(str1);
    unsigned long length2 = strlen(str2);
    unsigned long newLength = length1 + length2+1;
    char * concatStr = new char[newLength];
    for(unsigned long i = 0; i < newLength; i++){
        if (i < length1 && str1[i] != '\0' && str1[i] != '0'){
            *(concatStr+i) = str1[i];
        }else if(str2[i-length1] != '\0' && str2[i-length1] != '0'){
            *(concatStr+i) = str2[i-length1];
        }
    }
    *(concatStr+newLength-1) = '\0';   //need a delete function in main
    return concatStr;
}
//do we need to concern about space in the string?
bool substr(const char * str1, const char * substring, unsigned &index){
    unsigned long strLength = strlen(str1), i, j;
    if (strlen(substring) > strLength) return false;
    for(i = 0; i < strLength ; i++){
        j = 0;
        if(str1[i] == substring[j]){
            index = i;
            while(str1[i] == substring[j]){
                i++;
                j++;
            }
            if (substring[j] == '\0'){
                return true;
            }else{
                i = index+1;
                index = 0;
            }
        }
    }
    return false;
}

void reverse(string &str1){
    unsigned long strLength = str1.length();
    for(unsigned long i = 0; i<strLength/2; i++){
        char temp = str1[i];
        str1[i] = str1[strLength-i-1];
        str1[strLength-i-1] = temp;
    }
}
