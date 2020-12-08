/*
INSTRUCTIONS:
This file must include only the main function
The main function should print out the various cases
and finally print out tables showing the performance
of various policies with the different workloads.
Vary the cache size.

You may include a function or 2 to ease the printing of tables.

*/

#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int pages=100;//pages for workload
	int size=10000;//workload size		
	int replace = 4;//fifo,lru,approx lru,random				
	
	float hit_rate;
	struct workload* t=NULL;

	char* files[]={"loop.csv","random.csv"};//title of the csv file generated
	int type,i,csize;					//type is used for indicating type of workload

	for (type = 0; type < 2; type++)
	{
		if(type==0){
			pages=50;    		//for loop working we are only considering 50 unique pages
		}
		
        //data written into csv file 
		FILE* fp=fopen(files[type],"w+");
		t=generate_workload(type,pages,size);
		//generates the workload
		for ( i = 0; i < replace; i++)
		{
			if(i==0){
				fprintf(fp,"FIFO\n");//fifo replacement on workloads
				for ( csize = 1; csize < 100; csize++)
				{
					hit_rate=policy_FIFO(t,csize);
					fprintf(fp,"%f\n",hit_rate);
				}
				
			}

			else if(i==1){
				fprintf(fp,"LRU APPROX\n");//approx lru on work load
				for ( csize = 1; csize < 100; csize++)
				{
					hit_rate=policy_LRUapprox(t,csize);
					fprintf(fp,"%f\n",hit_rate);
				}
				
			}
			else if(i==2){
				fprintf(fp,"LRU\n");//lru on workload
				for ( csize = 1; csize < 100; csize++)
				{
					hit_rate=policy_LRU(t,csize);
					fprintf(fp,"%f\n",hit_rate);
				}
				
			}
			else{
				fprintf(fp,"RANDOM\n");//random replacement on workload
				for ( csize = 1; csize < 100; csize++)
				{
					hit_rate=policy_RANDOM(t,csize);
					fprintf(fp,"%f\n",hit_rate);
				}
				
			}
		}
		fclose(fp);
	}

	return 0;
}
