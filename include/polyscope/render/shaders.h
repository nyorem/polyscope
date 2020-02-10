#pragma once

#include "polyscope/render/engine.h"

namespace polyscope {
namespace render {

// == Texture draw shaders
extern const ShaderStageSpecification TEXTURE_DRAW_VERT_SHADER;
extern const ShaderStageSpecification SPHEREBG_DRAW_VERT_SHADER;
extern const ShaderStageSpecification PLAIN_TEXTURE_DRAW_FRAG_SHADER;
extern const ShaderStageSpecification DOT3_TEXTURE_DRAW_FRAG_SHADER;
extern const ShaderStageSpecification MAP3_TEXTURE_DRAW_FRAG_SHADER;
extern const ShaderStageSpecification SPHEREBG_DRAW_FRAG_SHADER;

// == Lighting shaders
extern const ShaderStageSpecification MAP_LIGHT_FRAG_SHADER;
extern const ShaderStageSpecification SPLIT_SPECULAR_PRECOMPUTE_FRAG_SHADER;

// == Histogram shaders
extern const ShaderStageSpecification HISTOGRAM_VERT_SHADER;
extern const ShaderStageSpecification HISTOGRAM_FRAG_SHADER;

// == Ground plane shaders
extern const ShaderStageSpecification GROUND_PLANE_VERT_SHADER;
extern const ShaderStageSpecification GROUND_PLANE_FRAG_SHADER;

// == Surface mesh shaders

extern const ShaderStageSpecification PLAIN_SURFACE_VERT_SHADER;
extern const ShaderStageSpecification PLAIN_SURFACE_FRAG_SHADER;
extern const ShaderStageSpecification SURFACE_WIREFRAME_VERT_SHADER;
extern const ShaderStageSpecification SURFACE_WIREFRAME_FRAG_SHADER;
extern const ShaderStageSpecification PICK_SURFACE_VERT_SHADER;
extern const ShaderStageSpecification PICK_SURFACE_FRAG_SHADER;

extern const ShaderStageSpecification VERTCOLOR3_SURFACE_VERT_SHADER;
extern const ShaderStageSpecification VERTCOLOR3_SURFACE_FRAG_SHADER;

extern const ShaderStageSpecification VERTCOLOR_SURFACE_VERT_SHADER;
extern const ShaderStageSpecification VERTCOLOR_SURFACE_FRAG_SHADER;
extern const ShaderStageSpecification HALFEDGECOLOR_SURFACE_VERT_SHADER;
extern const ShaderStageSpecification HALFEDGECOLOR_SURFACE_FRAG_SHADER;

extern const ShaderStageSpecification VERT_DIST_SURFACE_VERT_SHADER;
extern const ShaderStageSpecification VERT_DIST_SURFACE_FRAG_SHADER;
extern const ShaderStageSpecification PARAM_SURFACE_VERT_SHADER;
extern const ShaderStageSpecification PARAM_CHECKER_SURFACE_FRAG_SHADER;
extern const ShaderStageSpecification PARAM_GRID_SURFACE_FRAG_SHADER;
extern const ShaderStageSpecification PARAM_LOCAL_RAD_SURFACE_FRAG_SHADER;
extern const ShaderStageSpecification PARAM_LOCAL_CHECKER_SURFACE_FRAG_SHADER;

// == Vector shaders
extern const ShaderStageSpecification PASSTHRU_VECTOR_VERT_SHADER;
extern const ShaderStageSpecification VECTOR_GEOM_SHADER;
extern const ShaderStageSpecification VECTOR_FRAG_SHADER;

// == Ribbon shaders
extern const ShaderStageSpecification RIBBON_VERT_SHADER;
extern const ShaderStageSpecification RIBBON_GEOM_SHADER;
extern const ShaderStageSpecification RIBBON_FRAG_SHADER;


} // namespace render
} // namespace polyscope