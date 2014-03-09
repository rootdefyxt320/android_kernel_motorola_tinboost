/*
 * Misc utility routines for accessing chip-specific features
 * of Broadcom HNBU SiliconBackplane-based chips.
 *
 * $Copyright Open Broadcom Corporation$
 *
 * $Id: sbutils.h,v 13.197.4.7.2.1 2008-05-07 20:30:05 nisar Exp $
 */

#ifndef	_sbutils_h_
#define	_sbutils_h_

/*
 * Data structure to export all chip specific common variables
 * public (read-only) portion of sbutils handle returned by
 * sb_attach()/sb_kattach()
*/

struct sb_pub {

	uint	bustype;		/* SB_BUS, PCI_BUS  */
	uint	buscoretype;		/* SB_PCI, SB_PCMCIA, SB_PCIE */
	uint	buscorerev;		/* buscore rev */
	uint	buscoreidx;		/* buscore index */
	int	ccrev;			/* chip common core rev */
	uint32	cccaps;			/* chip common capabilities */
	int	pmurev;			/* pmu core rev */
	uint32	pmucaps;		/* pmu capabilities */
	uint	boardtype;		/* board type */
	uint	boardvendor;		/* board vendor */
	uint	boardflags;		/* board flags */
	uint	chip;			/* chip number */
	uint	chiprev;		/* chip revision */
	uint	chippkg;		/* chip package option */
	uint32	chipst;			/* chip status */
	bool	issim;			/* chip is in simulation or emulation */
	uint    sonicsrev;		/* sonics backplane rev */
	bool	pr32414;		/* XXX whether 432414 WAR applis to the chip */
};

typedef const struct sb_pub sb_t;

/*
 * Many of the routines below take an 'sbh' handle as their first arg.
 * Allocate this by calling sb_attach().  Free it by calling sb_detach().
 * At any one time, the sbh is logically focused on one particular sb core
 * (the "current core").
 * Use sb_setcore() or sb_setcoreidx() to change the association to another core.
 */

#define	SB_OSH		NULL	/* Use for sb_kattach when no osh is available */

/* exported externs */
extern sb_t *sb_attach(uint pcidev, osl_t *osh, void *regs, uint bustype,
                       void *sdh, char **vars, uint *varsz);
extern sb_t *sb_kattach(osl_t *osh);
extern void sb_detach(sb_t *sbh);
extern uint sb_chip(sb_t *sbh);
extern uint sb_chiprev(sb_t *sbh);
extern uint sb_chipcrev(sb_t *sbh);
extern uint sb_chippkg(sb_t *sbh);
extern uint sb_pcirev(sb_t *sbh);
extern bool sb_war16165(sb_t *sbh);
extern uint sb_pcmciarev(sb_t *sbh);
extern uint sb_boardvendor(sb_t *sbh);
extern uint sb_boardtype(sb_t *sbh);
extern uint sb_bus(sb_t *sbh);
extern uint sb_buscoretype(sb_t *sbh);
extern uint sb_buscorerev(sb_t *sbh);
extern uint sb_corelist(sb_t *sbh, uint coreid[]);
extern uint sb_coreid(sb_t *sbh);
extern uint sb_flag(sb_t *sbh);
extern uint sb_coreidx(sb_t *sbh);
extern uint sb_coreunit(sb_t *sbh);
extern uint sb_corevendor(sb_t *sbh);
extern uint sb_corerev(sb_t *sbh);
extern void *sb_osh(sb_t *sbh);
extern void sb_setosh(sb_t *sbh, osl_t *osh);
extern uint sb_corereg(sb_t *sbh, uint coreidx, uint regoff, uint mask, uint val);
extern void *sb_coreregs(sb_t *sbh);
extern uint32 sb_coreflags(sb_t *sbh, uint32 mask, uint32 val);
extern void sb_coreflags_wo(sb_t *sbh, uint32 mask, uint32 val);
extern uint32 sb_coreflagshi(sb_t *sbh, uint32 mask, uint32 val);
extern bool sb_iscoreup(sb_t *sbh);
extern uint sb_findcoreidx(sb_t *sbh, uint coreid, uint coreunit);
extern void *sb_setcoreidx(sb_t *sbh, uint coreidx);
extern void *sb_setcore(sb_t *sbh, uint coreid, uint coreunit);
extern int sb_corebist(sb_t *sbh);
extern void sb_commit(sb_t *sbh);
extern uint32 sb_base(uint32 admatch);
extern uint32 sb_size(uint32 admatch);
extern void sb_core_reset(sb_t *sbh, uint32 bits, uint32 resetbits);
extern void sb_core_tofixup(sb_t *sbh);
extern void sb_core_disable(sb_t *sbh, uint32 bits);
extern uint32 sb_clock_rate(uint32 pll_type, uint32 n, uint32 m);
extern uint32 sb_clock(sb_t *sbh);
extern void sb_clock_pmu_spuravoid(sb_t *sbh, bool spuravoid);
extern uint32 sb_alp_clock(sb_t *sbh);
extern uint32 sb_ilp_clock(sb_t *sbh);
extern void sb_pci_setup(sb_t *sbh, uint coremask);
extern void sb_pcmcia_init(sb_t *sbh);
void* sb_switch_core(sb_t *sbh, uint coreid, uint *origidx, uint *intr_val);
void sb_restore_core(sb_t *sbh, uint coreid, uint intr_val);
#ifdef BCMSDIO
extern void sb_sdio_init(sb_t *sbh);
#endif
extern void sb_watchdog(sb_t *sbh, uint ticks);
extern void sb_watchdog_ms(sb_t *sbh, uint32 ms);
extern void *sb_gpiosetcore(sb_t *sbh);
extern uint32 sb_gpiocontrol(sb_t *sbh, uint32 mask, uint32 val, uint8 priority);
extern uint32 sb_gpioouten(sb_t *sbh, uint32 mask, uint32 val, uint8 priority);
extern uint32 sb_gpioout(sb_t *sbh, uint32 mask, uint32 val, uint8 priority);
extern uint32 sb_gpioin(sb_t *sbh);
extern uint32 sb_gpiointpolarity(sb_t *sbh, uint32 mask, uint32 val, uint8 priority);
extern uint32 sb_gpiointmask(sb_t *sbh, uint32 mask, uint32 val, uint8 priority);
extern uint32 sb_gpioled(sb_t *sbh, uint32 mask, uint32 val);
extern uint32 sb_gpioreserve(sb_t *sbh, uint32 gpio_num, uint8 priority);
extern uint32 sb_gpiorelease(sb_t *sbh, uint32 gpio_num, uint8 priority);
extern uint32 sb_gpiopull(sb_t *sbh, bool updown, uint32 mask, uint32 val);
extern uint32 sb_gpioevent(sb_t *sbh, uint regtype, uint32 mask, uint32 val);
extern uint32 sb_gpio_int_enable(sb_t *sbh, bool enable);

