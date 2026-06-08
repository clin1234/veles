/*
 * Copyright 2026 Charlie Lin, 2016 Codilime
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
 *
 */
#include "ui/subchunkfileblobitem.h"

#include "dbif/universe.h"
#include "ui/simplefileblobitem.h"

namespace veles {
namespace ui {

namespace {

FileBlobItem* makeChildItem(const data::ChunkDataItem& item, QObject* parent) {
  using T = data::ChunkDataItem;
  if (item.type == T::SUBCHUNK) {
    return new SubchunkFileBlobItem(item.ref[0], parent);
  }
  if (item.type == T::FIELD) {
    QString comment;
    if (item.num_elements > 1) {
      comment += QString::number(item.num_elements) + " x ";
    }
    comment += QString::number(item.repack.to_width) + "b (";
    comment +=
        (item.repack.endian == veles::data::Endian::LITTLE) ? "LE" : "BE";
    comment += ")";
    return new FileBlobItem(item.name, item.raw_value.toString(16), comment,
                            item.start, item.end, parent);
  }
  if (item.type == T::SUBBLOB) {
    auto* child = new SimpleFileBlobItem(item.name, "open in new tab", parent);
    child->setIcon(QIcon::fromTheme(":/images/newTab.png"));
    child->setNewRoot(item.ref[0]);
    return child;
  }
  auto* child = new SimpleFileBlobItem(item.name, "unsupported", parent);
  child->setIcon(QIcon::fromTheme(":/images/error.ico"));
  return child;
}

bool childMatchesItem(FileBlobItem* child, const data::ChunkDataItem& item) {
  using T = data::ChunkDataItem;
  if (item.type == T::SUBCHUNK) return child->objectHandle() == item.ref[0];
  if (item.type == T::SUBBLOB) return child->newRoot() == item.ref[0];
  uint64_t s, e;
  return child->range(&s, &e) && s == item.start;
}

}  // namespace

int SubchunkFileBlobItem::childrenCount() {
  subscribeInfo();
  return FileBlobItem::childrenCount();
}

void SubchunkFileBlobItem::gotChunkDataResponse(
    const veles::dbif::PInfoReply& reply) {
  auto items = reply.dynamicCast<dbif::ChunkDataRequest::ReplyType>()->items;

  // If every existing child still matches the corresponding entry in the new
  // response (same identity, same order), only append the new tail.  This
  // keeps already-subscribed SubchunkFileBlobItems alive and prevents the
  // "loading" flash that would occur if they were destroyed and recreated.
  bool appendOnly = (children_.size() <= static_cast<int>(items.size()));
  for (int i = 0; i < children_.size() && appendOnly; ++i) {
    if (!childMatchesItem(children_[i], items[i])) appendOnly = false;
  }

  if (appendOnly) {
    QList<FileBlobItem*> newItems;
    for (int i = children_.size(); i < static_cast<int>(items.size()); ++i) {
      newItems.append(makeChildItem(items[i], this));
    }
    if (!newItems.empty()) addChildren(newItems);
    return;
  }

  // Fallback: items were removed or reordered (uncommon for parsers).
  FileBlobItem::removeOldChildren();
  QList<FileBlobItem*> newChildren;
  newChildren.reserve(items.size());
  for (const auto& item : items) {
    newChildren.append(makeChildItem(item, this));
  }
  addChildren(newChildren);
}

void SubchunkFileBlobItem::gotChunkDescriptionResponse(
    const veles::dbif::PInfoReply& reply) {
  if (auto description = reply.dynamicCast<dbif::ChunkDescriptionReply>()) {
    setFields(description->name, description->comment, description->start,
              description->end);
    emit dataUpdated(this);
  }
}

void SubchunkFileBlobItem::gotError(const veles::dbif::PError& error) {
  if (error.dynamicCast<veles::dbif::ObjectGoneError>() != nullptr) {
    FileBlobItem::setFields("removed", "", 0, 0);
  } else {
    FileBlobItem::setFields("error", "", 0, 0);
  }
}

void SubchunkFileBlobItem::subscribeInfo() {
  if (infoSubscribed_) {
    return;
  }

  auto dataPromise = dataObj_->asyncSubInfo<dbif::ChunkDataRequest>(this);
  connect(dataPromise, &dbif::InfoPromise::gotInfo, this,
          &SubchunkFileBlobItem::gotChunkDataResponse);

  dbif::DescriptionRequest req;
  auto descriptionPromise =
      dataObj_->asyncSubInfo<dbif::DescriptionRequest>(this, req);
  connect(descriptionPromise, &dbif::InfoPromise::gotInfo, this,
          &SubchunkFileBlobItem::gotChunkDescriptionResponse);
  connect(descriptionPromise, &dbif::InfoPromise::gotError, this,
          &SubchunkFileBlobItem::gotError);
  infoSubscribed_ = true;
}

SubchunkFileBlobItem::SubchunkFileBlobItem(const dbif::ObjectHandle& obj,
                                           QObject* parent)
    : FileBlobItem("loading", "", "loading", 0, 0, parent),
      infoSubscribed_(false) {
  dataObj_ = obj;
}

QString SubchunkFileBlobItem::name() {
  subscribeInfo();
  return FileBlobItem::name();
}

void SubchunkFileBlobItem::setComment(const QString& comment) {
  if (dataObj_->type() == dbif::CHUNK) {
    dataObj_->asyncRunMethod<dbif::SetCommentRequest>(this, comment);
  }
}

}  // namespace ui
}  // namespace veles
