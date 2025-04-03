#ifndef __CL_IMG_SAFETY_MECHANISMS_H
#define __CL_IMG_SAFETY_MECHANISMS_H

#include <CL/cl.h>

#ifdef __cplusplus
extern "C" {
#endif

#define cl_img_safety_mechanisms 1

/* To be used with cl_context_properties */
#define CL_CONTEXT_SAFETY_PROPERTIES_IMG 0x40D8

/* To be used with clGetDeviceInfo */
#define CL_DEVICE_WORKGROUP_PROTECTION_SVM_CAPABILITIES_IMG            0x40D9
#define CL_DEVICE_WORKGROUP_PROTECTION_DEVICE_ENQUEUE_CAPABILITIES_IMG 0x40DB

/* To be used with CL_CONTEXT_SAFETY_PROPERTIES_IMG */
typedef cl_bitfield cl_context_safety_properties_img;

/* To be used with cl_context_safety_properties_img */
#define CL_CONTEXT_WORKGROUP_PROTECTION_IMG            (1 << 0)
#define CL_CONTEXT_ENHANCED_EVENT_EXECUTION_STATUS_IMG (1 << 1)

/* param_value with CL_EVENT_COMMAND_EXECUTION_STATUS */
#define CL_ECC_RECOVERED_IMG   0x40DA
#define CL_PAGE_FAULT_IMG      -1122
#define CL_SAFETY_FAULT_IMG    -1123
#define CL_GENERAL_FAULT_IMG   -1124
#define CL_ECC_UNRECOVERED_IMG -1125

#ifdef __cplusplus
}
#endif

#endif
