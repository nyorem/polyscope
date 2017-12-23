#pragma once


// NOTE: You probably don't want to include this directly... see shaders.h

static const VertShader PASSTHRU_VECTOR_VERT_SHADER = {
    // uniforms
    {
    }, 

    // attributes
    {
        {"a_position", GLData::Vector3Float},
        {"a_vector", GLData::Vector3Float},
    },

    // source
    GLSL(150,
        in vec3 a_position;
        in vec3 a_vector;

        out vec3 vector;

        void main()
        {
            gl_Position = vec4(a_position,1.0);
            vector = a_vector;
        }
    )
};



static const GeomShader VECTOR_GEOM_SHADER = {
    
    // uniforms
    {
        {"u_viewMatrix", GLData::Matrix44Float},
        {"u_projMatrix", GLData::Matrix44Float},
        {"u_lengthMult", GLData::Float},
        {"u_radius", GLData::Float},
    }, 

    // attributes
    {
    },

    // source
    GLSL(150,
        layout(points) in;
        layout(triangle_strip, max_vertices=40) out;
        in vec3 vector[];
        uniform mat4 u_viewMatrix;
        uniform mat4 u_projMatrix;
        uniform float u_lengthMult;
        uniform float u_radius;
        out vec3 worldPosToFrag;
        out vec3 worldNormalToFrag;

        void main()   {
            mat4 PV = u_projMatrix * u_viewMatrix;

            const int nTheta = 8;
            const float PI = 3.14159;
            const float delTheta = 2.*PI / nTheta;            

            // Points along the central axis
            vec3 rootP = gl_in[0].gl_Position.xyz;
            vec3 capP = rootP + .8 * vector[0] * u_lengthMult;
            vec3 tipP = rootP + vector[0] * u_lengthMult;

            // Orthogonal basis
            const vec3 arbVec = vec3(0.129873, -.70892, .58972);
            vec3 radX = normalize(cross(vector[0], arbVec));
            vec3 radY = normalize(cross(vector[0], radX));

            // Generate each panel around the vector
            for(int iTheta = 0; iTheta < nTheta; iTheta++) {

                float theta0 = delTheta * iTheta;
                float theta1 = delTheta * (iTheta+1);

                float x0 = cos(theta0);
                float y0 = sin(theta0);
                float x1 = cos(theta1);
                float y1 = sin(theta1);

                vec3 norm0 = (x0 * radX + y0 * radY);
                vec3 norm1 = (x1 * radX + y1 * radY);

                { // Lower left
                    vec4 worldPos = vec4(rootP + norm0 * u_radius, 1.);
                    gl_Position = PV * worldPos;
                    worldPosToFrag = worldPos.xyz;
                    worldNormalToFrag = norm0;
                    EmitVertex();
                }
                
                { // Lower right
                    vec4 worldPos = vec4(rootP + norm1 * u_radius, 1.);
                    gl_Position = PV * worldPos;
                    worldPosToFrag = worldPos.xyz;
                    worldNormalToFrag = norm1;
                    EmitVertex();
                }
                
                { // Upper left
                    vec4 worldPos = vec4(capP + norm0 * u_radius, 1.);
                    gl_Position = PV * worldPos;
                    worldPosToFrag = worldPos.xyz;
                    worldNormalToFrag = norm0;
                    EmitVertex();
                }
                
                { // Upper right
                    vec4 worldPos = vec4(capP + norm1 * u_radius, 1.);
                    gl_Position = PV * worldPos;
                    worldPosToFrag = worldPos.xyz;
                    worldNormalToFrag = norm1;
                    EmitVertex();
                }
                
                { // Tip
                    vec3 tipNormal = normalize(norm0 + norm1);
                    vec4 worldPos = vec4(tipP, 1.);
                    gl_Position = PV * worldPos;
                    worldPosToFrag = worldPos.xyz;
                    worldNormalToFrag = tipNormal;
                    EmitVertex();
                }
        
                EndPrimitive();

            }

        }
    )
};



static const FragShader SHINY_VECTOR_FRAG_SHADER = {
    
    // uniforms
    {
        {"u_eye", GLData::Vector3Float},
        {"u_lightCenter", GLData::Vector3Float},
        {"u_lightDist", GLData::Float},
        {"u_color", GLData::Vector3Float},
    }, 

    // attributes
    {
    },
    
    // textures 
    {
    },
    
    // output location
    "outputF",
 
    // source
    GLSL(150,
        uniform vec3 u_eye;
        uniform vec3 u_lightCenter;
        uniform float u_lightDist;
        uniform vec3 u_color;
        in vec3 worldPosToFrag;
        in vec3 worldNormalToFrag;
        out vec4 outputF;

        // Forward declarations of methods from <shaders/common.h>
        // vec4 lightSurface( vec3 position, vec3 normal, vec3 color, vec3 light, vec3 eye );
        vec4 lightSurface( vec3 position, vec3 normal, vec3 color, vec3 lightC, float lightD, vec3 eye );

        void main()
        {
           outputF = lightSurface(worldPosToFrag, worldNormalToFrag, u_color, u_lightCenter, u_lightDist, u_eye);
        }
    )
};

