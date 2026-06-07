// This is a generated file! Please edit source .ksy file and use
// kaitai-struct-compiler to rebuild

#include "kaitai/stl.h"

stl_t::stl_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent,
             stl_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = this;
  m__io->popName();
  veles_obj = m__io->startChunk("stl");
  m__io->pushName("header");
  m_header = m__io->read_bytes(80);
  m__io->popName();
  m__io->pushName("num_triangles");
  m_num_triangles = m__io->read_u4le();
  m__io->popName();
  int l_triangles = num_triangles();
  m_triangles = new std::vector<triangle_t*>();
  m_triangles->reserve(l_triangles);
  for (int i = 0; i < l_triangles; i++) {
    m__io->pushName("triangles");
    m_triangles->push_back(new triangle_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->endChunk();
}

stl_t::~stl_t() {
  for (auto it = m_triangles->begin(); it != m_triangles->end(); ++it)
    delete *it;
  delete m_triangles;
}

stl_t::triangle_t::triangle_t(kaitai::kstream* p_io, stl_t* p_parent,
                               stl_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("triangle");
  m__io->pushName("normal");
  m_normal = new vec3d_t(m__io, this, m__root);
  m__io->popName();
  int l_vertices = 3;
  m_vertices = new std::vector<vec3d_t*>();
  m_vertices->reserve(l_vertices);
  for (int i = 0; i < l_vertices; i++) {
    m__io->pushName("vertices");
    m_vertices->push_back(new vec3d_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->pushName("abyte_cnt");
  m_abyte_cnt = m__io->read_u2le();
  m__io->popName();
  m__io->endChunk();
}

stl_t::triangle_t::~triangle_t() {
  delete m_normal;
  for (auto it = m_vertices->begin(); it != m_vertices->end(); ++it)
    delete *it;
  delete m_vertices;
}

stl_t::vec3d_t::vec3d_t(kaitai::kstream* p_io, stl_t::triangle_t* p_parent,
                         stl_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("vec3d");
  m__io->pushName("x");
  m_x = m__io->read_f4le();
  m__io->popName();
  m__io->pushName("y");
  m_y = m__io->read_f4le();
  m__io->popName();
  m__io->pushName("z");
  m_z = m__io->read_f4le();
  m__io->popName();
  m__io->endChunk();
}

stl_t::vec3d_t::~vec3d_t() {}
