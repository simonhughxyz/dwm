/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12", "FontAwesome:size=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_black[]       = "#000000";
static const char col_white[]       = "#ffffff";
static const char col_gray[]        = "#eeeeee";
static const char col_purple_light[]  = "#bb00ff";
static const char col_purple_dark[]   = "#9000ff";
static const char *colors[][3]      = {
	/*               fg                 bg                  border   */
	[SchemeNorm]   = { col_purple_light,  col_black,          col_black },
	[SchemeSel]    = { col_white,         col_purple_dark,    col_purple_dark  },
	[SchemeTitle]  = { col_gray,          col_black,          col_black  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "Vid" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance  title  tags mask  iscentered  isfloating  issticky  monitor  scratch key  float x,y,w,h floatborderpx */
	{ "mpv",       NULL,     NULL,  1 << 18,   1,          0,          0,        -1,       0,          -1,-1,1000,500, -1 },
	{ "powermenu", NULL,     NULL,  0,         1,          1,          1,        -1,      'P',         -1,-1,500,300, -1 },
	{ "passmenu",  NULL,     NULL,  0,         1,          1,          0,        -1,      'p',         -1,-1,800,400, -1 },
	{ "homemenu",  NULL,     NULL,  0,         1,          1,          0,        -1,      'h',         -1,-1,800,400, -1 },
	{ "appmenu",   NULL,     NULL,  0,         1,          1,          0,        -1,      'a',         -1,-1,800,400, -1 },
	{ "clipmenu",  NULL,     NULL,  0,         1,          1,          0,        -1,      'c',         -1,-1,800,400, -1 },
	{ "srmenu",    NULL,     NULL,  0,         0,          1,          1,        -1,      's',         -1,-1,1910,200, 1 },
	{ "calc",      NULL,     NULL,  0,         1,          1,          0,        -1,      'C',         -1,-1,800,400, -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* Key Definitions */

#define MODKEY Mod4Mask
#define ALT Mod1Mask
#define CTRL ControlMask
#define SHIFT ShiftMask

/* default terminal */
#define TERMINAL "/usr/local/bin/st"

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* helper to launch terminal based application */
#define TERMCMD(class, title, cmd) SHCMD(TERMINAL " -c " class " -t " title " -e " cmd)

/* helper to launch scratchpad applications */
#define SCRATCHCMD(skey, class, title, cmd) { .v = (const char*[]){skey, "/bin/sh", "-c", TERMINAL " -c " class " -t " title " -e " cmd, NULL} }

/* Tag Manipulation Controls */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                  KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|CTRL,             KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|SHIFT,            KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|CTRL|SHIFT,       KEY,      toggletag,      {.ui = 1 << TAG} },

/* Toggle Keys */
#define TOGGLEKEYUPDATE SHCMD("sleep 0.1; pkill -RTMIN+11 dwmblocks")
#define TOGGLEKEYS \
    { {0},                     XK_Caps_Lock,    spawn,        TOGGLEKEYUPDATE }, \
    { {0},                     XK_Num_Lock,     spawn,        TOGGLEKEYUPDATE }, \
    { {0},                     XK_Scroll_Lock,  spawn,        TOGGLEKEYUPDATE },

 /* Volume Controls */
#define VOLCMD(arg) SHCMD("/bin/pulsemixer " arg "; pkill -RTMIN+10 dwmblocks")

#define VOLADDKEY(KEY) \
    { MODKEY,                  KEY,      spawn,          VOLCMD("--change-volume +5") }, \
    { MODKEY|CTRL,             KEY,      spawn,          VOLCMD("--change-volume +1") }, \
    { MODKEY|SHIFT,            KEY,      spawn,          VOLCMD("--change-volume +20") }, \

#define VOLSUBKEY(KEY) \
    { MODKEY,                  KEY,      spawn,          VOLCMD("--change-volume -5") }, \
    { MODKEY|CTRL,             KEY,      spawn,          VOLCMD("--change-volume -1") }, \
    { MODKEY|SHIFT,            KEY,      spawn,          VOLCMD("--change-volume -20") }, \

/* Screen Brightness Controls */
#define BRIGHTNESSCMD(arg) SHCMD("/bin/xbacklight " arg)
#define BRIGHTNESSKEYS \
    { MODKEY|ALT,              XK_1,     spawn,          BRIGHTNESSCMD("10") }, \
    { MODKEY|ALT,              XK_2,     spawn,          BRIGHTNESSCMD("20") }, \
    { MODKEY|ALT,              XK_3,     spawn,          BRIGHTNESSCMD("30") }, \
    { MODKEY|ALT,              XK_4,     spawn,          BRIGHTNESSCMD("40") }, \
    { MODKEY|ALT,              XK_5,     spawn,          BRIGHTNESSCMD("50") }, \
    { MODKEY|ALT,              XK_6,     spawn,          BRIGHTNESSCMD("60") }, \
    { MODKEY|ALT,              XK_7,     spawn,          BRIGHTNESSCMD("70") }, \
    { MODKEY|ALT,              XK_8,     spawn,          BRIGHTNESSCMD("80") }, \
    { MODKEY|ALT,              XK_9,     spawn,          BRIGHTNESSCMD("90") }, \
    { MODKEY|ALT,              XK_0,     spawn,          BRIGHTNESSCMD("0") },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray, "-nf", col_gray, "-sb", col_purple_dark, "-sf", col_gray, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *lockcmd[]  = { "lock", NULL };
static const char *webcmd[]  = { "www", NULL };
static const char *chromecmd[]  = { "chromium", NULL };
static const char *torcmd[]  = { "torbrowser-launcher", NULL };

static Key keys[] = {
	/* modifier                key                  function        argument */

    /* Toggle Keys */
    TOGGLEKEYS

    /* Screen Brightness Controls */
    BRIGHTNESSKEYS

    /* Volume Controls */
    VOLADDKEY(                 XK_equal)
    VOLSUBKEY(                 XK_minus)
	{ MODKEY,                  XK_m,                spawn,          VOLCMD("--toggle-mute") },

    /* Terminal Based Applications */
	{ MODKEY,                  XK_n,                spawn,          TERMCMD("newsboat", "newsboat", "newsboat") },
	{ MODKEY|SHIFT,            XK_Return,           spawn,          TERMCMD("nnn", "nnn", "nnn") },
	{ MODKEY,                  XK_t,                spawn,          TERMCMD("bottom", "bottom", "btm -b") },
	{ MODKEY|SHIFT,            XK_t,                spawn,          TERMCMD("bottom", "bottom", "btm") },
	{ MODKEY|SHIFT,            XK_m,                spawn,          TERMCMD("netomutt", "mail", "netomutt") },
	{ MODKEY,                  XK_p,                spawn,          TERMCMD("pulsemixer", "pulsemixer", "pulsemixer") },

    /* Scratchpads */
	{ CTRL|ALT,                XK_Delete,           togglescratch,  SCRATCHCMD("P", "powermenu", "power", "powermenu") },
	{ MODKEY|SHIFT,            XK_p,                togglescratch,  SCRATCHCMD("p", "passmenu", "pass", "pass menu") },
	{ MODKEY,                  XK_a,                togglescratch,  SCRATCHCMD("h", "homemenu", "home", "home") },
	{ MODKEY|SHIFT,            XK_a,                togglescratch,  SCRATCHCMD("a", "appmenu", "apps", "appmenu") },
	{ MODKEY,                  XK_c,                togglescratch,  SCRATCHCMD("c", "clipmenu", "clip", "fclip") },
	{ MODKEY,                  XK_s,                togglescratch,  SCRATCHCMD("s", "srmenu", "search", "srmenu") }, 
	{ MODKEY|SHIFT,            XK_c,                togglescratch,  SCRATCHCMD("C", "calc", "calc", "qalc") },

	{ MODKEY,                  XK_Return,           spawn,          {.v = termcmd } },
	{ MODKEY,                  XK_x,                spawn,          {.v = lockcmd } },
	{ MODKEY,                  XK_w,                spawn,          {.v = webcmd } },
	{ MODKEY|SHIFT,            XK_b,                togglebar,      {0} },
	{ MODKEY,                  XK_Right,            focusstack,     {.i = +1 } },
	{ MODKEY,                  XK_Left,             focusstack,     {.i = -1 } },
	{ MODKEY,                  XK_i,                incnmaster,     {.i = +1 } },
	{ MODKEY,                  XK_d,                incnmaster,     {.i = -1 } },
	{ MODKEY,                  XK_z,                zoom,           {0} },
	{ MODKEY,                  XK_Tab,              view,           {0} },
	{ MODKEY,                  XK_BackSpace,        view,           {0} },
	{ MODKEY,                  XK_q,                killclient,     {0} },
	{ MODKEY,                  XK_Delete,           killclient,     {0} },
	{ MODKEY,                  XK_numbersign,       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                  XK_apostrophe,       setlayout,      {.v = &layouts[13]} },
	{ MODKEY,                  XK_f,                setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                  XK_space,            setlayout,      {0} },
	{ MODKEY|SHIFT,            XK_Left,             setmfact,       {.f = -0.05} },
	{ MODKEY|SHIFT,            XK_Right,            setmfact,       {.f = +0.05} },
	{ MODKEY|SHIFT,            XK_space,            togglefloating, {0} },
	{ MODKEY|SHIFT,            XK_s,                togglesticky,   {0} },
	{ MODKEY|SHIFT,            XK_Up,               setcfact,       {.f = +0.25} },
	{ MODKEY|SHIFT,            XK_Down,             setcfact,       {.f = -0.25} },
	{ MODKEY|SHIFT,            XK_o,                setcfact,       {.f =  0.00} },
	/* { MODKEY,               XK_0,                view,           {.ui = ~0 } }, */
	/* { MODKEY|SHIFT,         XK_0,                tag,            {.ui = ~0 } }, */
	{ MODKEY,                  XK_bracketright,     viewnext,       {0} },
	{ MODKEY,                  XK_bracketleft,      viewprev,       {0} },
	{ MODKEY|SHIFT,            XK_bracketright,     viewvacantnext, {0} },
	{ MODKEY|SHIFT,            XK_bracketleft,      viewvacantprev, {0} },
	{ MODKEY,                  XK_comma,            focusmon,       {.i = -1 } },
	{ MODKEY,                  XK_period,           focusmon,       {.i = +1 } },
	{ MODKEY|SHIFT,            XK_comma,            tagmon,         {.i = -1 } },
	{ MODKEY|SHIFT,            XK_period,           tagmon,         {.i = +1 } },
	TAGKEYS(                   XK_1,                                0)
	TAGKEYS(                   XK_2,                                1)
	TAGKEYS(                   XK_3,                                2)
	TAGKEYS(                   XK_4,                                3)
	TAGKEYS(                   XK_5,                                4)
	TAGKEYS(                   XK_6,                                5)
	TAGKEYS(                   XK_7,                                6)
	TAGKEYS(                   XK_8,                                7)
	TAGKEYS(                   XK_9,                                8)
	TAGKEYS(                   XK_0,                                9)
	TAGKEYS(                   XK_F1,                               10)
	TAGKEYS(                   XK_F2,                               11)
	TAGKEYS(                   XK_F3,                               12)
	TAGKEYS(                   XK_F4,                               13)
	TAGKEYS(                   XK_F9,                               14)
	TAGKEYS(                   XK_F10,                              15)
	TAGKEYS(                   XK_F11,                              16)
	TAGKEYS(                   XK_F12,                              17)
	TAGKEYS(                   XK_v,                                18)
	{ MODKEY|SHIFT,            XK_q,                quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

