
#include "wlcpp.hpp"

/* The following code was generated from the "wayland" protocol specification.
 *
 * Copyright © 2008-2011 Kristian Høgsberg
 * Copyright © 2010-2011 Intel Corporation
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

using namespace std;
using namespace wlcpp;

static const wl_interface* wl_registry_request_bind_types[] = { nullptr, nullptr, nullptr, nullptr };

static const wl_message wl_registry_requests[] = {
    { "bind", "usun", wl_registry_request_bind_types },
};

static const wl_interface* wl_registry_event_global_types[] = { nullptr, nullptr, nullptr };
static const wl_interface* wl_registry_event_global_remove_types[] = { nullptr };

static const wl_message wl_registry_events[] = {
    { "global", "usu", wl_registry_event_global_types },
    { "global_remove", "u", wl_registry_event_global_remove_types },
};

const wl_interface registry::interface = {
    "wl_registry", 1,
    1, wl_registry_requests,
    2, wl_registry_events
};

const registry::listener_t registry::listener = {
    &global_handler,
    &global_remove_handler,
};

registry::registry(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

registry::registry(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

void registry::global_handler(void* data, wl_proxy* wl_obj, uint32_t name_, const char* interface_, uint32_t version_) {
    auto& handler = proxy::user_data_to_wrapper_cast<registry>(data)->_global_handler;
    if(handler) {
        handler(name_, interface_, version_);
    }
}

void registry::global_remove_handler(void* data, wl_proxy* wl_obj, uint32_t name_) {
    auto& handler = proxy::user_data_to_wrapper_cast<registry>(data)->_global_remove_handler;
    if(handler) {
        handler(name_);
    }
}

static const wl_interface* wl_callback_event_done_types[] = { nullptr };

static const wl_message wl_callback_events[] = {
    { "done", "u", wl_callback_event_done_types },
};

const wl_interface callback::interface = {
    "wl_callback", 1,
    0, nullptr,
    1, wl_callback_events
};

const callback::listener_t callback::listener = {
    &done_handler,
};

callback::callback(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

callback::callback(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

void callback::done_handler(void* data, wl_proxy* wl_obj, uint32_t serial_) {
    auto& handler = proxy::user_data_to_wrapper_cast<callback>(data)->_done_handler;
    if(handler) {
        handler(serial_);
    }
}

static const wl_interface* wl_compositor_request_create_surface_types[] = { &surface::interface };
static const wl_interface* wl_compositor_request_create_region_types[] = { &region::interface };

static const wl_message wl_compositor_requests[] = {
    { "create_surface", "n", wl_compositor_request_create_surface_types },
    { "create_region", "n", wl_compositor_request_create_region_types },
};

const wl_interface compositor::interface = {
    "wl_compositor", 3,
    2, wl_compositor_requests,
    0, nullptr
};

compositor::compositor(wl_proxy* obj)
    : proxy(obj) {
}

compositor::compositor(proxy& factory)
    : proxy(factory, interface) {
}

surface compositor::create_surface() {
    surface id_(*this);
    marshal(0, id_.wl_obj());
    return id_;
}

region compositor::create_region() {
    region id_(*this);
    marshal(1, id_.wl_obj());
    return id_;
}

static const wl_interface* wl_shm_pool_request_create_buffer_types[] = { &buffer::interface, nullptr, nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_shm_pool_request_destroy_types[] = { };
static const wl_interface* wl_shm_pool_request_resize_types[] = { nullptr };

static const wl_message wl_shm_pool_requests[] = {
    { "create_buffer", "niiiiu", wl_shm_pool_request_create_buffer_types },
    { "destroy", "", wl_shm_pool_request_destroy_types },
    { "resize", "i", wl_shm_pool_request_resize_types },
};

const wl_interface shm_pool::interface = {
    "wl_shm_pool", 1,
    3, wl_shm_pool_requests,
    0, nullptr
};

shm_pool::shm_pool(wl_proxy* obj)
    : proxy(obj) {
}

shm_pool::shm_pool(proxy& factory)
    : proxy(factory, interface) {
}

shm_pool::~shm_pool(){
    destroy();
}

buffer shm_pool::create_buffer(int32_t offset_, int32_t width_, int32_t height_, int32_t stride_, uint32_t format_) {
    buffer id_(*this);
    marshal(0, id_.wl_obj(), offset_, width_, height_, stride_, format_);
    return id_;
}

void shm_pool::resize(int32_t size_) {
    marshal(2, size_);
}

void shm_pool::destroy() {
    if(valid()) {
        marshal(1);
    }
    proxy::destroy();
}

static const wl_interface* wl_shm_request_create_pool_types[] = { &shm_pool::interface, nullptr, nullptr };

static const wl_message wl_shm_requests[] = {
    { "create_pool", "nhi", wl_shm_request_create_pool_types },
};

static const wl_interface* wl_shm_event_format_types[] = { nullptr };

static const wl_message wl_shm_events[] = {
    { "format", "u", wl_shm_event_format_types },
};

const wl_interface shm::interface = {
    "wl_shm", 1,
    1, wl_shm_requests,
    1, wl_shm_events
};

const shm::listener_t shm::listener = {
    &format_handler,
};

shm::shm(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

shm::shm(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

shm_pool shm::create_pool(int32_t fd_, int32_t size_) {
    shm_pool id_(*this);
    marshal(0, id_.wl_obj(), fd_, size_);
    return id_;
}

void shm::format_handler(void* data, wl_proxy* wl_obj, uint32_t format_) {
    auto& handler = proxy::user_data_to_wrapper_cast<shm>(data)->_format_handler;
    if(handler) {
        handler(format_);
    }
}

static const wl_interface* wl_buffer_request_destroy_types[] = { };

static const wl_message wl_buffer_requests[] = {
    { "destroy", "", wl_buffer_request_destroy_types },
};

static const wl_interface* wl_buffer_event_release_types[] = { };

static const wl_message wl_buffer_events[] = {
    { "release", "", wl_buffer_event_release_types },
};

const wl_interface buffer::interface = {
    "wl_buffer", 1,
    1, wl_buffer_requests,
    1, wl_buffer_events
};

const buffer::listener_t buffer::listener = {
    &release_handler,
};

buffer::buffer(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

buffer::buffer(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

buffer::~buffer(){
    destroy();
}

void buffer::destroy() {
    if(valid()) {
        marshal(0);
    }
    proxy::destroy();
}

void buffer::release_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<buffer>(data)->_release_handler;
    if(handler) {
        handler();
    }
}

static const wl_interface* wl_data_offer_request_accept_types[] = { nullptr, nullptr };
static const wl_interface* wl_data_offer_request_receive_types[] = { nullptr, nullptr };
static const wl_interface* wl_data_offer_request_destroy_types[] = { };

static const wl_message wl_data_offer_requests[] = {
    { "accept", "u?s", wl_data_offer_request_accept_types },
    { "receive", "sh", wl_data_offer_request_receive_types },
    { "destroy", "", wl_data_offer_request_destroy_types },
};

static const wl_interface* wl_data_offer_event_offer_types[] = { nullptr };

static const wl_message wl_data_offer_events[] = {
    { "offer", "s", wl_data_offer_event_offer_types },
};

const wl_interface data_offer::interface = {
    "wl_data_offer", 1,
    3, wl_data_offer_requests,
    1, wl_data_offer_events
};

const data_offer::listener_t data_offer::listener = {
    &offer_handler,
};

data_offer::data_offer(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

data_offer::data_offer(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

data_offer::~data_offer(){
    destroy();
}

void data_offer::accept(uint32_t serial_, const string* mime_type_) {
    marshal(0, serial_, mime_type_ ? mime_type_->c_str() : nullptr);
}

void data_offer::receive(const string& mime_type_, int32_t fd_) {
    marshal(1, mime_type_.c_str(), fd_);
}

void data_offer::destroy() {
    if(valid()) {
        marshal(2);
    }
    proxy::destroy();
}

void data_offer::offer_handler(void* data, wl_proxy* wl_obj, const char* mime_type_) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_offer>(data)->_offer_handler;
    if(handler) {
        handler(mime_type_);
    }
}

static const wl_interface* wl_data_source_request_offer_types[] = { nullptr };
static const wl_interface* wl_data_source_request_destroy_types[] = { };

static const wl_message wl_data_source_requests[] = {
    { "offer", "s", wl_data_source_request_offer_types },
    { "destroy", "", wl_data_source_request_destroy_types },
};

static const wl_interface* wl_data_source_event_target_types[] = { nullptr };
static const wl_interface* wl_data_source_event_send_types[] = { nullptr, nullptr };
static const wl_interface* wl_data_source_event_cancelled_types[] = { };

static const wl_message wl_data_source_events[] = {
    { "target", "?s", wl_data_source_event_target_types },
    { "send", "sh", wl_data_source_event_send_types },
    { "cancelled", "", wl_data_source_event_cancelled_types },
};

const wl_interface data_source::interface = {
    "wl_data_source", 1,
    2, wl_data_source_requests,
    3, wl_data_source_events
};

const data_source::listener_t data_source::listener = {
    &target_handler,
    &send_handler,
    &cancelled_handler,
};

data_source::data_source(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

data_source::data_source(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

data_source::~data_source(){
    destroy();
}

void data_source::offer(const string& mime_type_) {
    marshal(0, mime_type_.c_str());
}

void data_source::destroy() {
    if(valid()) {
        marshal(1);
    }
    proxy::destroy();
}

void data_source::target_handler(void* data, wl_proxy* wl_obj, const char* mime_type_) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_source>(data)->_target_handler;
    if(handler) {
        string mime_type_str = mime_type_ ? mime_type_ : string();
        handler(mime_type_ ? &mime_type_str : nullptr);
    }
}

void data_source::send_handler(void* data, wl_proxy* wl_obj, const char* mime_type_, int32_t fd_) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_source>(data)->_send_handler;
    if(handler) {
        handler(mime_type_, fd_);
    }
}

void data_source::cancelled_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_source>(data)->_cancelled_handler;
    if(handler) {
        handler();
    }
}

static const wl_interface* wl_data_device_request_start_drag_types[] = { &data_source::interface, &surface::interface, &surface::interface, nullptr };
static const wl_interface* wl_data_device_request_set_selection_types[] = { &data_source::interface, nullptr };

static const wl_message wl_data_device_requests[] = {
    { "start_drag", "?oo?ou", wl_data_device_request_start_drag_types },
    { "set_selection", "?ou", wl_data_device_request_set_selection_types },
};

static const wl_interface* wl_data_device_event_data_offer_types[] = { &data_offer::interface };
static const wl_interface* wl_data_device_event_enter_types[] = { nullptr, &surface::interface, nullptr, nullptr, &data_offer::interface };
static const wl_interface* wl_data_device_event_leave_types[] = { };
static const wl_interface* wl_data_device_event_motion_types[] = { nullptr, nullptr, nullptr };
static const wl_interface* wl_data_device_event_drop_types[] = { };
static const wl_interface* wl_data_device_event_selection_types[] = { &data_offer::interface };

static const wl_message wl_data_device_events[] = {
    { "data_offer", "n", wl_data_device_event_data_offer_types },
    { "enter", "uoff?o", wl_data_device_event_enter_types },
    { "leave", "", wl_data_device_event_leave_types },
    { "motion", "uff", wl_data_device_event_motion_types },
    { "drop", "", wl_data_device_event_drop_types },
    { "selection", "?o", wl_data_device_event_selection_types },
};

const wl_interface data_device::interface = {
    "wl_data_device", 1,
    2, wl_data_device_requests,
    6, wl_data_device_events
};

const data_device::listener_t data_device::listener = {
    &data_offer_handler,
    &enter_handler,
    &leave_handler,
    &motion_handler,
    &drop_handler,
    &selection_handler,
};

data_device::data_device(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

data_device::data_device(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

void data_device::start_drag(data_source* source_, surface& origin_, surface* icon_, uint32_t serial_) {
    marshal(0, source_ ? source_->wl_obj() : nullptr, origin_.wl_obj(), icon_ ? icon_->wl_obj() : nullptr, serial_);
}

void data_device::set_selection(data_source* source_, uint32_t serial_) {
    marshal(1, source_ ? source_->wl_obj() : nullptr, serial_);
}

void data_device::data_offer_handler(void* data, wl_proxy* wl_obj, wl_proxy* id_) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_device>(data)->_data_offer_handler;
    if(handler) {
        handler(data_offer(id_));
    }
}

void data_device::enter_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, wl_proxy* surface_, wl_fixed_t x_, wl_fixed_t y_, wl_proxy* id_) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_device>(data)->_enter_handler;
    if(handler) {
        handler(serial_, *proxy::wrapper_cast<surface>(surface_), x_, y_, proxy::wrapper_cast<data_offer>(id_));
    }
}

void data_device::leave_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_device>(data)->_leave_handler;
    if(handler) {
        handler();
    }
}

void data_device::motion_handler(void* data, wl_proxy* wl_obj, uint32_t time_, wl_fixed_t x_, wl_fixed_t y_) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_device>(data)->_motion_handler;
    if(handler) {
        handler(time_, x_, y_);
    }
}

void data_device::drop_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_device>(data)->_drop_handler;
    if(handler) {
        handler();
    }
}

void data_device::selection_handler(void* data, wl_proxy* wl_obj, wl_proxy* id_) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_device>(data)->_selection_handler;
    if(handler) {
        handler(proxy::wrapper_cast<data_offer>(id_));
    }
}

static const wl_interface* wl_data_device_manager_request_create_data_source_types[] = { &data_source::interface };
static const wl_interface* wl_data_device_manager_request_get_data_device_types[] = { &data_device::interface, &seat::interface };

static const wl_message wl_data_device_manager_requests[] = {
    { "create_data_source", "n", wl_data_device_manager_request_create_data_source_types },
    { "get_data_device", "no", wl_data_device_manager_request_get_data_device_types },
};

const wl_interface data_device_manager::interface = {
    "wl_data_device_manager", 1,
    2, wl_data_device_manager_requests,
    0, nullptr
};

data_device_manager::data_device_manager(wl_proxy* obj)
    : proxy(obj) {
}

data_device_manager::data_device_manager(proxy& factory)
    : proxy(factory, interface) {
}

data_source data_device_manager::create_data_source() {
    data_source id_(*this);
    marshal(0, id_.wl_obj());
    return id_;
}

data_device data_device_manager::get_data_device(seat& seat_) {
    data_device id_(*this);
    marshal(1, id_.wl_obj(), seat_.wl_obj());
    return id_;
}

static const wl_interface* wl_shell_request_get_shell_surface_types[] = { &shell_surface::interface, &surface::interface };

static const wl_message wl_shell_requests[] = {
    { "get_shell_surface", "no", wl_shell_request_get_shell_surface_types },
};

const wl_interface shell::interface = {
    "wl_shell", 1,
    1, wl_shell_requests,
    0, nullptr
};

shell::shell(wl_proxy* obj)
    : proxy(obj) {
}

shell::shell(proxy& factory)
    : proxy(factory, interface) {
}

shell_surface shell::get_shell_surface(surface& surface_) {
    shell_surface id_(*this);
    marshal(0, id_.wl_obj(), surface_.wl_obj());
    return id_;
}

static const wl_interface* wl_shell_surface_request_pong_types[] = { nullptr };
static const wl_interface* wl_shell_surface_request_move_types[] = { &seat::interface, nullptr };
static const wl_interface* wl_shell_surface_request_resize_types[] = { &seat::interface, nullptr, nullptr };
static const wl_interface* wl_shell_surface_request_set_toplevel_types[] = { };
static const wl_interface* wl_shell_surface_request_set_transient_types[] = { &surface::interface, nullptr, nullptr, nullptr };
static const wl_interface* wl_shell_surface_request_set_fullscreen_types[] = { nullptr, nullptr, &output::interface };
static const wl_interface* wl_shell_surface_request_set_popup_types[] = { &seat::interface, nullptr, &surface::interface, nullptr, nullptr, nullptr };
static const wl_interface* wl_shell_surface_request_set_maximized_types[] = { &output::interface };
static const wl_interface* wl_shell_surface_request_set_title_types[] = { nullptr };
static const wl_interface* wl_shell_surface_request_set_class_types[] = { nullptr };

static const wl_message wl_shell_surface_requests[] = {
    { "pong", "u", wl_shell_surface_request_pong_types },
    { "move", "ou", wl_shell_surface_request_move_types },
    { "resize", "ouu", wl_shell_surface_request_resize_types },
    { "set_toplevel", "", wl_shell_surface_request_set_toplevel_types },
    { "set_transient", "oiiu", wl_shell_surface_request_set_transient_types },
    { "set_fullscreen", "uu?o", wl_shell_surface_request_set_fullscreen_types },
    { "set_popup", "ouoiiu", wl_shell_surface_request_set_popup_types },
    { "set_maximized", "?o", wl_shell_surface_request_set_maximized_types },
    { "set_title", "s", wl_shell_surface_request_set_title_types },
    { "set_class", "s", wl_shell_surface_request_set_class_types },
};

static const wl_interface* wl_shell_surface_event_ping_types[] = { nullptr };
static const wl_interface* wl_shell_surface_event_configure_types[] = { nullptr, nullptr, nullptr };
static const wl_interface* wl_shell_surface_event_popup_done_types[] = { };

static const wl_message wl_shell_surface_events[] = {
    { "ping", "u", wl_shell_surface_event_ping_types },
    { "configure", "uii", wl_shell_surface_event_configure_types },
    { "popup_done", "", wl_shell_surface_event_popup_done_types },
};

const wl_interface shell_surface::interface = {
    "wl_shell_surface", 1,
    10, wl_shell_surface_requests,
    3, wl_shell_surface_events
};

const shell_surface::listener_t shell_surface::listener = {
    &ping_handler,
    &configure_handler,
    &popup_done_handler,
};

shell_surface::shell_surface(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

shell_surface::shell_surface(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

void shell_surface::pong(uint32_t serial_) {
    marshal(0, serial_);
}

void shell_surface::move(seat& seat_, uint32_t serial_) {
    marshal(1, seat_.wl_obj(), serial_);
}

void shell_surface::resize(seat& seat_, uint32_t serial_, uint32_t edges_) {
    marshal(2, seat_.wl_obj(), serial_, edges_);
}

void shell_surface::set_toplevel() {
    marshal(3);
}

void shell_surface::set_transient(surface& parent_, int32_t x_, int32_t y_, uint32_t flags_) {
    marshal(4, parent_.wl_obj(), x_, y_, flags_);
}

void shell_surface::set_fullscreen(uint32_t method_, uint32_t framerate_, output* output_) {
    marshal(5, method_, framerate_, output_ ? output_->wl_obj() : nullptr);
}

void shell_surface::set_popup(seat& seat_, uint32_t serial_, surface& parent_, int32_t x_, int32_t y_, uint32_t flags_) {
    marshal(6, seat_.wl_obj(), serial_, parent_.wl_obj(), x_, y_, flags_);
}

void shell_surface::set_maximized(output* output_) {
    marshal(7, output_ ? output_->wl_obj() : nullptr);
}

void shell_surface::set_title(const string& title_) {
    marshal(8, title_.c_str());
}

void shell_surface::set_class(const string& class__) {
    marshal(9, class__.c_str());
}

void shell_surface::ping_handler(void* data, wl_proxy* wl_obj, uint32_t serial_) {
    auto& handler = proxy::user_data_to_wrapper_cast<shell_surface>(data)->_ping_handler;
    if(handler) {
        handler(serial_);
    }
}

void shell_surface::configure_handler(void* data, wl_proxy* wl_obj, uint32_t edges_, int32_t width_, int32_t height_) {
    auto& handler = proxy::user_data_to_wrapper_cast<shell_surface>(data)->_configure_handler;
    if(handler) {
        handler(edges_, width_, height_);
    }
}

void shell_surface::popup_done_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<shell_surface>(data)->_popup_done_handler;
    if(handler) {
        handler();
    }
}

static const wl_interface* wl_surface_request_destroy_types[] = { };
static const wl_interface* wl_surface_request_attach_types[] = { &buffer::interface, nullptr, nullptr };
static const wl_interface* wl_surface_request_damage_types[] = { nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_surface_request_frame_types[] = { &callback::interface };
static const wl_interface* wl_surface_request_set_opaque_region_types[] = { &region::interface };
static const wl_interface* wl_surface_request_set_input_region_types[] = { &region::interface };
static const wl_interface* wl_surface_request_commit_types[] = { };
static const wl_interface* wl_surface_request_set_buffer_transform_types[] = { nullptr };
static const wl_interface* wl_surface_request_set_buffer_scale_types[] = { nullptr };

static const wl_message wl_surface_requests[] = {
    { "destroy", "", wl_surface_request_destroy_types },
    { "attach", "?oii", wl_surface_request_attach_types },
    { "damage", "iiii", wl_surface_request_damage_types },
    { "frame", "n", wl_surface_request_frame_types },
    { "set_opaque_region", "?o", wl_surface_request_set_opaque_region_types },
    { "set_input_region", "?o", wl_surface_request_set_input_region_types },
    { "commit", "", wl_surface_request_commit_types },
    { "set_buffer_transform", "2i", wl_surface_request_set_buffer_transform_types },
    { "set_buffer_scale", "3i", wl_surface_request_set_buffer_scale_types },
};

static const wl_interface* wl_surface_event_enter_types[] = { &output::interface };
static const wl_interface* wl_surface_event_leave_types[] = { &output::interface };

static const wl_message wl_surface_events[] = {
    { "enter", "o", wl_surface_event_enter_types },
    { "leave", "o", wl_surface_event_leave_types },
};

const wl_interface surface::interface = {
    "wl_surface", 3,
    9, wl_surface_requests,
    2, wl_surface_events
};

const surface::listener_t surface::listener = {
    &enter_handler,
    &leave_handler,
};

surface::surface(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

surface::surface(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

surface::~surface(){
    destroy();
}

void surface::attach(buffer* buffer_, int32_t x_, int32_t y_) {
    marshal(1, buffer_ ? buffer_->wl_obj() : nullptr, x_, y_);
}

void surface::damage(int32_t x_, int32_t y_, int32_t width_, int32_t height_) {
    marshal(2, x_, y_, width_, height_);
}

callback surface::frame() {
    callback callback_(*this);
    marshal(3, callback_.wl_obj());
    return callback_;
}

void surface::set_opaque_region(region* region_) {
    marshal(4, region_ ? region_->wl_obj() : nullptr);
}

void surface::set_input_region(region* region_) {
    marshal(5, region_ ? region_->wl_obj() : nullptr);
}

void surface::commit() {
    marshal(6);
}

void surface::set_buffer_transform(int32_t transform_) {
    marshal(7, transform_);
}

void surface::set_buffer_scale(int32_t scale_) {
    marshal(8, scale_);
}

void surface::destroy() {
    if(valid()) {
        marshal(0);
    }
    proxy::destroy();
}

void surface::enter_handler(void* data, wl_proxy* wl_obj, wl_proxy* output_) {
    auto& handler = proxy::user_data_to_wrapper_cast<surface>(data)->_enter_handler;
    if(handler) {
        handler(*proxy::wrapper_cast<output>(output_));
    }
}

void surface::leave_handler(void* data, wl_proxy* wl_obj, wl_proxy* output_) {
    auto& handler = proxy::user_data_to_wrapper_cast<surface>(data)->_leave_handler;
    if(handler) {
        handler(*proxy::wrapper_cast<output>(output_));
    }
}

static const wl_interface* wl_seat_request_get_pointer_types[] = { &pointer::interface };
static const wl_interface* wl_seat_request_get_keyboard_types[] = { &keyboard::interface };
static const wl_interface* wl_seat_request_get_touch_types[] = { &touch::interface };

static const wl_message wl_seat_requests[] = {
    { "get_pointer", "n", wl_seat_request_get_pointer_types },
    { "get_keyboard", "n", wl_seat_request_get_keyboard_types },
    { "get_touch", "n", wl_seat_request_get_touch_types },
};

static const wl_interface* wl_seat_event_capabilities_types[] = { nullptr };
static const wl_interface* wl_seat_event_name_types[] = { nullptr };

static const wl_message wl_seat_events[] = {
    { "capabilities", "u", wl_seat_event_capabilities_types },
    { "name", "2s", wl_seat_event_name_types },
};

const wl_interface seat::interface = {
    "wl_seat", 3,
    3, wl_seat_requests,
    2, wl_seat_events
};

const seat::listener_t seat::listener = {
    &capabilities_handler,
    &name_handler,
};

seat::seat(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

seat::seat(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

pointer seat::get_pointer() {
    pointer id_(*this);
    marshal(0, id_.wl_obj());
    return id_;
}

keyboard seat::get_keyboard() {
    keyboard id_(*this);
    marshal(1, id_.wl_obj());
    return id_;
}

touch seat::get_touch() {
    touch id_(*this);
    marshal(2, id_.wl_obj());
    return id_;
}

void seat::capabilities_handler(void* data, wl_proxy* wl_obj, uint32_t capabilities_) {
    auto& handler = proxy::user_data_to_wrapper_cast<seat>(data)->_capabilities_handler;
    if(handler) {
        handler(capabilities_);
    }
}

void seat::name_handler(void* data, wl_proxy* wl_obj, const char* name_) {
    auto& handler = proxy::user_data_to_wrapper_cast<seat>(data)->_name_handler;
    if(handler) {
        handler(name_);
    }
}

static const wl_interface* wl_pointer_request_set_cursor_types[] = { nullptr, &surface::interface, nullptr, nullptr };
static const wl_interface* wl_pointer_request_release_types[] = { };

static const wl_message wl_pointer_requests[] = {
    { "set_cursor", "u?oii", wl_pointer_request_set_cursor_types },
    { "release", "3", wl_pointer_request_release_types },
};

static const wl_interface* wl_pointer_event_enter_types[] = { nullptr, &surface::interface, nullptr, nullptr };
static const wl_interface* wl_pointer_event_leave_types[] = { nullptr, &surface::interface };
static const wl_interface* wl_pointer_event_motion_types[] = { nullptr, nullptr, nullptr };
static const wl_interface* wl_pointer_event_button_types[] = { nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_pointer_event_axis_types[] = { nullptr, nullptr, nullptr };

static const wl_message wl_pointer_events[] = {
    { "enter", "uoff", wl_pointer_event_enter_types },
    { "leave", "uo", wl_pointer_event_leave_types },
    { "motion", "uff", wl_pointer_event_motion_types },
    { "button", "uuuu", wl_pointer_event_button_types },
    { "axis", "uuf", wl_pointer_event_axis_types },
};

const wl_interface pointer::interface = {
    "wl_pointer", 3,
    2, wl_pointer_requests,
    5, wl_pointer_events
};

const pointer::listener_t pointer::listener = {
    &enter_handler,
    &leave_handler,
    &motion_handler,
    &button_handler,
    &axis_handler,
};

pointer::pointer(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

pointer::pointer(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

pointer::~pointer(){
    destroy();
}

void pointer::set_cursor(uint32_t serial_, surface* surface_, int32_t hotspot_x_, int32_t hotspot_y_) {
    marshal(0, serial_, surface_ ? surface_->wl_obj() : nullptr, hotspot_x_, hotspot_y_);
}

void pointer::destroy() {
    if(valid()) {
        marshal(1);
    }
    proxy::destroy();
}

void pointer::enter_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, wl_proxy* surface_, wl_fixed_t surface_x_, wl_fixed_t surface_y_) {
    auto& handler = proxy::user_data_to_wrapper_cast<pointer>(data)->_enter_handler;
    if(handler) {
        handler(serial_, *proxy::wrapper_cast<surface>(surface_), surface_x_, surface_y_);
    }
}

void pointer::leave_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, wl_proxy* surface_) {
    auto& handler = proxy::user_data_to_wrapper_cast<pointer>(data)->_leave_handler;
    if(handler) {
        handler(serial_, *proxy::wrapper_cast<surface>(surface_));
    }
}

void pointer::motion_handler(void* data, wl_proxy* wl_obj, uint32_t time_, wl_fixed_t surface_x_, wl_fixed_t surface_y_) {
    auto& handler = proxy::user_data_to_wrapper_cast<pointer>(data)->_motion_handler;
    if(handler) {
        handler(time_, surface_x_, surface_y_);
    }
}

void pointer::button_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, uint32_t time_, uint32_t button_, uint32_t state_) {
    auto& handler = proxy::user_data_to_wrapper_cast<pointer>(data)->_button_handler;
    if(handler) {
        handler(serial_, time_, button_, state_);
    }
}

void pointer::axis_handler(void* data, wl_proxy* wl_obj, uint32_t time_, uint32_t axis_, wl_fixed_t value_) {
    auto& handler = proxy::user_data_to_wrapper_cast<pointer>(data)->_axis_handler;
    if(handler) {
        handler(time_, axis_, value_);
    }
}

static const wl_interface* wl_keyboard_request_release_types[] = { };

static const wl_message wl_keyboard_requests[] = {
    { "release", "3", wl_keyboard_request_release_types },
};

static const wl_interface* wl_keyboard_event_keymap_types[] = { nullptr, nullptr, nullptr };
static const wl_interface* wl_keyboard_event_enter_types[] = { nullptr, &surface::interface, nullptr };
static const wl_interface* wl_keyboard_event_leave_types[] = { nullptr, &surface::interface };
static const wl_interface* wl_keyboard_event_key_types[] = { nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_keyboard_event_modifiers_types[] = { nullptr, nullptr, nullptr, nullptr, nullptr };

static const wl_message wl_keyboard_events[] = {
    { "keymap", "uhu", wl_keyboard_event_keymap_types },
    { "enter", "uoa", wl_keyboard_event_enter_types },
    { "leave", "uo", wl_keyboard_event_leave_types },
    { "key", "uuuu", wl_keyboard_event_key_types },
    { "modifiers", "uuuuu", wl_keyboard_event_modifiers_types },
};

const wl_interface keyboard::interface = {
    "wl_keyboard", 3,
    1, wl_keyboard_requests,
    5, wl_keyboard_events
};

const keyboard::listener_t keyboard::listener = {
    &keymap_handler,
    &enter_handler,
    &leave_handler,
    &key_handler,
    &modifiers_handler,
};

keyboard::keyboard(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

keyboard::keyboard(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

keyboard::~keyboard(){
    destroy();
}

void keyboard::destroy() {
    if(valid()) {
        marshal(0);
    }
    proxy::destroy();
}

void keyboard::keymap_handler(void* data, wl_proxy* wl_obj, uint32_t format_, int32_t fd_, uint32_t size_) {
    auto& handler = proxy::user_data_to_wrapper_cast<keyboard>(data)->_keymap_handler;
    if(handler) {
        handler(format_, fd_, size_);
    }
}

void keyboard::enter_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, wl_proxy* surface_, const wl_array* keys_) {
    auto& handler = proxy::user_data_to_wrapper_cast<keyboard>(data)->_enter_handler;
    if(handler) {
        handler(serial_, *proxy::wrapper_cast<surface>(surface_), *keys_);
    }
}

void keyboard::leave_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, wl_proxy* surface_) {
    auto& handler = proxy::user_data_to_wrapper_cast<keyboard>(data)->_leave_handler;
    if(handler) {
        handler(serial_, *proxy::wrapper_cast<surface>(surface_));
    }
}

void keyboard::key_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, uint32_t time_, uint32_t key_, uint32_t state_) {
    auto& handler = proxy::user_data_to_wrapper_cast<keyboard>(data)->_key_handler;
    if(handler) {
        handler(serial_, time_, key_, state_);
    }
}

void keyboard::modifiers_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, uint32_t mods_depressed_, uint32_t mods_latched_, uint32_t mods_locked_, uint32_t group_) {
    auto& handler = proxy::user_data_to_wrapper_cast<keyboard>(data)->_modifiers_handler;
    if(handler) {
        handler(serial_, mods_depressed_, mods_latched_, mods_locked_, group_);
    }
}

static const wl_interface* wl_touch_request_release_types[] = { };

static const wl_message wl_touch_requests[] = {
    { "release", "3", wl_touch_request_release_types },
};

static const wl_interface* wl_touch_event_down_types[] = { nullptr, nullptr, &surface::interface, nullptr, nullptr, nullptr };
static const wl_interface* wl_touch_event_up_types[] = { nullptr, nullptr, nullptr };
static const wl_interface* wl_touch_event_motion_types[] = { nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_touch_event_frame_types[] = { };
static const wl_interface* wl_touch_event_cancel_types[] = { };

static const wl_message wl_touch_events[] = {
    { "down", "uuoiff", wl_touch_event_down_types },
    { "up", "uui", wl_touch_event_up_types },
    { "motion", "uiff", wl_touch_event_motion_types },
    { "frame", "", wl_touch_event_frame_types },
    { "cancel", "", wl_touch_event_cancel_types },
};

const wl_interface touch::interface = {
    "wl_touch", 3,
    1, wl_touch_requests,
    5, wl_touch_events
};

const touch::listener_t touch::listener = {
    &down_handler,
    &up_handler,
    &motion_handler,
    &frame_handler,
    &cancel_handler,
};

touch::touch(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

touch::touch(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

touch::~touch(){
    destroy();
}

void touch::destroy() {
    if(valid()) {
        marshal(0);
    }
    proxy::destroy();
}

void touch::down_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, uint32_t time_, wl_proxy* surface_, int32_t id_, wl_fixed_t x_, wl_fixed_t y_) {
    auto& handler = proxy::user_data_to_wrapper_cast<touch>(data)->_down_handler;
    if(handler) {
        handler(serial_, time_, *proxy::wrapper_cast<surface>(surface_), id_, x_, y_);
    }
}

void touch::up_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, uint32_t time_, int32_t id_) {
    auto& handler = proxy::user_data_to_wrapper_cast<touch>(data)->_up_handler;
    if(handler) {
        handler(serial_, time_, id_);
    }
}

void touch::motion_handler(void* data, wl_proxy* wl_obj, uint32_t time_, int32_t id_, wl_fixed_t x_, wl_fixed_t y_) {
    auto& handler = proxy::user_data_to_wrapper_cast<touch>(data)->_motion_handler;
    if(handler) {
        handler(time_, id_, x_, y_);
    }
}

void touch::frame_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<touch>(data)->_frame_handler;
    if(handler) {
        handler();
    }
}

void touch::cancel_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<touch>(data)->_cancel_handler;
    if(handler) {
        handler();
    }
}

static const wl_interface* wl_output_event_geometry_types[] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_output_event_mode_types[] = { nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_output_event_done_types[] = { };
static const wl_interface* wl_output_event_scale_types[] = { nullptr };

static const wl_message wl_output_events[] = {
    { "geometry", "iiiiissi", wl_output_event_geometry_types },
    { "mode", "uiii", wl_output_event_mode_types },
    { "done", "2", wl_output_event_done_types },
    { "scale", "2i", wl_output_event_scale_types },
};

const wl_interface output::interface = {
    "wl_output", 2,
    0, nullptr,
    4, wl_output_events
};

const output::listener_t output::listener = {
    &geometry_handler,
    &mode_handler,
    &done_handler,
    &scale_handler,
};

output::output(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

output::output(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

void output::geometry_handler(void* data, wl_proxy* wl_obj, int32_t x_, int32_t y_, int32_t physical_width_, int32_t physical_height_, int32_t subpixel_, const char* make_, const char* model_, int32_t transform_) {
    auto& handler = proxy::user_data_to_wrapper_cast<output>(data)->_geometry_handler;
    if(handler) {
        handler(x_, y_, physical_width_, physical_height_, subpixel_, make_, model_, transform_);
    }
}

void output::mode_handler(void* data, wl_proxy* wl_obj, uint32_t flags_, int32_t width_, int32_t height_, int32_t refresh_) {
    auto& handler = proxy::user_data_to_wrapper_cast<output>(data)->_mode_handler;
    if(handler) {
        handler(flags_, width_, height_, refresh_);
    }
}

void output::done_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<output>(data)->_done_handler;
    if(handler) {
        handler();
    }
}

void output::scale_handler(void* data, wl_proxy* wl_obj, int32_t factor_) {
    auto& handler = proxy::user_data_to_wrapper_cast<output>(data)->_scale_handler;
    if(handler) {
        handler(factor_);
    }
}

static const wl_interface* wl_region_request_destroy_types[] = { };
static const wl_interface* wl_region_request_add_types[] = { nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_region_request_subtract_types[] = { nullptr, nullptr, nullptr, nullptr };

static const wl_message wl_region_requests[] = {
    { "destroy", "", wl_region_request_destroy_types },
    { "add", "iiii", wl_region_request_add_types },
    { "subtract", "iiii", wl_region_request_subtract_types },
};

const wl_interface region::interface = {
    "wl_region", 1,
    3, wl_region_requests,
    0, nullptr
};

region::region(wl_proxy* obj)
    : proxy(obj) {
}

region::region(proxy& factory)
    : proxy(factory, interface) {
}

region::~region(){
    destroy();
}

void region::add(int32_t x_, int32_t y_, int32_t width_, int32_t height_) {
    marshal(1, x_, y_, width_, height_);
}

void region::subtract(int32_t x_, int32_t y_, int32_t width_, int32_t height_) {
    marshal(2, x_, y_, width_, height_);
}

void region::destroy() {
    if(valid()) {
        marshal(0);
    }
    proxy::destroy();
}

