
#ifndef __OPENCL_CL_SEMAPHORE_H
#define __OPENCL_CL_SEMAPHORE_H

#include <CL/cl.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CL_DEVICE_HANDLE_LIST_IMG                           0x2051
#define CL_DEVICE_HANDLE_LIST_END_IMG                       0

typedef struct _cl_semaphore* cl_semaphore;

/* type cl_semaphore_img */
typedef cl_properties       cl_semaphore_properties_img;
typedef cl_uint             cl_semaphore_info_img;
typedef cl_uint             cl_semaphore_type_img;
typedef cl_ulong            cl_semaphore_payload_img;

/* legacy to support already shipping headers */
typedef cl_uint             cl_semaphore_type;

/* cl_semaphore_type */
#define CL_SEMAPHORE_TYPE_BINARY_IMG                        1

/* cl_platform_info */
#define CL_PLATFORM_SEMAPHORE_TYPES_IMG                     0x2036

/* cl_device_info */
#define CL_DEVICE_SEMAPHORE_TYPES_IMG                       0x204C

/* cl_semaphore_info_img */
#define CL_SEMAPHORE_CONTEXT_IMG                            0x2039
#define CL_SEMAPHORE_REFERENCE_COUNT_IMG                    0x203A
#define CL_SEMAPHORE_PROPERTIES_IMG                         0x203B
#define CL_SEMAPHORE_PAYLOAD_IMG                            0x203C

/* cl_semaphore_info_img or cl_semaphore_properties_img */
#define CL_SEMAPHORE_TYPE_IMG                               0x203D
/* enum CL_DEVICE_HANDLE_LIST_IMG */
/* enum CL_DEVICE_HANDLE_LIST_END_IMG */

/* cl_command_type */
#define CL_COMMAND_SEMAPHORE_WAIT_IMG                       0x2042
#define CL_COMMAND_SEMAPHORE_SIGNAL_IMG                     0x2043

/* Error codes */
#define CL_INVALID_SEMAPHORE_IMG                            -1138

typedef CL_API_ENTRY cl_semaphore
(CL_API_CALL *clCreateSemaphoreWithPropertiesIMG_fn)(cl_context 					psContext,
												     cl_semaphore_properties_img*	sema_props,
												     cl_int* 						pui32ErrorCodeRet);

typedef CL_API_ENTRY cl_int
(CL_API_CALL *clEnqueueWaitSemaphoresIMG_fn)(cl_command_queue			   		psCommandQueue,
						 					 cl_uint					   		uiNumSemaphoresInList,
								  			 const cl_semaphore*		   		ppsSemaphoreList,
								  			 const cl_semaphore_payload_img*  	ppsSemaphorePayloadList,
								  			 cl_uint					   		uiNumEventsInWaitList,
								  			 const cl_event*			   		ppsEventWaitList,
								  			 cl_event*					   		ppsEvent);

typedef CL_API_ENTRY cl_int
(CL_API_CALL *clEnqueueSignalSemaphoresIMG_fn)(cl_command_queue					psCommandQueue,
								 				cl_uint							uiNumSemaphoresInList,
								 				const cl_semaphore*				ppsSemaphoreList,
								 				const cl_semaphore_payload_img*	ppsSemaphorePayloadList,
								 				cl_uint							uiNumEventsInWaitList,
								 				const cl_event*					ppsEventWaitList,
								 				cl_event*						ppsEvent);

typedef CL_API_ENTRY cl_int
(CL_API_CALL *clGetSemaphoreInfoIMG_fn)(cl_semaphore 	psSemaphore,
							 cl_semaphore_info_img		param_name,
							 size_t 					param_size,
							 void* 						param_value,
							 size_t* 					param_size_ret);


typedef CL_API_ENTRY cl_int
(CL_API_CALL *clReleaseSemaphoreIMG_fn)(cl_semaphore 	psSemaphore);

typedef CL_API_ENTRY cl_int
(CL_API_CALL *clRetainSemaphoreIMG_fn)(cl_semaphore 	psSemaphore);

extern CL_API_ENTRY cl_semaphore CL_API_CALL
clCreateSemaphoreWithPropertiesIMG(cl_context psContext,
								   cl_semaphore_properties_img* sema_props,
								   cl_int* pui32ErrorCodeRet)  CL_API_SUFFIX__VERSION_1_2;

extern CL_API_ENTRY cl_int CL_API_CALL
clEnqueueWaitSemaphoresIMG (cl_command_queue command_queue,
                            cl_uint num_sema_descs,
                            const cl_semaphore *sema_list,
                            const cl_semaphore_payload_img *sema_payload_list,
                            cl_uint num_events_in_wait_list,
                            const cl_event *event_wait_list,
                            cl_event *event)  CL_API_SUFFIX__VERSION_1_2;

extern CL_API_ENTRY cl_int CL_API_CALL
clEnqueueSignalSemaphoresIMG (cl_command_queue command_queue,
                              cl_uint num_sema_descs,
                              const cl_semaphore *sema_list,
                              const cl_semaphore_payload_img *sema_payload_list,
                              cl_uint num_events_in_wait_list,
                              const cl_event *event_wait_list,
                              cl_event *event)  CL_API_SUFFIX__VERSION_1_2;

extern CL_API_ENTRY cl_int CL_API_CALL
clGetSemaphoreInfoIMG(const cl_semaphore semaphore,
					  cl_semaphore_info_img param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret)  CL_API_SUFFIX__VERSION_1_2;

extern CL_API_ENTRY cl_int CL_API_CALL
clReleaseSemaphoreIMG (cl_semaphore sema_object) CL_API_SUFFIX__VERSION_1_2;

extern CL_API_ENTRY cl_int CL_API_CALL
clRetainSemaphoreIMG (cl_semaphore sema_object) CL_API_SUFFIX__VERSION_1_2;

#ifdef __cplusplus
}
#endif

#endif /*__OPENCL_CL_SEMAPHORE_H*/
