/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2016,2017,2019,2020 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
 *
 * This file is part of GNU Mes.
 *
 * GNU Mes is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * GNU Mes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Mes.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mes/lib-mini.h"

#define SYS_exit   "0x01"

// *INDENT-OFF*
void
_exit (int code)
{
  asm (
       "mov    $"SYS_exit",%%eax\n\t"
       "mov    %0,%%ebx\n\t"
       "push   %%ebx\n\t"
       "push   %%ebx\n\t"
       "int    $0x80\n\t"
       : // no outputs "=" (r)
       : "rm" (code)
       : "eax", "ebx"
       );
  // not reached
  _exit (0);
}
