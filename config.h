/* See LICENSE file for copyright and license details. */

#define SESSION_FILE "/tmp/dwm_session"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:pixelsize=14" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeStatus]={ col_cyan, col_gray1,  NULL  },
};

const char *spcmd1[] = {"st", "-c", "st-256color", "-n", "spterm", "-t", "Scratchpad", \
	"-g", "120x34", NULL };


/* status bar */
static const Block blocks[] = {
	/* fg           command                             interval    signal */
	{ "#FFFFFF",    "sb-power.sh",                      0,          0},
	{ col_gray3,    "sb-battery.sh",                    10,         0},
	{ col_gray3,    "sb-datetime.sh",                   30,         1},
	{ col_gray3,    "sb-volume.sh",                     0,          2},
	{ col_gray3,    "sb-brightness.sh",                 0,          3},
	// { col_gray1,    "sb-disk",                          9000,        2},
	// { col_gray3,    "sb-internet",                      10,          4},
	// { col_cyan,     "sb-mailbox",                       0,           5},
	// { "#000001",    "sb-moonphase",                     0,           6},
	// { "#1F0077",    "sb-forecast",                      0,           7},
	// { "#000077",    "sb-volume",                        0,           8},
	// { "#F77000",    "sb-pacpackages",                   0,           9},
	// { "#177000",    "sb-sync",                          0,           10},
	// { col_gray1,    "sb-mpc",                           0,           26},
	// { col_gray2,    "sb-music",                         0,           11},
	// { col_gray3,    "sb-tasks",                         10,          12},
	// { col_gray4,    "sb-notes",                         0,           13},
	// { col_cyan,     "echo '';cat /tmp/recordingicon",   0,           14},
};

