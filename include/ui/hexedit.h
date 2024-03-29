/*
 * Copyright 2016 CodiLime
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
#pragma once

#include <functional>

#include <QAbstractScrollArea>
#include <QItemSelectionModel>
#include <QMenu>
#include <QMouseEvent>
#include <QStaticText>
#include <QStringList>

#include "ui/dialogs/createchunkdialog.h"
#include "ui/dialogs/gotoaddressdialog.h"
#include "ui/fileblobmodel.h"
#include "util/edit.h"
#include "util/encoders/hex_encoder.h"
#include "util/encoders/text_encoder.h"
#include "util/settings/shortcuts.h"

namespace veles {
namespace ui {

class HexEdit : public QAbstractScrollArea {
  Q_OBJECT
 public:
  explicit HexEdit(FileBlobModel* dataModel,
                   QItemSelectionModel* selectionModel = nullptr,
                   QWidget* parent = nullptr);
  /** Mark bytes as selected and optionally scroll screen to make these bytes
   * visible */
  void setSelection(qint64 start, qint64 size, bool set_visible = false,
                    qint64 pos_in_byte = 0);
  int getBytesPerRow() const { return bytesPerRow_; }
  /** Sets how many bytes should be displayed in the single hex row or optionaly
   *  turn on automatic mode which will adjust bytes per row to window size */
  void setBytesPerRow(int bytes_count, bool automatic);
  void setAutoBytesPerRow(bool automatic);
  /** Scroll screen to make byte visible */
  void scrollToByte(qint64 bytePos, bool minimal_change = false);
  void scrollRows(qint64 num_rows);
  FileBlobModel* dataModel() { return dataModel_; }
  void setParserIds(const QStringList& ids);
  void processEditEvent(QKeyEvent* event);
  uint64_t byteValue(qint64 pos) const;
  void setBytesValues(qint64 pos, const data::BinData& new_data);
  bool isInInsertMode() const { return in_insert_mode_; }
  void setInInsertMode(bool in_insert_mode) {
    in_insert_mode_ = in_insert_mode;
  }
  void saveToFile(const QString& file_name);

 public slots:
  void newBinData();
  void dataChanged() const;
  void modelSelectionChanged();
  void applyChanges();
  void undo();
  void discardChanges();

 protected:
  void paintEvent(QPaintEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseDoubleClickEvent(QMouseEvent* event) override;
  void contextMenuEvent(QContextMenuEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  bool focusNextPrevChild(bool next) override;

 signals:
  void selectionChanged(qint64 start_addr, qint64 selection_size);
  void editStateChanged(bool has_changes, bool has_undo);

 private:
  FileBlobModel* dataModel_;
  uint32_t bindata_width_;
  QItemSelectionModel* chunkSelectionModel_;

  /** Total number of bytes in the blob */
  qint64 dataBytesCount_;
  /** Number of bytes displayed in singled hex edit row */
  qint64 bytesPerRow_;
  /** Indicates if bytes per row should be automatically adjusted to window
   * width */
  bool autoBytesPerRow_;
  /** Byte offset of whole blob */
  qint64 startOffset_;
  /** Total number of rows in hex edit (counting last address only row) */
  qint64 rowsCount_;
  /** Total number of rows in hex edit (not counting address only row) */
  qint64 data_rows_count_;
  /** Number of rows displayed on the screen (calculated from window and font
   * height) */
  qint64 rowsOnScreen_;
  /** Number of rows that are not being cropped by viewport height */
  qint64 totally_visible_rows_;
  /** Number of hex chars used to display one byte */
  qint64 byteCharsCount_;
  /** maximum value of byte */
  quint64 byte_max_value_;
  /** Number of pixels between two bytes in hex view (calculated from char
   * width) */
  int spaceAfterByte_;
  /** Number of pixels between two bytes in ASCII view (calculated from char
   * width) */
  int spaceAfterAsciiByte_;
  /** Width of single character in pixels */
  int charWidth_;
  /** Height of single character in pixels */
  int charHeight_;
  /** Number of pixels between two bytes (vertically) in hex view (calculated
   * from char height)  */
  int verticalByteBorderMargin_;
  /** Number of bytes (8 bit) used to represent offset addr */
  qint64 addressBytes_;
  /** Width in pixels of address area */
  qint64 addressWidth_;
  /** Width in pixels of hex area */
  qint64 hexAreaWidth_;
  /** Width in pixels of ascii area */
  qint64 asciiWidth_;
  /** Height in pixels of area separator */
  qint64 lineWidth_;
  /** Number of first row displayed on the screen */
  qint64 startRow_;
  /** Number of first pixel from left which should be displayed on the screen */
  qint64 startPosX_;
  /** Number of byte where selection starts (counting from beginning of blob) */
  qint64 current_position_;
  /** Number of bytes in selection */
  qint64 selection_size_;

  // Cache for faster rendering.
  QStaticText hex_text_cache_[256];
  QStaticText ascii_text_cache_[256];
  QColor selectionColor_;

  enum class WindowArea {
    ADDRESS,
    HEX,
    ASCII,
    OUTSIDE,
  };

  WindowArea current_area_;
  qint64 cursor_pos_in_byte_;
  bool cursor_visible_;
  bool in_insert_mode_;

  CreateChunkDialog* createChunkDialog_;
  GoToAddressDialog* goToAddressDialog_;

  QAction* createChunkAction_;
  QAction* createChildChunkAction_;
  QAction* goToAddressAction_;
  QAction* removeChunkAction_;
  QAction* selectChunkAction_;
  QAction* saveChunkAction_;
  QAction* delete_selection_action_;
  QAction* saveSelectionAction_;
  QStringList parsers_ids_;
  QMenu menu_;
  QMenu parsers_menu_;
  QTimer cursor_timer_;
  QScopedPointer<util::encoders::HexEncoder> hexEncoder_;
  QScopedPointer<util::encoders::TextEncoder> textEncoder_;
  util::EditEngine edit_engine_;

  void recalculateValues();
  void resetFontCache();
  void initParseMenu();
  void adjustBytesPerRowToWindowSize();
  QRect bytePosToRect(qint64 pos, bool ascii = false,
                      qint64 char_pos = 0) const;
  qint64 pointToRowNum(QPoint pos) const;
  qint64 pointToColumnNum(QPoint pos) const;
  qint64 pointToBytePos(QPoint pos);
  void flipCursorVisibility();
  WindowArea pointToWindowArea(QPoint pos);
  QString addressAsText(qint64 pos);
  QString hexRepresentationFromByte(uint64_t byte_val) const;
  static QString asciiRepresentationFromByte(uint64_t byte_val);

  static QColor byteTextColorFromByteValue(uint64_t byte_val);
  QColor byteBackroundColorFromPos(qint64 pos, bool modified);

  qint64 selectionStart() const;
  qint64 selectionEnd() const;
  qint64 selectionSize() const;

  QModelIndex selectedChunk();

  void setByteValue(qint64 pos, uint64_t byte_value);
  void insertBytes(qint64 pos, const data::BinData& new_data);
  void insertBytes(qint64 pos, uint64_t size, uint64_t byte_value);
  void insertByte(qint64 pos, uint64_t byte_value);
  void removeBytes(qint64 pos, uint64_t size);

  void createAction(util::settings::shortcuts::ShortcutType type,
                    const std::function<void()>& f);

  void getRangeFromIndex(const QModelIndex& index, qint64* start, qint64* size);
  void drawBorder(qint64 start, qint64 size, bool asciiArea = false,
                  bool dotted = false);

  void setSelectedChunk(QModelIndex newSelectedChunk);
  bool cursorOnLastRow() const;
  bool isRangeVisible(qint64 start, qint64 size) const;
  bool isByteVisible(qint64 bytePos);
  void setSelectionEnd(qint64 bytePos);
  void saveSelectionToFile(const QString& path);
  void saveChunkToFile(const QString& path);
  void saveDataToFile(qint64 byte_offset, qint64 size, const QString& path);
  void scrollToCurrentChunk();
  void parse(QAction* action);
  void resetCursor();

 private slots:
  void reloadSettings();
  void copyToClipboard(util::encoders::IEncoder* enc = nullptr);
  void pasteFromClipboard(util::encoders::IDecoder* enc = nullptr);
};

}  // namespace ui
}  // namespace veles
