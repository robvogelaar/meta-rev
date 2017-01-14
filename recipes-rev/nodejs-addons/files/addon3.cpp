#include <math.h>
#include <node/v8.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>


#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>


typedef int (*v8_timeout_callback_f)(void *user_data, void *isolate,
                                     int timeout_ms);

extern "C" bool V8_set_timeout(void *isolate, v8_timeout_callback_f callback,
                               void *user_data, int timeout_ms);

#define RED_REVERSE_MARKER "[31;1;7m"
#define GREEN_REVERSE_MARKER "[32;1;7m"
#define YELLOW_REVERSE_MARKER "[33;1;7m"
#define CLEAR_MARKER "[0m"

#define SD_DEBUG(s...)                     \
  ({                                       \
    fprintf(stderr, GREEN_REVERSE_MARKER); \
    fprintf(stderr, s);                    \
    fprintf(stderr, CLEAR_MARKER);         \
  })

using namespace v8;
using namespace std;

static Persistent<Value> onChange;
static Persistent<Value> onRunDone;
static Persistent<Object> onRunDoneThis;

static void Callback_onChange_get(Local<String>,
                                  const PropertyCallbackInfo<Value> &info) {
  SD_DEBUG(" %4d | %s ++\n", __LINE__, __FUNCTION__);
  info.GetReturnValue().Set(onChange.Get(info.GetIsolate()));
  SD_DEBUG(" %4d | %s --\n", __LINE__, __FUNCTION__);
}

static void Callback_onChange_set(Local<String>, Handle<Value> val,
                                  const PropertyCallbackInfo<Value> &info) {
  SD_DEBUG(" %4d | %s ++\n", __LINE__, __FUNCTION__);
  SD_DEBUG(" %4d | %s --\n", __LINE__, __FUNCTION__);
}

static void Callback_onRunDone_get(Local<String>,
                                   const PropertyCallbackInfo<Value> &info) {
  SD_DEBUG(" %4d | %s ++\n", __LINE__, __FUNCTION__);
  info.GetReturnValue().Set(onRunDone.Get(info.GetIsolate()));
  SD_DEBUG(" %4d | %s --\n", __LINE__, __FUNCTION__);
}

static void Callback_onRunDone_set(Local<String>, Handle<Value> val,
                                   const PropertyCallbackInfo<Value> &info) {
  SD_DEBUG(" %4d | %s ++\n", __LINE__, __FUNCTION__);
  if (!val->IsFunction()) {
    onRunDone.Reset();
    onRunDoneThis.Reset();
  } else {
    Isolate *isolate = info.GetIsolate();
    onRunDone.Reset(isolate, val);
    onRunDoneThis.Reset(isolate, info.This());
  }
  SD_DEBUG(" %4d | %s --\n", __LINE__, __FUNCTION__);
}

