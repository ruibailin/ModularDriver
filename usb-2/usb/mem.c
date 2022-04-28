
/*------------------------------------
 * mem.c
 * Create:  2021-11-16
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */


/*================================================================*/
void btr_usb_memcpy(void *s,void *d,int l);
void btr_usb_memcpy(void *s,void *d,int l)
{
	int i, il;
	il = l>>2;
	for(i=0;i<il;i++)
	{
		*((int *)s+i) = *((int *)d+i);
	}
	for(i=0;i<(l-il);i++)
	{
		*((char *)s+i) = *((char *)d+i);
	}
}


void btr_usb_memset(void *s,int v,int l);
void btr_usb_memset(void *s,int v,int l)
{
	int i, il;
	il = l>>2;
	for(i=0;i<il;i++)
	{
		*((int *)s+i) = v;
	}
	for(i=0;i<(l-il);i++)
	{
		*((char *)s+i) = (char)v;
	}
}
/*================================================================*/

/* end of mem.c */
