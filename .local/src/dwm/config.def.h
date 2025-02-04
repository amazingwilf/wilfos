/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx	= 3; 
static const unsigned int snap		= 32;
static int floatposgrid_x			= 5; 
static int floatposgrid_y			= 5; 
static const char *toggle_float_pos	= "50% 50% 80% 80%"; 

static const int showbar			= 1;	
static const int topbar				= 1;	
static const int user_bh			= 52;
#define ICONSIZE (bh - 12) 
#define ICONSPACING 10

static const unsigned int gappih	= 15;	
static const unsigned int gappiv	= 15;	
static const unsigned int gappoh	= 15;	
static const unsigned int gappov	= 15;	
static	int smartgaps				= 1;	

static const char *fonts[]	= { "Noto Sans:style=Medoum:size=12",
								"monospace:size=10:style=Bold",
								"JetBrainsMono Nerd Font:size=13",
								"Noto Sans:size=10" };

static const char col_gray1[]	= "#000000";
static const char col_gray2[]	= "#4a697d";
static const char col_gray3[]	= "#c4c7c8";
static const char col_gray4[]	= "#fdf6e3";
static const char col_yellow[]	= "#fdd835";
static const char col_blue[]	= "#42a5f8";
static const char col_magenta[]	= "#ba68c8";
static const char col_cyan[]	= "#006000";

static const char *colors[][3]	= {
	[SchemeNorm] 		= { col_gray3, 		col_gray1, 	col_gray2   },
	[SchemeSel]			= { col_gray4, 		col_cyan,	col_blue	},
	[SchemeFloat]		= { col_gray4, 		col_cyan,	col_magenta	},
	[SchemeScratch]		= { col_gray4, 		col_cyan,	col_yellow	},
	[SchemeLtSymbol]	= { col_yellow,		col_gray1,	col_gray1	},
	[SchemeTagsNorm]	= { col_magenta,	col_gray1,	col_gray1 },
};

/* tagging */
static char *tags[] = { " ", " ", " ", " ", " ", " ", " ", " " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	{ .class = "Lxappearance", .isfloating = 1, .floatpos = "50% 50% -1h -1w" },
	{ .class = "Firefox", .tags = 1 << 1 },
	{ .class = "Chromium", .tags = 1 << 2 },
	{ .class = "Thunar", .tags = 1 << 3 },
	{ .instance = "spterm", .scratchkey = 't', .isfloating = 1, .floatpos = "50% 50% 80% 80%" },
};

/* layout(s) */
static const float mfact		= 0.50;
static const int nmaster		= 1; 
static const int resizehints 	= 0; 
static const int lockfullscreen = 1; 

#define FORCE_VSPLIT 1	
#include "vanitygaps.c"

static const Layout layouts[] = {
	{ "[]=",	tile },
	{ "><>",	NULL },
	{ "[M]",	monocle },
	{ "[@]",	spiral },
	{ "[\\]",	dwindle },
	{ "D[]",	deck },
	{ "TTT",	bstack },
	{ "===",	bstackhoriz },
	{ "HHH",	grid },
	{ "###",	nrowgrid },
	{ "---",	horizgrid },
	{ ":::",	gaplessgrid },
	{ "|M|",	centeredmaster },
	{ ">M>",	centeredfloatingmaster },
	{ NULL,		NULL },
};

/* key definitions */
#define MOD Mod4Mask
#define ALT Mod1Mask
#define SFT ShiftMask
#define CTL ControlMask

#define SCRATCHKEYS(KEY,CMD) \
	{ MOD,		KEY,	togglescratch,	{.v = CMD} }, \
	{ MOD|SFT,	KEY,	removescratch,	{.v = CMD} }, \
	{ MOD|CTL,	KEY,	setscratch,		{.v = CMD} },

