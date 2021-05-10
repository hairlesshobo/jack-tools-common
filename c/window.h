#ifndef _COMMON_WINDOW_H
#define _COMMON_WINDOW_H

typedef void (window_f_t) (float *, int);
typedef void (beta_window_f_t) (float *, int, float);

enum WINDOW_TYPE {
    RECTANGULAR_WINDOW,
    HANNING_WINDOW,
    HAMMING_WINDOW,
    BLACKMAN2_WINDOW,
    BLACKMAN3_WINDOW,
    BLACKMAN4_WINDOW,
    BARTLETT_WINDOW,
    KAISER_WINDOW,
    CAUCHY_WINDOW,
    POISSON_WINDOW,
    GAUSSIAN_WINDOW,
    WELCH_WINDOW,
    PARZEN_WINDOW,
    RIEMANN_WINDOW,
    EXPONENTIAL_WINDOW,
    TUKEY_WINDOW,
};

int parse_window_type(const char *type);
window_f_t *get_apply_window_f(enum WINDOW_TYPE type);
beta_window_f_t *get_apply_beta_window_f(enum WINDOW_TYPE type);
void apply_typed_window(enum WINDOW_TYPE type, float *data, int n, float beta);
void make_typed_window(enum WINDOW_TYPE type, float *data, int n, float beta);

#endif
