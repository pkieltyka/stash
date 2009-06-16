//==============================================================================
// Stash: STASH.H
// Part of the Stash project.
//
// Created: 01/20/03
// Updated: 02/20/03
//
// Copyright (C) 2003 Peter Kieltyka <peter_kieltyka@hotmail.com>
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//==============================================================================

#ifndef _STASH_H_
#define _STASH_H_

#define VERSION		"0.3"				// Application version
#define CONTSIZE	1024				// Container byte range
#define	DATASIZE	CONTSIZE>>3			// Data byte range

#define STARTBYTE	64

struct stash_hdr {
	unsigned long len;
};


int encode_steg(char *, char *, char *, unsigned char *);
int decode_steg(char *, char *, unsigned char *);


#endif
