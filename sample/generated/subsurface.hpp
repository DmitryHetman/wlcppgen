
#ifndef _SUBSURFACE_HPP_
#define _SUBSURFACE_HPP_

#include <functional>
#include <string>
#include <utility>
#include "../proxy.hpp"

/* The following code was generated from the "wayland" protocol specification.
 *
 * Copyright © 2008-2011 Kristian Høgsberg
 * Copyright © 2010-2011 Intel Corporation
 * Copyright © 2012-2013 Collabora, Ltd.
 *
 * Permission to use, copy, modify, distribute, and sell this
 * software and its documentation for any purpose is hereby granted
 * without fee, provided that the above copyright notice appear in
 * all copies and that both that copyright notice and this permission
 * notice appear in supporting documentation, and that the name of
 * the copyright holders not be used in advertising or publicity
 * pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied
 * warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
 * THIS SOFTWARE.
 */

namespace wlcpp {

class surface;

#define WLCPP_SUBSURFACE_VERSION 1

/**
 */
enum subsurface_error {
    SUBSURFACE_ERROR_BAD_SURFACE = 0, /**< wl_surface is not a sibling or the parent */
};

/** \brief sub-surface interface to a wl_surface
 *
 *  An additional interface to a wl_surface object, which has been made a
 *  sub-surface. A sub-surface has one parent surface. A sub-surface's size and
 *  position are not limited to that of the parent. Particularly, a sub-surface
 *  is not automatically clipped to its parent's area.
 *
 *  A sub-surface becomes mapped, when a non-NULL wl_buffer is applied and the
 *  parent surface is mapped. The order of which one happens first is
 *  irrelevant. A sub-surface is hidden if the parent becomes hidden, or if a
 *  NULL wl_buffer is applied. These rules apply recursively through the tree of
 *  surfaces.
 *
 *  The behaviour of wl_surface.commit request on a sub-surface depends on the
 *  sub-surface's mode. The possible modes are synchronized and desynchronized,
 *  see methods wl_subsurface.set_sync and wl_subsurface.set_desync.
 *  Synchronized mode caches the wl_surface state to be applied when the
 *  parent's state gets applied, and desynchronized mode applies the pending
 *  wl_surface state directly. A sub-surface is initially in the synchronized
 *  mode.
 *
 *  Sub-surfaces have also other kind of state, which is managed by
 *  wl_subsurface requests, as opposed to wl_surface requests. This state
 *  includes the sub-surface position relative to the parent surface
 *  (wl_subsurface.set_position), and the stacking order of the parent and its
 *  sub-surfaces (wl_subsurface.place_above and .place_below). This state is
 *  applied when the parent surface's wl_surface state is applied, regardless of
 *  the sub-surface's mode. As the exception, set_sync and set_desync are
 *  effective immediately.
 *
 *  The main surface can be thought to be always in desynchronized mode, since
 *  it does not have a parent in the sub-surfaces sense.
 *
 *  Even if a sub-surface is in desynchronized mode, it will behave as in
 *  synchronized mode, if its parent surface behaves as in synchronized mode.
 *  This rule is applied recursively throughout the tree of surfaces. This
 *  means, that one can set a sub-surface into synchronized mode, and then
 *  assume that all its child and grand-child sub-surfaces are synchronized,
 *  too, without explicitly setting them.
 *
 *  If the wl_surface associated with the wl_subsurface is destroyed, the
 *  wl_subsurface object becomes inert. Note, that destroying either object
 *  takes effect immediately. If you need to synchronize the removal of a
 *  sub-surface to the parent surface update, unmap the sub-surface first by
 *  attaching a NULL wl_buffer, update parent, and then destroy the sub-surface.
 *
 *  If the parent wl_surface object is destroyed, the sub-surface is unmapped.
 */
class subsurface final
    : public proxy {
public:
    /** \brief wl_interface for @ref subsurface */
    static const wl_interface interface;

    /** \brief @ref subsurface version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_subsurface object
     *  @param obj Existing native object to wrap, can be nullptr
     *  @param managed true, if the new wrapper object owns the wl_subsurface object and is responsible for destryoing it
     */
    subsurface(wl_proxy* obj = nullptr, bool managed = true);

    /** \brief Create new @ref subsurface from factory
     *  @param factory Object which acts as the factory
     */
    explicit subsurface(proxy& factory);

    /** \brief Default move constructor */
    subsurface(subsurface&& rhs) = default;

    /** \brief Destructor */
    virtual ~subsurface();

    /** \brief Default move assignment operator */
    subsurface& operator=(subsurface&& rhs) = default;

    /** \brief reposition the sub-surface
     *
     *  This schedules a sub-surface position change. The sub-surface will be moved
     *  so, that its origin (top-left corner pixel) will be at the location x, y of
     *  the parent surface coordinate system. The coordinates are not restricted to
     *  the parent surface area. Negative values are allowed.
     *
     *  The next wl_surface.commit on the parent surface will reset the
     *  sub-surface's position to the scheduled coordinates.
     *
     *  If more than one set_position request is invoked by the client before the
     *  commit of the parent surface, the position of a new request always replaces
     *  the scheduled position from any previous request.
     *
     *  The initial position is 0, 0.
     *
     *  @param x_ coordinate in the parent surface
     *  @param y_ coordinate in the parent surface
     */
    void set_position(std::int32_t x_, std::int32_t y_);

    /** \brief restack the sub-surface
     *
     *  This sub-surface is taken from the stack, and put back just above the
     *  reference surface, changing the z-order of the sub-surfaces. The reference
     *  surface must be one of the sibling surfaces, or the parent surface. Using
     *  any other surface, including this sub-surface, will cause a protocol error.
     *
     *  The z-order is double-buffered. Requests are handled in order and applied
     *  immediately to a pending state, then committed to the active state on the
     *  next commit of the parent surface. See wl_surface.commit and
     *  wl_subcompositor.get_subsurface.
     *
     *  A new sub-surface is initially added as the top-most in the stack of its
     *  siblings and parent.
     *
     *  @param sibling_ the reference surface
     */
    void place_above(surface& sibling_);

    /** \brief restack the sub-surface
     *
     *  The sub-surface is placed just below of the reference surface. See
     *  wl_subsurface.place_above.
     *
     *  @param sibling_ the reference surface
     */
    void place_below(surface& sibling_);

    /** \brief set sub-surface to synchronized mode
     *
     *  Change the commit behaviour of the sub-surface to synchronized mode, also
     *  described as the parent dependant mode.
     *
     *  In synchronized mode, wl_surface.commit on a sub-surface will accumulate the
     *  committed state in a cache, but the state will not be applied and hence will
     *  not change the compositor output. The cached state is applied to the
     *  sub-surface immediately after the parent surface's state is applied. This
     *  ensures atomic updates of the parent and all its synchronized sub-surfaces.
     *  Applying the cached state will invalidate the cache, so further parent
     *  surface commits do not (re-)apply old state.
     *
     *  See wl_subsurface for the recursive effect of this mode.
     */
    void set_sync();

    /** \brief set sub-surface to desynchronized mode
     *
     *  Change the commit behaviour of the sub-surface to desynchronized mode, also
     *  described as independent or freely running mode.
     *
     *  In desynchronized mode, wl_surface.commit on a sub-surface will apply the
     *  pending state directly, without caching, as happens normally with a
     *  wl_surface. Calling wl_surface.commit on the parent surface has no effect on
     *  the sub-surface's wl_surface state. This mode allows a sub-surface to be
     *  updated on its own.
     *
     *  If cached state exists when wl_surface.commit is called in desynchronized
     *  mode, the pending state is added to the cached state, and applied as whole.
     *  This invalidates the cache.
     *
     *  Note: even if a sub-surface is set to desynchronized, a parent sub-surface
     *  may override it to behave as synchronized. For details, see wl_subsurface.
     *
     *  If a surface's parent surface behaves as desynchronized, then the cached
     *  state is applied on set_desync.
     */
    void set_desync();

protected:
    void destroy() override;
};

} // namespace wlcpp

#endif // _SUBSURFACE_HPP_

