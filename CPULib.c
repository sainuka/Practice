#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pslibrary.h"


#define READY  0
#define RUNNING  1
#define WAITING  2
#define DONE  3

static char stateChars[] = {'r','R','w',0};

/* 1) handle state changes:
         running process completes CPU burst
         running process has quantum expire
         IO complete
   2) do context switch if necessary
         both ready
         one ready and CPU free
   3) append appropriate characters to character arrays
         avoid putting in multiple string terminators
*/
/* assume s1 and s2 point to buffers with enough space to hold the result */
/* assume that the int parameters are strictly greater than 0 */
void fcfs(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
    int i;                                   /* next string position (time) */
    int state1 = READY;                            /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

    for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                /* running process completes its CPU burst */
	if ((state1 == RUNNING) && (cpuLeft1 == 0)) {
            if (ioLeft1 == 0) {
                state1 = DONE;
                s1[i] = stateChars[state1];            /* terminate the string */
            }
            else
                state1 = WAITING;
	}  
	else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
            if (ioLeft2 == 0) {
		state2 = DONE;
		s2[i] = stateChars[state2];
	    }
	    else
		state2 = WAITING;
        }  
                                                     /* handle IO complete */
        if ((state1 == WAITING) && (ioLeft1 == 0)) {
            state1 = READY;
            cpuLeft1 = z1;
        }  
        if ((state2 == WAITING) && (ioLeft2 == 0)) {
            state2 = READY;
	    cpuLeft2 = z2;
        }  
                                    /* if both ready, depends on algorithm */
        if ( (state1 == READY) && (state2 == READY)) {
            state1 = RUNNING;
        }  
                                     /* handle one ready and CPU available */
        else if ( (state1 == READY) && (state2 != RUNNING)) {
            state1 = RUNNING;
        }  
        else if ( (state2 == READY) && (state1 != RUNNING)) {
            state2 = RUNNING;
        }  
   /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
                                                        /* decrement counts */
        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;
    }                                               /* end of main for loop */
}

void sjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
    int i;                                   /* next string position (time) */
    int state1 = READY;                            /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

    for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                /* running process completes its CPU burst */
	if ((state1 == RUNNING) && (cpuLeft1== 0)) {
            if (ioLeft1 == 0) {
                state1 = DONE;
                s1[i] = stateChars[state1];            /* terminate the string */
            }
            else
                state1 = WAITING;
	}  
	else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
            if (ioLeft2 == 0) {
		state2 = DONE;
		s2[i] = stateChars[state2];
	    }
	    else
		state2 = WAITING;
        }  
                                                     /* handle IO complete */
        if ((state1 == WAITING) && (ioLeft1 == 0)) {
            state1 = READY;
            cpuLeft1 = z1;
        }  
        if ((state2 == WAITING) && (ioLeft2 == 0)) {
            state2 = READY;
            cpuLeft2 = z2;
        }  
                                    /* if both ready, depends on algorithm */
        if ( (state1 == READY) && (state2 == READY)) {
            if (cpuLeft1 <= cpuLeft2) /* p1 has shorter CPU burst time */ 
		state1 = RUNNING;
	    else state2 = RUNNING;
        }  
                                     /* handle one ready and CPU available */
        else if ( (state1 == READY) && (state2 != RUNNING)) {
            state1 = RUNNING;
        }  
        else if ( (state2 == READY) && (state1 != RUNNING)) {
            state2 = RUNNING;
        }  
   /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
                                                        /* decrement counts */
        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;
    }                                               /* end of main for loop */

} 

void psjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
    int i;                                   /* next string position (time) */
    int state1 = READY;                            /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

    for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                /* running process completes its CPU burst */
	if ((state1 == RUNNING) && (cpuLeft1== 0)) {
            if (ioLeft1 == 0) {
                state1 = DONE;
                s1[i] = stateChars[state1];            /* terminate the string */
            }
            else
                state1 = WAITING;
	}  
	else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
            if (ioLeft2 == 0) {
		state2 = DONE;
		s2[i] = stateChars[state2];
	    }
	    else
		state2 = WAITING;
        }  
                                                     /* handle IO complete */
        if ((state1 == WAITING) && (ioLeft1 == 0)) {
            state1 = READY;
            cpuLeft1 = z1;
        }  
        if ((state2 == WAITING) && (ioLeft2 == 0)) {
            state2 = READY;
            cpuLeft2 = z2;
        }  
                                    /* if both ready, depends on algorithm */
        if ( (state1 == READY) && (state2 == READY)) {
            if (cpuLeft1 <= cpuLeft2) /* p1 has shorter CPU burst time */ 
		state1 = RUNNING;
	    else state2 = RUNNING;
        }  
                                     /* handle one ready and CPU available */
        else if ( (state1 == READY) && (state2 != RUNNING)) {
            state1 = RUNNING;
        }  
        else if ( (state2 == READY) && (state1 != RUNNING)) {
            state2 = RUNNING;
        }  
   /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
                                                        /* decrement counts */
        if (state1 == RUNNING)
            cpuLeft1--;
	    if ((cpuLeft1 > cpuLeft2) && (cpuLeft1 != 0)) { 
		state1 = READY; /* if p1's cpuLeft is greater than p2's, send p1 to ready que */
	    }
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
	    if ((cpuLeft1 <= cpuLeft2) && (cpuLeft2 != 0)) {
		state2 = READY; /* if p2's cpuLeft is greater that p1's, send p2 to ready que */
	    }
        if (state2 == WAITING)
            ioLeft2--;
    }                                               /* end of main for loop */

}

