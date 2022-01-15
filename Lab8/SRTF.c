#include <stdio.h>

int main() 
{
    int n; //Number of Process
    int ari[10], bur[10]; // Two Arrays for Arival time and Busrt time
    int total = 0; // Count of Total Busrt Time
    int i, j, small, temp; // Initial Values for out for-loops
    int procs[100], k, waiting[10], finish[10]; // Values for counting Times
    float tavg = 0.0, wavg = 0.0; // To count the Average of Waiting and Turnaround
    
    //The Input Part
    
    printf ("Enter Number of the Process:");
    scanf ("%d", &n);
    for (i = 0; i < n; i++){
        printf ("Enter the Arrival time of the Process %d:  ", i);
        scanf ("%d", &ari[i]);
        printf ("Enter Burst Time of the Process %d:  ", i);
        scanf ("%d", &bur[i]);
        waiting[i] = 0;
        total += bur[i];
    }
    
    //Create a Ready QUEUE based of Arrival times , swaping if it needs change
    for (i = 0; i < n; i++){
        for (j = i + 1; j < n; j++){
            if (ari[i] > ari[j]){
    	      
                temp = ari[i];
                ari[i] = ari[j];
                ari[j] = temp;
                temp = bur[i];
                bur[i] = bur[j];
                bur[j] = temp;
            }
    	}
    }
      
    //Main Part : Comparing Remaining time
    for (i = 0; i < total; i++){
        small = 3200;
        for (j = 0; j < n; j++){
    	    if ((bur[j] != 0) && (ari[j] <= i) && (bur[j] < small)){
    	       
    	        small = bur[j];
    	        k = j;
    	    }
        }
        
        bur[k]--;
        procs[i] = k;
    }
    // Checking the Finished Status of a Process  
    k = 0;
    for (i = 0; i < total; i++){
        for (j = 0; j < n; j++){
    	    if (procs[i] == j){
    	        finish[j] = i;
    	        waiting[j]++;
    	    }
    	}
    }
    
    // Printing the Result
    for (i = 0; i < n; i++){
        printf("\n PROCESS %d: Finish Time==> %d Turnaround Time==>%d Watiting Time==>%d\n",
        	 i + 1, finish[i] + 1, (finish[i] - ari[i]) + 1,
        	 (((finish[i] + 1) - waiting[i]) - ari[i]));
              
        wavg = wavg + (((finish[i] + 1) - waiting[i]) - ari[i]);
        tavg = tavg + ((finish[i] - ari[i]) + 1);
        
    }
      
    // Printing Average Values
    printf ("\n Watiting Time Average==>\t%f\n Turnaround Time Average==>\t%f\n", (wavg / n), (tavg / n));
    return 0;
}
