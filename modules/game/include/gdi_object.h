#if 0

#pragma once

namespace gdi_traits {

  template <typename T, typename DtorFn>
  class GdiObject final {
  public:
    GdiObject(T handle, DtorFn dtor) noexcept;

    GdiObject() noexcept;

    ~GdiObject() noexcept;

  private:
    T      _handle; //any HGDIOBJ-like type
    DtorFn _dtor;

  };

} //namespace gdi_traits

#endif //0
