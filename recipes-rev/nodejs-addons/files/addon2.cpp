#include <node/v8.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

typedef int (*v8_timeout_callback_f)( void *user_data, void *isolate, int timeout_ms );

extern "C" bool V8_set_timeout( void *isolate, v8_timeout_callback_f callback, void *user_data, int timeout_ms );


#define CLEAR_MARKER "[0m"
#define ERROR_MARKER "[31;1;7m"

#define SD_DEBUG(s...)                          ({ fprintf(stderr,ERROR_MARKER); fprintf(stderr,s); fprintf(stderr,CLEAR_MARKER); })

using namespace v8;

static Persistent<Value> onChange;
static Persistent<Value> onRunDone;
static Persistent<Object> onRunDoneThis;

#define PROPERTY(name_) \
   #name_, Callback_## name_ ##_get, Callback_## name_ ##_set, NULL

#define METHOD(name_) \
   #name_, NULL, NULL, Callback_## name_

static void Callback_onChange_get(Local<String>, const PropertyCallbackInfo<Value> &info) {
  SD_DEBUG( " %4d | %s ++\n", __LINE__, __FUNCTION__);
  info.GetReturnValue().Set(onChange.Get(info.GetIsolate()));
  SD_DEBUG( " %4d | %s --\n", __LINE__, __FUNCTION__);
}

static void Callback_onChange_set(Local<String>, Handle<Value> val, const PropertyCallbackInfo<Value> &info) {
  SD_DEBUG( " %4d | %s ++\n", __LINE__, __FUNCTION__);
  SD_DEBUG( " %4d | %s --\n", __LINE__, __FUNCTION__);
}

static void Callback_onRunDone_get(Local<String>, const PropertyCallbackInfo<Value> &info) {
  SD_DEBUG( " %4d | %s ++\n", __LINE__, __FUNCTION__);
  info.GetReturnValue().Set(onRunDone.Get(info.GetIsolate()));
  SD_DEBUG( " %4d | %s --\n", __LINE__, __FUNCTION__);
}

static void Callback_onRunDone_set(Local<String>, Handle<Value> val, const PropertyCallbackInfo<Value> &info) {
  SD_DEBUG( " %4d | %s ++\n", __LINE__, __FUNCTION__);
  if (!val->IsFunction()) {
    onRunDone.Reset();
    onRunDoneThis.Reset();
  } else {
    Isolate* isolate = info.GetIsolate();
    onRunDone.Reset(isolate, val);
    onRunDoneThis.Reset(isolate, info.This());
  }
  SD_DEBUG( " %4d | %s --\n", __LINE__, __FUNCTION__);
}

static void Callback_setPosition(const FunctionCallbackInfo<Value>& args) {
  int ret = -1;
  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 3) {
    ret = 0;
  }
  SD_DEBUG( " %4d | %s | %d\n", __LINE__, __FUNCTION__, ret );
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_setSize(const FunctionCallbackInfo<Value>& args) {
  int ret = -1;
  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 3) {
    ret = 0;
  }
  SD_DEBUG( " %4d | %s | %d\n", __LINE__, __FUNCTION__, ret );
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_setScale(const FunctionCallbackInfo<Value>& args) {
  int ret = -1;
  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 3) {
    ret = 0;
  }
  SD_DEBUG( " %4d | %s | %d\n", __LINE__, __FUNCTION__, ret );
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_setZorder(const FunctionCallbackInfo<Value>& args) {
  int ret = -1;
  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 2) {
    ret = 0;
  }
  SD_DEBUG( " %4d | %s | %d\n", __LINE__, __FUNCTION__, ret );
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_setOpacity(const FunctionCallbackInfo<Value>& args) {
  int ret = -1;
  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 2) {
    ret = 0;
  }
  SD_DEBUG( " %4d | %s | %d\n", __LINE__, __FUNCTION__, ret );
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_setFocus(const FunctionCallbackInfo<Value>& args) {
  int ret = -1;
  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 1) {
    ret = 0;
  }
  SD_DEBUG( " %4d | %s | %d\n", __LINE__, __FUNCTION__, ret );
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_setVisible(const FunctionCallbackInfo<Value>& args) {
  HandleScope scope(args.GetIsolate());
  int ret = -1;
  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 2) {
    ret = 0;
  }
  SD_DEBUG( " %4d | %s | %d\n", __LINE__, __FUNCTION__, ret );
  args.GetReturnValue().Set(Integer::New(scope.GetIsolate(), ret));
}

