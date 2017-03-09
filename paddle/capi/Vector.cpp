/* Copyright (c) 2016 PaddlePaddle Authors. All Rights Reserve.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#include "PaddleCAPI.h"
#include "PaddleCAPIPrivate.h"

using paddle::capi::cast;

extern "C" {

int PDIVecCreateNone(PD_IVector* ivec) {
  if (ivec == nullptr) return kPD_NULLPTR;
  auto ptr = new paddle::capi::CIVector();
  *ivec = ptr;
  return kPD_NO_ERROR;
}

int PDIVectorCreate(PD_IVector* ivec, int* array, uint64_t size, bool copy) {
  //! TODO(lizhao): Complete this method.
  if (ivec == nullptr) return kPD_NULLPTR;
  auto ptr = new paddle::capi::CIVector();
  if (copy) {
    ptr->vec = paddle::IVector::create(size, false);
    ptr->vec->copyFrom(array, size);
  } else {
    ptr->vec = paddle::IVector::create(array, size, false);
  }
  *ivec = ptr;
  return kPD_NO_ERROR;
}

int PDIVecDestroy(PD_IVector ivec) {
  if (ivec == nullptr) return kPD_NULLPTR;
  delete cast<paddle::capi::CIVector>(ivec);
  return kPD_NO_ERROR;
}

int PDIVectorGet(PD_IVector ivec, int** buffer) {
  if (ivec == nullptr || buffer == nullptr) return kPD_NULLPTR;
  auto v = cast<paddle::capi::CIVector>(ivec);
  if (v->vec == nullptr) return kPD_NULLPTR;
  *buffer = v->vec->getData();
  return kPD_NO_ERROR;
}

int PDIVectorResize(PD_IVector ivec, uint64_t size) {
  //! TODO(lizhao): Complete this method.
  if (ivec == nullptr) return kPD_NULLPTR;
  auto v = cast<paddle::capi::CIVector>(ivec);
  if (v->vec == nullptr) return kPD_NULLPTR;
  v->vec->resize(size);
  return kPD_NO_ERROR;
}

int PDIVectorGetSize(PD_IVector ivec, uint64_t* size) {
  //! TODO(lizhao): Complete this method.
  if (ivec == nullptr) return kPD_NULLPTR;
  auto v = cast<paddle::capi::CIVector>(ivec);
  if (v->vec == nullptr) return kPD_NULLPTR;
  *size = v->vec->getSize();
  return kPD_NO_ERROR;
}
}
