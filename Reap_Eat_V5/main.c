#include "SCH_Tasks.h"
#include "SYS_Initialize.h"

int main(void)
{
#define DEBUG_OUTPUT

    SYS_Init();
   // HW_Cooler_On();
    BIOS_start();

    return (0);
}
