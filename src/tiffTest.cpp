/*  Code for testing the tiffIO function.
     
  David Tarboton
  Utah State University  
  May 23, 2010 

*/

/*  Copyright (C) 2010  David Tarboton, Utah State University

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License 
version 2, 1991 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

A copy of the full GNU General Public License is included in file 
gpl.html. This is also available at:
http://www.gnu.org/copyleft/gpl.html
or from:
The Free Software Foundation, Inc., 59 Temple Place - Suite 330, 
Boston, MA  02111-1307, USA.

If you wish to use or incorporate this program (or parts of it) into 
other software that does not meet the GNU General Public License 
conditions contact the author to request permission.
David G. Tarboton  
Utah State University 
8200 Old Main Hill 
Logan, UT 84322-8200 
USA 
http://www.engineering.usu.edu/dtarb/ 
email:  dtarb@usu.edu 
*/

//  This software is distributed from http://hydrology.usu.edu/taudem/

#include "tiffIO.h"
#include "commonLib.h"
#include "stdint.h"
#include "mpi.h"

#include "linearpart.h"
#include "createpart.h"

int main(){
	MPI_Init(NULL, NULL);
	{
		//  Program used to test Tiffio.  Provide any format in.tif file.
		//  Compile with type in the line below either SHORT_TYPE, LONG_TYPE or FLOAT_TYPE
		//  Then the output in out.tif should be the input data changed to the designated type
//  Code to repeat memory allocation many times to test linearpart.h code for trapping exception
//  in memory allocation
		tiffIO infile("logan/logan.tif",FLOAT_TYPE);
		//tiffIO infile("gsl100.tif",FLOAT_TYPE);
		//long cols = infile.getTotalX();
		//long rows = infile.getTotalY();
		//	//Create partition and read data
		//tdpartition* elevDEM[10000];
		//float dx,dy;
		//for(int i=0; i<10000; i++)
		//{
		//	elevDEM[i] = CreateNewPartition(infile.getDatatype(), cols, rows, dx, dy, infile.getNodata());
		//	if(elevDEM[i]==0)printf("Failed to create partition\n");
		//	fflush(stdout);
		//	int nx = elevDEM[i]->getnx();
		//	int ny = elevDEM[i]->getny();
		//	int xstart, ystart;
		//	elevDEM[i]->localToGlobal(0, 0, xstart, ystart);
		//	fprintf(stdout,"Partition created %d\n",i);
		//	fflush(stdout);
		//	infile.read(xstart, ystart, ny, nx, elevDEM[i]->getGridPointer());
		//}

//  Tiffio testing block of code
		//tiffIO infile("streambuffreclass2.tif",LONG_TYPE);
		//long cols = infile.getTotalX();
		//long rows = infile.getTotalY();

		//DATA_TYPE type = infile.getDatatype();
		//tiffIO fel("fs_small.tif",FLOAT_TYPE);
		//if(!fel.compareTiff(infile))
		//printf("Mismatch\n");

		//void *inarray;
		//void* nd = infile.getNodata();	
		//if(type == SHORT_TYPE){
		//	inarray = new short[rows*cols];
		//	short ndv= *(short *)nd;
		//	printf("No data: %d\n",ndv);
		//}
		//else if(type == LONG_TYPE){
		//	inarray = new long[rows*cols];
		//	long ndv= *(long *)nd;
		//	printf("No data: %ld\n",ndv);
		//}
		//else if(type == FLOAT_TYPE){
		//	inarray = new float[rows*cols];
		//}

		//infile.read(0, 0, rows, cols, inarray);
		printf("Char Size %d\n",sizeof(char));
		printf("Short Size %d\n",sizeof(short));
		printf("Int Size %d\n",sizeof(int));
		printf("Long Size %d\n",sizeof(long));
		printf("Long Long Size %d\n",sizeof(long long));
		printf("Float Size %d\n",sizeof(float));
		printf("Double Size %d\n",sizeof(double));
		printf("Long Double Size %d\n",sizeof(long double));
		printf("int32_t %d\n",sizeof(int32_t));
		printf("int64_t %d\n",sizeof(int64_t));

	//	float nd = 1.0f;
		//tiffIO outfile("out.tif", type, nd, infile);
		//outfile.write(0, 0, rows, cols, inarray);
   	}
	MPI_Finalize();
	return 0;
}
