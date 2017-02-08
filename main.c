#include<stdio.h>


/* ******************************************************************** */
/* **********************   Macro definitions   *********************** */
/* ******************************************************************** */

#define BITS_PER_BYTE 8
#define NUM_OF_BYTES_IN_32BIT 4

#define IN_SIZE		4
#define OUT_SIZE	(IN_SIZE * NUM_OF_BYTES_IN_32BIT)




/* ******************************************************************** */
/* ***********************   Type definitions   *********************** */
/* ******************************************************************** */

typedef unsigned long uint32;
typedef unsigned char uint8;


typedef enum
{
	no_error = 0x00,
	index_equals_zero,
	not_enough_output_data_size
}convert_error;


/* ******************************************************************** */
/* ********************   function declartations   ******************** */
/* ******************************************************************** */

convert_error convert_uint32_to_uint8(uint32* in_data, uint8 in_data_size, uint8* out_data, uint8 out_data_size);
void print_error_status(convert_error status);
void print_uint8_buf(uint8* buffer, uint8 buffer_size);
void print_uint32_buf(uint32* buffer, uint8 buffer_size);


/* ******************************************************************** */
/* *****************     Global variables section     ***************** */
/* ******************************************************************** */

uint32 in_buf[IN_SIZE] = {0x44332211, 0x87654321, 0x01020304, 0x22446688};
uint8 out_buf[OUT_SIZE];


/* ******************************************************************** */


int main()
{
	convert_error status;
	
	print_uint32_buf(in_buf, IN_SIZE);
	
	status = convert_uint32_to_uint8(in_buf, IN_SIZE, out_buf, OUT_SIZE);
	
	print_error_status(status);
	
	if(status == no_error)
	{
		print_uint8_buf(out_buf, OUT_SIZE);
	}
	
	printf("\n\n Conversion by casting resuts:\n");
    	print_uint8_buf((uint8*)in_buf, OUT_SIZE);
	
	//printf("\n\nPush any button to exit...");
	//getch();
	
	return 0;
}



/* ******************************************************************** */
/* *********************** function definitions *********************** */
/* ******************************************************************** */

convert_error convert_uint32_to_uint8(uint32* in_data, uint8 in_data_size, uint8* out_data, uint8 out_data_size)
{
	convert_error error_status = no_error;
	
	/* Data sizes are equal 0 or less */
	if( (in_data_size == 0) || (out_data_size == 0) )
	{
		error_status = index_equals_zero;
	}
	
	/* Output_data has not enough size */
	else if(in_data_size > (uint8)(out_data_size / NUM_OF_BYTES_IN_32BIT))
	{
		error_status = not_enough_output_data_size;
	}

	if(error_status == no_error)
	{
		uint8 i;
		uint8 j;
		uint8 k;
		
		for(i=0;i<in_data_size;i++)
		{
			k=0;
			for(j=i*NUM_OF_BYTES_IN_32BIT;j<NUM_OF_BYTES_IN_32BIT*(i+1);j++)
			{
				out_data[j] = (uint8)(in_data[i]>>(k*BITS_PER_BYTE));
				k++;
			}
		}
	}

	return error_status;
}



void print_error_status(convert_error status)
{
	printf("******\tSTATUS OF CONVERSION\t******\n******\t");
	
	switch(status)
	{	
		case no_error:
		{
			printf("Conversion completed.");
			break;
		}
		
		case index_equals_zero:
		{
			printf("One or all indexes are equal zero!");
			break;
		}
		
		case not_enough_output_data_size:
		{
			printf("Output buffer has not enough size to convert data!");
			break;
		}
		
		default:
		{
			printf("Status do not recognize!");
			break;
		}
	}
	
	printf("\t******\n\n");
}



void print_uint8_buf(uint8* buffer, uint8 buffer_size)
{
	uint8 i;
	for(i=0;i<buffer_size;i++)
	{
		printf("Output buffer:\t address %d = ", i);
		printf("0x%08x ", (buffer+i) );
		printf("\tout[%d] = ", i);
		printf("0x%02x\n\r", buffer[i] );
	}
	printf("\n");
}


void print_uint32_buf(uint32* buffer, uint8 buffer_size)
{
	uint8 i;
	for(i=0;i<buffer_size;i++)
	{
		printf("Input buffer:\t address %d = ", i);
		printf("0x%08x ", (buffer+i) );
		printf("\tout[%d] = ", i);
		printf("0x%02x\n\r", buffer[i] );
	}
	printf("\n");
}