/* inverse the order of the blocks, comment to disable */
#define INVERSED	1
/* delimeter between blocks commands. NULL character ('\0') means no delimeter. */
static char delimiter[] = " | ";
/* max number of character that one block command can output */
#define CMDLENGTH	50


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance        title               tags mask       isfloating  monitor */
	{ "Gimp",               NULL,           NULL,               0,              1,          -1 },
	{ "Inkscape",           NULL,           NULL,               0,              1,          -1 },
	{ "Firefox",            NULL,           NULL,               1 << 8,         0,          -1 },
	{ "qutebrowser",        NULL,           NULL,               1 << 8,         0,          -1 },
	{ "Chromium",           NULL,           NULL,               1 << 8,         0,          -1 },
	{ "st-256color",        "floatterm",    NULL,               0,              1,          -1 },
	{ "st-256color",        "spterm",       "Scratchpad",       SPTAG(0),       1,          -1 },
	{ "jetbrains-studio",   NULL,           NULL,               0,              1,          -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-c", "-l", "10", "-m", dmenumon, "-fn", dmenufont, 
	"-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL
};
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                             key                 function            argument */
	{ MODKEY,                               XK_space,           spawn,              {.v = dmenucmd } },
	{ MODKEY,                               XK_Return,          spawn,              {.v = termcmd } },
	{ MODKEY|ShiftMask,                     XK_b,               togglebar,          {0} },
	{ MODKEY,                               XK_j,               focusstack,         {.i = +1 } },
	{ MODKEY,                               XK_k,               focusstack,         {.i = -1 } },
	{ MODKEY|ShiftMask,                     XK_j,               movestack,          {.i = +1 } },
	{ MODKEY|ShiftMask,                     XK_k,               movestack,          {.i = -1 } },
	{ MODKEY,                               XK_i,               incnmaster,         {.i = +1 } },
	{ MODKEY,                               XK_d,               incnmaster,         {.i = -1 } },
	{ MODKEY,                               XK_l,               setmfact,           {.f = +0.05} },
	{ MODKEY,                               XK_h,               setmfact,           {.f = -0.05} },
	{ MODKEY,                               XK_z,               zoom,               {0} },
	{ MODKEY,                               XK_Tab,             view,               {0} },
	{ MODKEY|ShiftMask,                     XK_q,               killclient,         {0} },
	{ MODKEY|ShiftMask,                     XK_t,               setlayout,          {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,                     XK_f,               setlayout,          {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,                     XK_m,               setlayout,          {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,                     XK_space,           setlayout,          {0} },
	{ MODKEY,                               XK_f,               togglefloating,     {0} },
	{ MODKEY,                               XK_0,               view,               {.ui = ~0 } },
	{ MODKEY|ShiftMask,                     XK_0,               tag,                {.ui = ~0 } },
	{ MODKEY,                               XK_period,          focusmon,           {.i = +1 } },
	{ MODKEY,                               XK_comma,           focusmon,           {.i = -1 } },
	{ MODKEY|ShiftMask,                     XK_period,          tagmon,             {.i = +1 } },
	{ MODKEY|ShiftMask,                     XK_comma,           tagmon,             {.i = -1 } },
	{ MODKEY,                               XK_s,               togglescratch,      {.ui = 0 } },
	{ MODKEY,                               XK_c,               movecenter,         {0} },
	{ MODKEY,                               XK_n,               viewadjacent,       {.i = +1 } },
	{ MODKEY|ShiftMask,                     XK_n,               viewadjacent,       {.i = -1 } },
	{ MODKEY,                               XK_Down,            moveresize,         {.v = (int []){ 0, 25, 0, 0 }}},
	{ MODKEY,                               XK_Up,              moveresize,         {.v = (int []){ 0, -25, 0, 0 }}},
	{ MODKEY,                               XK_Right,           moveresize,         {.v = (int []){ 25, 0, 0, 0 }}},
	{ MODKEY,                               XK_Left,            moveresize,         {.v = (int []){ -25, 0, 0, 0 }}},
	{ MODKEY|ShiftMask,                     XK_Down,            moveresize,         {.v = (int []){ 0, 0, 0, 25 }}},
	{ MODKEY|ShiftMask,                     XK_Up,              moveresize,         {.v = (int []){ 0, 0, 0, -25 }}},
	{ MODKEY|ShiftMask,                     XK_Right,           moveresize,         {.v = (int []){ 0, 0, 25, 0 }}},
	{ MODKEY|ShiftMask,                     XK_Left,            moveresize,         {.v = (int []){ 0, 0, -25, 0 }}},
	TAGKEYS(                                XK_1,                                   0)
	TAGKEYS(                                XK_2,                                   1)
	TAGKEYS(                                XK_3,                                   2)
	TAGKEYS(                                XK_4,                                   3)
	TAGKEYS(                                XK_5,                                   4)
	TAGKEYS(                                XK_6,                                   5)
	TAGKEYS(                                XK_7,                                   6)
	TAGKEYS(                                XK_8,                                   7)
	TAGKEYS(                                XK_9,                                   8)
	{ MODKEY|ControlMask|ShiftMask,         XK_r,               quit,               {1} },
	{ MODKEY|ControlMask|ShiftMask,         XK_q,               quit,               {0} },
};

/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
	/* width change         height change */
	{ +scrollsensetivity,	0 },
	{ -scrollsensetivity,	0 },
	{ 0,                    +scrollsensetivity },
	{ 0,                    -scrollsensetivity },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function            argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,          {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,          {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,               {0} },

	{ ClkStatusText,        0,              Button1,        sendstatusbar,      {.i = 1 } },
	{ ClkStatusText,        0,              Button2,        sendstatusbar,      {.i = 2 } },
	{ ClkStatusText,        0,              Button3,        sendstatusbar,      {.i = 3 } },
	{ ClkStatusText,        0,              Button4,        sendstatusbar,      {.i = 4 } },
	{ ClkStatusText,        0,              Button5,        sendstatusbar,      {.i = 5 } },
	{ ClkStatusText,        ShiftMask,      Button1,        sendstatusbar,      {.i = 6 } },

	{ ClkClientWin,         MODKEY,         Button1,        movemouse,          {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating,     {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,        {0} },
	{ ClkClientWin,         MODKEY,         Button4,        resizemousescroll,  {.v = &scrollargs[0]} },
	{ ClkClientWin,         MODKEY,         Button5,        resizemousescroll,  {.v = &scrollargs[1]} },
	{ ClkClientWin,         MODKEY,         Button6,        resizemousescroll,  {.v = &scrollargs[2]} },
	{ ClkClientWin,         MODKEY,         Button7,        resizemousescroll,  {.v = &scrollargs[3]} },
	{ ClkTagBar,            0,              Button1,        view,               {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,         {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,                {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,          {0} },
};