void rr(char *s1, char *s2, int q, int x1, int y1, int z1, int x2, int y2, int z2) {
    int i;                                   /* next string position (time) */
    int state1 = READY;                            /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */
    int qleft;                                         /* quantum remaining */
    int oldest;			    /* keeps track of process that just rans*/

    for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                /* running process completes its CPU burst */
	if ((state1 == RUNNING) && (cpuLeft1== 0)) {
            if (ioLeft1 == 0) {
                state1 = DONE;
                s1[i] = stateChars[state1];            /* terminate the string */
            }
            else
                state1 = WAITING;
	}  
	else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
            if (ioLeft2 == 0) {
                state2 = DONE;
                s2[i] = stateChars[state2];            /* terminate the string */
            }
            else
                state2 = WAITING;
        }  
                                     /* running process has quantum expire */
        if ((state1 == RUNNING) && (qleft == 0) ) {
            if (cpuLeft1 != 0) {
		state1 = READY;	   
	    }
	    else state1 = WAITING;
        }  
        if ((state2 == RUNNING) && (qleft == 0) ) {
            if (cpuLeft2 != 0) {
		state2 = READY;	   
	    }
	    else state2 = WAITING;
        }  
                                                     /* handle IO complete */
        if ((state1 == WAITING) && (ioLeft1 == 0)) {
            state1 = READY;
            cpuLeft1 = z1;
        }  
        if ((state2 == WAITING) && (ioLeft2 == 0)) {
            state2 = READY;
            cpuLeft2 = z2;
        }  
                                    /* if both ready, depends on algorithm */
        if ( (state1 == READY) && (state2 == READY) && (i == 0)) {
            state1 = RUNNING;   /* if both ready at the beginning, p1 goes first */
	    oldest = 1;
	    qleft = q;
        } else if ((state1 == READY) && (state2 == READY) && (i != 0)) {
	    if (oldest == 1) {	/* any other time, it is based on oldest process */
		state2 = RUNNING;
		oldest = 2;
		qleft = q;
	    } else if (oldest == 2) {
		state1 = RUNNING;
		oldest = 1;
		qleft = q;
	    }
	}
                                     /* handle one ready and CPU available */
        else if ( (state1 == READY) && (state2 != RUNNING)) {
            state1 = RUNNING;
	    oldest = 1;
            qleft = q;
        }  
        else if ( (state2 == READY) && (state1 != RUNNING)) {
            state2 = RUNNING;
	    oldest = 2;
	    qleft = q;
        }  
   /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
                                                        /* decrement counts */
        qleft--;                   /* OK to decrement even if nothing running */
        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;
    }                                               /* end of main for loop */

}

void displayOutput(char *heading, char *s1, char *s2) {
    double s1Len = 0, s2Len = 0;
    double countRunning = 0, countReadyP1 = 0, countReadyP2 = 0; 
    double avg = 0;
    double cpuUtilization = 0;
    int i; 

    printf("\n");
    printf("%s\n", heading);
    printf("%s\n", s1);
    printf("%s\n", s2);

    s1Len = strlen(s1);   /* get string lengths for loops */
    s2Len = strlen(s2);

    for (i = 0; i < s1Len; i++) {
	if (s1[i] == 'R') countRunning++;  /* count running time for p1 */
	if (s1[i] == 'r') countReadyP1++;  /* count ready time for p1 */
    }

    for (i = 0; i < s2Len; i++) {
	if (s2[i] == 'R') countRunning++; /* count running time for p2 and add to running time of p1 */
	if (s2[i] == 'r') countReadyP2++; /* count ready time for p2 */
    }

    avg = (countReadyP1 + countReadyP2)/2; /* find average ready time */

    if (s1Len >= s2Len) {
	cpuUtilization = countRunning/s1Len; /* find cpu utilization */
    }
    else cpuUtilization = countRunning/s2Len;

    printf("%.f %.f %.01f %.06f\n", countReadyP1, countReadyP2, avg, cpuUtilization);
}
