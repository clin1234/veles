/*
 * Copyright 2026 Charlie Lin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <algorithm>
#include <cstdlib>
#include <vector>

#include <QObject>
#include <QSharedPointer>

#include "data/bindata.h"
#include "data/field.h"
#include "dbif/info.h"
#include "dbif/method.h"
#include "dbif/promise.h"
#include "dbif/types.h"
#include "dbif/universe.h"

namespace veles {
namespace test {

// ---------------------------------------------------------------------------
// These subclasses expose the protected signals of InfoPromise /
// MethodResultPromise so mock implementations can emit them without Q_OBJECT.
// Neither adds new signals, so no moc step is required.
// ---------------------------------------------------------------------------
class FireableInfoPromise : public dbif::InfoPromise {
 public:
  void fire(dbif::PInfoReply reply) { emit gotInfo(reply); }
};

class FireableMethodPromise : public dbif::MethodResultPromise {
 public:
  void fire(dbif::PMethodReply reply) { emit gotResult(reply); }
};

// ---------------------------------------------------------------------------
// MockDB: shared log that records every ChunkCreate and SetChunkParse call.
// ---------------------------------------------------------------------------
struct MockDB {
  struct CreateEntry {
    int id;
    QString name;
    QString type;
    dbif::ObjectHandle parent;  // null or MockChunkHandle for nested
    uint64_t start;
    uint64_t end;
  };
  struct ParseEntry {
    int handle_id;
    uint64_t start;
    uint64_t end;
    std::vector<data::ChunkDataItem> items;
  };

  std::vector<CreateEntry> creates;
  std::vector<ParseEntry> parses;
  int next_id = 0;
};

// ---------------------------------------------------------------------------
// MockChunkHandle: records SetChunkParseRequest calls.
// ObjectHandleBase is NOT a QObject, so no Q_OBJECT / moc needed.
// ---------------------------------------------------------------------------
class MockChunkHandle : public dbif::ObjectHandleBase {
 public:
  MockChunkHandle(MockDB& db, int id) : db_(db), id_(id) {}

  dbif::InfoPromise* getInfo(const dbif::PInfoRequest&) override {
    return new FireableInfoPromise();  // not expected in tests
  }

  dbif::InfoPromise* subInfo(const dbif::PInfoRequest&) override {
    return new FireableInfoPromise();
  }

  dbif::MethodResultPromise* runMethod(
      const dbif::PMethodRequest& req) override;

  dbif::ObjectType type() const override { return dbif::ObjectType::CHUNK; }

  MockDB& db_;
  int id_;
};

// ---------------------------------------------------------------------------
// chunkId — returns the integer ID of a MockChunkHandle, or -1 for null/other.
// Defined here, after MockChunkHandle is complete, so dynamic_cast is valid.
// ---------------------------------------------------------------------------
inline int chunkId(const dbif::ObjectHandle& h) {
  if (!h) return -1;
  const auto* mch = dynamic_cast<const MockChunkHandle*>(h.get());
  return mch ? mch->id_ : -1;
}

// ---------------------------------------------------------------------------
// logChunkCreate — allocate a MockChunkHandle, log the creation, return it.
// Also defined after MockChunkHandle is complete (required by create<>).
// ---------------------------------------------------------------------------
inline dbif::ObjectHandle logChunkCreate(MockDB& db, const QString& name,
                                         const QString& type,
                                         const dbif::ObjectHandle& parent,
                                         uint64_t start, uint64_t end) {
  int id = db.next_id++;
  auto handle = QSharedPointer<MockChunkHandle>::create(db, id);
  db.creates.push_back({id, name, type, parent, start, end});
  return handle;
}

// ---------------------------------------------------------------------------
// MockBlobHandle: serves DescriptionRequest / BlobDataRequest for reads and
// routes ChunkCreateRequest to logChunkCreate.
// ---------------------------------------------------------------------------
class MockBlobHandle : public dbif::ObjectHandleBase {
 public:
  MockBlobHandle(MockDB& db, std::vector<uint8_t> bytes)
      : db_(db), bytes_(std::move(bytes)) {}

  dbif::InfoPromise* getInfo(const dbif::PInfoRequest& req) override {
    auto* p = new FireableInfoPromise();
    dbif::PInfoReply reply;

    if (dynamic_cast<const dbif::DescriptionRequest*>(req.get())) {
      reply = QSharedPointer<dbif::BlobDescriptionReply>::create(
          QString("blob"), QString(""), uint64_t(0),
          static_cast<uint64_t>(bytes_.size()), int(8));

    } else if (auto* dr =
                   dynamic_cast<const dbif::BlobDataRequest*>(req.get())) {
      uint64_t start = dr->start;
      uint64_t end =
          std::min(dr->end, static_cast<uint64_t>(bytes_.size()));
      size_t len =
          (end > start) ? static_cast<size_t>(end - start) : size_t(0);
      const uint8_t* src = (len > 0) ? (bytes_.data() + start) : nullptr;
      reply = QSharedPointer<dbif::BlobDataReply>::create(
          data::BinData(8, len, src));

    } else {
      std::abort();  // unexpected request type in test
    }

    // Queue the signal so baseSyncGetInfo's processEvents loop picks it up.
    QMetaObject::invokeMethod(p, [p, reply]() { p->fire(reply); },
                              Qt::QueuedConnection);
    return p;
  }

  dbif::InfoPromise* subInfo(const dbif::PInfoRequest&) override {
    return new FireableInfoPromise();
  }

  dbif::MethodResultPromise* runMethod(
      const dbif::PMethodRequest& req) override {
    auto* p = new FireableMethodPromise();
    dbif::PMethodReply reply;

    if (auto* cr =
            dynamic_cast<const dbif::ChunkCreateRequest*>(req.get())) {
      dbif::ObjectHandle chunk =
          logChunkCreate(db_, cr->name, cr->chunk_type, cr->parent_chunk,
                         cr->start, cr->end);
      reply = QSharedPointer<dbif::CreatedReply>::create(chunk);

    } else {
      std::abort();
    }

    QMetaObject::invokeMethod(p, [p, reply]() { p->fire(reply); },
                              Qt::QueuedConnection);
    return p;
  }

  dbif::ObjectType type() const override { return dbif::ObjectType::FILE_BLOB; }

 private:
  MockDB& db_;
  std::vector<uint8_t> bytes_;
};

// ---------------------------------------------------------------------------
// MockChunkHandle::runMethod definition — placed after MockBlobHandle so it
// has visibility of all types (though only SetChunkParseRequest is used here).
// ---------------------------------------------------------------------------
inline dbif::MethodResultPromise* MockChunkHandle::runMethod(
    const dbif::PMethodRequest& req) {
  auto* p = new FireableMethodPromise();
  dbif::PMethodReply reply;

  if (auto* pr =
          dynamic_cast<const dbif::SetChunkParseRequest*>(req.get())) {
    db_.parses.push_back({id_, pr->start, pr->end, pr->items});
    reply = QSharedPointer<dbif::NullReply>::create();

  } else {
    std::abort();
  }

  QMetaObject::invokeMethod(p, [p, reply]() { p->fire(reply); },
                             Qt::QueuedConnection);
  return p;
}

// Convenience factory used in tests.
inline dbif::ObjectHandle makeBlobHandle(MockDB& db,
                                         std::vector<uint8_t> bytes) {
  return QSharedPointer<MockBlobHandle>::create(db, std::move(bytes));
}

}  // namespace test
}  // namespace veles
