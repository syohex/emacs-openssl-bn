/*
  Copyright (C) 2020 by Shohei YOSHIDA

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define _DEFAULT_SOURCE
#include <emacs-module.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <openssl/bn.h>

int plugin_is_GPL_compatible;

static char *retrieve_string(emacs_env *env, emacs_value str, ptrdiff_t *size) {
    *size = 0;

    env->copy_string_contents(env, str, NULL, size);
    char *p = malloc(*size);
    if (p == NULL) {
        *size = 0;
        return NULL;
    }
    env->copy_string_contents(env, str, p, size);

    return p;
}

emacs_value Fopenssl_bn_core_is_prime(emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data) {
    ptrdiff_t input_size = 0;
    char *str = retrieve_string(env, args[0], &input_size);
    if (str == NULL) {
        return env->intern(env, "nil");
    }

    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *num = BN_new();

    BN_dec2bn(&num, str);
    free(str);

    int ret = BN_is_prime_ex(num, BN_prime_checks, ctx, NULL);
    BN_free(num);
    BN_CTX_free(ctx);

    if (ret == 1) {
        return env->intern(env, "t");
    }

    return env->intern(env, "nil");
}

static void bind_function(emacs_env *env, const char *name, emacs_value Sfun) {
    emacs_value Qfset = env->intern(env, "fset");
    emacs_value Qsym = env->intern(env, name);
    emacs_value args[] = {Qsym, Sfun};

    env->funcall(env, Qfset, 2, args);
}

static void provide(emacs_env *env, const char *feature) {
    emacs_value Qfeat = env->intern(env, feature);
    emacs_value Qprovide = env->intern(env, "provide");
    emacs_value args[] = {Qfeat};

    env->funcall(env, Qprovide, 1, args);
}

int emacs_module_init(struct emacs_runtime *ert) {
    emacs_env *env = ert->get_environment(ert);

#define DEFUN(lsym, csym, amin, amax, doc, data) bind_function(env, lsym, env->make_function(env, amin, amax, csym, doc, data))

    DEFUN("openssl-bn-core-prime-p", Fopenssl_bn_core_is_prime, 1, 1, NULL, NULL);
#undef DEFUN

    provide(env, "openssl-bn-core");
    return 0;
}
