/* Enable to make ^Z dump the inode table for debug */
#undef CONFIG_IDUMP
/* Enable to make ^A drop back into the monitor */
#undef CONFIG_MONITOR
/* Profil syscall support (not yet complete) */
#undef CONFIG_PROFIL
/* Multiple processes in memory at once */
#undef CONFIG_MULTI
/* Single tasking */
#define CONFIG_SINGLETASK
/* CP/M emulation */
#undef CONFIG_CPM_EMU

#define TICKSPERSEC 100   /* Ticks per second */
#define PROGBASE    ((char *)(0x0100))  /* also data base */
#define PROGTOP     ((char *)(0xF000))  /* Top of program, base of U_DATA copy */

#define BOOT_TTY 9        /* Set this to default device for stdio, stderr */
                          /* In this case, the default is the first TTY device */

/* We need a tidier way to do this from the loader */
#define CMDLINE	NULL	  /* Location of root dev name */

/* Device parameters */
#define NUM_DEV_TTY 3
#define NDEVS    17       /* Devices 0..NDEVS-1 are capable of being mounted */
                          /*  (add new mountable devices to beginning area.) */
#define TTYDEV   BOOT_TTY /* Device used by kernel for messages, panics */
#define NBUFS    10       /* Number of block buffers */
#define NMOUNTS	 4	  /* Number of mounts at a time */

