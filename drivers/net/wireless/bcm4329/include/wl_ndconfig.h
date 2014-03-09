/*
 * NDIS-specific Windows registry configuration override
 * defines for Broadcom 802.11abg Networking Device Driver
 *
 * $Copyright (C) 2001-2004 Broadcom Corporation$
 *
 * $Id: wl_ndconfig.h,v 13.11 2008-05-13 17:11:45 jkoenig Exp $
 */

#ifndef _wl_ndconfig_h_
#define _wl_ndconfig_h_

/* bit definitions for "flags" */
#define SKIP_MINUS_1		0x01	/* -1 == "don't override driver default" */
#define SIMPLE_CONFIG		0x02	/* config ioctl val needs no special processing */
#define SIMPLE_IOVAR_CONFIG	0x04	/* config iovar val needs no special processing */

/* "param" field only used by RNDIS */
typedef struct {
	const char *str;
	uint type;
	int cmd;
	uint32 flags;
	PNDIS_CONFIGURATION_PARAMETER param;
} ndis_config_t;

#if defined(STA) || defined(UNDER_CE)
extern ndis_config_t *
wl_findconfig(
	const char *name,
	ndis_config_t *table,
	int *index
);

extern PNDIS_CONFIGURATION_PARAMETER
wl_readparam(
	ndis_config_t *ndis_config,
	const char *str,
	NDIS_HANDLE confighandle,
	void *wl,
	int *index
);

extern bool
wl_writeparam(
	ndis_config_t *ndis_config,
	const char *str,
	void *arg,
	NDIS_HANDLE confighandle,
	void *wl,
	int *index);

extern VOID
wl_readconfigoverrides(
	void *wl,
	NDIS_HANDLE confighandle,
	char *id,
	uint unit,
	uint OS
);

extern VOID
wl_read_macaddr_override(
	void* wl,
	NDIS_HANDLE confighandle,
	char *id,
	uint unit
);

extern void
wl_scanoverrides(
	void *wl,
	NDIS_HANDLE confighandle,
	char *id,
	uint unit
);

#endif /* defined(STA) || defined(UNDER_CE) */

#endif /* _wl_ndconfig_h_ */
