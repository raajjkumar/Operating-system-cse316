#include<stdio.h>
#include<stdlib.h>
typedef struct
{

    int arrival_time,burst_time,queue;
    int process_id;
}process;

int main()
{
    int size,quantum,done =0;
    int count = 0;
    int time,smallest,waiting_time[50],turnaround_time[50],completion[50],temp_burst[50];
    double average_waiting,average_turnaround;
    printf("\nEnter the number of processes:");
    scanf("%d",&size);
    process no[size];
    for(int i = 0; i < size; i++)
	{
		printf("\nProcess ID:\t");
		scanf("%d", &no[i].process_id);
		printf("Arrival Time:\t");
		scanf("%d", &no[i].arrival_time);
		printf("Burst Time:\t");
		scanf("%d", &no[i].burst_time);
		printf("Queue1/Queue2(1/2):\t");
		scanf("%d", &no[i].queue);
	}
	printf("\nEnter the time quantum for Round Robin:");
	scanf("%d",&quantum);
    for(int i=0;i<size;i++)
    {
        temp_burst[i] = no[i].burst_time;//storing the burst time in a array for  further use.
    }

    no[size+1].burst_time = 999;//  assign a max burst for comparison

    for(time=0;count!=size;time++) // shortest remaining time first scheduling
    {
         smallest = size+1;
         for(int i=0;i<size;i++)
         {
            if(no[i].arrival_time<=time && no[i].burst_time<no[smallest].burst_time && no[i].burst_time>0 && no[i].queue == 1)
            {
                smallest=i;
            }
         }

         if(count >= size/2) //round robin scheduling
          {
            while(1)
            {
              for(int j=0;j<size;j++)
              {
                  if(no[j].arrival_time<=time && no[j].burst_time > quantum && no[j].queue == 2 )
                  {
                      no[j].burst_time -= quantum;
                      smallest = j;
                  }
                  else if(no[j].arrival_time<=time && no[j].burst_time < quantum && no[j].queue == 2)
                  {
                      no[j].burst_time = 0;
                      smallest = j;
                      goto a;
                  }
              }
            }
          }

        no[smallest].burst_time--; //decrementing  the burst time

        a: if(no[smallest].burst_time == 0)
         {
            count++;
            completion[smallest] = time+1;
            turnaround_time[smallest] = completion[smallest] - no[smallest].arrival_time;
            waiting_time[smallest] = turnaround_time[smallest] - temp_burst[smallest];
         }
    }
    printf("\n\nProcess Id\tArrival Time\t Burst Time\t Waiting Time\tTurnaround Time");
    for(int i=0;i<size;i++)
    {
        printf("\n   P%d   \t\t%d\t\t%d  \t\t%d\t\t%d",no[i].process_id,no[i].arrival_time,temp_burst[i],waiting_time[i],turnaround_time[i]);
        average_waiting += waiting_time[i];
        average_turnaround += turnaround_time[i];
    }
    printf("\n\nAverage waiting time = %lf\n",average_waiting/size);
    printf("Average Turnaround time = %lf",average_turnaround/size);

}