/* GPIO event handlers */
typedef void (*gpio_handler_t)(uint32 stat, void *arg);

extern void *sb_gpio_handler_register(sb_t *sbh, uint32 event,
	bool level, gpio_handler_t cb, void *arg);
extern void sb_gpio_handler_unregister(sb_t *sbh, void* gpioh);
extern void sb_gpio_handler_process(sb_t *sbh);

extern void sb_clkctl_init(sb_t *sbh);
extern uint16 sb_clkctl_fast_pwrup_delay(sb_t *sbh);
extern bool sb_clkctl_cc(sb_t *sbh, uint mode);
extern int sb_clkctl_xtal(sb_t *sbh, uint what, bool on);
extern void sb_register_intr_callback(sb_t *sbh, void *intrsoff_fn, void *intrsrestore_fn,
                                      void *intrsenabled_fn, void *intr_arg);
extern void sb_deregister_intr_callback(sb_t *sbh);
extern uint32 sb_set_initiator_to(sb_t *sbh, uint32 to, uint idx);
extern uint16 sb_d11_devid(sb_t *sbh);
extern int sb_corepciid(sb_t *sbh, uint func, uint16 *pcivendor, uint16 *pcidevice,
                        uint8 *pciclass, uint8 *pcisubclass, uint8 *pciprogif,
                        uint8 *pciheader);
extern uint32 sb_gpiotimerval(sb_t *sbh, uint32 mask, uint32 val);
extern bool sb_backplane64(sb_t *sbh);
extern void sb_btcgpiowar(sb_t *sbh);

#if defined(BCMINTERNAL) && defined(BCMDBG)
extern int sb_dump_pcieregs(sb_t *sbh, struct bcmstrbuf *b);
extern int sb_gpiodump(sb_t *sbh, struct bcmstrbuf *b);
#endif
#ifdef BCMINTERNAL
extern uint32 sb_pciereg(sb_t *sbh, uint32 offset, uint32 mask, uint32 val, uint type);
extern uint32 sb_pciesbreg(sb_t *sbh, uint32 offset, uint32 mask, uint32 val);
extern uint32 sb_pcieserdesreg(sb_t *sbh, uint32 mdioslave, uint32 offset, uint32 mask, uint32 val);
#endif
extern uint32 sb_ccreg(sb_t *sbh, uint32 offset, uint32 mask, uint32 val);

/* XXX Mogrifier hack alert- BCMINTERNAL should not be the last in the following
 * if defined string
 */
#if defined(BCMINTERNAL) || defined(BCMDBG_ASSERT) || defined(BCMDBG_ERR)
extern bool sb_taclear(sb_t *sbh, bool details);
#endif /* BCMINTERNAL || BCMDBG_ASSERT || BCMDBG_ERR */

#ifdef BCMDBG
extern void sb_dump(sb_t *sbh, struct bcmstrbuf *b);
extern void sb_dumpregs(sb_t *sbh, struct bcmstrbuf *b);
extern void sb_view(sb_t *sbh, bool verbose);
extern void sb_viewall(sb_t *sbh, bool verbose);
extern void sb_ccreg_dump(sb_t *sbh, struct bcmstrbuf *b);
extern void sb_clkctl_dump(sb_t *sbh, struct bcmstrbuf *b);
extern uint32 sb_pcielcreg(sb_t *sbh, uint32 mask, uint32 val);
#endif