static void Callback_setPosition(const FunctionCallbackInfo<Value> &args) {
  int ret = -1;
  SD_DEBUG(" %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 3) {
    ret = 0;
  }
  SD_DEBUG(" %4d | %s | %d\n", __LINE__, __FUNCTION__, ret);
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_setSize(const FunctionCallbackInfo<Value> &args) {
  int ret = -1;
  SD_DEBUG(" %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 3) {
    ret = 0;
  }
  SD_DEBUG(" %4d | %s | %d\n", __LINE__, __FUNCTION__, ret);
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_setScale(const FunctionCallbackInfo<Value> &args) {
  int ret = -1;
  SD_DEBUG(" %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 3) {
    ret = 0;
  }
  SD_DEBUG(" %4d | %s | %d\n", __LINE__, __FUNCTION__, ret);
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_setZorder(const FunctionCallbackInfo<Value> &args) {
  int ret = -1;
  SD_DEBUG(" %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 2) {
    ret = 0;
  }
  SD_DEBUG(" %4d | %s | %d\n", __LINE__, __FUNCTION__, ret);
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_setOpacity(const FunctionCallbackInfo<Value> &args) {
  int ret = -1;
  SD_DEBUG(" %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 2) {
    SD_DEBUG("%d %d\n", args[0]->IntegerValue(), args[1]->NumberValue());
    ret = 0;
  }
  SD_DEBUG(" %4d | %s | %d\n", __LINE__, __FUNCTION__, ret);
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_setFocus(const FunctionCallbackInfo<Value> &args) {
  int ret = -1;
  SD_DEBUG(" %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 1) {
    SD_DEBUG("%d\n", args[0]->IntegerValue());
    ret = 0;
  }
  SD_DEBUG(" %4d | %s | %d\n", __LINE__, __FUNCTION__, ret);
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_setVisible(const FunctionCallbackInfo<Value> &args) {
  HandleScope scope(args.GetIsolate());
  int ret = -1;
  SD_DEBUG(" %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 2) {
    SD_DEBUG("%d %d\n", args[0]->IntegerValue(), args[1]->BooleanValue());
    ret = 0;
  }
  SD_DEBUG(" %4d | %s | %d\n", __LINE__, __FUNCTION__, ret);
  args.GetReturnValue().Set(Integer::New(scope.GetIsolate(), ret));
}

static void Callback_animatePosition(const FunctionCallbackInfo<Value> &args) {
  int ret = -1;
  SD_DEBUG(" %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 5) {
    ret = 0;
  }
  SD_DEBUG(" %4d | %s | %d\n", __LINE__, __FUNCTION__, ret);
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_animateScale(const FunctionCallbackInfo<Value> &args) {
  int ret = -1;
  SD_DEBUG(" %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 5) {
    ret = 0;
  }
  SD_DEBUG(" %4d | %s | %d\n", __LINE__, __FUNCTION__, ret);
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_animateOpacity(const FunctionCallbackInfo<Value> &args) {
  int ret = -1;
  SD_DEBUG(" %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 4) {
    ret = 0;
  }
  SD_DEBUG(" %4d | %s | %d\n", __LINE__, __FUNCTION__, ret);
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_getWindowsInfo(const FunctionCallbackInfo<Value> &args) {
  SD_DEBUG(" %4d | %s\n", __LINE__, __FUNCTION__);
  Isolate *isolate = args.GetIsolate();

  Local<Array> ret = Array::New(isolate, 10);

  int i = 0;
  for (int items = 0 ; items < 10; items++) {
    Local<Array> item = Array::New(isolate, 3);
    int j = 0;
    item->Set(j++, Uint32::New(isolate, 10 + items));
    item->Set(j++, Uint32::New(isolate, 1000 * items));
    item->Set(j++, Boolean::New(isolate, true));
    item->Set(j++, Boolean::New(isolate, true));
    SD_DEBUG( " %4d | %s #%u: { s:%u, p:%u, main:%u, visible:%u }\n", __LINE__, __FUNCTION__, i, 10 + items, 1000 * items, true, true);
    ret->Set(i++, item);
  }

  SD_DEBUG(" %4d | %s\n", __LINE__, __FUNCTION__);
  args.GetReturnValue().Set(ret);
}

static void Callback_kill(const FunctionCallbackInfo<Value> &args) {
  int ret = -1;
  SD_DEBUG(" %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 1) {
    ret = 0;
  }
  SD_DEBUG(" %4d | %s | %d\n", __LINE__, __FUNCTION__, ret);
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), 0));
}

static int _run_id = 0;

static int _succeed(void *data, void *_isolate, int) {
  Isolate *isolate = reinterpret_cast<Isolate *>(_isolate);
  HandleScope scope(isolate);
  int *run_id = reinterpret_cast<int *>(data);
  if (!onRunDone.IsEmpty()) {
    Handle<Value> args[] = {Integer::New(isolate, *run_id),
                            Integer::New(isolate, 0),
                            Integer::New(isolate, 666)};
    Local<Function> func = Local<Function>::Cast(onRunDone.Get(isolate));
    Local<Value> thiz = onRunDoneThis.Get(isolate);
    func->Call(thiz, sizeof(args) / sizeof(*args), args);
  }
  delete run_id;
  return -1;
}

static void Callback_run(const FunctionCallbackInfo<Value> &args) {
  HandleScope scope(args.GetIsolate());
  int ret = -1;
  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__);
  if ((args.Length() == 2 && args[1]->IsObject()) ||
      (args.Length() == 3 && args[1]->IsObject() && args[2]->IsObject())) {
    Local<Object> obj = args[1]->ToObject();
    Local<Array> prop = obj->GetPropertyNames();


    SD_DEBUG(" [1] %s\n", *String::Utf8Value(args[0]->ToString()));
    SD_DEBUG(" [2] size %d\n", prop->Length());

    auto params = std::make_shared<vector<string> >(prop->Length());
    for (unsigned int i = 0; i < prop->Length(); ++i) {
      SD_DEBUG("  -- [%d][%s]\n", i, *String::Utf8Value(obj->Get(i)->ToString()));
      params->at(i) = *String::Utf8Value(obj->Get(i)->ToString());
    }

    auto window_params = std::make_shared<vector<string> >(0);
    if (args.Length() == 3) {
      Local<Object> obj = args[2]->ToObject();
      Local<Array> prop = obj->GetPropertyNames();

      SD_DEBUG(" [3] size %d\n", prop->Length());
      window_params->resize(prop->Length());
      for (unsigned int i = 0; i < prop->Length(); ++i) {
        SD_DEBUG("  -- [%d][%s]\n", i, *String::Utf8Value(obj->Get(i)->ToString()));
        window_params->at(i) = *String::Utf8Value(obj->Get(i)->ToString());
      }
    }

    #if 0
    ret = ApplicationController::getInstance()->run(*String::Utf8Value(args[0]->ToString()),
                                                     params,
                                                     window_params,
                                                     new ACListener(scope.GetIsolate()),
                                                     args.GetIsolate());
    #endif
  }
  SD_DEBUG( " %4d | %s | %d\n", __LINE__, __FUNCTION__, ret );
  args.GetReturnValue().Set(Integer::New(scope.GetIsolate(), ret));
}

#include <node/node.h>

namespace {

void myInit(Handle<Object> exports) {
  SD_DEBUG("AWC %4d | %s ---- INIT START \n", __LINE__, __FUNCTION__);

  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  exports->Set(
      String::NewFromUtf8(isolate, "setPosition"),
      FunctionTemplate::New(isolate, Callback_setPosition)->GetFunction());

  exports->Set(String::NewFromUtf8(isolate, "setSize"),
               FunctionTemplate::New(isolate, Callback_setSize)->GetFunction());

  exports->Set(
      String::NewFromUtf8(isolate, "setScale"),
      FunctionTemplate::New(isolate, Callback_setScale)->GetFunction());

  exports->Set(
      String::NewFromUtf8(isolate, "setZorder"),
      FunctionTemplate::New(isolate, Callback_setZorder)->GetFunction());

  exports->Set(
      String::NewFromUtf8(isolate, "setOpacity"),
      FunctionTemplate::New(isolate, Callback_setOpacity)->GetFunction());

  exports->Set(
      String::NewFromUtf8(isolate, "setFocus"),
      FunctionTemplate::New(isolate, Callback_setFocus)->GetFunction());

  exports->Set(
      String::NewFromUtf8(isolate, "setVisible"),
      FunctionTemplate::New(isolate, Callback_setVisible)->GetFunction());

  exports->Set(
      String::NewFromUtf8(isolate, "animatePosition"),
      FunctionTemplate::New(isolate, Callback_animatePosition)->GetFunction());

  exports->Set(
      String::NewFromUtf8(isolate, "animateScale"),
      FunctionTemplate::New(isolate, Callback_animateScale)->GetFunction());

  exports->Set(
      String::NewFromUtf8(isolate, "animateOpacity"),
      FunctionTemplate::New(isolate, Callback_animateOpacity)->GetFunction());

  exports->Set(
      String::NewFromUtf8(isolate, "getWindowsInfo"),
      FunctionTemplate::New(isolate, Callback_getWindowsInfo)->GetFunction());

  exports->SetAccessor(String::NewFromUtf8(isolate, "onChange"),
                       Callback_onChange_get, Callback_onChange_set);

  exports->Set(String::NewFromUtf8(isolate, "kill"),
               FunctionTemplate::New(isolate, Callback_kill)->GetFunction());

  exports->Set(String::NewFromUtf8(isolate, "run"),
               FunctionTemplate::New(isolate, Callback_run)->GetFunction());

  exports->SetAccessor(String::NewFromUtf8(isolate, "onRunDone"),
                       Callback_onRunDone_get, Callback_onRunDone_set);

  SD_DEBUG("AWC %4d | %s -- INIT DONE\n", __LINE__, __FUNCTION__);
}
}

NODE_MODULE(addon3, myInit)
