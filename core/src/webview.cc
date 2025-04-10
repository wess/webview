#include "webview/webview.h"
#include "webview/errors.h"
#include "webview/api.h"
#include <queue>
#include <mutex>
#include <string>

namespace {
std::queue<std::string> message_queue;
std::mutex queue_mutex;
}

WEBVIEW_API webview_error_t webview_send_message(webview_t w, const char *message) {
std::lock_guard<std::mutex> lock(queue_mutex);
message_queue.push(message);
return WEBVIEW_SUCCESS;
}

WEBVIEW_API webview_error_t webview_receive_message(webview_t w, char *buffer, size_t length) {
std::lock_guard<std::mutex> lock(queue_mutex);
if (message_queue.empty()) {
return WEBVIEW_ERROR_EMPTY;
}
std::string message = message_queue.front();
message_queue.pop();
if (message.length() >= length) {
return WEBVIEW_ERROR_OVERFLOW;
}
std::strncpy(buffer, message.c_str(), length);
return WEBVIEW_SUCCESS;
}