static void Callback_animatePosition(const FunctionCallbackInfo<Value>& args) {
  int ret = -1;
  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 5) {
    ret = 0;
  }
  SD_DEBUG( " %4d | %s | %d\n", __LINE__, __FUNCTION__, ret );
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_animateScale(const FunctionCallbackInfo<Value>& args) {
  int ret = -1;
  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 5) {
    ret = 0;
  }
  SD_DEBUG( " %4d | %s | %d\n", __LINE__, __FUNCTION__, ret );
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_animateOpacity(const FunctionCallbackInfo<Value>& args) {
  int ret = -1;
  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 4) {
    ret = 0;
  }
  SD_DEBUG( " %4d | %s | %d\n", __LINE__, __FUNCTION__, ret );
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

static void Callback_getWindowsInfo(const FunctionCallbackInfo<Value>& args) {
  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__);
  Isolate* isolate = args.GetIsolate();

  Local<Array> ret = Array::New(isolate, 0);

  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__ );
  args.GetReturnValue().Set(ret);
}

static void Callback_kill(const FunctionCallbackInfo<Value>& args) {
  int ret = -1;
  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 1) {
    ret = 0;
  }
  SD_DEBUG( " %4d | %s | %d\n", __LINE__, __FUNCTION__, ret );
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), 0));
}

static int _run_id = 0;

static int _succeed( void *data, void *_isolate, int )
{
  Isolate *isolate = reinterpret_cast<Isolate*>( _isolate );
  HandleScope scope(isolate);
  int *run_id = reinterpret_cast<int*>(data);
  if( !onRunDone.IsEmpty() )
  {
    Handle<Value> args[]    = { Integer::New(isolate, *run_id), Integer::New(isolate, 0), Integer::New(isolate, 666) };
    Local<Function> func    = Local<Function>::Cast(onRunDone.Get(isolate));
    Local<Value>    thiz    = onRunDoneThis.Get(isolate);
    func->Call( thiz, sizeof( args ) / sizeof( *args ), args );
  }
  delete run_id;
  return -1;
}

static void Callback_run(const FunctionCallbackInfo<Value>& args) {
  int ret = -1;
  SD_DEBUG( " %4d | %s\n", __LINE__, __FUNCTION__);
  if (args.Length() == 2 && args[1]->IsObject()) {
    int *tmp = new int;
    *tmp = ret = ++_run_id;
    V8_set_timeout(args.GetIsolate(), _succeed, tmp, 0);
  }
  SD_DEBUG( " %4d | %s | %d\n", __LINE__, __FUNCTION__, ret );
  args.GetReturnValue().Set(Integer::New(args.GetIsolate(), ret));
}

inline void RegisterProperties(Isolate *isolate, Handle<Object> prototype, ...) {
  va_list arg;

  va_start(arg, prototype);
  for (const char *name = va_arg(arg, const char *); name; name = va_arg(arg, const char *)) {
    AccessorGetterCallback get_callback = va_arg(arg, AccessorGetterCallback);
    AccessorSetterCallback set_callback = va_arg(arg, AccessorSetterCallback);
    FunctionCallback inv_callback = va_arg(arg, FunctionCallback);

    if (inv_callback) {
      prototype->Set(String::NewFromUtf8(isolate,name), FunctionTemplate::New(isolate,inv_callback)->GetFunction());
    } else {
      prototype->SetAccessor(String::NewFromUtf8(isolate,name), get_callback, set_callback);
    }
  }
  va_end(arg);
}

extern "C" void RegisterModule(Isolate *isolate, Handle<Object> target) {
  SD_DEBUG( "AWC %4d | %s ---- INIT START \n", __LINE__, __FUNCTION__ );
  HandleScope scope( isolate );
  RegisterProperties( isolate,
                      target,
                      METHOD(setPosition),
                      METHOD(setSize),
                      METHOD(setScale),
                      METHOD(setZorder),
                      METHOD(setOpacity),
                      METHOD(setFocus),
                      METHOD(setVisible),
                      METHOD(animatePosition),
                      METHOD(animateScale),
                      METHOD(animateOpacity),
                      METHOD(getWindowsInfo),
                      PROPERTY(onChange),

                      METHOD(kill),
                      METHOD(run),
                      PROPERTY(onRunDone),

                      NULL
                      );
  SD_DEBUG( "AWC %4d | %s -- INIT DONE\n", __LINE__, __FUNCTION__ );
}

#include <node/node.h>

namespace {

void init(Handle<Object> exports) {
  SD_DEBUG( "AWC %4d | %s ---- INIT START \n", __LINE__, __FUNCTION__ );
  RegisterModule(Isolate::GetCurrent(), exports);
  SD_DEBUG( "AWC %4d | %s -- INIT DONE\n", __LINE__, __FUNCTION__ );
}

}

NODE_MODULE(awc, init)
