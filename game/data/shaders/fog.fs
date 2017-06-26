
varying vec3 v_position;
varying vec3 v_world_position;
varying vec3 v_normal;
varying vec2 v_uv;
varying vec4 v_color;

uniform sampler2D u_texture;
uniform vec3 u_poscam;

void main()
{
    vec4 color =  0.5 * texture2D(u_texture, v_uv);
    vec4 fog_color = vec4(0.6,0.7,0.7);

    float dist = length(v_world_position - u_poscam);
    float c = clamp(pow(dist/15000.0 , 0.5), 0.0,1.0);

    color = mix(color,fog_color,factor);
	gl_FragColor = color;
}
