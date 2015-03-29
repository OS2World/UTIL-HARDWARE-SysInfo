#define INCL_DOSMISC
#define INCL_DOSERRORS
#include <os2.h>
#include <stdio.h>

void main(void)
{
  int iStart=1, iLast=QSV_MAX, Buf[QSV_MAX+1], BufSize=QSV_MAX*sizeof(ULONG), Major, Minor, processoren;
  int dagen, uren, minuten, secondes, milisecondes;
  APIRET rc;
  rc=DosQuerySysInfo(iStart, iLast, Buf, BufSize);
  printf("SysInfo 1.0\n");
  printf("Copyright 1999 by D.J. van Enckevort\n");
  switch (Buf[QSV_VERSION_MINOR-1])
     {
     case 0:
        Major=2; Minor=0;
        break;
     case 10:
        Major=2; Minor=1;
        break;
     case 11:
        Major=2; Minor=11;
        break;
     case 30:
        Major=3; Minor=0;
        break;
     case 40:
        Major=4; Minor=0;
        break;
     default:
        Major=Buf[QSV_VERSION_MINOR-1]/10; Minor=Buf[QSV_VERSION_MINOR-1]%10;
        break;
     }
  printf("\nOS/2 version is %u.%u revision %u\n", Major, Minor, Buf[QSV_VERSION_REVISION-1]);
  printf("The bootdrive is: %c\n", (char)Buf[QSV_BOOT_DRIVE-1]+64);
  printf("\nMaximum number of sessions:\n");
  printf("Text: %u PM: %u VDM: %u\n", Buf[QSV_MAX_TEXT_SESSIONS-1], Buf[QSV_MAX_PM_SESSIONS-1], Buf[QSV_MAX_VDM_SESSIONS-1]);
  printf("\nTask Management:\n");
  rc=DosQuerySysInfo(26, 26, &processoren, sizeof(int));
  if (rc==ERROR_INVALID_PARAMETER)
     {
     printf("OS/2 is running on 1 processor\n");
     }
  else
     {
     if (rc==NO_ERROR)
        {
        printf("OS/2 is running on %u processor(s)\n", processoren);
        }
     }
  printf("Time slices: Min: %u ms Max: %u ms\n", Buf[QSV_MIN_SLICE-1], Buf[QSV_MAX_SLICE-1]);
  printf("Maximum wait: %u s\n", Buf[QSV_MAX_WAIT-1]);
  printf("Priority variation: ");
  if (Buf[QSV_DYN_PRI_VARIATION-1]==0)
     {
     printf("Absolute\n");
     }
  else
     {
     printf("Dynamic\n");
     }
  printf("\nMemory:\n");
  printf("Total physical memory: %u kB\n", Buf[QSV_TOTPHYSMEM-1]/1024);
  printf("Total resident memory: %u kB\n", Buf[QSV_TOTRESMEM-1]/1024);
  printf("Total available memory: %u kB\n", Buf[QSV_TOTAVAILMEM-1]/1024);
  printf("Memory page size: %u B\n", Buf[QSV_PAGE_SIZE-1]);
  printf("Maximum available private memory:  %u kB\n", Buf[QSV_MAXPRMEM-1]/1024);
  printf("Maximum available shared memory: %u kB\n", Buf[QSV_MAXSHMEM-1]/1024);
  printf("\nPath\n");
  printf("Maximum length: %u\n", Buf[QSV_MAX_PATH_LENGTH-1]);
  printf("Maximum component length: %u\n", Buf[QSV_MAX_COMP_LENGTH-1]);
  printf("\nTime\n");
  dagen=Buf[QSV_MS_COUNT-1]/86400000;
  uren=Buf[QSV_MS_COUNT-1]/3600000;
  uren%=24;
  minuten=Buf[QSV_MS_COUNT-1]/60000;
  minuten%=60;
  secondes=Buf[QSV_MS_COUNT-1]/1000;
  secondes%=60;
  milisecondes=Buf[QSV_MS_COUNT-1]%1000;
  printf("System uptime: %u dagen %u:%u:%u.%u (=%ums)\n", dagen, uren, minuten, secondes, milisecondes, Buf[QSV_MS_COUNT-1]);
  printf("Timer interval: %u tenth of ms\n", Buf[QSV_TIMER_INTERVAL-1]);
  printf("\nForeground session: %u\n", Buf[QSV_FOREGROUND_FS_SESSION-1]);
  printf("Foreground process: %u\n", Buf[QSV_FOREGROUND_PROCESS-1]);
  return;
}

