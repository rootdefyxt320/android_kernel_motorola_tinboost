/*
 * wep.h
 * Prototypes for WEP functions.
 *
 * $ Copyright Broadcom Corporation 2005 $
 *
 * $Id: wep.h,v 1.3 2006-06-14 21:10:12 gmo Exp $
 */

#ifndef _WEP_H_
#define _WEP_H_

#include <typedefs.h>

/* WEP-encrypt a buffer */
/* assumes a contiguous buffer, with IV prepended, and with enough space at
 * the end for the ICV
 */
extern void BCMROMFN(wep_encrypt)(uint buf_len, uint8 *buf, uint sec_len, uint8 *sec_data);

/* wep-decrypt a buffer */
/* Assumes a contigious buffer, with IV prepended, and return TRUE on ICV pass
 * else FAIL
 */
extern bool BCMROMFN(wep_decrypt)(uint buf_len, uint8 *buf, uint sec_len, uint8 *sec_data);

#endif /* _WEP_H_ */
