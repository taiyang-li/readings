/* imageshared.c
 *
 * Copyright (c) 2001 Sean Walton and Macmillan Publishers.  Use may be in
 * whole or in part in accordance to the General Public License (GPL).
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
*/

/*****************************************************************************/
/*** imageshared.c                                                         ***/
/***                                                                       ***/
/*** Shared tools for UDP file multicasting.                               ***/
/*****************************************************************************/

#include <stdio.h>
#include "imagecaster.h"

/*---------------------------------------------------------------------*/
/*--- dx_hack_hash - relatively uniform hash (leveraged).           ---*/
/*---------------------------------------------------------------------*/
u32 dx_hack_hash(const void *d, int len)
{	const char *data = d;
	u32 hash0 = 0x12A3FE2D;
	u32 hash1 = 0x37ABE8F9;
	while ( len-- )
	{
		u32 hash = hash1 + (hash0 ^ (*data++ * 71523));
		if ( hash < 0 )
			hash -= 0x7FFFFFFF;	/* when is hash going to be less than zero if unsigned? */
		hash1 = hash0;
		hash0 = hash;
	}
	return hash0;
}

/*---------------------------------------------------------------------*/
/*--- checksum - calculate the checksum of data.                    ---*/
/*---------------------------------------------------------------------*/
u16 checksum(const void *d, int len)
{
	u32 sum = 0;
	const unsigned char *data = d;

	while ( len-- )
		sum += *data++;
	sum = (sum & 0xFFFF) + (sum >> 16);
	sum = (sum & 0xFFFF) + (sum >> 16);
	return sum;
}

/*---------------------------------------------------------------------*/
/*--- ismulticast - check range for multicast address.              ---*/
/*---------------------------------------------------------------------*/
int ismulticast(struct in_addr in_addr)
{	struct in_addr MCAST_LOWER, MCAST_UPPER;

	inet_aton("224.0.0.0", &MCAST_LOWER);
	inet_aton("239.255.255.255", &MCAST_UPPER);
	return (ntohl(MCAST_LOWER.s_addr) <= ntohl(in_addr.s_addr)  &&
			(ntohl(in_addr.s_addr) <= ntohl(MCAST_UPPER.s_addr)) );
}

