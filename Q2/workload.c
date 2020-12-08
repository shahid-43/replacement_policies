/*
INSTRUCTIONS:

This file will contain all the functions related to the generation of workload

*/

#include "definitions.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Note: The work must be generated for the returned pointer
struct workload * generate_workload(WorkloadsT type, int pages, int size)
{
    struct workload* load=(struct workload*) malloc(sizeof(struct workload));
    load->pages=pages;
    load->size=size;
    load->type=type;
    if(type==RANDOM){
        load=generate_random(load);
    }
    else if(type==LOOP){
        load=generate_loop(load);
    }
    else if(type==LOCAL){
        load=generate_local(load);
    }
    return load;
}

struct workload * generate_random(struct workload * w)
{
    int i=0;
    w->work=malloc(sizeof(int)*(w->size));
    //srand(time(0));
    for ( i = 0; i < w->size; i++)
    {
        w->work[i]=((rand())%w->pages);
        //random page within the page limit 
    }
    return w;
}

struct workload * generate_loop(struct workload * w)
{
    w->work=malloc(sizeof(int)*(w->size));
    int i=0,val=0;
   
    for ( i = 0; i < w->size; i++)
    {
        w->work[i]=val;
        val=(val+1)%(w->pages);//pages are in order and loop ex: 0,1,2,0,1,2....
    }
    return w;
}

struct workload * generate_local(struct workload * w)
{
}
