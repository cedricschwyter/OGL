/**
    Defines the BaseVertex struct

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         BaseVertex.hpp
    @brief        Definition of the BaseVertex struct
*/
#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include <functional>

namespace ogl {

    /**
        Defines a templated hash-function to combine the fields of structs for a decent quality hash function

        @param      hash_       The previously computed hash
        @param      field_      The field to add to the hash
    */
    template < class T >
    void hashField(std::size_t& hash_, const T& field_) {

        std::hash< T > hashFunc;
        hash_ ^= hashFunc(field_) + 0x9e3779b9 + (hash_ << 6) + (hash_ >> 2);

    }

}

struct BaseVertex {

    alignas(16) glm::vec3 pos;
    alignas(16) glm::vec3 nor;
    alignas(16) glm::vec2 tex;
    alignas(16) glm::vec3 tan;
    alignas(16) glm::vec3 bit;

    /**
        Overload comparison-operator
    */
    bool operator==(const BaseVertex& otherVertex) const {

        return pos == otherVertex.pos && nor == otherVertex.nor && tex == otherVertex.tex && tan == otherVertex.tan && bit == otherVertex.bit;

    }

};

/**
    Expand standard namespace
*/
namespace std {

    /**
        Hash-function for vertex !!!This is some high level C++!!! (following recommended approach for hash-functions on cppreference.com's std::hash page)
    */
    template<  > struct hash< BaseVertex > {

        size_t operator()(BaseVertex const& vertex) const noexcept {

            std::size_t result = 0;

            ogl::hashField(result, vertex.pos);
            ogl::hashField(result, vertex.nor);
            ogl::hashField(result, vertex.tex);
            ogl::hashField(result, vertex.tan);
            ogl::hashField(result, vertex.bit);

            return result;

        }

    };

}