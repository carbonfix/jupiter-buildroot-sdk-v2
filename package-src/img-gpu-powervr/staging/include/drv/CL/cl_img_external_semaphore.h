#include "cl_img_semaphore.h"

#ifndef __OPENCL_CL_IMG_EXTERNAL_SEMAPHORE_H
#define __OPENCL_CL_IMG_EXTERNAL_SEMAPHORE_H

#define CL_PLATFORM_SEMAPHORE_IMPORT_HANDLE_TYPES_IMG       0x2037
#define CL_PLATFORM_SEMAPHORE_EXPORT_HANDLE_TYPES_IMG       0x2038

#define CL_DEVICE_SEMAPHORE_IMPORT_HANDLE_TYPES_IMG         0x204D
#define CL_DEVICE_SEMAPHORE_EXPORT_HANDLE_TYPES_IMG         0x204E

#define CL_SEMAPHORE_DESC_IMG                               0x203E
#define CL_SEMAPHORE_EXPORT_HANDLE_TYPES_IMG                0x203F

#define CL_INVALID_SEMAPHORE_DESC_IMG                       -1139
#define CL_INVALID_SEMAPHORE_HANDLE_IMG                     -1140
#define CL_INVALID_SEMAPHORE_HANDLE_TYPE_IMG                -1141

typedef cl_bitfield cl_semaphore_handle_type_img;

typedef struct _cl_semaphore_desc_img_st {
    cl_semaphore_handle_type_img type;
    void *handle;
} cl_semaphore_desc_img;

typedef CL_API_ENTRY cl_int
(CL_API_CALL *clGetSemaphoreHandleForTypeIMG_fn)(cl_semaphore 					sema_object,
												 const cl_device_id				device,
												 cl_semaphore_handle_type_img	handle_type,
												 size_t							handle_size,
												 void*							handle_ptr,
												 size_t*						handle_size_ret);

extern CL_API_ENTRY cl_int CL_API_CALL
clGetSemaphoreHandleForTypeIMG (cl_semaphore sema_object,
								const cl_device_id device,
								cl_semaphore_handle_type_img handle_type,
								size_t handle_size,
								void* handle_ptr,
								size_t*	handle_size_ret) CL_API_SUFFIX__VERSION_1_2;

#endif /*__OPENCL_CL_IMG_EXTERNAL_SEMAPHORE_H*/
