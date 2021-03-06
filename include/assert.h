//
// assert.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2019  R. Stange <rsta2@o2online.de>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef _assert_h
#define _assert_h

#include <circle/macros.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NDEBUG
	#define assert(expr)	((void) 0)
#else
	void assertion_failed (const char *pExpr, const char *pFile, unsigned nLine);

	#define assert(expr)	(  likely (expr)	\
				 ? ((void) 0)		\
				 : assertion_failed (#expr, __FILE__, __LINE__))
#endif

#define ASSERT_STATIC(expr)	extern int assert_static[(expr) ? 1 : -1]

#ifdef __cplusplus
}
#endif

#endif
