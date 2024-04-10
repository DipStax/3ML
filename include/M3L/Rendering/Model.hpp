#pragma once

#include <istream>
#include <map>
#include <string>
#include <vector>
#include <memory>

#include "M3L/Maths/Point3.hpp"
#include "M3L/Rendering/IDrawable3D.hpp"
#include "M3L/Rendering/Vertex.hpp"

namespace m3l
{
    class M3L_API Model : public IDrawable3D
    {
        public:
            Model();
            ~Model() = default;

            void load(const std::string &_path);

            void setTexture(Texture _txtr);

        protected:
            void draw(RenderTarget3D &_target, const Texture *_txtr) const;

        private:
            using FnParsing = void (Model::*)(const std::string &);

            static void Init();
            static inline std::map<std::string, FnParsing> m_fnParsing;

            // https://en.wikipedia.org/wiki/Wavefront_.obj_file
            void fnLoadF(const std::string &_file);
            void fnLoadV(const std::string &_file);
            void fnLoadVn(const std::string &_file);
            void fnLoadVp(const std::string &_file);
            void fnLoadVt(const std::string &_file);
            void fnComment(const std::string &_file);

        private:
            std::vector<m3l::Vector3<float>> m_v;
            std::vector<m3l::Vector3<float>> m_vn;
            std::vector<m3l::Vector3<float>> m_vt;
            std::vector<m3l::Vector3<float>> m_vp;
            std::vector<std::vector<Vertex3D>> m_f;

            Texture m_txtr;
    };
}