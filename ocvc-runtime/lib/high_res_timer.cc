#include <ocvc/high_res_timer.h>

#ifdef OCVC_HRT_USE_CLOCK_GETTIME
clockid_t oc::high_res_timer_source = CLOCK_THREAD_CPUTIME_ID;
#endif



