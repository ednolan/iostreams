// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_BOOL_TRAIT_DEF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BOOL_TRAIT_DEF_HPP_INCLUDED     

#include <boost/config.hpp> // BOOST_STATIC_CONSTANT.
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
 
// 
// Macro name: BOOST_IOSTREAMS_BOOL_TRAIT_DEF
// Description: Used to generate the traits classes is_istream, is_ostream,
//      etc.
//
#define BOOST_IOSTREAMS_BOOL_TRAIT_DEF(trait, type, arity) \
    namespace boost { namespace iostreams { namespace detail { \
      template<BOOST_PP_ENUM_PARAMS(arity, typename T)> \
      type_traits::yes_type BOOST_PP_CAT(trait, _helper) \
          (const volatile type<BOOST_PP_ENUM_PARAMS(arity, T)>*); \
      type_traits::no_type BOOST_PP_CAT(trait, _helper)(...); \
      template<typename T> \
      struct BOOST_PP_CAT(trait, _impl) { \
           BOOST_STATIC_CONSTANT(bool, value = \
               (sizeof(BOOST_PP_CAT(trait, _helper)(static_cast<T*>(0))) == \
                sizeof(type_traits::yes_type))); \
      }; \
    } \
    template<typename T> \
    struct trait \
        : mpl::bool_<detail::BOOST_PP_CAT(trait, _impl)<T>::value> \
    { BOOST_MPL_AUX_LAMBDA_SUPPORT(1, trait, (T)) }; \
    } } \
    /**/

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BOOL_TRAIT_DEF_HPP_INCLUDED