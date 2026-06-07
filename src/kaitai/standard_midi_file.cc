// This is a generated file! Please edit source .ksy file and use
// kaitai-struct-compiler to rebuild

#include "kaitai/standard_midi_file.h"
#include "kaitai/vlq_base128_be.h"

standard_midi_file_t::standard_midi_file_t(kaitai::kstream* p_io,
    kaitai::kstruct* p_parent, standard_midi_file_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = this;
  m__io->popName();
  veles_obj = m__io->startChunk("standard_midi_file");
  m__io->pushName("hdr");
  m_hdr = new header_t(m__io, this, m__root);
  m__io->popName();
  int l_tracks = hdr()->qty_tracks();
  m_tracks = new std::vector<track_t*>();
  m_tracks->reserve(l_tracks);
  for (int i = 0; i < l_tracks; i++) {
    m__io->pushName("tracks");
    m_tracks->push_back(new track_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->endChunk();
}

standard_midi_file_t::~standard_midi_file_t() {
  delete m_hdr;
  for (auto it = m_tracks->begin(); it != m_tracks->end(); ++it)
    delete *it;
  delete m_tracks;
}

standard_midi_file_t::track_events_t::track_events_t(kaitai::kstream* p_io,
    standard_midi_file_t::track_t* p_parent, standard_midi_file_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("track_events");
  m_event = new std::vector<track_event_t*>();
  while (!m__io->is_eof()) {
    m__io->pushName("event");
    m_event->push_back(new track_event_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->endChunk();
}

standard_midi_file_t::track_events_t::~track_events_t() {
  for (auto it = m_event->begin(); it != m_event->end(); ++it)
    delete *it;
  delete m_event;
}

standard_midi_file_t::track_event_t::track_event_t(kaitai::kstream* p_io,
    standard_midi_file_t::track_events_t* p_parent, standard_midi_file_t* p_root)
    : kaitai::kstruct(p_io),
      f_event_type(false), f_channel(false),
      m_meta_event_body(nullptr), m_sysex_body(nullptr), m_event_body(nullptr) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("track_event");
  m__io->pushName("v_time");
  m_v_time = new vlq_base128_be_t(m__io);
  m__io->popName();
  m__io->pushName("event_header");
  m_event_header = m__io->read_u1();
  m__io->popName();
  n_meta_event_body = true;
  if (event_header() == 255) {
    n_meta_event_body = false;
    m__io->pushName("meta_event_body");
    m_meta_event_body = new meta_event_body_t(m__io, this, m__root);
    m__io->popName();
  }
  n_sysex_body = true;
  if (event_header() == 240) {
    n_sysex_body = false;
    m__io->pushName("sysex_body");
    m_sysex_body = new sysex_event_body_t(m__io, this, m__root);
    m__io->popName();
  }
  switch (event_type()) {
    case 224:
      m__io->pushName("event_body");
      m_event_body = new pitch_bend_event_t(m__io, this, m__root);
      m__io->popName();
      break;
    case 144:
      m__io->pushName("event_body");
      m_event_body = new note_on_event_t(m__io, this, m__root);
      m__io->popName();
      break;
    case 208:
      m__io->pushName("event_body");
      m_event_body = new channel_pressure_event_t(m__io, this, m__root);
      m__io->popName();
      break;
    case 192:
      m__io->pushName("event_body");
      m_event_body = new program_change_event_t(m__io, this, m__root);
      m__io->popName();
      break;
    case 160:
      m__io->pushName("event_body");
      m_event_body = new polyphonic_pressure_event_t(m__io, this, m__root);
      m__io->popName();
      break;
    case 176:
      m__io->pushName("event_body");
      m_event_body = new controller_event_t(m__io, this, m__root);
      m__io->popName();
      break;
    case 128:
      m__io->pushName("event_body");
      m_event_body = new note_off_event_t(m__io, this, m__root);
      m__io->popName();
      break;
    default:
      break;
  }
  m__io->endChunk();
}

standard_midi_file_t::track_event_t::~track_event_t() {
  delete m_v_time;
  if (!n_meta_event_body) delete m_meta_event_body;
  if (!n_sysex_body) delete m_sysex_body;
  delete m_event_body;
}

int32_t standard_midi_file_t::track_event_t::event_type() {
  if (f_event_type) return m_event_type;
  m_event_type = event_header() & 240;
  f_event_type = true;
  return m_event_type;
}

int32_t standard_midi_file_t::track_event_t::channel() {
  if (f_channel) return m_channel;
  n_channel = true;
  if (event_type() != 240) {
    n_channel = false;
    m_channel = event_header() & 15;
  }
  f_channel = true;
  return m_channel;
}

standard_midi_file_t::pitch_bend_event_t::pitch_bend_event_t(kaitai::kstream* p_io,
    standard_midi_file_t::track_event_t* p_parent, standard_midi_file_t* p_root)
    : kaitai::kstruct(p_io), f_bend_value(false), f_adj_bend_value(false) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("pitch_bend");
  m__io->pushName("b1");
  m_b1 = m__io->read_u1();
  m__io->popName();
  m__io->pushName("b2");
  m_b2 = m__io->read_u1();
  m__io->popName();
  m__io->endChunk();
}

standard_midi_file_t::pitch_bend_event_t::~pitch_bend_event_t() {}

int32_t standard_midi_file_t::pitch_bend_event_t::bend_value() {
  if (f_bend_value) return m_bend_value;
  m_bend_value = (((b2() << 7) + b1()) - 16384);
  f_bend_value = true;
  return m_bend_value;
}

int32_t standard_midi_file_t::pitch_bend_event_t::adj_bend_value() {
  if (f_adj_bend_value) return m_adj_bend_value;
  m_adj_bend_value = bend_value() - 16384;
  f_adj_bend_value = true;
  return m_adj_bend_value;
}

standard_midi_file_t::program_change_event_t::program_change_event_t(
    kaitai::kstream* p_io, standard_midi_file_t::track_event_t* p_parent,
    standard_midi_file_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("program_change");
  m__io->pushName("program");
  m_program = m__io->read_u1();
  m__io->popName();
  m__io->endChunk();
}

standard_midi_file_t::program_change_event_t::~program_change_event_t() {}

standard_midi_file_t::note_on_event_t::note_on_event_t(kaitai::kstream* p_io,
    standard_midi_file_t::track_event_t* p_parent, standard_midi_file_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("note_on");
  m__io->pushName("note");
  m_note = m__io->read_u1();
  m__io->popName();
  m__io->pushName("velocity");
  m_velocity = m__io->read_u1();
  m__io->popName();
  m__io->endChunk();
}

standard_midi_file_t::note_on_event_t::~note_on_event_t() {}

standard_midi_file_t::polyphonic_pressure_event_t::polyphonic_pressure_event_t(
    kaitai::kstream* p_io, standard_midi_file_t::track_event_t* p_parent,
    standard_midi_file_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("polyphonic_pressure");
  m__io->pushName("note");
  m_note = m__io->read_u1();
  m__io->popName();
  m__io->pushName("pressure");
  m_pressure = m__io->read_u1();
  m__io->popName();
  m__io->endChunk();
}

standard_midi_file_t::polyphonic_pressure_event_t::~polyphonic_pressure_event_t() {}

standard_midi_file_t::track_t::track_t(kaitai::kstream* p_io,
    standard_midi_file_t* p_parent, standard_midi_file_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("track");
  m__io->pushName("magic");
  m_magic = m__io->ensure_fixed_contents(std::string("\x4D\x54\x72\x6B", 4));
  m__io->popName();
  m__io->pushName("track_length");
  m_track_length = m__io->read_u4be();
  m__io->popName();
  // Read the raw track data from the main stream to advance its position,
  // then create a blob-backed sub-stream over that region so that event
  // chunks are recorded as children of this track chunk in the Veles tree.
  uint64_t events_start = m__io->pos();
  m__raw_events = m__io->read_bytes(track_length());
  m__io__raw_events = new kaitai::kstream(
      m__io->blob(), events_start, veles_obj, track_length());
  m_events = new track_events_t(m__io__raw_events, this, m__root);
  m__io->addSubchunkItem(events_start, events_start + track_length(),
                         "events", m_events->veles_obj);
  m__io->endChunk();
}

standard_midi_file_t::track_t::~track_t() {
  delete m__io__raw_events;
  delete m_events;
}

standard_midi_file_t::meta_event_body_t::meta_event_body_t(kaitai::kstream* p_io,
    standard_midi_file_t::track_event_t* p_parent, standard_midi_file_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("meta_event");
  m__io->pushName("meta_type");
  m_meta_type = static_cast<meta_type_enum_t>(m__io->read_u1());
  m__io->popName();
  m__io->pushName("len");
  m_len = new vlq_base128_be_t(m__io);
  m__io->popName();
  m__io->pushName("body");
  m_body = m__io->read_bytes(len()->value());
  m__io->popName();
  m__io->endChunk();
}

standard_midi_file_t::meta_event_body_t::~meta_event_body_t() {
  delete m_len;
}

standard_midi_file_t::controller_event_t::controller_event_t(kaitai::kstream* p_io,
    standard_midi_file_t::track_event_t* p_parent, standard_midi_file_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("controller");
  m__io->pushName("controller");
  m_controller = m__io->read_u1();
  m__io->popName();
  m__io->pushName("value");
  m_value = m__io->read_u1();
  m__io->popName();
  m__io->endChunk();
}

standard_midi_file_t::controller_event_t::~controller_event_t() {}

standard_midi_file_t::header_t::header_t(kaitai::kstream* p_io,
    standard_midi_file_t* p_parent, standard_midi_file_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("header");
  m__io->pushName("magic");
  m_magic = m__io->ensure_fixed_contents(std::string("\x4D\x54\x68\x64", 4));
  m__io->popName();
  m__io->pushName("header_length");
  m_header_length = m__io->read_u4be();
  m__io->popName();
  m__io->pushName("format");
  m_format = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("qty_tracks");
  m_qty_tracks = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("division");
  m_division = m__io->read_s2be();
  m__io->popName();
  m__io->endChunk();
}

standard_midi_file_t::header_t::~header_t() {}

standard_midi_file_t::sysex_event_body_t::sysex_event_body_t(kaitai::kstream* p_io,
    standard_midi_file_t::track_event_t* p_parent, standard_midi_file_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("sysex");
  m__io->pushName("len");
  m_len = new vlq_base128_be_t(m__io);
  m__io->popName();
  m__io->pushName("data");
  m_data = m__io->read_bytes(len()->value());
  m__io->popName();
  m__io->endChunk();
}

standard_midi_file_t::sysex_event_body_t::~sysex_event_body_t() {
  delete m_len;
}

standard_midi_file_t::note_off_event_t::note_off_event_t(kaitai::kstream* p_io,
    standard_midi_file_t::track_event_t* p_parent, standard_midi_file_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("note_off");
  m__io->pushName("note");
  m_note = m__io->read_u1();
  m__io->popName();
  m__io->pushName("velocity");
  m_velocity = m__io->read_u1();
  m__io->popName();
  m__io->endChunk();
}

standard_midi_file_t::note_off_event_t::~note_off_event_t() {}

standard_midi_file_t::channel_pressure_event_t::channel_pressure_event_t(
    kaitai::kstream* p_io, standard_midi_file_t::track_event_t* p_parent,
    standard_midi_file_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("channel_pressure");
  m__io->pushName("pressure");
  m_pressure = m__io->read_u1();
  m__io->popName();
  m__io->endChunk();
}

standard_midi_file_t::channel_pressure_event_t::~channel_pressure_event_t() {}
