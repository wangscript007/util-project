
#ifndef MONGOCXX_API_H
#define MONGOCXX_API_H

#ifdef MONGOCXX_STATIC
#  define MONGOCXX_API
#  define MONGOCXX_PRIVATE
#else

#ifdef __linux__
#  ifndef MONGOCXX_API
#    ifdef mongocxx_mocked_EXPORTS
        /* We are building this library */
#      define MONGOCXX_API 
#    else
        /* We are using this library */
#      define MONGOCXX_API 
#    endif
#  endif
#else
#  ifndef MONGOCXX_API
#    ifdef MONGOCXX_EXPORTS
        /* We are building this library */
#      define MONGOCXX_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define MONGOCXX_API __declspec(dllimport)
#    endif
#  endif
#endif

#  ifndef MONGOCXX_PRIVATE
#    define MONGOCXX_PRIVATE 
#  endif
#endif

#ifdef __linux__
#ifndef BSONCXX_DEPRECATED
#  define MONGOCXX_DEPRECATED __attribute__ ((__deprecated__))
#endif
#else
#ifndef MONGOCXX_DEPRECATED
#  define MONGOCXX_DEPRECATED __declspec(deprecated)
#endif
#endif

#ifndef MONGOCXX_DEPRECATED_EXPORT
#  define MONGOCXX_DEPRECATED_EXPORT MONGOCXX_API MONGOCXX_DEPRECATED
#endif

#ifndef MONGOCXX_DEPRECATED_NO_EXPORT
#  define MONGOCXX_DEPRECATED_NO_EXPORT MONGOCXX_PRIVATE MONGOCXX_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MONGOCXX_NO_DEPRECATED
#    define MONGOCXX_NO_DEPRECATED
#  endif
#endif

#endif /* MONGOCXX_API_H */