extern bool sb_deviceremoved(sb_t *sbh);
extern uint32 sb_socram_size(sb_t *sbh);

/*
* Build device path. Path size must be >= SB_DEVPATH_BUFSZ.
* The returned path is NULL terminated and has trailing '/'.
* Return 0 on success, nonzero otherwise.
*/
extern int sb_devpath(sb_t *sbh, char *path, int size);
/* Read variable with prepending the devpath to the name */
extern char *sb_getdevpathvar(sb_t *sbh, const char *name);
extern int sb_getdevpathintvar(sb_t *sbh, const char *name);

extern uint8 sb_pcieclkreq(sb_t *sbh, uint32 mask, uint32 val);
extern void sb_war42780_clkreq(sb_t *sbh, bool clkreq);
extern void sb_pci_sleep(sb_t *sbh);
extern void sb_pci_down(sb_t *sbh);
extern void sb_pci_up(sb_t *sbh);
extern void sb_pcie_war_ovr_disable(sb_t *sbh);
extern void sb_pcie_extendL1timer(sb_t *sbh, bool extend);
extern int sb_pci_fixcfg(sb_t *sbh);
#ifndef BCMDONGLEHOST
extern bool sb_ldo_war(sb_t *sbh, uint devid);
#endif /* BCMDONGLEHOST */

/* Wake-on-wireless-LAN (WOWL) */
extern bool sb_pci_pmecap(sb_t *sbh);
struct osl_info;
extern bool sb_pci_fastpmecap(struct osl_info *osh);
extern bool sb_pci_pmeclr(sb_t *sbh);
extern void sb_pci_pmeen(sb_t *sbh);
extern uint sb_pcie_readreg(void *sih, uint addrtype, uint offset);

#ifdef BCMECICOEX
extern void *sb_eci_init(sb_t *sbh);
extern void sb_eci_notify_bt(sb_t *sbh, uint32 mask, uint32 val);
#else
#define sb_eci_init(sbh) (0)
#define sb_eci_notify_bt(sbh, type, val)  (0)
#endif /* BCMECICOEX */

/* OTP status */
extern bool sb_is_otp_disabled(sb_t *sbh);
extern bool sb_is_otp_powered(sb_t *sbh);
/* OTP power */
extern void sb_otp_power(sb_t *sbh, bool on);

/* SPROM availability */
extern bool sb_is_sprom_available(sb_t *sbh);

/* OTP/SROM CIS stuff */
extern int sb_cis_source(sb_t *sbh);
#define CIS_DEFAULT	0
#define CIS_SROM	1
#define CIS_OTP		2

/* clkctl xtal what flags */
#define	XTAL			0x1	/* primary crystal oscillator (2050) */
#define	PLL			0x2	/* main chip pll */

/* clkctl clk mode */
#define	CLK_FAST		0	/* force fast (pll) clock */
#define	CLK_DYNAMIC		2	/* enable dynamic clock control */

/* GPIO usage priorities */
#define GPIO_DRV_PRIORITY	0	/* Driver */
#define GPIO_APP_PRIORITY	1	/* Application */
#define GPIO_HI_PRIORITY	2	/* Highest priority. Ignore GPIO reservation */

/* GPIO pull up/down */
#define GPIO_PULLUP		0
#define GPIO_PULLDN		1

/* GPIO event regtype */
#define GPIO_REGEVT		0	/* GPIO register event */
#define GPIO_REGEVT_INTMSK	1	/* GPIO register event int mask */
#define GPIO_REGEVT_INTPOL	2	/* GPIO register event int polarity */

/* device path */
#define SB_DEVPATH_BUFSZ	16	/* min buffer size in bytes */

/* SB routine enumeration: to be used by update function with multiple hooks */
#define	SB_DOATTACH	1
#define SB_PCIDOWN	2
#define SB_PCIUP	3

#if defined(BCMINTERNAL) || defined(BCMQT)
#define	ISSIM_ENAB(sbh)	((sbh)->issim)
#else
#define	ISSIM_ENAB(sbh)	0
#endif

/* PMU clock/power control */
#if defined(BCMPMUCTL)
#define PMUCTL_ENAB(sbh)	(BCMPMUCTL)
#else
#define PMUCTL_ENAB(sbh)	((sbh)->cccaps & CC_CAP_PMU)
#endif

/* chipcommon clock/power control (exclusive with PMU's) */
#if defined(BCMPMUCTL) && BCMPMUCTL
#define CCCTL_ENAB(sbh)		(0)
#define CCPLL_ENAB(sbh)		(0)
#else
#define CCCTL_ENAB(sbh)		((sbh)->cccaps & CC_CAP_PWR_CTL)
#define CCPLL_ENAB(sbh)		((sbh)->cccaps & CC_CAP_PLL_MASK)
#endif

#endif	/* _sbutils_h_ */