#define TAGKEYS(KEY,TAG) \
	{ MOD,			KEY,	view,		{.ui = 1 << TAG} }, \
	{ MOD|CTL,		KEY,	toggleview,	{.ui = 1 << TAG} }, \
	{ MOD|SFT,		KEY,	tag,		{.ui = 1 << TAG} }, \
	{ MOD|CTL|SFT,	KEY,	toggletag,	{.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static const char *termcmd[]		= { "ghostty", "--title=Terminal", NULL };
static const char *roficmd[]		= { "rofi", "-show", "drun", "-dpi", "1", "-kb-cancel", "Alt-F1", NULL };
static const char *firefoxcmd[]		= { "firefox", NULL };
static const char *chromiumcmd[]	= { "chromium", NULL };

static const char *sptermcmd[]		= { "t", "ghostty", "--x11-instance-name=spterm", "--title=Scratchpad", NULL };

/* Hardware keys for volume and brightness */
#include <X11/XF86keysym.h>
static const char *mutevol[]		= { "volume", "--toggle", NULL };
static const char *mutemic[] 		= { "volume", "--toggle-mic", NULL };
static const char *upvol[]   		= { "volume", "--inc", NULL };
static const char *downvol[] 		= { "volume", "--dec", NULL };
static const char *upbl[] 			= { "brightness", "--inc", NULL };
static const char *downbl[] 		= { "brightness", "--dec", NULL };

static Key keys[] = {
	{ ALT,			XK_F1,						spawn,				{.v = roficmd } },
	{ MOD,			XK_Return, 					spawn,				{.v = termcmd } },
	{ MOD,			XK_w,						spawn,				{.v = firefoxcmd } },
	{ MOD|SFT,		XK_w,						spawn,				{.v = chromiumcmd } },

	{ 0, 			XF86XK_AudioMute, 			spawn, 				{.v = mutevol } },
	{ 0, 			XF86XK_AudioMicMute, 		spawn, 				{.v = mutemic } },
	{ 0, 			XF86XK_AudioLowerVolume, 	spawn, 				{.v = downvol } },
	{ 0, 			XF86XK_AudioRaiseVolume, 	spawn, 				{.v = upvol } },
	{ 0, 			XF86XK_MonBrightnessUp, 	spawn, 				{.v = upbl } },
	{ 0, 			XF86XK_MonBrightnessDown, 	spawn, 				{.v = downbl } },

	{ MOD,			XK_j,						focusstack,			{.i = +1 } },
	{ MOD,			XK_k,						focusstack,			{.i = -1 } },
	{ MOD|SFT,		XK_j,						rotatestack,		{.i = +1 } },
	{ MOD|SFT,		XK_k,						rotatestack,		{.i = -1 } },
	{ MOD,			XK_i,						incnmaster,			{.i = +1 } },
	{ MOD,			XK_d,						incnmaster,			{.i = -1 } },
	{ MOD,			XK_h,						setmfact,			{.f = -0.05} },
	{ MOD,			XK_l,						setmfact,			{.f = +0.05} },
	{ MOD|SFT,		XK_h,						setcfact,			{.f = +0.25} },
	{ MOD|SFT,		XK_l,						setcfact,			{.f = -0.25} },
	{ MOD|SFT,		XK_o,						setcfact,			{.f =	0.00} },

	{ MOD,			XK_Up,						incrgaps,			{.i = +1 } },
	{ MOD,			XK_Down,					incrgaps,			{.i = -1 } },
	{ MOD|SFT,		XK_g,						togglegaps,			{0} },
	{ MOD|CTL,		XK_g,						defaultgaps,		{0} },

	{ MOD,			XK_q,						killclient,			{0} },
	{ MOD|SFT,		XK_q,						quit,				{0} },
	{ MOD|SFT,		XK_r,						quit,				{1} }, 

	{ MOD,			XK_t,						setlayout,			{.v = &layouts[0]} },
	{ MOD,			XK_f,						setlayout,			{.v = &layouts[1]} },
	{ MOD,			XK_m,						setlayout,			{.v = &layouts[2]} },
	{ MOD,			XK_comma,					cyclelayout,		{.i = -1 } },
	{ MOD,			XK_period,					cyclelayout,		{.i = +1 } },

	{ MOD|SFT,		XK_b,						togglebar,			{0} },
	{ MOD|SFT,		XK_space,					togglefloating,		{0} },
	{ MOD|SFT,		XK_f,						togglefullscr,		{0} },

	{ MOD,			XK_0,						view,				{.ui = ~0 } },
	{ MOD|SFT,		XK_0,						tag,				{.ui = ~0 } },
	{ MOD,			XK_Right,					viewnext,			{0} },
	{ MOD,			XK_Left,					viewprev,			{0} },
	{ MOD|SFT,		XK_Right,					tagtonext,			{0} },
	{ MOD|SFT,		XK_Left,					tagtoprev,			{0} },

	SCRATCHKEYS(	XK_grave,										sptermcmd)

	TAGKEYS(		XK_1,											0)
	TAGKEYS(		XK_2,											1)
	TAGKEYS(		XK_3,											2)
	TAGKEYS(		XK_4,											3)
	TAGKEYS(		XK_5,											4)
	TAGKEYS(		XK_6,											5)
	TAGKEYS(		XK_7,											6)
	TAGKEYS(		XK_8,											7)
};

/* button definitions */
static Button buttons[] = {
	{ ClkLtSymbol,		0,		Button1,	setlayout,		{0} },
	{ ClkLtSymbol,		0,		Button3,	setlayout,		{.v = &layouts[2]} },
	{ ClkWinTitle,		0,		Button2,	zoom,			{0} },
	{ ClkStatusText,	0,		Button1,	sigstatusbar,	{.i = 1} },
	{ ClkStatusText,	0,		Button2,	sigstatusbar,	{.i = 2} },
	{ ClkStatusText,	0,		Button3,	sigstatusbar,	{.i = 3} },
	{ ClkStatusText,	0,		Button4,	sigstatusbar,	{.i = 4} },
	{ ClkStatusText,	0,		Button5,	sigstatusbar,	{.i = 5} },
	{ ClkClientWin,		MOD,	Button1,	movemouse,		{0} },
	{ ClkClientWin,		MOD,	Button2,	togglefloating, {0} },
	{ ClkClientWin,		MOD,	Button3,	resizemouse,	{0} },
	{ ClkTagBar,		0,		Button1,	view,			{0} },
	{ ClkTagBar,		0,		Button3,	toggleview,		{0} },
	{ ClkTagBar,		MOD,	Button1,	tag,			{0} },
	{ ClkTagBar,		MOD,	Button3,	toggletag,		{0} },
};

