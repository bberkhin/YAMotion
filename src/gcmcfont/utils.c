/*
 * G-code meta compiler - Font conversion
 *
 * Copyright (C) 2015  B. Stultiens
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "config.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils.h"

void testalloc(void **p, unsigned n, unsigned *na, size_t elemsize)
{
	if(!*p) {
		assert(n == 0);
		*p = calloc(8, elemsize);
		assert(*p != NULL);
		*na = 8;
	}
	if(n >= *na) {
		void *pp = calloc(2 * *na, elemsize);
		assert(pp != NULL);
		memcpy(pp, *p, n*elemsize);
		free(*p);
		*p = pp;
		*na *= 2;
	}
}
