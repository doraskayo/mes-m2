/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2016,2017,2018 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
 * Copyright © 2019 Jeremiah Orians
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

#include "gcc_req.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// CONSTANT STDIN 0
#define STDIN 0
// CONSTANT STDOUT 1
#define STDOUT 1
// CONSTANT STDERR 2
#define STDERR 2

// CONSTANT FALSE 0
#define FALSE 0
// CONSTANT TRUE 1
#define TRUE 1

// CONSTANT RLIMIT_NOFILE 1024
#define RLIMIT_NOFILE 1024
// CONSTANT FRAME_PROCEDURE 4
#define FRAME_PROCEDURE 4

struct scm
{
	SCM type;
	union
	{
		struct scm* car;
		SCM rac;
		SCM length;
		struct scm* macro;
		SCM port;
	};
	union
	{
		struct scm* cdr;
		char* cbytes;
		struct scm* closure;
		struct scm* continuation;
		SCM value;
		struct scm* vector;
		char* string;
		struct scm* struc;
	};
};

// CONSTANT CELL_SIZE sizeof(struct scm)
#define CELL_SIZE 1

struct scm *g_cells;

char **environ;
int __stdin;
int __stdout;
int __stderr;
SCM g_continuations;
struct scm* g_symbols;
SCM g_stack;
struct scm** g_stack_array;
int MAX_STRING;
char *g_buf;
SCM g_free;
int g_debug;
SCM g_symbol_max;
int* __ungetc_buf;

/* Mes core locals */
struct scm* R0;
/* param 1 */
struct scm* R1;
/* save 2 */
struct scm* R2;
/* continuation */
struct scm* R3;
/* current-module */
struct scm* M0;
/* macro */
struct scm* g_macros;
struct scm* G_MACROS;
struct scm* g_ports;
struct scm* G_PORTS;


struct scm* cell_nil;
struct scm* cell_f;
struct scm* cell_t;
struct scm* cell_dot;
struct scm* cell_arrow;
struct scm* cell_undefined;
struct scm* cell_unspecified;
struct scm* cell_closure;
struct scm* cell_circular;
struct scm* cell_begin;
struct scm* cell_call_with_current_continuation;
struct scm* cell_vm_apply;
struct scm* cell_vm_apply2;
struct scm* cell_vm_begin;
struct scm* cell_vm_begin_eval;
struct scm* cell_vm_begin_expand;
struct scm* cell_vm_begin_expand_eval;
struct scm* cell_vm_begin_expand_macro;
struct scm* cell_vm_begin_expand_primitive_load;
struct scm* cell_vm_begin_primitive_load;
struct scm* cell_vm_begin_read_input_file;
struct scm* cell_vm_call_with_current_continuation2;
struct scm* cell_vm_call_with_values2;
struct scm* cell_vm_eval;
struct scm* cell_vm_eval2;
struct scm* cell_vm_eval_check_func;
struct scm* cell_vm_eval_define;
struct scm* cell_vm_eval_macro_expand_eval;
struct scm* cell_vm_eval_macro_expand_expand;
struct scm* cell_vm_eval_pmatch_car;
struct scm* cell_vm_eval_pmatch_cdr;
struct scm* cell_vm_eval_set_x;
struct scm* cell_vm_evlis;
struct scm* cell_vm_evlis2;
struct scm* cell_vm_evlis3;
struct scm* cell_vm_if;
struct scm* cell_vm_if_expr;
struct scm* cell_vm_macro_expand;
struct scm* cell_vm_macro_expand_car;
struct scm* cell_vm_macro_expand_cdr;
struct scm* cell_vm_macro_expand_define;
struct scm* cell_vm_macro_expand_define_macro;
struct scm* cell_vm_macro_expand_lambda;
struct scm* cell_vm_macro_expand_set_x;
struct scm* cell_vm_return;
struct scm* cell_symbol_dot;
struct scm* cell_symbol_lambda;
struct scm* cell_symbol_begin;
struct scm* cell_symbol_if;
struct scm* cell_symbol_quote;
struct scm* cell_symbol_define;
struct scm* cell_symbol_define_macro;
struct scm* cell_symbol_quasiquote;
struct scm* cell_symbol_unquote;
struct scm* cell_symbol_unquote_splicing;
struct scm* cell_symbol_syntax;
struct scm* cell_symbol_quasisyntax;
struct scm* cell_symbol_unsyntax;
struct scm* cell_symbol_unsyntax_splicing;
struct scm* cell_symbol_set_x;
struct scm* cell_symbol_sc_expand;
struct scm* cell_symbol_macro_expand;
struct scm* cell_symbol_portable_macro_expand;
struct scm* cell_symbol_sc_expander_alist;
struct scm* cell_symbol_call_with_values;
struct scm* cell_symbol_call_with_current_continuation;
struct scm* cell_symbol_boot_module;
struct scm* cell_symbol_current_module;
struct scm* cell_symbol_primitive_load;
struct scm* cell_symbol_read_input_file;
struct scm* cell_symbol_write;
struct scm* cell_symbol_display;
struct scm* cell_symbol_car;
struct scm* cell_symbol_cdr;
struct scm* cell_symbol_not_a_number;
struct scm* cell_symbol_not_a_pair;
struct scm* cell_symbol_system_error;
struct scm* cell_symbol_throw;
struct scm* cell_symbol_unbound_variable;
struct scm* cell_symbol_wrong_number_of_args;
struct scm* cell_symbol_wrong_type_arg;
struct scm* cell_symbol_buckets;
struct scm* cell_symbol_builtin;
struct scm* cell_symbol_frame;
struct scm* cell_symbol_hashq_table;
struct scm* cell_symbol_module;
struct scm* cell_symbol_procedure;
struct scm* cell_symbol_record_type;
struct scm* cell_symbol_size;
struct scm* cell_symbol_stack;
struct scm* cell_symbol_argv;
struct scm* cell_symbol_mes_prefix;
struct scm* cell_symbol_mes_version;
struct scm* cell_symbol_internal_time_units_per_second;
struct scm* cell_symbol_compiler;
struct scm* cell_symbol_arch;
struct scm* cell_symbol_pmatch_car;
struct scm* cell_symbol_pmatch_cdr;
struct scm* cell_type_bytes;
struct scm* cell_type_char;
struct scm* cell_type_closure;
struct scm* cell_type_continuation;
struct scm* cell_type_function;
struct scm* cell_type_keyword;
struct scm* cell_type_macro;
struct scm* cell_type_number;
struct scm* cell_type_pair;
struct scm* cell_type_port;
struct scm* cell_type_ref;
struct scm* cell_type_special;
struct scm* cell_type_string;
struct scm* cell_type_struct;
struct scm* cell_type_symbol;
struct scm* cell_type_values;
struct scm* cell_type_variable;
struct scm* cell_type_vector;
struct scm* cell_type_broken_heart;
struct scm* cell_symbol_test;
struct scm* cell_test;
