#ifndef STL_H_
#define STL_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <kaitai/kaitaistruct.h>
#include <kaitai/kaitaistream.h>

#include <stdint.h>
#include <vector>
#include <sstream>

class stl_t : public kaitai::kstruct {

public:
    class triangle_t;
    class vec3d_t;

    stl_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent = 0, stl_t* p_root = 0);
    veles::dbif::ObjectHandle veles_obj;
    ~stl_t();

    class triangle_t : public kaitai::kstruct {

    public:

        triangle_t(kaitai::kstream* p_io, stl_t* p_parent = 0, stl_t* p_root = 0);
        veles::dbif::ObjectHandle veles_obj;
        ~triangle_t();

    private:
        vec3d_t* m_normal;
        std::vector<vec3d_t*>* m_vertices;
        uint16_t m_abyte_cnt;
        stl_t* m__root;
        stl_t* m__parent;

    public:
        vec3d_t* normal() const { return m_normal; }
        std::vector<vec3d_t*>* vertices() const { return m_vertices; }
        uint16_t abyte_cnt() const { return m_abyte_cnt; }
        stl_t* _root() const { return m__root; }
        stl_t* _parent() const { return m__parent; }
    };

    class vec3d_t : public kaitai::kstruct {

    public:

        vec3d_t(kaitai::kstream* p_io, stl_t::triangle_t* p_parent = 0, stl_t* p_root = 0);
        veles::dbif::ObjectHandle veles_obj;
        ~vec3d_t();

    private:
        float m_x;
        float m_y;
        float m_z;
        stl_t* m__root;
        stl_t::triangle_t* m__parent;

    public:
        float x() const { return m_x; }
        float y() const { return m_y; }
        float z() const { return m_z; }
        stl_t* _root() const { return m__root; }
        stl_t::triangle_t* _parent() const { return m__parent; }
    };

private:
    std::string m_header;
    uint32_t m_num_triangles;
    std::vector<triangle_t*>* m_triangles;
    stl_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::string header() const { return m_header; }
    uint32_t num_triangles() const { return m_num_triangles; }
    std::vector<triangle_t*>* triangles() const { return m_triangles; }
    stl_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // STL_H_
