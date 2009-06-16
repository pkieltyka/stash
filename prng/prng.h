//==============================================================================
// Pseudo Random Number Generator: PRNG.H
// Part of the Stash Project.
//
// Created: 01/20/03
// Updated: 05/28/03
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

#ifndef _PRNG_H_
#define _PRNG_H_

// Stash Library
void prng_seed(unsigned char [16]);
unsigned long prng(unsigned long, unsigned long);
void prng_array_shuffle(unsigned char *, unsigned int);
void prng_array_unshuffle(unsigned char *, unsigned int);

// External Library
void init_genrand(unsigned long);
void init_by_array(unsigned long [], unsigned long);
unsigned long genrand_int32(void);

#endif