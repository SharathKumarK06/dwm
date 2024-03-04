/*
 * next prev tag
 * Description
 * - Increment or decrement the selected tag
 * - [shiftview.c](https://lists.suckless.org/dev/1104/7590.html) is a better
 *   implementation of this, allowing you to rotate the selected tags
 * 
 * Example
 * static Key keys[] = {
 * 	   ...
 *	{ MODKEY,              XK_i,           view_adjacent,  { .i = +1 } },
 *	{ MODKEY,              XK_u,           view_adjacent,  { .i = -1 } },
 *	   ...
 * };
 * static Button buttons[] = {
 * 	   ...
 *	{ ClkTagBar,            0,              Button4,        view_adjacent,     { .i = -1 } },
 * 	{ ClkTagBar,            0,              Button5,        view_adjacent,     { .i = +1 } },
 * };
 *
 * Author
 * - Rob Pilling - robpilling gmail com
 */
void
viewadjacent(const Arg *arg)
{
	int i, curtags;
	int seltag = 0;
	Arg a;

	curtags = selmon->tagset[selmon->seltags];
	for(i = 0; i < LENGTH(tags); i++)
		if(curtags & (1 << i)){
			seltag = i;
			break;
		}

	seltag = (seltag + arg->i) % (int)LENGTH(tags);
	if(seltag < 0)
		seltag += LENGTH(tags);

	a.i = (1 << seltag);
	view(&a);
}
