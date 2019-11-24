#if 0

#include "gdi_object.h"

namespace gdi_traits {

  template <typename T, typename DtorFn>
  GdiObject<T, DtorFn>::GdiObject(T handle, DtorFn dtor) noexcept
    : _handle(handle)
    , _dtor(dtor)
  { }
  
  template <typename T, typename DtorFn>
  GdiObject<T, DtorFn>::GdiObject() noexcept
    : _handle(nullptr)
  { }
  
  template <typename T, typename DtorFn>
  GdiObject<T, DtorFn>::~GdiObject() noexcept {
      if(_handle) {
        _dtor();
      }
  }

} //namespace gdi_traits

#endif //