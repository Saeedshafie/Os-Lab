#include <stdio.h>

struct process{
	int waiting_time;
	int burst_time;
	int turnaround_time;
};
int n;

void average_waiting_time(struct process p []){
	int i;

	float sum_waiting = 0.0;
	for (i = 0; i < n; i++){
		sum_waiting += p[i].waiting_time;
	}
	printf("Average waiting time: %f\n", sum_waiting / n);
}

void calculate_waiting_times(struct process p []){
	int i;
	printf("Waiting time for each process:\n");
	printf("process No.1: 0\n");

	for (i = 1; i < n; i++){
		printf("process No.%d: ", i + 1);
		p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
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

void calculate_turnaround_times(struct process p []){
	int i;
	printf("turnaround time for each process:\n");
	for (i = 0; i < n; i++){
		printf("process No.%d: ", i + 1);
		p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
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
	// get burst time of each process
	for (i = 0; i < n; i++){
		printf("Enter burst time of process %d: ", i + 1);
		scanf("%d", &(proc_list[i].burst_time));
	}
	proc_list[0].waiting_time = 0;

	calculate_waiting_times(proc_list);
	calculate_turnaround_times(proc_list);
	average_waiting_time(proc_list);
	average_turnaround_time(proc_list);
}
