#include <stdio.h>
#include <stdbool.h>
struct process{
	int waiting_time;
	int burst_time;
	int turnaround_time;
	// remaining time
	int rem_time;
};
int n;
// quantum time
int q;

bool task_done(struct process p []){
	int i;
	for (i = 0; i < n; i++){
		if (p[i].rem_time != 0)
			return false;
	}	
	return true;
}

void sequence(struct process p []){
	int i;
	int timepassed = 0;
	while (!task_done(p)){
		for (i = 0; i < n; i++){
			if (p[i].rem_time > 0){
				if (p[i].rem_time > q){
					p[i].rem_time -= q;
					timepassed += q;
				}
				else{// if ramaining time is less than/equal to q
				
					timepassed += p[i].rem_time;
					// process is completed so the remaining time should be zero
					p[i].rem_time = 0;
					// turnaround time = Completion time(timepassed) - Arrival time(= 0)
					p[i].turnaround_time = timepassed;
					p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
				}
				printf("process %d\n", i + 1);
			}
		}
	}
}

void average_waiting_time(struct process p []){
	int i;
	
	float sum_waiting = 0.0;
	for (i = 0; i < n; i++){
		sum_waiting += p[i].waiting_time; 
	}
	printf("Average waiting time: %f\n", sum_waiting / n);
}

void show_waiting_times(struct process p []){
	int i;
	printf("Waiting time for each process:\n");
	printf("process No.1: 0\n");
	
	for (i = 1; i < n; i++){
		printf("process No.%d: ", i + 1);
		printf("waiting time = %d\n", p[i].waiting_time);
	}
}

void average_turnaround_time(struct process p []){
	int i;
	
	float sum_turnaround = 0.0;
	for (i = 0; i < n; i++){
		sum_turnaround += p[i].turnaround_time; 
	}
	printf("Average turnaround time: %f\n", sum_turnaround / n);
}

void show_turnaround_times(struct process p []){
	int i;
	printf("turnaround time for each process:\n");
	for (i = 0; i < n; i++){
		printf("process No.%d: ", i + 1);
		printf("turnaround time = %d\n", p[i].turnaround_time);
	}
}

int main(){
	int	i;
	printf("Enter number of processes: ");
	// number of processes
	scanf("%d", &n);
	// list of processes with size n
	struct process proc_list[n];
	// get burst time and priority of each process
	for (i = 0; i < n; i++){
		printf("Enter burst time of process %d: ", i + 1);
		scanf("%d", &(proc_list[i].burst_time));
		proc_list[i].rem_time = proc_list[i].burst_time;	
	}
	proc_list[0].waiting_time = 0;
	
	// get quantum time from user
	printf("Enter quantum time: ");
	scanf("%d", &q);
	
	// this function shows the seqence of executing processes
	// and calculates waiting time and turnaround time for each process
	sequence(proc_list);
	
	show_waiting_times(proc_list);
	show_turnaround_times(proc_list);
	average_waiting_time(proc_list);
	average_turnaround_time(proc_list);
}
