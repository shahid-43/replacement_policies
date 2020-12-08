/* INSTRUCTIONS:
This file will contain all functions related with various policies.
Each policy must return the hit rate
*/
#include "definitions.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void init(int arr[], int n)
//initializing the cache 
{
	for (int i = 0; i < n; ++i)
	{
		arr[i] = -1;
	}
}
int random_ind(int n)
{
	srand(time(0));
	int k=rand()%n;
	return k;
}

int findcache(int cache[],int size,int page){
	//checks wether the page is present or not 
	int i,check=-1;
	for ( i = 0; i < size; i++)
	{
		if(cache[i]==page){//if hit occured 
			check=i;
			return check;
		}
	}
	return check;
}


int lru(int a[], int n)
//gives the index of the least recent page
{
	int i = 0, min = 0;
	for (int i = 1; i < n; ++i)
	{
		if (a[i] < a[min])
		{
			min = i;
		}
	}
	return min;
}

float policy_FIFO(struct workload *w, int cache_size)
{
	float hitrate;
	int check=0;
	int cache[cache_size];
	init(cache, cache_size);
	int start = 0;//start index
	int fault = 0, i = 0, j = 0; //fault == misses 

	for (i = 0; i < w->size; ++i)
	{
		check=findcache(cache,cache_size,w->work[i]);
		//check wether it is a hit or miss
		if (check==-1)
		//if miss, implies the first in will be replaced
		{
			fault++;
			cache[start] = w->work[i];
			start = (start + 1) % cache_size;
			//if cache is filled the index will circle back to 0
		}
	}

	hitrate = (1-((float)fault/(w->size)));
	return hitrate;
}

float policy_LRU(struct workload *w, int cache_size)
{
	float hitrate = 0;
	int cache[cache_size];
	init(cache, cache_size);
	int t[cache_size];
	//array to store the times of hits for the pages
	for (int i = 0; i < cache_size; ++i)
	//at time = 0
	{
		t[i] = 0;
	}
	int fault = 0, i, j, count = 0, currsize = 0;
	int check,position;

	for (i = 0; i < w->size; ++i)
	{
		check = 0;
		//if hit occurs the time of that page will be updated
		for (j = 0; j < cache_size; ++j)
		{
			if (cache[j] == w->work[i])
			{
				count++;
				t[j] = count;
				check = 1;
				break;
			}
		}

		if (!check)
		{
			fault++;
			if (currsize < cache_size)//fills the cache 
			{
				cache[currsize]=w->work[i];
				count++;
				t[currsize]=count;
				currsize++;
			}
			else//after filled and miss occured 
			{
				position = lru(t, cache_size);
				//gives the index of least time
				cache[position] = w->work[i];
				count++;
				t[position] = count;
				//update the time of the page
			}
		}
	}

	hitrate = (1-((float)fault/(w->size)));
	return hitrate;
}

float policy_LRUapprox(struct workload *w, int cache_size)
{
	float hitrate = 0;
	int fault=0;
	int cache[cache_size];
	int refbit[cache_size];
	//each page has ref bit with either 0 or 1 values
	int i,j,ind,ref=0,currsize=0;
    //ref indicates the index of the refbit array
	for (int i = 0; i < cache_size; ++i)
	{
		refbit[i] = 0;
		//initiate with all 0's
	}
	init(cache,cache_size);
	for ( i = 0; i < w->size; i++)
	{
		ind=findcache(cache,cache_size,w->work[i]);
		//if hit occured 
		if(ind!=-1){
			refbit[ind]=1;
			//the refbit of the hit will be updated to 1
		}
		else{
			//if page is not found in cache
			fault++;
			if(currsize<cache_size){
			//cache is not full
				cache[currsize]=w->work[i];
				currsize++;
			}
			else{
				while(1){
					if(refbit[ref]){
						//if miss occured and the first in page has ref bit=1 then we will give a second chance and change 
						//and change its ref bit to 0 and go for the next one
						refbit[ref]=0;
						ref=(ref+1)%cache_size;
					}
					else{
						cache[ref]=w->work[i];
						ref=(ref+1)%cache_size;
						break;
					}
				}
			}
		}	
	}
	hitrate = (1-((float)fault/(w->size)));
	return hitrate;
}

float policy_RANDOM(struct workload *w, int cache_size)
{
	float hitrate;
	int check=0;
	int currsize=0;
	int ind,fault=0;
	int cache[cache_size];
    init(cache,cache_size);
	for (int i = 0; i < w->size; ++i)
	{
		check=findcache(cache,cache_size,w->work[i]);
		if(check==-1){//if miss occurs 
			fault++;
			if(currsize<cache_size){//if cache not filled fill it
				cache[currsize]=w->work[i];
				currsize++;
			}
			else//if cache filled and miss occured 
			{							
				ind=random_ind(cache_size);
				//replace the page with any of the existing pages randomly
				cache[ind]=w->work[i];
			}
		}
	}
	hitrate = (1-((float)fault/(w->size)));
	return hitrate;
}


