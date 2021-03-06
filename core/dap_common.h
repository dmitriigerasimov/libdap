/*
 * Authors:
 * Dmitriy A. Gearasimov <kahovski@gmail.com>
 * DeM Labs Inc.   https://demlabs.net
 * DeM Labs Open source community https://github.com/demlabsinc
 * Copyright  (c) 2017-2018
 * All rights reserved.

 This file is part of DAP (Deus Applications Prototypes) the open source project

    DAP (Deus Applicaions Prototypes) is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DAP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with any DAP based project.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#define DAP_NEW(a)    ( (a*) malloc(sizeof(a)))
#define DAP_NEW_SIZE(a,b)    ( (a*) malloc(b))
#define DAP_NEW_Z(a) ( (a*) calloc(1,sizeof(a)))
#define DAP_NEW_Z_SIZE(a,b) ( (a*) calloc(1,b))

#define DAP_DELETE(a)   free(a)
#define DAP_DUP(a) (__typeof(a) ret = memcpy(ret,a,sizeof(*a)) )

#define DAP_PROTOCOL_VERSION 21



#if defined(__GNUC__) ||defined (__clang__)
#define DAP_ALIGN_PACKED  __attribute__((aligned(1),packed))
#endif


enum log_level{L_CRITICAL=5,L_ERROR=4, L_WARNING=3,L_NOTICE=2,L_INFO=1,L_DEBUG=0};
//extern enum log_level log_level;

#ifdef __cplusplus
extern "C" {
#endif

int dap_common_init( const char * a_log_file );
void dap_common_deinit();

void _log_it(const char * log_tag, enum log_level, const char * format,...);
void _vlog_it(const char * log_tag, enum log_level, const char * format, va_list ap );
#define log_it(_log_level,...) _log_it(LOG_TAG,_log_level,##__VA_ARGS__)
#define vlog_it(a_log_level,a_format,a_ap) _vlog_it(LOG_TAG,a_log_level,a_format,a_ap)

const char * log_error();
void set_log_level(enum log_level ll);

#ifdef __GNUC__
char *itoa(int i);


#elif _MSC_VER
char *strndup(const char *s, size_t n);
#endif
int time_to_rfc822(char * out, size_t out_size_max, time_t t);

int get_select_breaker();
int send_select_break();
char * exec_with_ret(const char * a_cmd);
char * exec_with_ret_multistring(const char * a_cmd);
char * random_string_create(size_t a_length);

#ifdef __cplusplus
}
#endif
