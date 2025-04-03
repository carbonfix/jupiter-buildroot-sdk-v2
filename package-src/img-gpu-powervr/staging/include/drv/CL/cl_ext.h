/*************************************************************************/ /*!
@File           cl_ext.h
@Title          CL extensions.
@Copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved
@License        Strictly Confidential.
*/ /**************************************************************************/

#ifndef __drv_clext_h__
#define __drv_clext_h__

/* Trusted Execute Environment Extension */
#define CL_MEM_PROTECTED_CONTENT_IMG (1U << 29)

/* cl_img_use_signal_heap */
#define CL_MEM_USE_SIGNAL_HEAP_IMG (1U << 30)

#define CL_DEVICE_MAX_SIGNALS_IMG       0x2000
#define CL_DEVICE_SIGNAL_SIZE_BYTES_IMG 0x2001

#endif /* __drv_clext_h__ */
