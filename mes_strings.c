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

#include "mes.h"
#include "mes_constants.h"

char *itoa (int number);
SCM cons_ (SCM x, SCM y);
struct scm* make_cell(SCM type, struct scm* car, struct scm* cdr);
SCM make_cell__(SCM type, SCM car, SCM cdr);
struct scm* make_bytes(char const* s, size_t length);
SCM write_error_ (SCM x);
struct scm* hash_ref (SCM table, SCM key, SCM dflt);
struct scm* hash_set_x (SCM table, SCM key, SCM value);
void assert_max_string(int i, char const* msg, char* string);
SCM error(SCM key, SCM x);

char const* list_to_cstring(struct scm* list, int* size)
{
	int i = 0;
	list = bad2good(list);

	while(GetSCM2(list) != cell_nil)
	{
		assert_max_string(i, "list_to_string", g_buf);

		g_buf[i] = bad2good(list->car)->value;
		i = i + 1;
		list = bad2good(list->cdr);
	}

	g_buf[i] = 0;
	*size = i;
	return g_buf;
}

struct scm* make_string_(char const* s) /* internal only */
{
	assert_max_string(strlen(s) , "make_string_", (char*)s);

	SCM x = make_cell__(TSTRING, strlen(s), 0);
	struct scm* y = Getstructscm2(x);
	SCM v = GetSCM2(make_bytes(s, strlen(s)));
	y->rdc = v;
	return y;
}

struct scm* make_string(char const* s, int length)
{
	assert_max_string(length, "make_string", (char*)s);
	SCM x = make_cell__(TSTRING, length, 0);
	struct scm* y = Getstructscm2(x);
	SCM v = GetSCM2(make_bytes(s, length));
	y->rdc = v;
	return good2bad(y);
}

struct scm* string_equal_p(SCM a, SCM b)
{
	struct scm* a2 = Getstructscm2(a);
	struct scm* b2 = Getstructscm2(b);
	assert(a2->type == TSTRING || a2->type == TKEYWORD);
	assert(b2->type == TSTRING || b2->type == TKEYWORD);
	struct scm* tee = Getstructscm2(cell_t);
	struct scm* nil = Getstructscm2(cell_f);

	/* If they are the same thing */
	if(a == b) return tee;

	/* If they point to the same string */
	if(a2->cdr == b2->cdr) return tee;

	/*If they are both empty strings */
	if((NULL == a2->car) && (NULL == b2->car)) return tee;

	/* If they are different lengths they can't be the same string */
	if(a2->length != b2->length) return nil;

	/* Need to fix */
	char* s1 = (char*)&bad2good(a2->cdr)->string;
	char* s2 = (char*)&bad2good(b2->cdr)->string;

	while(s1[0] == s2[0])
	{
		if(0 == s1[0]) return tee;
		s1 = s1 + 1;
		s2 = s2 + 1;
	}

	return nil;
}

struct scm* symbol_to_string(SCM symbol)
{
	struct scm* a = Getstructscm2(symbol);
	return make_cell(TSTRING, bad2good(a->car), bad2good(a->cdr));
}

struct scm* symbol_to_keyword(SCM symbol)
{
	struct scm* a = Getstructscm2(symbol);
	return make_cell(TKEYWORD, bad2good(a->car), bad2good(a->cdr));
}

struct scm* make_symbol(SCM string)
{
	struct scm* s = Getstructscm2(string);
	struct scm* x = make_cell(TSYMBOL, bad2good(s->car), bad2good(s->cdr));
	hash_set_x(g_symbols, string, GetSCM2(x));
	return x;
}

struct scm* string_to_symbol(SCM string)
{
	struct scm* x = hash_ref(g_symbols, string, cell_f);

	if(GetSCM2(x) == cell_f)
	{
		x = make_symbol(string);
	}

	return good2bad(x);
}

struct scm* cstring_to_symbol(char const *s)
{
	SCM string = GetSCM2(make_string_(s));
	return bad2good(string_to_symbol(string));
}

/* EXTERNAL */

struct scm* string_equal_p_(SCM a, SCM b)
{
	return good2bad(string_equal_p(a, b));
}

struct scm* symbol_to_string_(SCM symbol)
{
	return good2bad(symbol_to_string(symbol));
}

struct scm* symbol_to_keyword_(SCM symbol)
{
	return good2bad(symbol_to_keyword(symbol));
}

struct scm* keyword_to_string(SCM keyword)
{
	struct scm* a = Getstructscm2(keyword);
	return good2bad(Getstructscm2(make_cell__(TSTRING, a->length, a->rdc)));
}

struct scm* make_symbol_(SCM string)
{
	return good2bad(make_symbol(string));
}

struct scm* string_to_list(SCM string)
{
	struct scm* x = Getstructscm2(string);
	char* s = (char*)&bad2good(x->cdr)->rdc;
	SCM i = strlen(s);
	struct scm* p = Getstructscm2(cell_nil);

	while(0 != i)
	{
		i = i - 1;
		int c = (0xFF & s[i]);
		p = Getstructscm2(cons_(make_cell__ (TCHAR, 0, c), GetSCM2(p)));
	}

	return good2bad(p);
}

struct scm* list_to_string(SCM list)
{
	int size;
	char const *s = list_to_cstring(good2bad(Getstructscm2(list)), &size);
	return make_string(s, size);
}

struct scm* string_append(SCM x)  /*((arity . n))*/
{
	char *p = g_buf;
	g_buf[0] = 0;
	int size = 0;
	struct scm* y1 = Getstructscm2(x);

	while(GetSCM2(y1) != cell_nil)
	{
		struct scm* y2 = bad2good(y1->car);
		assert(y2->type == TSTRING);
		memcpy(p, &bad2good(y2->cdr)->rdc, y2->rac + 1);
		p += y2->length;
		size += y2->length;

		assert_max_string(size, "string_append", g_buf);

		y1 = bad2good(y1->cdr);
	}

	return make_string(g_buf, size);
}

struct scm* string_length(SCM string)
{
	struct scm* x = Getstructscm2(string);
	assert(x->type == TSTRING);
	return good2bad(Getstructscm2(make_cell__ (TNUMBER, 0, x->length)));
}

struct scm* string_ref(SCM str, SCM k)
{
	struct scm* x = Getstructscm2(str);
	struct scm* y = Getstructscm2(k);
	assert(x->type == TSTRING);
	assert(y->type == TNUMBER);
	size_t size = x->length;
	size_t i = y->rdc;

	if(i > size)
	{
		error(cell_symbol_system_error, cons_(GetSCM2(bad2good(make_string("value out of range", strlen ("value out of range")))), k));
	}

	char const *p = (char*) &bad2good(x->cdr)->string;
	return good2bad(Getstructscm2(make_cell__ (TCHAR, 0, p[i])));
}
