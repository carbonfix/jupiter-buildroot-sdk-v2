/*
 * src is cuda/cudaUtility.h
 */

#ifndef __SPM_UTILITY_H_
#define __SPM_UTILITY_H_


#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "logging.h"

// #define spmSuccess                        (0)
// https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__TYPES.html
typedef enum {
    spmSuccess = 0,
	spmErrorInvalidValue  = 1,
	spmErrorMemoryAllocation = 2,
	spmErrorInitializationError = 3,
	spmErrorUnknown = 999,
	spmErrorApiFailureBase = 10000,
} spmError_t;

/**
 * Execute a SPM call and print out any errors
 * @return the original spmError_t result
 * @ingroup spmError_t
 */
#define SPM(x)				spmCheckError((x), #x, __FILE__, __LINE__)

/**
 * Evaluates to true on success
 * @ingroup spmError_t
 */
#define SPM_SUCCESS(x)			(SPM(x) == spmSuccess)

/**
 * Evaluates to true on failure
 * @ingroup spmError_t
 */
#define SPM_FAILED(x)			(SPM(x) != spmSuccess)

/**
 * Return from the boolean function if SPM call fails
 * @ingroup spmError_t
 */
#define SPM_VERIFY(x)			if(SPM_FAILED(x))	return false;

/**
 * Return on SPM errors, continue on spmSuccess.
 * @ingroup spmError_t
 */
#define SPM_ASSERT(x)          { const spmError_t _retval = SPM(x); if(_retval != spmSuccess) return _retval; }

/**
 * LOG_SPM string.
 * @ingroup spmError_t
 */
#define LOG_SPM "[SPM]   "

/*
 * define this if you want all SPM calls to be printed
 * @ingroup spmError_t
 */
//#define SPM_TRACE

inline char* SPMGetErrorString(spmError_t error)
{
	if (error == spmSuccess) {
		return "Success";
	} else if (error == spmErrorInvalidValue) {
		return "Invalid Value";
	} else if (error == spmErrorMemoryAllocation) {
		return "Memory Allocation";
	} else if (error == spmErrorInitializationError) {
		return "Initialization Error";
	} else if (error == spmErrorUnknown) {
		return "Unknown Error";
	} else {
		return "Not Defined";
	}
}

inline char* spmGetErrorString (spmError_t error)
{
	return SPMGetErrorString(error);
}

/**
 * SPMCheckError
 * @ingroup spmError_t
 */
inline spmError_t spmCheckError(spmError_t retval, const char* txt, const char* file, int line )
{
	if( retval == spmSuccess )
	{
	#if !defined(SPM_TRACE)
		return spmSuccess;
	#else
		LogDebug(LOG_SPM "%s\n", txt);
	#endif
	}
	else
	{
		LogError(LOG_SPM "%s\n", txt);
		LogError(LOG_SPM "   %s (error %u) (hex 0x%02X)\n", SPMGetErrorString(retval), retval, retval);
		LogError(LOG_SPM "   %s:%i\n", file, line);
	}

	return retval;
}

inline spmError_t spmFreeHost(void* p)
{
	if(p != NULL)
	{
		free(p);
		p = NULL;
		return spmSuccess;
	}
	else{
		return spmErrorMemoryAllocation;
	}
}

//__host__ __device__ cudaError_t cudaMalloc(void** devPtr, size_t size)
inline spmError_t spmMalloc (void** p, size_t size)
{
	char *tmp = (char *)malloc(size);
	if(tmp != NULL)
	{
		*p = tmp;
		return spmSuccess;
	}
	else{
		return spmErrorMemoryAllocation;
	}
}

//Frees memory on the device.
inline spmError_t spmFree (void* devPtr)
{
	return spmFreeHost(devPtr);
}


/**
 * Check for non-NULL pointer before freeing it, and then set the pointer to NULL.
 * @ingroup spmError_t
 */
#define SPM_FREE(x) 		if(x != NULL) { SPMFree(x); x = NULL; }

/**
 * Check for non-NULL pointer before freeing it, and then set the pointer to NULL.
 * @ingroup spmError_t
 */
#define SPM_FREE_HOST(x)	if(x != NULL) { spmFreeHost(x); x = NULL; }

/**
 * Check for non-NULL pointer before deleting it, and then set the pointer to NULL.
 * @ingroup util
 */
#define SAFE_DELETE(x) 		if(x != NULL) { delete x; x = NULL; }

/**
 * Check for non-NULL pointer before freeing it, and then set the pointer to NULL.
 * @ingroup util
 */
#define SAFE_FREE(x) 		if(x != NULL) { free(x); x = NULL; }


/**
 * If a / b has a remainder, round up.  This function is commonly using when launching
 * SPM kernels, to compute a grid size inclusive of the entire dataset if it's dimensions
 * aren't evenly divisible by the block size.
 *
 * For example:
 *
 *    const dim3 blockDim(8,8);
 *    const dim3 gridDim(iDivUp(imgWidth,blockDim.x), iDivUp(imgHeight,blockDim.y));
 *
 * Then inside the SPM kernel, there is typically a check that thread index is in-bounds.
 *
 * Without the use of iDivUp(), if the data dimensions weren't evenly divisible by the
 * block size, parts of the data wouldn't be covered by the grid and not processed.
 *
 * @ingroup SPM
 */
//inline __device__ __host__ int iDivUp( int a, int b )  		{ return (a % b != 0) ? (a / b + 1) : (a / b); }
inline int iDivUp( int a, int b )  		{ return (a % b != 0) ? (a / b + 1) : (a / b); }

#endif

