#pragma once

#   define __STL_BEGIN_NAMESPACE namespace mystl {
#   define __STL_END_NAMESPACE }

#define __STL_TRY try
#define __STL_CATCH_ALL catch(...)
#define __STL_RETHROW throw
#define __STL_NOTHROW throw()
#define __STL_UNWIND(action) catch(...) { action; throw; }

#define __STL_TEMPLATE_NULL template<>
