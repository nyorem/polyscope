// Copyright 2017-2019, Nicholas Sharp and the Polyscope contributors. http://polyscope.run.

#include "polyscope/render/opengl/gl_shaders.h"

namespace polyscope {
namespace render {

// clang-format off

const ShaderStageSpecification SPHERE_VERT_SHADER = {

    ShaderStageType::Vertex,

    { // uniforms
        {"u_modelView", DataType::Matrix44Float},
		}, 

    // attributes
    {
        {"a_position", DataType::Vector3Float},
    },
		
    {}, // textures

    // source
    POLYSCOPE_GLSL(150,
        uniform mat4 u_modelView;
        in vec3 a_position;
					
        void main()
        {
            gl_Position = u_modelView * vec4(a_position,1.0);
        }
    )
};

const ShaderStageSpecification SPHERE_VALUE_VERT_SHADER = {
    
    ShaderStageType::Vertex,

    { // uniforms
        {"u_modelView", DataType::Matrix44Float},
		}, 

    // attributes
    {
        {"a_position", DataType::Vector3Float},
        {"a_value", DataType::Float},
    },
		
    {}, // textures

    // source
    POLYSCOPE_GLSL(150,
        uniform mat4 u_modelView;
        in vec3 a_position;
        in float a_value;
        out float value;

        void main()
        {
            gl_Position = u_modelView * vec4(a_position,1.0);
            value = a_value;
        }
    )
};


const ShaderStageSpecification SPHERE_COLOR_VERT_SHADER = {
    
    ShaderStageType::Vertex,

    // uniforms
    {
        {"u_modelView", DataType::Matrix44Float},
    }, 

    // attributes
    {
        {"a_position", DataType::Vector3Float},
        {"a_color", DataType::Vector3Float},
    },

		{}, // textures

    // source
    POLYSCOPE_GLSL(150,
        uniform mat4 u_modelView;
        in vec3 a_position;
        in vec3 a_color;
        out vec3 color;
        void main()
        {
            color = a_color;
            gl_Position = u_modelView * vec4(a_position,1.0);
        }
    )
};



const ShaderStageSpecification SPHERE_BILLBOARD_GEOM_SHADER = {

    ShaderStageType::Geometry,
    
    // uniforms
    {
        {"u_projMatrix", DataType::Matrix44Float},
        {"u_pointRadius", DataType::Float},
    }, 

    // attributes
    {
    },
		
    {}, // textures

    // source
    POLYSCOPE_GLSL(150,
        layout(points) in;
        layout(triangle_strip, max_vertices=14) out;
        uniform mat4 u_projMatrix;
        uniform float u_pointRadius;
				out vec3 sphereCenterView;

        void main()   {

						// Compute corners of cube
					  vec4 centerWorld = u_projMatrix * gl_in[0].gl_Position;
						vec4 dx = u_projMatrix * vec4(u_pointRadius, 0., 0., 0.);
						vec4 dy = u_projMatrix * vec4(0., u_pointRadius, 0., 0.);
						vec4 dz = u_projMatrix * vec4(0., 0., u_pointRadius, 0.);
						vec4 p1 = centerWorld - dx - dy - dz;
						vec4 p2 = centerWorld + dx - dy - dz;
						vec4 p3 = centerWorld - dx + dy - dz;
						vec4 p4 = centerWorld + dx + dy - dz;
						vec4 p5 = centerWorld - dx - dy + dz;
						vec4 p6 = centerWorld + dx - dy + dz;
						vec4 p7 = centerWorld - dx + dy + dz;
						vec4 p8 = centerWorld + dx + dy + dz;
						
						// Other data to emit		
						vec3 sphereCenterViewVal = gl_in[0].gl_Position.xyz / gl_in[0].gl_Position.w;
		
						// Emit the vertices as a triangle strip
						sphereCenterView = sphereCenterViewVal;	gl_Position = p7; EmitVertex(); 
						sphereCenterView = sphereCenterViewVal;	gl_Position = p8; EmitVertex(); 
						sphereCenterView = sphereCenterViewVal;	gl_Position = p5; EmitVertex(); 
						sphereCenterView = sphereCenterViewVal;	gl_Position = p6; EmitVertex(); 
						sphereCenterView = sphereCenterViewVal;	gl_Position = p2; EmitVertex(); 
						sphereCenterView = sphereCenterViewVal;	gl_Position = p8; EmitVertex(); 
						sphereCenterView = sphereCenterViewVal;	gl_Position = p4; EmitVertex(); 
						sphereCenterView = sphereCenterViewVal;	gl_Position = p7; EmitVertex(); 
						sphereCenterView = sphereCenterViewVal;	gl_Position = p3; EmitVertex(); 
						sphereCenterView = sphereCenterViewVal;	gl_Position = p5; EmitVertex(); 
						sphereCenterView = sphereCenterViewVal;	gl_Position = p1; EmitVertex(); 
						sphereCenterView = sphereCenterViewVal;	gl_Position = p2; EmitVertex(); 
						sphereCenterView = sphereCenterViewVal;	gl_Position = p3; EmitVertex(); 
						sphereCenterView = sphereCenterViewVal;	gl_Position = p4; EmitVertex();
    
            EndPrimitive();
        }
    )
};

const ShaderStageSpecification SPHERE_VALUE_BILLBOARD_GEOM_SHADER = {
    
    ShaderStageType::Geometry,
    
    // uniforms
    {
        {"u_projMatrix", DataType::Matrix44Float},
        {"u_pointRadius", DataType::Float},
    }, 

    // attributes
    {
    },
		
    {}, // textures

    // source
    POLYSCOPE_GLSL(150,
        layout(points) in;
        layout(triangle_strip, max_vertices=14) out;
        in float value[];
        uniform mat4 u_projMatrix;
        uniform float u_pointRadius;
        flat out float valueToFrag;
				out vec3 sphereCenterView;

        void main()   {

						// Compute corners of cube
					  vec4 centerWorld = u_projMatrix * gl_in[0].gl_Position;
						vec4 dx = u_projMatrix * vec4(u_pointRadius, 0., 0., 0.);
						vec4 dy = u_projMatrix * vec4(0., u_pointRadius, 0., 0.);
						vec4 dz = u_projMatrix * vec4(0., 0., u_pointRadius, 0.);
						vec4 p1 = centerWorld - dx - dy - dz;
						vec4 p2 = centerWorld + dx - dy - dz;
						vec4 p3 = centerWorld - dx + dy - dz;
						vec4 p4 = centerWorld + dx + dy - dz;
						vec4 p5 = centerWorld - dx - dy + dz;
						vec4 p6 = centerWorld + dx - dy + dz;
						vec4 p7 = centerWorld - dx + dy + dz;
						vec4 p8 = centerWorld + dx + dy + dz;
						
						// Other data to emit		
						vec3 sphereCenterViewVal = gl_in[0].gl_Position.xyz / gl_in[0].gl_Position.w;
						float valueOut = value[0];
		
						// Emit the vertices as a triangle strip
						valueToFrag = valueOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p7; EmitVertex(); 
						valueToFrag = valueOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p8; EmitVertex(); 
						valueToFrag = valueOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p5; EmitVertex(); 
						valueToFrag = valueOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p6; EmitVertex(); 
						valueToFrag = valueOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p2; EmitVertex(); 
						valueToFrag = valueOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p8; EmitVertex(); 
						valueToFrag = valueOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p4; EmitVertex(); 
						valueToFrag = valueOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p7; EmitVertex(); 
						valueToFrag = valueOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p3; EmitVertex(); 
						valueToFrag = valueOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p5; EmitVertex(); 
						valueToFrag = valueOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p1; EmitVertex(); 
						valueToFrag = valueOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p2; EmitVertex(); 
						valueToFrag = valueOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p3; EmitVertex(); 
						valueToFrag = valueOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p4; EmitVertex();
    
            EndPrimitive();

        }
    )
};

const ShaderStageSpecification SPHERE_COLOR_BILLBOARD_GEOM_SHADER = {
    
    ShaderStageType::Geometry,
    
    // uniforms
    {
        {"u_projMatrix", DataType::Matrix44Float},
        {"u_pointRadius", DataType::Float},
    }, 

    {}, // attributes
		
    {}, // textures

    // source
    POLYSCOPE_GLSL(150,
        layout(points) in;
        layout(triangle_strip, max_vertices=14) out;
        in vec3 color[];
        uniform mat4 u_projMatrix;
        uniform float u_pointRadius;
				out vec3 sphereCenterView;
        flat out vec3 colorToFrag;

        void main()   {
						
						// Compute corners of cube
					  vec4 centerWorld = u_projMatrix * gl_in[0].gl_Position;
						vec4 dx = u_projMatrix * vec4(u_pointRadius, 0., 0., 0.);
						vec4 dy = u_projMatrix * vec4(0., u_pointRadius, 0., 0.);
						vec4 dz = u_projMatrix * vec4(0., 0., u_pointRadius, 0.);
						vec4 p1 = centerWorld - dx - dy - dz;
						vec4 p2 = centerWorld + dx - dy - dz;
						vec4 p3 = centerWorld - dx + dy - dz;
						vec4 p4 = centerWorld + dx + dy - dz;
						vec4 p5 = centerWorld - dx - dy + dz;
						vec4 p6 = centerWorld + dx - dy + dz;
						vec4 p7 = centerWorld - dx + dy + dz;
						vec4 p8 = centerWorld + dx + dy + dz;
						
						// Other data to emit		
						vec3 sphereCenterViewVal = gl_in[0].gl_Position.xyz / gl_in[0].gl_Position.w;
						vec3 colorOut = color[0];
		
						// Emit the vertices as a triangle strip
						colorToFrag = colorOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p7; EmitVertex(); 
						colorToFrag = colorOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p8; EmitVertex(); 
						colorToFrag = colorOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p5; EmitVertex(); 
						colorToFrag = colorOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p6; EmitVertex(); 
						colorToFrag = colorOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p2; EmitVertex(); 
						colorToFrag = colorOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p8; EmitVertex(); 
						colorToFrag = colorOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p4; EmitVertex(); 
						colorToFrag = colorOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p7; EmitVertex(); 
						colorToFrag = colorOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p3; EmitVertex(); 
						colorToFrag = colorOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p5; EmitVertex(); 
						colorToFrag = colorOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p1; EmitVertex(); 
						colorToFrag = colorOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p2; EmitVertex(); 
						colorToFrag = colorOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p3; EmitVertex(); 
						colorToFrag = colorOut; sphereCenterView = sphereCenterViewVal;	gl_Position = p4; EmitVertex();
    
            EndPrimitive();

        }
    )
};




const ShaderStageSpecification SPHERE_BILLBOARD_FRAG_SHADER = {
    
    ShaderStageType::Fragment,
    
    { // uniforms
        {"u_projMatrix", DataType::Matrix44Float},
        {"u_invProjMatrix", DataType::Matrix44Float},
        {"u_viewport", DataType::Vector4Float},
        {"u_pointRadius", DataType::Float},
        {"u_baseColor", DataType::Vector3Float},
    }, 

    { }, // attributes
    
    // textures 
    {
        {"t_mat_r", 2},
        {"t_mat_g", 2},
        {"t_mat_b", 2},
        {"t_mat_k", 2},
    },
    
    // source
    POLYSCOPE_GLSL(330 core,
        uniform mat4 u_projMatrix;
        uniform mat4 u_invProjMatrix;
        uniform vec4 u_viewport;
        uniform float u_pointRadius;
        uniform vec3 u_baseColor;
        in vec3 sphereCenterView;
        uniform sampler2D t_mat_r;
        uniform sampler2D t_mat_g;
        uniform sampler2D t_mat_b;
        uniform sampler2D t_mat_k;
        layout(location = 0) out vec4 outputF;

        vec3 lightSurfaceMat(vec3 normal, vec3 color, sampler2D t_mat_r, sampler2D t_mat_g, sampler2D t_mat_b, sampler2D t_mat_k);
				vec3 fragmentViewPosition(vec4 viewport, vec2 depthRange, mat4 invProjMat, vec4 fragCoord);
				void raySphereIntersection(vec3 rayStart, vec3 rayDir, vec3 sphereCenter, float sphereRad, out float tHit, out vec3 pHit, out vec3 nHit);
				float fragDepthFromView(mat4 projMat, vec2 depthRange, vec3 viewPoint);


        void main()
        {
					 // Build a ray corresponding to this fragment
					 vec2 depthRange = vec2(gl_DepthRange.near, gl_DepthRange.far);
					 vec3 viewRay = fragmentViewPosition(u_viewport, depthRange, u_invProjMatrix, gl_FragCoord);

					 // Raycast to the sphere	
					 float tHit;
					 vec3 pHit;
					 vec3 nHit;
					 raySphereIntersection(vec3(0., 0., 0), viewRay, sphereCenterView, u_pointRadius, tHit, pHit, nHit);
					 if(tHit < 0.) {
							discard;
					 }

           // Lighting
           outputF = vec4(lightSurfaceMat(nHit, u_baseColor, t_mat_r, t_mat_g, t_mat_b, t_mat_k), 1.);

           // Set depth (expensive!)
					 float depth = fragDepthFromView(u_projMatrix, depthRange, pHit);
					 gl_FragDepth = depth;
        }
    )
};

const ShaderStageSpecification SPHERE_VALUE_BILLBOARD_FRAG_SHADER = {
    
    ShaderStageType::Fragment,
    
    { // uniforms
        {"u_projMatrix", DataType::Matrix44Float},
        {"u_invProjMatrix", DataType::Matrix44Float},
        {"u_viewport", DataType::Vector4Float},
        {"u_pointRadius", DataType::Float},
        {"u_rangeLow", DataType::Float},
        {"u_rangeHigh", DataType::Float},
    }, 

    { }, // attributes
    
    // textures 
    {
        {"t_mat_r", 2},
        {"t_mat_g", 2},
        {"t_mat_b", 2},
        {"t_mat_k", 2},
        {"t_colormap", 1},
    },
    
    // source
    POLYSCOPE_GLSL(330 core,
        uniform mat4 u_projMatrix;
        uniform mat4 u_invProjMatrix;
        uniform vec4 u_viewport;
        uniform float u_pointRadius;
        uniform float u_rangeLow;
        uniform float u_rangeHigh;
        flat in float valueToFrag;
        in vec3 sphereCenterView;
        uniform sampler2D t_mat_r;
        uniform sampler2D t_mat_g;
        uniform sampler2D t_mat_b;
        uniform sampler2D t_mat_k;
        uniform sampler1D t_colormap;
        layout(location = 0) out vec4 outputF;

        vec3 lightSurfaceMat(vec3 normal, vec3 color, sampler2D t_mat_r, sampler2D t_mat_g, sampler2D t_mat_b, sampler2D t_mat_k);
				vec3 fragmentViewPosition(vec4 viewport, vec2 depthRange, mat4 invProjMat, vec4 fragCoord);
				void raySphereIntersection(vec3 rayStart, vec3 rayDir, vec3 sphereCenter, float sphereRad, out float tHit, out vec3 pHit, out vec3 nHit);
				float fragDepthFromView(mat4 projMat, vec2 depthRange, vec3 viewPoint);

        vec3 surfaceColor() {
          float t = (valueToFrag - u_rangeLow) / (u_rangeHigh - u_rangeLow);
          t = clamp(t, 0.f, 1.f);
          return texture(t_colormap, t).rgb;
        }

        void main()
        {
					 // Build a ray corresponding to this fragment
					 vec2 depthRange = vec2(gl_DepthRange.near, gl_DepthRange.far);
					 vec3 viewRay = fragmentViewPosition(u_viewport, depthRange, u_invProjMatrix, gl_FragCoord);

					 // Raycast to the sphere	
					 float tHit;
					 vec3 pHit;
					 vec3 nHit;
					 raySphereIntersection(vec3(0., 0., 0), viewRay, sphereCenterView, u_pointRadius, tHit, pHit, nHit);
					 if(tHit < 0.) {
							discard;
					 }

           // Lighting
           outputF = vec4(lightSurfaceMat(nHit, surfaceColor(), t_mat_r, t_mat_g, t_mat_b, t_mat_k), 1.);

           // Set depth (expensive!)
					 float depth = fragDepthFromView(u_projMatrix, depthRange, pHit);
					 gl_FragDepth = depth;
        }
    )
};

const ShaderStageSpecification SPHERE_COLOR_BILLBOARD_FRAG_SHADER = {
    
    ShaderStageType::Fragment,
    
    { // uniforms
        {"u_projMatrix", DataType::Matrix44Float},
        {"u_invProjMatrix", DataType::Matrix44Float},
        {"u_viewport", DataType::Vector4Float},
        {"u_pointRadius", DataType::Float},
    }, 

    { }, // attributes
    
    // textures 
    {
        {"t_mat_r", 2},
        {"t_mat_g", 2},
        {"t_mat_b", 2},
        {"t_mat_k", 2},
    },
    
    // source
    POLYSCOPE_GLSL(330 core,
        uniform mat4 u_projMatrix;
        uniform mat4 u_invProjMatrix;
        uniform vec4 u_viewport;
        uniform float u_pointRadius;
        in vec3 sphereCenterView;
        flat in vec3 colorToFrag;
        uniform sampler2D t_mat_r;
        uniform sampler2D t_mat_g;
        uniform sampler2D t_mat_b;
        uniform sampler2D t_mat_k;
        layout(location = 0) out vec4 outputF;

        vec3 lightSurfaceMat(vec3 normal, vec3 color, sampler2D t_mat_r, sampler2D t_mat_g, sampler2D t_mat_b, sampler2D t_mat_k);
				vec3 fragmentViewPosition(vec4 viewport, vec2 depthRange, mat4 invProjMat, vec4 fragCoord);
				void raySphereIntersection(vec3 rayStart, vec3 rayDir, vec3 sphereCenter, float sphereRad, out float tHit, out vec3 pHit, out vec3 nHit);
				float fragDepthFromView(mat4 projMat, vec2 depthRange, vec3 viewPoint);


        void main()
        {
					 // Build a ray corresponding to this fragment
					 vec2 depthRange = vec2(gl_DepthRange.near, gl_DepthRange.far);
					 vec3 viewRay = fragmentViewPosition(u_viewport, depthRange, u_invProjMatrix, gl_FragCoord);

					 // Raycast to the sphere	
					 float tHit;
					 vec3 pHit;
					 vec3 nHit;
					 raySphereIntersection(vec3(0., 0., 0), viewRay, sphereCenterView, u_pointRadius, tHit, pHit, nHit);
					 if(tHit < 0.) {
							discard;
					 }

           // Lighting
           outputF = vec4(lightSurfaceMat(nHit, colorToFrag, t_mat_r, t_mat_g, t_mat_b, t_mat_k), 1.);

           // Set depth (expensive!)
					 float depth = fragDepthFromView(u_projMatrix, depthRange, pHit);
					 gl_FragDepth = depth;
        }
    )
};



const ShaderStageSpecification SPHERE_COLOR_PLAIN_BILLBOARD_FRAG_SHADER = {
    
    ShaderStageType::Fragment,
    
    { // uniforms
        {"u_projMatrix", DataType::Matrix44Float},
        {"u_invProjMatrix", DataType::Matrix44Float},
        {"u_viewport", DataType::Vector4Float},
        {"u_pointRadius", DataType::Float},
    }, 

    { }, // attributes
    
    // textures 
    { },
    
    // source
    POLYSCOPE_GLSL(330 core,
        uniform mat4 u_projMatrix;
        uniform mat4 u_invProjMatrix;
        uniform vec4 u_viewport;
        uniform float u_pointRadius;
        in vec3 sphereCenterView;
        flat in vec3 colorToFrag;
        layout(location = 0) out vec4 outputF;

				vec3 fragmentViewPosition(vec4 viewport, vec2 depthRange, mat4 invProjMat, vec4 fragCoord);
				void raySphereIntersection(vec3 rayStart, vec3 rayDir, vec3 sphereCenter, float sphereRad, out float tHit, out vec3 pHit, out vec3 nHit);
				float fragDepthFromView(mat4 projMat, vec2 depthRange, vec3 viewPoint);


        void main()
        {
					 // Build a ray corresponding to this fragment
					 vec2 depthRange = vec2(gl_DepthRange.near, gl_DepthRange.far);
					 vec3 viewRay = fragmentViewPosition(u_viewport, depthRange, u_invProjMatrix, gl_FragCoord);

					 // Raycast to the sphere	
					 float tHit;
					 vec3 pHit;
					 vec3 nHit;
					 raySphereIntersection(vec3(0., 0., 0), viewRay, sphereCenterView, u_pointRadius, tHit, pHit, nHit);
					 if(tHit < 0.) {
							discard;
					 }

           // Lighting
           outputF = vec4(colorToFrag, 1.);

           // Set depth (expensive!)
					 float depth = fragDepthFromView(u_projMatrix, depthRange, pHit);
					 gl_FragDepth = depth;
        }
    )
};


// clang-format on

} // namespace render
} // namespace polyscope