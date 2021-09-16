/* See LICENSE file for copyright and license details. */
/* make var swap betwin 1 et 2 */
static int swap_layout=1;
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 15;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int rmaster            = 1;        /* 1 means master-area is initially on the right */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 0;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "FiraCode\ Nerd\ Font:size=12" };
static const char dmenufont[]       =   "FiraCode\ Nerd\ Font:size=12";
static const char col_gray1[]       = "#000000";
/* static const char col_gray1[]       = "#222222"; */
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char gruv_black[]      = "#282828";
static const char gruv_red[]        = "#9d0006";
static const char gruv_yellow[]     = "#d79921";
static const char gruv_white[]     = "#ebdbb2";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },

  [SchemeTagsSel]   = { gruv_white, gruv_yellow, "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
  [SchemeTagsNorm]  = { gruv_white, gruv_red,    "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
  [SchemeInfoSel]   = { gruv_white, gruv_black,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
  [SchemeInfoNorm]  = { gruv_white, gruv_black,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
	[SchemeStatus]    = { gruv_white, gruv_black,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}

	/* [SchemeStatus]  = { col_gray3, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty} */
	/* [SchemeTagsSel]  = { col_gray4, col_cyan,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty} */
  /* [SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty} */
  /* [SchemeInfoSel]  = { col_gray4, col_cyan,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty} */
  /* [SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty} */

};

/* tagging */
static const char *tags[] = { "1", "2", "3" ,"4" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Chromium",  NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Brave",    NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 3,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachdirection = 3;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]",      tile },    /* first entry is default */
	{ "<>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
   
    // new terminal
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
   
    // hide bare
	{ MODKEY,                       XK_b,      togglebar,      {0} },
   
    // move betwin layout
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
   
    // move to last tag
	{ MODKEY,                       XK_Tab,    view,           {0} },
   
    // kill layout
	{ MODKEY,                       XK_q,      killclient,     {0} },
   
    // full layout
	//{ MODKEY,                       XK_space,  setlayout,      {.v = &layouts[2]} },

 	{ MODKEY,                     	XK_space,  cyclelayout,    {.i = -1 } },
 	{ MODKEY,                       XK_period, cyclelayout,    {.i = +1 } },
   
    // till layout
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[0]} },
   
    // float layout
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[1]} },
   
    // last {full,float,till}=focuse
	/* { MODKEY,                       XK_space,  setlayout,      {0} }, */
   
    // focuse master
	{ MODKEY|ControlMask,           XK_space,  focusmaster,    {0} },
   
    // off floating
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
   
    // swip betwin layout
	{ MODKEY,                       XK_r,      togglermaster,  {0} },
   
    // viw all
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
   
    // goto tag
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
   
    //restart dwm
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
	/* signum       function        argument  */
	{ 1,            setlayout,      {.v = 0} },
};

