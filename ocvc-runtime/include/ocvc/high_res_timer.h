/* -*- c++ -*- */
/*
 * Copyright 2011,2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef INCLUDED_OCVC_HIGH_RES_TIMER_H
#define INCLUDED_OCVC_HIGH_RES_TIMER_H

#include <ocvc/api.h>

////////////////////////////////////////////////////////////////////////
// Use architecture defines to determine the implementation
////////////////////////////////////////////////////////////////////////
#if defined(linux) || defined(__linux) || defined(__linux__)
    #define OCVC_HRT_USE_CLOCK_GETTIME
    #include <ctime>
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    #define OCVC_HRT_USE_QUERY_PERFORMANCE_COUNTER
#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
    #define OCVC_HRT_USE_MACH_ABSOLUTE_TIME
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
    #define OCVC_HRT_USE_CLOCK_GETTIME
    #include <ctime>
#else
    #define OCVC_HRT_USE_MICROSEC_CLOCK
#endif


////////////////////////////////////////////////////////////////////////
namespace oc {

    //! Typedef for the timer tick count
    typedef signed long long high_res_timer_type;

    //! Get the current time in ticks
    high_res_timer_type high_res_timer_now(void);

    //! Get the current time in ticks - for performance monitoring
    high_res_timer_type high_res_timer_now_perfmon(void);

    //! Get the number of ticks per second
    high_res_timer_type high_res_timer_tps(void);

    //! Get the tick count at the epoch
    high_res_timer_type high_res_timer_epoch(void);

#ifdef OCVC_HRT_USE_CLOCK_GETTIME
    //! storage for high res timer type
    OC_RUNTIME_API extern clockid_t high_res_timer_source;
#endif

} /* namespace oc */

////////////////////////////////////////////////////////////////////////
#ifdef OCVC_HRT_USE_CLOCK_GETTIME
    inline oc::high_res_timer_type oc::high_res_timer_now(void){
        timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return ts.tv_sec*high_res_timer_tps() + ts.tv_nsec;
    }

    inline oc::high_res_timer_type oc::high_res_timer_now_perfmon(void){
        timespec ts;
        clock_gettime(high_res_timer_source, &ts);
        return ts.tv_sec*high_res_timer_tps() + ts.tv_nsec;
    }

    inline oc::high_res_timer_type oc::high_res_timer_tps(void){
        return 1000000000UL;
    }
#endif /* OCVC_HRT_USE_CLOCK_GETTIME */

////////////////////////////////////////////////////////////////////////
#ifdef OCVC_HRT_USE_MACH_ABSOLUTE_TIME
    #include <mach/mach_time.h>

    inline oc::high_res_timer_type oc::high_res_timer_now(void){
        return mach_absolute_time();
    }

    inline oc::high_res_timer_type oc::high_res_timer_now_perfmon(void){
        return oc::high_res_timer_now();
    }

    inline oc::high_res_timer_type oc::high_res_timer_tps(void){
        mach_timebase_info_data_t info;
        mach_timebase_info(&info);
        return oc::high_res_timer_type(info.numer*1000000000UL)/info.denom;
    }
#endif

////////////////////////////////////////////////////////////////////////
#ifdef OCVC_HRT_USE_QUERY_PERFORMANCE_COUNTER
    #include <Windows.h>

    inline oc::high_res_timer_type oc::high_res_timer_now(void){
        LARGE_INTEGER counts;
        QueryPerformanceCounter(&counts);
        return counts.QuadPart;
    }

    inline oc::high_res_timer_type oc::high_res_timer_now_perfmon(void){
        return oc::high_res_timer_now();
    }

    inline oc::high_res_timer_type oc::high_res_timer_tps(void){
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        return freq.QuadPart;
    }
#endif

////////////////////////////////////////////////////////////////////////
#ifdef OCVC_HRT_USE_MICROSEC_CLOCK
    #include <boost/date_time/posix_time/posix_time.hpp>

    inline oc::high_res_timer_type oc::high_res_timer_now(void){
        static const boost::posix_time::ptime epoch(boost::posix_time::from_time_t(0));
        return (boost::posix_time::microsec_clock::universal_time() - epoch).ticks();
    }

    inline oc::high_res_timer_type oc::high_res_timer_now_perfmon(void){
        return oc::high_res_timer_now();
    }

    inline oc::high_res_timer_type oc::high_res_timer_tps(void){
        return boost::posix_time::time_duration::ticks_per_second();
    }
#endif

////////////////////////////////////////////////////////////////////////
#include <boost/date_time/posix_time/posix_time.hpp>

inline oc::high_res_timer_type oc::high_res_timer_epoch(void){
    static const double hrt_ticks_per_utc_ticks = oc::high_res_timer_tps()/double(boost::posix_time::time_duration::ticks_per_second());
    boost::posix_time::time_duration utc = boost::posix_time::microsec_clock::universal_time() - boost::posix_time::from_time_t(0);
    return oc::high_res_timer_now() - utc.ticks()*hrt_ticks_per_utc_ticks;
}

#endif /* INCLUDED_OCVC_HIGH_RES_TIMER_H */
