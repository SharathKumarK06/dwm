/*
 * moveresize
 *
 * Description
 * This changes allows you to move and resize dwm's clients using keyboard bindings.
 *
 * Usage
 * Put the following moveresize() function somewhere in your dwm.c.
 *
 * 1. Add a moveresize() function definition in dwm.c below the line:
 * static void moveresize(const Arg *arg);
 *
 * 2. Insert the bindings into the keys list. Here is an example which uses the
 * arrow keys to move (mod+arrow) or resize (mod+shift+arrow) the selected
 * client:
 * { MODKEY,				XK_Down,	moveresize,		{.v = (int []){ 0, 25, 0, 0 }}},
 * { MODKEY,				XK_Up,		moveresize,		{.v = (int []){ 0, -25, 0, 0 }}},
 * { MODKEY,				XK_Right,	moveresize,		{.v = (int []){ 25, 0, 0, 0 }}},
 * { MODKEY,				XK_Left,	moveresize,		{.v = (int []){ -25, 0, 0, 0 }}},
 * { MODKEY|ShiftMask,			XK_Down,	moveresize,		{.v = (int []){ 0, 0, 0, 25 }}},
 * { MODKEY|ShiftMask,			XK_Up,		moveresize,		{.v = (int []){ 0, 0, 0, -25 }}},
 * { MODKEY|ShiftMask,			XK_Right,	moveresize,		{.v = (int []){ 0, 0, 25, 0 }}},
 * { MODKEY|ShiftMask,			XK_Left,	moveresize,		{.v = (int []){ 0, 0, -25, 0 }}}, 
 *
 */

static void
moveresize(const Arg *arg)
{
	XEvent ev;
	Monitor *m = selmon;
	if(!(m->sel && arg && arg->v && m->sel->isfloating))
		return;
	resize(m->sel, m->sel->x + ((int *)arg->v)[0],
		m->sel->y + ((int *)arg->v)[1],
		m->sel->w + ((int *)arg->v)[2],
		m->sel->h + ((int *)arg->v)[3],
		True);
	while(XCheckMaskEvent(dpy, EnterWindowMask, &ev));
}

