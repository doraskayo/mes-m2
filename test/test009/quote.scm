;;; GNU Mes --- Maxwell Equations of Software
;;; Copyright © 2016,2018 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
;;;
;;; This file is part of GNU Mes.
;;;
;;; GNU Mes is free software; you can redistribute it and/or modify it
;;; under the terms of the GNU General Public License as published by
;;; the Free Software Foundation; either version 3 of the License, or (at
;;; your option) any later version.
;;;
;;; GNU Mes is distributed in the hope that it will be useful, but
;;; WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.
;;;
;;; You should have received a copy of the GNU General Public License
;;; along with GNU Mes.  If not, see <http://www.gnu.org/licenses/>

;; Setup output file
(set-current-output-port (open-output-file "test/results/test009.answer"))

;; Demonstrate using 'S-expression
(core:display "making a quote with ' character\n")
(core:write '(display (string-append "Hello " "Guix" "\n")))
(core:display #\newline)
(core:write '(a b c (d e)))

;; Demonstrate using (quote S-expression)
(core:display "\nmake a quote with quote\n")
(core:write (quote (display (string-append "Hello " "Guix" "\n"))))
(core:display #\newline)
(core:write (quote (a b c (d e))))

;; Demonstrate 'block
(core:display 'foo)
(core:display #\newline)
(exit 0)
