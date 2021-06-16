#include "GetCustomerCollectionsIdAsyncWorker.h"
#include <Windows.h>
#include <string>

GetCustomerCollectionsIdAsyncWorker::GetCustomerCollectionsIdAsyncWorker(const Napi::Function &callback, std::string token,
                                                                   std::string type, WindowsStoreImpl *pImpl)
    : Napi::AsyncWorker(callback), m_token(token), m_type(type), m_pImpl(pImpl), m_result("") {}

void GetCustomerCollectionsIdAsyncWorker::Execute() {
  m_result = m_pImpl->GetCustomerCollectionsId(m_token, m_type);
  m_pImpl->GetCustomerCollectionsIdAsync(m_token, m_type);
}

void GetCustomerCollectionsIdAsyncWorker::OnOK() {
  Napi::Env env = Env();

  Callback().MakeCallback(Receiver().Value(), {env.Null(), Napi::String::New(env, m_result)});
}

void GetCustomerCollectionsIdAsyncWorker::OnError(const Napi::Error &e) {
  Napi::Env env = Env();

  Callback().MakeCallback(Receiver().Value(), {e.Value(), env.Undefined()});
}
