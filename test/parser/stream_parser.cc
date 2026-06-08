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

#include "gtest/gtest.h"
#include "mock_object_handle.h"
#include "parser/stream.h"

namespace veles {
namespace test {
namespace {

// 16-byte test blob: bytes 0x00…0x0F.
dbif::ObjectHandle makeBlob(MockDB& db) {
  std::vector<uint8_t> v(16);
  for (uint8_t i = 0; i < 16; ++i) v[i] = i;
  return makeBlobHandle(db, std::move(v));
}

// ============================================================================
// Non-deferred mode
// ============================================================================

TEST(StreamParser_NonDeferred, SingleChunkCreatedAndParsed) {
  MockDB db;
  auto blob = makeBlob(db);
  parser::StreamParser sp(blob, 0);

  sp.startChunk("mytype", "myname");
  sp.endChunk();

  ASSERT_EQ(1u, db.creates.size());
  EXPECT_EQ(QString("myname"), db.creates[0].name);
  EXPECT_EQ(QString("mytype"), db.creates[0].type);
  // startChunk passes pos_,pos_ so start==end at creation time
  EXPECT_EQ(0u, db.creates[0].start);
  EXPECT_EQ(0u, db.creates[0].end);

  ASSERT_EQ(1u, db.parses.size());
  EXPECT_EQ(db.creates[0].id, db.parses[0].handle_id);
  EXPECT_EQ(0u, db.parses[0].start);
  EXPECT_EQ(0u, db.parses[0].end);  // no bytes read
  EXPECT_TRUE(db.parses[0].items.empty());
}

TEST(StreamParser_NonDeferred, FieldItemRecordedInParse) {
  MockDB db;
  auto blob = makeBlob(db);
  parser::StreamParser sp(blob, 0);

  sp.startChunk("t", "n");
  sp.getByte("byte0");
  sp.getByte("byte1");
  sp.endChunk();

  ASSERT_EQ(1u, db.parses.size());
  EXPECT_EQ(0u, db.parses[0].start);
  EXPECT_EQ(2u, db.parses[0].end);

  const auto& items = db.parses[0].items;
  ASSERT_EQ(2u, items.size());
  EXPECT_EQ(data::ChunkDataItem::FIELD, items[0].type);
  EXPECT_EQ(QString("byte0"), items[0].name);
  EXPECT_EQ(0u, items[0].start);
  EXPECT_EQ(1u, items[0].end);

  EXPECT_EQ(data::ChunkDataItem::FIELD, items[1].type);
  EXPECT_EQ(QString("byte1"), items[1].name);
  EXPECT_EQ(1u, items[1].start);
  EXPECT_EQ(2u, items[1].end);
}

TEST(StreamParser_NonDeferred, NestedChunkParentBeforeChild) {
  MockDB db;
  auto blob = makeBlob(db);
  parser::StreamParser sp(blob, 0);

  sp.startChunk("outer_t", "outer");
  sp.startChunk("inner_t", "inner");
  sp.getByte("b");
  sp.endChunk();  // inner
  sp.endChunk();  // outer

  // Both chunks created in pre-order (outer first)
  ASSERT_EQ(2u, db.creates.size());
  EXPECT_EQ(QString("outer"), db.creates[0].name);
  EXPECT_EQ(QString("inner"), db.creates[1].name);
  EXPECT_EQ(db.creates[0].id, chunkId(db.creates[1].parent));

  // Inner is parsed before outer (inner endChunk fires first)
  ASSERT_EQ(2u, db.parses.size());
  EXPECT_EQ(db.creates[1].id, db.parses[0].handle_id);
  EXPECT_EQ(1u, db.parses[0].end);

  EXPECT_EQ(db.creates[0].id, db.parses[1].handle_id);
  EXPECT_EQ(0u, db.parses[1].start);
  EXPECT_EQ(1u, db.parses[1].end);
}

TEST(StreamParser_NonDeferred, NestedChunkAppearsAsSubchunkInParent) {
  MockDB db;
  auto blob = makeBlob(db);
  parser::StreamParser sp(blob, 0);

  sp.startChunk("outer_t", "outer");
  sp.startChunk("inner_t", "inner");
  sp.getByte("b");
  sp.endChunk();  // inner
  sp.endChunk();  // outer

  ASSERT_EQ(2u, db.parses.size());
  const auto& outer_items = db.parses[1].items;
  ASSERT_EQ(1u, outer_items.size());
  EXPECT_EQ(data::ChunkDataItem::SUBCHUNK, outer_items[0].type);
  EXPECT_EQ(QString("inner"), outer_items[0].name);
  EXPECT_EQ(0u, outer_items[0].start);
  EXPECT_EQ(1u, outer_items[0].end);
  // The ref must point to the actual inner chunk handle
  ASSERT_EQ(1u, outer_items[0].ref.size());
  EXPECT_EQ(db.creates[1].id, chunkId(outer_items[0].ref[0]));
}

TEST(StreamParser_NonDeferred, AddSubchunkItemAppearsInParse) {
  MockDB db;
  auto blob = makeBlob(db);
  // Create an external chunk to reference (e.g. from a sub-stream parser)
  dbif::ObjectHandle ext = logChunkCreate(db, "ext", "et", {}, 2, 5);
  db.creates.clear();  // don't count this pre-creation

  parser::StreamParser sp(blob, 0);
  sp.startChunk("top", "top");
  sp.addSubchunkItem(2, 5, "ext_ref", ext);
  sp.endChunk();

  ASSERT_EQ(1u, db.parses.size());
  const auto& items = db.parses[0].items;
  ASSERT_EQ(1u, items.size());
  EXPECT_EQ(data::ChunkDataItem::SUBCHUNK, items[0].type);
  EXPECT_EQ(QString("ext_ref"), items[0].name);
  EXPECT_EQ(2u, items[0].start);
  EXPECT_EQ(5u, items[0].end);
  ASSERT_EQ(1u, items[0].ref.size());
  EXPECT_EQ(ext, items[0].ref[0]);
}

TEST(StreamParser_NonDeferred, SeekSetsPosition) {
  MockDB db;
  auto blob = makeBlob(db);
  parser::StreamParser sp(blob, 0);

  sp.startChunk("t", "n");
  sp.seek(7);
  EXPECT_EQ(7u, sp.pos());
  sp.endChunk();

  ASSERT_EQ(1u, db.parses.size());
  EXPECT_EQ(7u, db.parses[0].end);
}

TEST(StreamParser_NonDeferred, PosEofBytesLeft) {
  MockDB db;
  auto blob = makeBlob(db);  // 16 bytes
  parser::StreamParser sp(blob, 0);

  EXPECT_EQ(0u, sp.pos());
  EXPECT_FALSE(sp.eof());
  EXPECT_EQ(16u, sp.bytesLeft());

  sp.seek(16);
  EXPECT_TRUE(sp.eof());
  EXPECT_EQ(0u, sp.bytesLeft());
}

// ============================================================================
// Deferred mode
// ============================================================================

TEST(StreamParser_Deferred, StartChunkReturnsNullHandle) {
  MockDB db;
  auto blob = makeBlob(db);
  parser::StreamParser sp(blob, 0, {}, /*deferred=*/true);

  auto h = sp.startChunk("t", "n");
  EXPECT_FALSE(h);  // deferred mode returns a null handle

  // No DB interaction until the outermost endChunk
  EXPECT_TRUE(db.creates.empty());
  EXPECT_TRUE(db.parses.empty());

  sp.endChunk();
  EXPECT_EQ(1u, db.creates.size());
}

TEST(StreamParser_Deferred, InnerEndChunkReturnsNull) {
  MockDB db;
  auto blob = makeBlob(db);
  parser::StreamParser sp(blob, 0, {}, /*deferred=*/true);

  sp.startChunk("outer", "outer");
  sp.startChunk("inner", "inner");

  // Inner endChunk is not the outermost: returns null, no DB writes
  dbif::ObjectHandle inner_result = sp.endChunk();
  EXPECT_FALSE(inner_result);
  EXPECT_TRUE(db.creates.empty());
  EXPECT_TRUE(db.parses.empty());

  // Outer endChunk flushes everything
  dbif::ObjectHandle outer_result = sp.endChunk();
  EXPECT_TRUE(outer_result);
  EXPECT_EQ(2u, db.creates.size());
  EXPECT_EQ(2u, db.parses.size());
}

TEST(StreamParser_Deferred, FlushHappensAtOutermostEndChunk) {
  MockDB db;
  auto blob = makeBlob(db);
  parser::StreamParser sp(blob, 0, {}, /*deferred=*/true);

  sp.startChunk("mytype", "myname");
  sp.getByte("b0");
  sp.getByte("b1");
  sp.endChunk();

  // All DB writes happened in a single batch
  ASSERT_EQ(1u, db.creates.size());
  EXPECT_EQ(QString("myname"), db.creates[0].name);
  EXPECT_EQ(0u, db.creates[0].start);
  EXPECT_EQ(2u, db.creates[0].end);  // deferred stores correct end

  ASSERT_EQ(1u, db.parses.size());
  EXPECT_EQ(2u, db.parses[0].items.size());
  EXPECT_EQ(data::ChunkDataItem::FIELD, db.parses[0].items[0].type);
}

TEST(StreamParser_Deferred, ParentCreatedBeforeChild) {
  // flushDeferred must create the parent chunk before recursing into children,
  // because children need the parent's handle as their parent argument.
  MockDB db;
  auto blob = makeBlob(db);
  parser::StreamParser sp(blob, 0, {}, /*deferred=*/true);

  sp.startChunk("outer_t", "outer");
  sp.startChunk("inner_t", "inner");
  sp.getByte("b");
  sp.endChunk();  // inner
  sp.endChunk();  // outer — flushes

  ASSERT_EQ(2u, db.creates.size());
  EXPECT_EQ(QString("outer"), db.creates[0].name);
  EXPECT_EQ(QString("inner"), db.creates[1].name);
  // Inner's parent should be the outer handle
  EXPECT_EQ(db.creates[0].id, chunkId(db.creates[1].parent));
}

TEST(StreamParser_Deferred, ParseOrderChildBeforeParent) {
  // flushDeferred recurses into children before calling SetChunkParseRequest
  // on the parent, so the child's parse is recorded first.
  MockDB db;
  auto blob = makeBlob(db);
  parser::StreamParser sp(blob, 0, {}, /*deferred=*/true);

  sp.startChunk("outer_t", "outer");
  sp.startChunk("inner_t", "inner");
  sp.getByte("b");
  sp.endChunk();  // inner
  sp.endChunk();  // outer

  ASSERT_EQ(2u, db.parses.size());
  EXPECT_EQ(db.creates[1].id, db.parses[0].handle_id);  // inner first
  EXPECT_EQ(db.creates[0].id, db.parses[1].handle_id);  // outer second
}

TEST(StreamParser_Deferred, OuterItemsContainSubchunkWithCorrectRef) {
  // The SUBCHUNK item in the outer chunk's item list must reference the handle
  // that was actually created for the inner chunk by flushDeferred.
  MockDB db;
  auto blob = makeBlob(db);
  parser::StreamParser sp(blob, 0, {}, /*deferred=*/true);

  sp.startChunk("outer_t", "outer");
  sp.startChunk("inner_t", "inner");
  sp.getByte("b");
  sp.endChunk();  // inner
  sp.endChunk();  // outer

  // Outer parse items: one SUBCHUNK for inner
  ASSERT_EQ(2u, db.parses.size());
  const auto& outer_items = db.parses[1].items;
  ASSERT_EQ(1u, outer_items.size());
  EXPECT_EQ(data::ChunkDataItem::SUBCHUNK, outer_items[0].type);
  EXPECT_EQ(QString("inner"), outer_items[0].name);
  EXPECT_EQ(0u, outer_items[0].start);
  EXPECT_EQ(1u, outer_items[0].end);

  ASSERT_EQ(1u, outer_items[0].ref.size());
  EXPECT_EQ(db.creates[1].id, chunkId(outer_items[0].ref[0]));
}

TEST(StreamParser_Deferred, MixedFieldsAndChildPreservesOrder) {
  // Items written before, between, and after nested chunks must appear in
  // original parse order in the parent's final item list.
  MockDB db;
  auto blob = makeBlob(db);
  parser::StreamParser sp(blob, 0, {}, /*deferred=*/true);

  sp.startChunk("top_t", "top");
  sp.getByte("field0");       // [0,1)
  sp.startChunk("child_t", "child");
  sp.getByte("cb");           // [1,2)
  sp.endChunk();              // child
  sp.getByte("field1");       // [2,3)
  sp.endChunk();              // top

  ASSERT_EQ(2u, db.parses.size());
  // top is the parent → parses[1] (child parsed first)
  const auto& top_items = db.parses[1].items;
  ASSERT_EQ(3u, top_items.size());

  EXPECT_EQ(data::ChunkDataItem::FIELD,    top_items[0].type);
  EXPECT_EQ(QString("field0"),             top_items[0].name);
  EXPECT_EQ(0u, top_items[0].start);
  EXPECT_EQ(1u, top_items[0].end);

  EXPECT_EQ(data::ChunkDataItem::SUBCHUNK, top_items[1].type);
  EXPECT_EQ(QString("child"),              top_items[1].name);
  EXPECT_EQ(1u, top_items[1].start);
  EXPECT_EQ(2u, top_items[1].end);

  EXPECT_EQ(data::ChunkDataItem::FIELD,    top_items[2].type);
  EXPECT_EQ(QString("field1"),             top_items[2].name);
  EXPECT_EQ(2u, top_items[2].start);
  EXPECT_EQ(3u, top_items[2].end);
}

TEST(StreamParser_Deferred, AddSubchunkItemAppearsInParse) {
  MockDB db;
  auto blob = makeBlob(db);
  dbif::ObjectHandle ext = logChunkCreate(db, "ext", "et", {}, 0, 4);
  db.creates.clear();

  parser::StreamParser sp(blob, 0, {}, /*deferred=*/true);
  sp.startChunk("top", "top");
  sp.addSubchunkItem(0, 4, "ext_ref", ext);
  sp.endChunk();

  ASSERT_EQ(1u, db.parses.size());
  const auto& items = db.parses[0].items;
  ASSERT_EQ(1u, items.size());
  EXPECT_EQ(data::ChunkDataItem::SUBCHUNK, items[0].type);
  EXPECT_EQ(QString("ext_ref"), items[0].name);
  EXPECT_EQ(0u, items[0].start);
  EXPECT_EQ(4u, items[0].end);
  ASSERT_EQ(1u, items[0].ref.size());
  EXPECT_EQ(ext, items[0].ref[0]);
}

// ============================================================================
// Mode parity: both modes must produce the same tree structure.
// ============================================================================

// Runs the same parse sequence in the requested mode and returns the log.
static MockDB runParityParse(bool deferred) {
  MockDB db;
  auto blob = makeBlobHandle(db, {0x01, 0x02, 0x03, 0x04, 0x05});
  parser::StreamParser sp(blob, 0, {}, deferred);

  sp.startChunk("root_t", "root");
  sp.getByte("byte0");            // [0,1)
  sp.startChunk("child_t", "child");
  sp.getByte("cb");               // [1,2)
  sp.endChunk();                  // child
  sp.getByte("byte1");            // [2,3)
  sp.endChunk();                  // root

  return db;
}

TEST(StreamParser_Parity, SameChunkNamesAndTypes) {
  MockDB nd = runParityParse(false);
  MockDB d  = runParityParse(true);

  ASSERT_EQ(nd.creates.size(), d.creates.size());
  for (size_t i = 0; i < nd.creates.size(); ++i) {
    EXPECT_EQ(nd.creates[i].name, d.creates[i].name)
        << "creates[" << i << "].name";
    EXPECT_EQ(nd.creates[i].type, d.creates[i].type)
        << "creates[" << i << "].type";
  }
}

TEST(StreamParser_Parity, SameParentChildRelationship) {
  MockDB nd = runParityParse(false);
  MockDB d  = runParityParse(true);

  ASSERT_EQ(2u, nd.creates.size());
  ASSERT_EQ(2u, d.creates.size());
  // Both: root has no parent; child's parent is root (id 0)
  EXPECT_EQ(-1, chunkId(nd.creates[0].parent));
  EXPECT_EQ(-1, chunkId(d.creates[0].parent));
  EXPECT_EQ(nd.creates[0].id, chunkId(nd.creates[1].parent));
  EXPECT_EQ(d.creates[0].id,  chunkId(d.creates[1].parent));
}

TEST(StreamParser_Parity, SameParseBoundsAndItemStructure) {
  MockDB nd = runParityParse(false);
  MockDB d  = runParityParse(true);

  ASSERT_EQ(nd.parses.size(), d.parses.size());
  for (size_t i = 0; i < nd.parses.size(); ++i) {
    EXPECT_EQ(nd.parses[i].start, d.parses[i].start)
        << "parses[" << i << "].start";
    EXPECT_EQ(nd.parses[i].end, d.parses[i].end)
        << "parses[" << i << "].end";

    ASSERT_EQ(nd.parses[i].items.size(), d.parses[i].items.size())
        << "parses[" << i << "].items.size()";
    for (size_t j = 0; j < nd.parses[i].items.size(); ++j) {
      const auto& ni = nd.parses[i].items[j];
      const auto& di = d.parses[i].items[j];
      EXPECT_EQ(ni.type,  di.type)  << "parses[" << i << "].items[" << j << "].type";
      EXPECT_EQ(ni.name,  di.name)  << "parses[" << i << "].items[" << j << "].name";
      EXPECT_EQ(ni.start, di.start) << "parses[" << i << "].items[" << j << "].start";
      EXPECT_EQ(ni.end,   di.end)   << "parses[" << i << "].items[" << j << "].end";
    }
  }
}

}  // namespace
}  // namespace test
}  // namespace veles
