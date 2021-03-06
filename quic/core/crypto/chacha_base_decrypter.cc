// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "quic/core/crypto/chacha_base_decrypter.h"

#include <cstdint>

#include "third_party/boringssl/src/include/openssl/chacha.h"
#include "quic/core/quic_data_reader.h"
#include "quic/platform/api/quic_bug_tracker.h"
#include "common/platform/api/quiche_arraysize.h"
#include "common/platform/api/quiche_endian.h"
#include "common/platform/api/quiche_string_piece.h"

namespace quic {

bool ChaChaBaseDecrypter::SetHeaderProtectionKey(
    quiche::QuicheStringPiece key) {
  if (key.size() != GetKeySize()) {
    QUIC_BUG << "Invalid key size for header protection";
    return false;
  }
  memcpy(pne_key_, key.data(), key.size());
  return true;
}

std::string ChaChaBaseDecrypter::GenerateHeaderProtectionMask(
    QuicDataReader* sample_reader) {
  quiche::QuicheStringPiece sample;
  if (!sample_reader->ReadStringPiece(&sample, 16)) {
    return std::string();
  }
  const uint8_t* nonce = reinterpret_cast<const uint8_t*>(sample.data()) + 4;
  uint32_t counter;
  QuicDataReader(sample.data(), 4, quiche::HOST_BYTE_ORDER)
      .ReadUInt32(&counter);
  const uint8_t zeroes[] = {0, 0, 0, 0, 0};
  std::string out(QUICHE_ARRAYSIZE(zeroes), 0);
  CRYPTO_chacha_20(reinterpret_cast<uint8_t*>(const_cast<char*>(out.data())),
                   zeroes, QUICHE_ARRAYSIZE(zeroes), pne_key_, nonce, counter);
  return out;
}

}  // namespace quic
