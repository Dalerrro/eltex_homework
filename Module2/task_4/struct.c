#include <stdlib.h>
#include <stdio.h>
#include <stdalign.h>
#include <stddef.h>

// pragma pack(push, 1)
struct Person {
     char Name[20];         /*    0     20 */
     char Surname[40];      /*    20    40 */
     int age;               /*    60     4 */
     double GPA;            /*    64     8 */
     int phoneNumber[10];   /*    72    40 */
}a;
// pragma pack(loc)

struct CompressedPerson {
    double GPA;             /*     0     8 */
    int age;                /*     8     4 */
    int phoneNumber[10];    /*    12    40 */
    char Name[20];          /*    52    20 */ 
    char Surname[40];       /*    72    40 */  
} b;

int main(){
    
    printf("Sizeof Person = %ld\n", sizeof(a));
    printf("Alignof Person  = %ld\n", alignof(a));

    printf("Sizeof Person = %ld\n", sizeof(b));
    printf("Alignof Person  = %ld\n", alignof(b));


    return 0;
}