/* -*-comment-start: "//";comment-end:""-*-
 * Mes --- Maxwell Equations of Software
 * Copyright © 2017 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
 *
 * This file is part of Mes.
 *
 * Mes is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * Mes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Mes.  If not, see <http://www.gnu.org/licenses/>.
 */

int test ();

int
main ()
{
  int r = test ();
#if __MESC__
  asm ("mov____%eax,%ebx");
  asm ("mov____$i32,%eax SYS_exit");
  asm ("int____$0x80");
#elif __GNUC__
  asm ("mov    %0,%%ebx"
       : // no outputs
       : "" (r));
  asm ("mov    $1,%eax");
  asm ("int    $0x80");
#elif __TINYC__
  asm ("mov    %0,%%ebx"
       : // no outputs
       : "Ir" (r));
  asm ("mov    $1,%eax");
  asm ("int    $128");
#endif // __GNUC__
}
