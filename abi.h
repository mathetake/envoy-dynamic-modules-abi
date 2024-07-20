#ifndef ENVOY_DYNAMIC_MODULE_ABI_
#define ENVOY_DYNAMIC_MODULE_ABI_

#ifdef __cplusplus
#include <cstddef>
extern "C" {
#else
#include <stddef.h>
#endif

// -----------------------------------------------------------------------------
// ----------------------------------- Types -----------------------------------
// -----------------------------------------------------------------------------

// These two macros are used to indicate the ownership of the memory for the types suffixed by
// `Ptr`.
#define OWNED_BY_ENVOY  // Indicates that the memory is owned by Envoy.
#define OWNED_BY_MODULE // Indicates that the memory is owned by the module.

// __envoy_dynamic_module_v1_type_ModuleConfigPtr is a pointer to the configuration passed to the
// __envoy_dynamic_module_v1_event_module_init function. Envoy owns the memory of the configuration
// and the module is not supposed to take ownership of it.
typedef const char* __envoy_dynamic_module_v1_type_ModuleConfigPtr OWNED_BY_ENVOY;

// __envoy_dynamic_module_v1_type_ModuleConfigSize is the size of the configuration passed to the
// __envoy_dynamic_module_v1_event_module_init function.
typedef size_t __envoy_dynamic_module_v1_type_ModuleConfigSize;

// __envoy_dynamic_module_v1_type_ModuleContextPtr is a pointer to in-module singleton context
// corresponding to the module. This is passed to __envoy_dynamic_module_v1_event_http_context_init.
typedef void* __envoy_dynamic_module_v1_type_ModuleContextPtr OWNED_BY_MODULE;

// __envoy_dynamic_module_v1_type_EnvoyFilterPtr is a pointer to the DynamicModule::HttpFilter
// instance. It is always passed to the module's http event hooks. Modules are not supposed to
// manipulate this pointer.
typedef void* __envoy_dynamic_module_v1_type_EnvoyFilterPtr OWNED_BY_ENVOY;

// __envoy_dynamic_module_v1_type_HttpContextPtr is a pointer to in-module context corresponding
// to a single DynamicModule::HttpFilter instance. It is always passed to the module's event hooks.
typedef void* __envoy_dynamic_module_v1_type_HttpContextPtr OWNED_BY_MODULE;

// __envoy_dynamic_module_v1_type_HttpRequestHeadersMapPtr is a pointer to the header map instance.
// This is passed to the __envoy_dynamic_module_v1_event_http_request_headers event hook.
// Modules are not supposed to manipulate this pointer.
typedef void* __envoy_dynamic_module_v1_type_HttpRequestHeadersMapPtr OWNED_BY_ENVOY;

// __envoy_dynamic_module_v1_type_EventHttpRequestHeadersStatus is the return value of the
// __envoy_dynamic_module_v1_event_http_request_headers event. It should be one of the values
// defined in the FilterHeadersStatus enum.
typedef size_t __envoy_dynamic_module_v1_type_EventHttpRequestHeadersStatus;

// __envoy_dynamic_module_v1_type_HttpResponseHeaderMapPtr is a pointer to the header map instance.
// This is passed to the __envoy_dynamic_module_v1_event_http_response_headers event hook.
// Modules are not supposed to manipulate this pointer.
typedef void* __envoy_dynamic_module_v1_type_HttpResponseHeaderMapPtr OWNED_BY_ENVOY;

// __envoy_dynamic_module_v1_type_EventHttpResponseHeadersStatus is the return value of the
// __envoy_dynamic_module_v1_event_http_response_headers event. It should be one of the values
// defined in the FilterHeadersStatus enum.
typedef size_t __envoy_dynamic_module_v1_type_EventHttpResponseHeadersStatus;

// __envoy_dynamic_module_v1_type_HttpRequestBodyBufferPtr is a pointer to the body buffer instance
// passed via __envoy_dynamic_module_v1_event_http_request_body event hook.
// Modules are not supposed to manipulate this pointer directly.
typedef void* __envoy_dynamic_module_v1_type_HttpRequestBodyBufferPtr OWNED_BY_ENVOY;

// __envoy_dynamic_module_v1_type_EventHttpRequestBodyStatus is the return value of the
// __envoy_dynamic_module_v1_event_http_request_body event. It should be one of the values defined
// in the FilterDataStatus enum.
typedef size_t __envoy_dynamic_module_v1_type_EventHttpRequestBodyStatus;

// __envoy_dynamic_module_v1_type_HttpResponseBodyBufferPtr is a pointer to the body buffer instance
// passed via __envoy_dynamic_module_v1_event_http_response_body event hook.
// Modules are not supposed to manipulate this pointer directly.
typedef void* __envoy_dynamic_module_v1_type_HttpResponseBodyBufferPtr OWNED_BY_ENVOY;

// __envoy_dynamic_module_v1_type_EventHttpResponseBodyStatus is the return value of the
// __envoy_dynamic_module_v1_event_http_response_body event. It should be one of the values defined
// in the FilterDataStatus enum.
typedef size_t __envoy_dynamic_module_v1_type_EventHttpResponseBodyStatus;

// __envoy_dynamic_module_v1_type_EndOfStream is a boolean value indicating whether the stream has
// reached the end. The value should be 0 if the stream has not reached the end, and 1 if the stream
// has reached the end.
typedef size_t __envoy_dynamic_module_v1_type_EndOfStream;

// __envoy_dynamic_module_v1_type_InModuleBufferPtr is a pointer to a buffer that is managed by the
// module.
typedef const char* __envoy_dynamic_module_v1_type_InModuleBufferPtr OWNED_BY_MODULE;

// __envoy_dynamic_module_v1_type_InModuleBufferLength is the length of the buffer.
typedef size_t __envoy_dynamic_module_v1_type_InModuleBufferLength;

// __envoy_dynamic_module_v1_type_DataSlicePtr is a pointer to a buffer that is managed by Envoy.
// This is used to pass buffer slices to the module.
typedef const char* __envoy_dynamic_module_v1_type_DataSlicePtr OWNED_BY_MODULE;

// __envoy_dynamic_module_v1_type_DataSliceLength is the length of the buffer slice.
typedef size_t __envoy_dynamic_module_v1_type_DataSliceLength;

// -----------------------------------------------------------------------------
// ----------------------------------- Enums -----------------------------------
// -----------------------------------------------------------------------------

// __ENVOY_DYNAMIC_MODULE_V1_HEADER_STATUS_CONTINUE indicates that the module has finished
// processing the headers and Envoy should continue processing the request body or response body.
#define __ENVOY_DYNAMIC_MODULE_V1_HEADER_STATUS_CONTINUE 0
// __ENVOY_DYNAMIC_MODULE_V1_HEADER_STATUS_STOP_ITERATION indicates that Envoy shouldn't continue
// from processing the headers and should stop iteration. This means that body data will not be
// processed. In other words, event_http_request_body and event_http_response_body will not be
// called until continue_request or continue_response is called.
#define __ENVOY_DYNAMIC_MODULE_V1_HEADER_STATUS_STOP_ITERATION 1
// __ENVOY_DYNAMIC_MODULE_V1_HEADER_STATUS_STOP_ALL_ITERATION_AND_BUFFER indicates
// that Envoy should stop iteration on headers but continue to buffer the request/response body
// until the limit is reached. When the limit is reached, Envoy will stop buffering and returns 500
// to the client. This means that event_http_request_body and event_http_response_body will be
// called while without sendin headers to the upstream.
//
// The header processing can be resumed by either calling continue_request/continue_response, or
// returns continue status in the event_http_request_body or event_http_response_body.
#define __ENVOY_DYNAMIC_MODULE_V1_HEADER_STATUS_STOP_ALL_ITERATION_AND_BUFFER 3

const __envoy_dynamic_module_v1_type_EventHttpRequestHeadersStatus
    __envoy_dynamic_module_v1_type_EventHttpRequestHeadersStatusContinue =
        __ENVOY_DYNAMIC_MODULE_V1_HEADER_STATUS_CONTINUE;
const __envoy_dynamic_module_v1_type_EventHttpRequestHeadersStatus
    __envoy_dynamic_module_v1_type_EventHttpRequestHeadersStatusStopIteration =
        __ENVOY_DYNAMIC_MODULE_V1_HEADER_STATUS_STOP_ITERATION;
const __envoy_dynamic_module_v1_type_EventHttpRequestHeadersStatus
    __envoy_dynamic_module_v1_type_EventHttpRequestHeadersStatusStopAllIterationAndBuffer =
        __ENVOY_DYNAMIC_MODULE_V1_HEADER_STATUS_STOP_ALL_ITERATION_AND_BUFFER;

const __envoy_dynamic_module_v1_type_EventHttpResponseHeadersStatus
    __envoy_dynamic_module_v1_type_EventHttpResponseHeadersStatusContinue =
        __ENVOY_DYNAMIC_MODULE_V1_HEADER_STATUS_CONTINUE;
const __envoy_dynamic_module_v1_type_EventHttpResponseHeadersStatus
    __envoy_dynamic_module_v1_type_EventHttpResponseHeadersStatusStopIteration =
        __ENVOY_DYNAMIC_MODULE_V1_HEADER_STATUS_STOP_ITERATION;
const __envoy_dynamic_module_v1_type_EventHttpResponseHeadersStatus
    __envoy_dynamic_module_v1_type_EventHttpResponseHeadersStatusStopAllIterationAndBuffer =
        __ENVOY_DYNAMIC_MODULE_V1_HEADER_STATUS_STOP_ALL_ITERATION_AND_BUFFER;

// __ENVOY_DYNAMIC_MODULE_V1_BODY_STATUS_CONTINUE indicates that the module has finished
// processing the body frame and Envoy should continue processing the request or response.
//
// This resumes the header processing if it was stopped in the event_http_request_headers or
// event_http_response_headers.
#define __ENVOY_DYNAMIC_MODULE_V1_BODY_STATUS_CONTINUE 0

// __ENVOY_DYNAMIC_MODULE_V1_BODY_STATUS_STOP_ITERATION indicates that Envoy shouldn't continue
// from processing the body frame and should stop iteration, but continue buffering the body until
// the limit is reached. When the limit is reached, Envoy will stop buffering and returns 500 to the
// client.
//
// This stops sending body data to the upstream, so if the module wants to continue sending body
// data, it should call continue_request or continue_response or return continue status in the
// subsequent event_http_request_body or event_http_response_body.
#define __ENVOY_DYNAMIC_MODULE_V1_BODY_STATUS_STOP_ITERATION_AND_BUFFER 1

const __envoy_dynamic_module_v1_type_EventHttpRequestBodyStatus
    __envoy_dynamic_module_v1_type_EventHttpRequestBodyStatusContinue =
        __ENVOY_DYNAMIC_MODULE_V1_BODY_STATUS_CONTINUE;

const __envoy_dynamic_module_v1_type_EventHttpResponseBodyStatus
    __envoy_dynamic_module_v1_type_EventHttpResponseBodyStatusContinue =
        __ENVOY_DYNAMIC_MODULE_V1_BODY_STATUS_CONTINUE;

// -----------------------------------------------------------------------------
// ------------------------------- Event Hooks ---------------------------------
// -----------------------------------------------------------------------------
//
// Event hooks are functions that are called by Envoy to notify the module of events.
// The module must implement and export these functions in the dynamic module.

// If this is the Envoy code, all definitions are declared as function pointers typedefs.
#ifdef ENVOY_DYNAMIC_MODULE
typedef __envoy_dynamic_module_v1_type_ModuleContextPtr (
    *__envoy_dynamic_module_v1_event_module_init)(__envoy_dynamic_module_v1_type_ModuleConfigPtr,
                                                  __envoy_dynamic_module_v1_type_ModuleConfigSize);
typedef __envoy_dynamic_module_v1_type_HttpContextPtr (
    *__envoy_dynamic_module_v1_event_http_context_init)(
    __envoy_dynamic_module_v1_type_EnvoyFilterPtr, __envoy_dynamic_module_v1_type_ModuleContextPtr);
typedef __envoy_dynamic_module_v1_type_EventHttpRequestHeadersStatus (
    *__envoy_dynamic_module_v1_event_http_request_headers)(
    __envoy_dynamic_module_v1_type_EnvoyFilterPtr, __envoy_dynamic_module_v1_type_HttpContextPtr,
    __envoy_dynamic_module_v1_type_HttpRequestHeadersMapPtr,
    __envoy_dynamic_module_v1_type_EndOfStream);
typedef __envoy_dynamic_module_v1_type_EventHttpRequestBodyStatus (
    *__envoy_dynamic_module_v1_event_http_request_body)(
    __envoy_dynamic_module_v1_type_EnvoyFilterPtr, __envoy_dynamic_module_v1_type_HttpContextPtr,
    __envoy_dynamic_module_v1_type_HttpRequestBodyBufferPtr,
    __envoy_dynamic_module_v1_type_EndOfStream);
typedef __envoy_dynamic_module_v1_type_EventHttpResponseHeadersStatus (
    *__envoy_dynamic_module_v1_event_http_response_headers)(
    __envoy_dynamic_module_v1_type_EnvoyFilterPtr, __envoy_dynamic_module_v1_type_HttpContextPtr,
    __envoy_dynamic_module_v1_type_HttpResponseHeaderMapPtr,
    __envoy_dynamic_module_v1_type_EndOfStream);
typedef __envoy_dynamic_module_v1_type_EventHttpResponseBodyStatus (
    *__envoy_dynamic_module_v1_event_http_response_body)(
    __envoy_dynamic_module_v1_type_EnvoyFilterPtr, __envoy_dynamic_module_v1_type_HttpContextPtr,
    __envoy_dynamic_module_v1_type_HttpResponseBodyBufferPtr,
    __envoy_dynamic_module_v1_type_EndOfStream);
typedef void (*__envoy_dynamic_module_v1_event_http_destroy)(
    __envoy_dynamic_module_v1_type_EnvoyFilterPtr, __envoy_dynamic_module_v1_type_HttpContextPtr);

#else // If this is the module code, all definitions are declared function prototypes.

// __envoy_dynamic_module_v1_event_module_init is called by the main thread when the module is
// loaded exactly once per module. The function returns
// __envoy_dynamic_module_v1_type_ModuleContextPtr which is a pointer to the module context. The
// lifetime of the returned pointer should be managed by the dynamic module. Returning nullptr
// indicates a failure to initialize the module.
__envoy_dynamic_module_v1_type_ModuleContextPtr __envoy_dynamic_module_v1_event_module_init(
    __envoy_dynamic_module_v1_type_ModuleConfigPtr config_ptr,
    __envoy_dynamic_module_v1_type_ModuleConfigSize config_size);

// __envoy_dynamic_module_v1_event_http_context_init is called by any worker thread when a new
// stream is created. That means that the function should be thread-safe.
//
// The function returns a pointer to a new instance of the context or nullptr on failure.
// The lifetime of the returned pointer should be managed by the dynamic module.
__envoy_dynamic_module_v1_type_HttpContextPtr __envoy_dynamic_module_v1_event_http_context_init(
    __envoy_dynamic_module_v1_type_EnvoyFilterPtr envoy_filter_ptr,
    __envoy_dynamic_module_v1_type_ModuleContextPtr module_ctx_ptr);

// __envoy_dynamic_module_v1_event_http_request_headers is called when request headers are received.
__envoy_dynamic_module_v1_type_EventHttpRequestHeadersStatus
__envoy_dynamic_module_v1_event_http_request_headers(
    __envoy_dynamic_module_v1_type_EnvoyFilterPtr envoy_filter_ptr,
    __envoy_dynamic_module_v1_type_HttpContextPtr http_context_ptr,
    __envoy_dynamic_module_v1_type_HttpRequestHeadersMapPtr request_headers_ptr,
    __envoy_dynamic_module_v1_type_EndOfStream end_of_stream);

// __envoy_dynamic_module_v1_event_http_request_body is called when request body data is received.
__envoy_dynamic_module_v1_type_EventHttpRequestBodyStatus
__envoy_dynamic_module_v1_event_http_request_body(
    __envoy_dynamic_module_v1_type_EnvoyFilterPtr envoy_filter_ptr,
    __envoy_dynamic_module_v1_type_HttpContextPtr http_context_ptr,
    __envoy_dynamic_module_v1_type_HttpRequestBodyBufferPtr buffer,
    __envoy_dynamic_module_v1_type_EndOfStream end_of_stream);

// __envoy_dynamic_module_v1_event_http_response_headers is called when response headers are
// received.
__envoy_dynamic_module_v1_type_EventHttpResponseHeadersStatus
__envoy_dynamic_module_v1_event_http_response_headers(
    __envoy_dynamic_module_v1_type_EnvoyFilterPtr envoy_filter_ptr,
    __envoy_dynamic_module_v1_type_HttpContextPtr http_context_ptr,
    __envoy_dynamic_module_v1_type_HttpResponseHeaderMapPtr response_headers_map_ptr,
    __envoy_dynamic_module_v1_type_EndOfStream end_of_stream);

// __envoy_dynamic_module_v1_event_http_response_body is called when response body data is received.
__envoy_dynamic_module_v1_type_EventHttpResponseBodyStatus
__envoy_dynamic_module_v1_event_http_response_body(
    __envoy_dynamic_module_v1_type_EnvoyFilterPtr envoy_filter_ptr,
    __envoy_dynamic_module_v1_type_HttpContextPtr http_context_ptr,
    __envoy_dynamic_module_v1_type_HttpResponseBodyBufferPtr buffer,
    __envoy_dynamic_module_v1_type_EndOfStream end_of_stream);

// __envoy_dynamic_module_v1_event_http_destroy is called when the stream is destroyed.
void __envoy_dynamic_module_v1_event_http_destroy(
    __envoy_dynamic_module_v1_type_EnvoyFilterPtr envoy_filter_ptr,
    __envoy_dynamic_module_v1_type_HttpContextPtr http_context_ptr);
#endif

#undef OWNED_BY_ENVOY
#undef OWNED_BY_MODULE

// ---------------------------------------------------------------------------------
// ----------------------------------- Envoy API -----------------------------------
// ---------------------------------------------------------------------------------
//
// The following functions are called by the module to interact with Envoy.

// ---------------- Header API ----------------

// __envoy_dynamic_module_v1_get_request_header is called by the module to get the value for a
// request header key. headers is the one passed to the
// __envoy_dynamic_module_v1_event_http_request_headers. key is the header key to look up.
// result_buffer_ptr and result_buffer_length_ptr are direct references to the buffer and length of
// the value. The function returns the number of values found. If the key is not found, this
// function returns nullptr and 0.
//
// Basically, this acts as a fast zero-copy lookup for a single header value, which is almost always
// guaranteed to be true. In case of multiple values, the module can access n-th value by calling
// __envoy_dynamic_module_v1_http_get_request_header_value_nth following this function.
size_t __envoy_dynamic_module_v1_http_get_request_header_value(
    __envoy_dynamic_module_v1_type_HttpResponseHeaderMapPtr headers,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr key,
    __envoy_dynamic_module_v1_type_InModuleBufferLength key_length,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr* result_buffer_ptr,
    __envoy_dynamic_module_v1_type_InModuleBufferLength* result_buffer_length_ptr);

// __envoy_dynamic_module_v1_http_get_request_header_value_nth is almost the same as
// __envoy_dynamic_module_v1_http_get_request_header_value, but it allows the module to access n-th
// value of the header. The function returns the number of values found. If nth is out of
// bounds, this function returns nullptr and 0.
void __envoy_dynamic_module_v1_http_get_request_header_value_nth(
    __envoy_dynamic_module_v1_type_HttpResponseHeaderMapPtr headers,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr key,
    __envoy_dynamic_module_v1_type_InModuleBufferLength key_length,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr* result_buffer_ptr,
    __envoy_dynamic_module_v1_type_InModuleBufferLength* result_buffer_length_ptr, size_t nth);

// __envoy_dynamic_module_v1_http_get_response_header_value is called by the module to get the value
// for a response header key. headers is the one passed to the
// __envoy_dynamic_module_v1_event_http_response_headers. key is the header key to look up.
// result_buffer_ptr and result_buffer_length_ptr are direct references to the buffer and length of
// the value. The function returns the number of values found. If the key is not found, this
// function returns nullptr and 0.
//
// Basically, this acts as a fast zero-copy lookup for a single header value, which is almost always
// guaranteed to be true. In case of multiple values, the module can access n-th value by calling
// __envoy_dynamic_module_v1_http_get_response_header_value_nth following this function.
size_t __envoy_dynamic_module_v1_http_get_response_header_value(
    __envoy_dynamic_module_v1_type_HttpResponseHeaderMapPtr headers,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr key,
    __envoy_dynamic_module_v1_type_InModuleBufferLength key_length,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr* result_buffer_ptr,
    __envoy_dynamic_module_v1_type_InModuleBufferLength* result_buffer_length_ptr);

// __envoy_dynamic_module_v1_http_get_response_header_value_nth is almost the same as
// __envoy_dynamic_module_v1_http_get_response_header_value, but it allows the module to access n-th
// value of the header. The function returns the number of values found. If nth is out of
// bounds, this function returns nullptr and 0.
void __envoy_dynamic_module_v1_http_get_response_header_value_nth(
    __envoy_dynamic_module_v1_type_HttpResponseHeaderMapPtr headers,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr key,
    __envoy_dynamic_module_v1_type_InModuleBufferLength key_length,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr* result_buffer_ptr,
    __envoy_dynamic_module_v1_type_InModuleBufferLength* result_buffer_length_ptr, size_t nth);

// __envoy_dynamic_module_v1_http_set_request_header is called by the module to set the value
// for a request header key. headers is the one passed to the
// __envoy_dynamic_module_v1_event_http_request_headers. If the key is not found, this function
// should add a new header with the key and value. If the key is found, this function should replace
// the value with the new one. If the value is empty, this function should remove the key. If there
// are multiple headers with the same key, this function removes all of them and adds a new one.
void __envoy_dynamic_module_v1_http_set_request_header(
    __envoy_dynamic_module_v1_type_HttpRequestHeadersMapPtr headers,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr key,
    __envoy_dynamic_module_v1_type_InModuleBufferLength key_length,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr value,
    __envoy_dynamic_module_v1_type_InModuleBufferLength value_length);

// __envoy_dynamic_module_v1_http_set_response_header is called by the module to set the value
// for a response header key. headers is the one passed to the
// __envoy_dynamic_module_v1_event_http_response_headers.
// If the key is not found, this function should add a new header with the key and value. If the key
// is found, this function should replace the value with the new one. If the value is empty, this
// function should remove the key. If there are multiple headers with the same key, this function
// removes all of them and adds a new one.
void __envoy_dynamic_module_v1_http_set_response_header(
    __envoy_dynamic_module_v1_type_HttpResponseHeaderMapPtr headers,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr key,
    __envoy_dynamic_module_v1_type_InModuleBufferLength key_length,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr value,
    __envoy_dynamic_module_v1_type_InModuleBufferLength value_length);

// ---------------- Buffer API ----------------

// __envoy_dynamic_module_v1_http_get_request_body_buffer_length is called by the module to get the
// length (number of bytes) of the request body buffer. The function returns the length of the
// buffer.
size_t __envoy_dynamic_module_v1_http_get_request_body_buffer_length(
    __envoy_dynamic_module_v1_type_HttpRequestBodyBufferPtr buffer);

// __envoy_dynamic_module_v1_http_get_request_body_buffer_slices_count is called by the module to
// get the number of slices in the request body buffer. The function returns the number of
// slices.
size_t __envoy_dynamic_module_v1_http_get_request_body_buffer_slices_count(
    __envoy_dynamic_module_v1_type_HttpRequestBodyBufferPtr buffer);

// __envoy_dynamic_module_v1_http_get_request_body_buffer_slice is called by the module to get the
// n-th slice of the request body buffer. The function returns the buffer and length of the
// slice. If nth is out of bounds, this function returns nullptr and 0.
void __envoy_dynamic_module_v1_http_get_request_body_buffer_slice(
    __envoy_dynamic_module_v1_type_HttpRequestBodyBufferPtr buffer, size_t nth,
    __envoy_dynamic_module_v1_type_DataSlicePtr* result_buffer_ptr,
    __envoy_dynamic_module_v1_type_DataSliceLength* result_buffer_length_ptr);

// __envoy_dynamic_module_v1_http_get_request_body_buffer_append is called by the module to append
// data to the request body buffer. The function appends data to the end of the buffer.
//
// After calling this function, the previously returned slices may be invalidated.
void __envoy_dynamic_module_v1_http_get_request_body_buffer_append(
    __envoy_dynamic_module_v1_type_HttpRequestBodyBufferPtr buffer,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr data,
    __envoy_dynamic_module_v1_type_InModuleBufferLength data_length);

// __envoy_dynamic_module_v1_http_get_request_body_buffer_prepend is called by the module to prepend
// data to the request body buffer. The function prepends data to the beginning of the buffer.
//
// After calling this function, the previously returned slices may be invalidated.
void __envoy_dynamic_module_v1_http_get_request_body_buffer_prepend(
    __envoy_dynamic_module_v1_type_HttpRequestBodyBufferPtr buffer,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr data,
    __envoy_dynamic_module_v1_type_InModuleBufferLength data_length);

// __envoy_dynamic_module_v1_http_get_request_body_buffer_drain is called by the module to drain
// data from the request body buffer. The function drains length bytes from the beginning of the
// buffer.
//
// After calling this function, the previously returned slices may be invalidated.
void __envoy_dynamic_module_v1_http_get_request_body_buffer_drain(
    __envoy_dynamic_module_v1_type_HttpRequestBodyBufferPtr buffer, size_t length);

// __envoy_dynamic_module_v1_http_get_response_body_buffer_length is called by the module to get the
// length (number of bytes) of the response body buffer. The function returns the length of the
// buffer.
size_t __envoy_dynamic_module_v1_http_get_response_body_buffer_length(
    __envoy_dynamic_module_v1_type_HttpResponseBodyBufferPtr buffer);

// __envoy_dynamic_module_v1_http_get_response_body_buffer_slices_count is called by the module to
// get the number of slices in the response body buffer. The function returns the number of
// slices.
size_t __envoy_dynamic_module_v1_http_get_response_body_buffer_slices_count(
    __envoy_dynamic_module_v1_type_HttpResponseBodyBufferPtr buffer);

// __envoy_dynamic_module_v1_http_get_response_body_buffer_slice is called by the module to get the
// n-th slice of the response body buffer. The function returns the buffer and length of the
// slice. If nth is out of bounds, this function returns nullptr and 0.
void __envoy_dynamic_module_v1_http_get_response_body_buffer_slice(
    __envoy_dynamic_module_v1_type_HttpResponseBodyBufferPtr buffer, size_t nth,
    __envoy_dynamic_module_v1_type_DataSlicePtr* result_buffer_ptr,
    __envoy_dynamic_module_v1_type_DataSliceLength* result_buffer_length_ptr);

// __envoy_dynamic_module_v1_http_get_response_body_buffer_append is called by the module to append
// data to the response body buffer. The function appends data to the end of the buffer.
//
// After calling this function, the previously returned slices may be invalidated.
void __envoy_dynamic_module_v1_http_get_response_body_buffer_append(
    __envoy_dynamic_module_v1_type_HttpResponseBodyBufferPtr buffer,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr data,
    __envoy_dynamic_module_v1_type_InModuleBufferLength data_length);

// __envoy_dynamic_module_v1_http_get_response_body_buffer_prepend is called by the module to
// prepend data to the response body buffer. The function prepends data to the beginning of the
// buffer.
//
// After calling this function, the previously returned slices may be invalidated.
void __envoy_dynamic_module_v1_http_get_response_body_buffer_prepend(
    __envoy_dynamic_module_v1_type_HttpResponseBodyBufferPtr buffer,
    __envoy_dynamic_module_v1_type_InModuleBufferPtr data,
    __envoy_dynamic_module_v1_type_InModuleBufferLength data_length);

// __envoy_dynamic_module_v1_http_get_response_body_buffer_drain is called by the module to drain
// data from the response body buffer. The function drains length bytes from the beginning of the
// buffer.
//
// After calling this function, the previously returned slices may be invalidated.
void __envoy_dynamic_module_v1_http_get_response_body_buffer_drain(
    __envoy_dynamic_module_v1_type_HttpResponseBodyBufferPtr buffer, size_t length);

// __envoy_dynamic_module_v1_http_continue_request is called by the module to continue processing
// the request. This function is used when the module returned non Continue status in the events.
void __envoy_dynamic_module_v1_http_continue_request(
    __envoy_dynamic_module_v1_type_EnvoyFilterPtr envoy_filter_ptr);

// __envoy_dynamic_module_v1_http_continue_response is called by the module to continue processing
// the response. This function is used when the module returned non Continue status in the events.
void __envoy_dynamic_module_v1_http_continue_response(
    __envoy_dynamic_module_v1_type_EnvoyFilterPtr envoy_filter_ptr);

#ifdef __cplusplus
}
#endif

#endif // ENVOY_DYNAMIC_MODULE_ABI_
